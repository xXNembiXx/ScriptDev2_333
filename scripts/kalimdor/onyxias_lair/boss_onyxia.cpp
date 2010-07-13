/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Onyxia
SD%Complete: 65
SDComment: Phase 3 need additianal code. Phase 2 requires entries in spell_target_position with specific locations. See bottom of file.
SDCategory: Onyxia's Lair
EndScriptData */

#include "precompiled.h"

enum
{
    SAY_AGGRO                   = -1249000,
    SAY_KILL                    = -1249001,
    SAY_PHASE_2_TRANS           = -1249002,
    SAY_PHASE_3_TRANS           = -1249003,
    EMOTE_BREATH                = -1249004,

    SPELL_WINGBUFFET            = 18500,
    H_SPELL_WINGBUFFET          = 69293,
    SPELL_FLAMEBREATH           = 18435,
    H_SPELL_FLAMEBREATH         = 68970,
    SPELL_CLEAVE                = 68868,
    SPELL_TAILSWEEP             = 68867,
    H_SPELL_TAILSWEEP           = 69286,
    SPELL_KNOCK_AWAY            = 19633,
    SPELL_FIREBALL              = 18392,
    H_SPELL_FIREBALL            = 68926,
    SPELL_ERRUPTION             = 17731,                    // does not work                
    H_SPELL_ERRUPTION           = 69294,                    // does not work

    //Not much choise about these. We have to make own defintion on the direction/start-end point
    //SPELL_BREATH_NORTH_TO_SOUTH = 17086,                  // 20x in "array"
    //SPELL_BREATH_SOUTH_TO_NORTH = 18351,                  // 11x in "array"

    SPELL_BREATH_EAST_TO_WEST   = 18576,                    // 7x in "array"
    SPELL_BREATH_WEST_TO_EAST   = 18609,                    // 7x in "array"

    SPELL_BREATH_SE_TO_NW       = 18564,                    // 12x in "array"
    SPELL_BREATH_NW_TO_SE       = 18584,                    // 12x in "array"
    SPELL_BREATH_SW_TO_NE       = 18596,                    // 12x in "array"
    SPELL_BREATH_NE_TO_SW       = 18617,                    // 12x in "array"

    //SPELL_BREATH                = 21131,                  // 8x in "array", different initial cast than the other arrays

    SPELL_BELLOWINGROAR         = 18431,
    SPELL_HEATED_GROUND         = 22191,                    // make server crash

    SPELL_SUMMONWHELP           = 17646,
    SPELL_SUMMONGUARD           = 68968,
    NPC_WHELP                   = 11262,
    NPC_GUARD                   = 36561,

    PHASE_START                 = 1,
    PHASE_BREATH                = 2,
    PHASE_END                   = 3
};

struct sOnyxMove
{
    uint32 uiLocId;
    uint32 uiLocIdEnd;
    uint32 uiSpellId;
    float fX, fY, fZ;
};

static sOnyxMove aMoveData[]=
{
    {0, 1, SPELL_BREATH_WEST_TO_EAST,   -33.5561f, -182.682f, -60.9457f},//west
    {1, 0, SPELL_BREATH_EAST_TO_WEST,   -31.4963f, -250.123f, -60.1278f},//east
    {2, 4, SPELL_BREATH_NW_TO_SE,         6.8951f, -180.246f, -60.896f},//north-west
    {3, 5, SPELL_BREATH_NE_TO_SW,        10.2191f, -247.912f, -60.896f},//north-east
    {4, 2, SPELL_BREATH_SE_TO_NW,       -63.5156f, -240.096f, -60.477f},//south-east
    {5, 3, SPELL_BREATH_SW_TO_NE,       -58.2509f, -189.020f, -60.790f},//south-west
    //{6, 7, SPELL_BREATH_SOUTH_TO_NORTH, -65.8444f, -213.809f, -60.2985f},//south
    //{7, 6, SPELL_BREATH_NORTH_TO_SOUTH,  22.8763f, -217.152f, -60.0548f},//north
};

static float SpawnLocs[4][3]=
{
    {-30.127f, -254.463f, -89.440f}, //whelps
    {-30.817f, -177.106f, -89.258f}, //whelps
    {-126.57f, -214.609f, -71.446f}, //guardians
    {-22.347f, -214.571f, -89.104f}  //Onyxia
};

struct MANGOS_DLL_DECL boss_onyxiaAI : public ScriptedAI
{
    boss_onyxiaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Regular = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    bool Regular;
    uint32 m_uiEvadeCheckCooldown;
    uint32 m_uiPhase;

    uint32 m_uiFlameBreathTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiTailSweepTimer;
    uint32 m_uiWingBuffetTimer;

    uint32 m_uiMovePoint;
    uint32 m_uiMovementTimer;
    sOnyxMove* m_pPointData;

    uint32 m_uiEngulfingFlamesTimer;
    uint32 m_uiSummonWhelpsTimer;
    uint32 m_uiBellowingRoarTimer;
    uint32 m_uiWhelpTimer;
    uint32 SummonGuardTimer;

    uint8 m_uiSummonCount;
    uint8 m_uiMaxWhelps;
    bool m_bIsSummoningWhelps;

    void Reset()
    {
        if (!IsCombatMovement())
            SetCombatMovement(true);

        m_uiEvadeCheckCooldown = 2000;
        m_uiPhase = PHASE_START;

        m_uiFlameBreathTimer = urand(10000, 20000);
        m_uiTailSweepTimer = urand(15000, 20000);
        m_uiCleaveTimer = urand(2000, 5000);
        m_uiWingBuffetTimer = urand(10000, 20000);

        m_uiMovePoint = urand(0, 5);
        m_uiMovementTimer = 20000;
        m_pPointData = GetMoveData();

        m_uiEngulfingFlamesTimer = 15000;
        m_uiSummonWhelpsTimer = 15000;
        m_uiBellowingRoarTimer = 30000;
        m_uiWhelpTimer = 1000;
        SummonGuardTimer = 35000;

        m_uiSummonCount = 0;
        m_uiMaxWhelps = Regular ? 20 : 40;
        m_bIsSummoningWhelps = false;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->SetInCombatWithZone();
    }

    void JustSummoned(Creature *pSummoned)
    {
        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            pSummoned->AI()->AttackStart(pTarget);

        ++m_uiSummonCount;
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void SpellHit(Unit *pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_BREATH_EAST_TO_WEST ||
            pSpell->Id == SPELL_BREATH_WEST_TO_EAST ||
            pSpell->Id == SPELL_BREATH_SE_TO_NW ||
            pSpell->Id == SPELL_BREATH_NW_TO_SE ||
            pSpell->Id == SPELL_BREATH_SW_TO_NE ||
            pSpell->Id == SPELL_BREATH_NE_TO_SW)
        {
            if (m_pPointData)
            {
                m_creature->MonsterMove(m_pPointData->fX, m_pPointData->fY, m_pPointData->fZ, 1);
            }
        }
    }

    sOnyxMove* GetMoveData()
    {
        uint32 uiMaxCount = sizeof(aMoveData)/sizeof(sOnyxMove);

        for (uint32 i = 0; i < uiMaxCount; ++i)
        {
            if (aMoveData[i].uiLocId == m_uiMovePoint)
                return &aMoveData[i];
        }

        return NULL;
    }

    void SetNextRandomPoint()
    {
        uint32 uiMaxCount = sizeof(aMoveData)/sizeof(sOnyxMove);

        uint32 iTemp = urand(0, uiMaxCount-1);

        if (iTemp >= m_uiMovePoint)
            ++iTemp;

        m_uiMovePoint = iTemp;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiEvadeCheckCooldown < uiDiff)
        {
            if (m_creature->GetDistance2d(-22.346f, -214.57f) > 100.0f)
            {
                EnterEvadeMode();
                m_uiPhase = PHASE_START;
            }
            m_uiEvadeCheckCooldown = 2000;
        }
        else
            m_uiEvadeCheckCooldown -= uiDiff;

        if (m_uiPhase == PHASE_START || m_uiPhase == PHASE_END)
        {
            if (m_uiFlameBreathTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), Regular ? SPELL_FLAMEBREATH : H_SPELL_FLAMEBREATH);
                m_uiFlameBreathTimer = urand(10000, 20000);
            }
            else
                m_uiFlameBreathTimer -= uiDiff;

            if (m_uiTailSweepTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, Regular ? SPELL_TAILSWEEP : H_SPELL_TAILSWEEP);
                m_uiTailSweepTimer = urand(15000, 20000);
            }
            else
                m_uiTailSweepTimer -= uiDiff;

            if (m_uiCleaveTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
                m_uiCleaveTimer = urand(2000, 5000);
            }
            else
                m_uiCleaveTimer -= uiDiff;

            if (m_uiWingBuffetTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), Regular ? SPELL_WINGBUFFET : H_SPELL_WINGBUFFET);
                m_uiWingBuffetTimer = urand(15000, 30000);
            }
            else
                m_uiWingBuffetTimer -= uiDiff;

            if (m_uiPhase == PHASE_END)
            {
                if (m_uiBellowingRoarTimer < uiDiff)
                {
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_BELLOWINGROAR);
                    m_uiBellowingRoarTimer = 30000;
                }
                else
                    m_uiBellowingRoarTimer -= uiDiff;
            }
            else
            {
                if (m_creature->GetHealthPercent() < 65.0f)
                {
					// make boss fly
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);

                    m_uiPhase = PHASE_BREATH;

                    SetCombatMovement(false);

                    m_creature->GetMotionMaster()->Clear(false);
                    m_creature->GetMotionMaster()->MoveIdle();

                    DoScriptText(SAY_PHASE_2_TRANS, m_creature);

                    if (m_pPointData)
                        m_creature->GetMotionMaster()->MovePoint(m_pPointData->uiLocId, m_pPointData->fX, m_pPointData->fY, m_pPointData->fZ);

                    SetNextRandomPoint();
                    return;
                }
            }

            DoMeleeAttackIfReady();
        }
        else
        {
            if (m_creature->GetHealthPercent() < 40.0f)
            {
				// make boss land
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);

                m_uiPhase = PHASE_END;
                DoScriptText(SAY_PHASE_3_TRANS, m_creature);

                SetCombatMovement(true);
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());

                return;
            }

            if (m_uiMovementTimer < uiDiff)
            {
                m_pPointData = GetMoveData();

                SetNextRandomPoint();

                m_uiMovementTimer = 25000;

                if (!m_pPointData)
                    return;

                if (m_uiMovePoint == m_pPointData->uiLocIdEnd)
                {
                    if (m_creature->IsNonMeleeSpellCasted(false))
                        m_creature->InterruptNonMeleeSpells(false);

                    DoScriptText(EMOTE_BREATH, m_creature);
                    DoCastSpellIfCan(m_creature, m_pPointData->uiSpellId);
                }
                else
                {
                    m_creature->GetMotionMaster()->MovePoint(m_pPointData->uiLocId, m_pPointData->fX, m_pPointData->fY, m_pPointData->fZ);
                }
            }
            else
                m_uiMovementTimer -= uiDiff;

            if (m_uiEngulfingFlamesTimer < uiDiff)
            {
                if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
                {
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCastSpellIfCan(pTarget, SPELL_FIREBALL);

                    m_uiEngulfingFlamesTimer = 8000;
                }
            }
            else
                m_uiEngulfingFlamesTimer -= uiDiff;           //engulfingflames is supposed to be activated by a fireball but haven't come by

            if (m_bIsSummoningWhelps)
            {
                if (m_uiSummonCount < m_uiMaxWhelps)
                {
                    if (m_uiWhelpTimer < uiDiff)
                    {
                        m_creature->SummonCreature(NPC_WHELP, SpawnLocs[0][0], SpawnLocs[0][1], SpawnLocs[0][2], 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                        m_creature->SummonCreature(NPC_WHELP, SpawnLocs[1][0], SpawnLocs[1][1], SpawnLocs[1][2], 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                        m_uiSummonCount += 2;
                        m_uiWhelpTimer = 500;
                    }
                    else
                        m_uiWhelpTimer -= uiDiff;
                }
                else
                {
                    m_bIsSummoningWhelps = false;
                    m_uiSummonCount = 0;
                    m_uiSummonWhelpsTimer = 85000;
                }
            }
            else
            {
                if (m_uiSummonWhelpsTimer < uiDiff)
                    m_bIsSummoningWhelps = true;
                else
                    m_uiSummonWhelpsTimer -= uiDiff;
            }

            if(SummonGuardTimer < uiDiff)
            {
                m_creature->SummonCreature(NPC_GUARD, SpawnLocs[2][0], SpawnLocs[2][1], SpawnLocs[2][2], 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);
                SummonGuardTimer = 30000;
            }
            else 
                SummonGuardTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_boss_onyxiaAI(Creature* pCreature)
{
    return new boss_onyxiaAI(pCreature);
}

void AddSC_boss_onyxia()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_onyxia";
    newscript->GetAI = &GetAI_boss_onyxiaAI;
    newscript->RegisterSelf();
}
