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
SDName: Event
SDAuthor: Nembi & Sys
SD%Complete: 100
SDComment: Inferna Christmas PreEvent == Entry
SDCategory: Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

//texts
#define EVENT1	-2500100 // npc
#define EVENT2  -2500101 // player
#define EVENT3  -2500102 // npc
#define EVENT4  -2500103 // player
#define EVENT5  -2500104 // npc
#define EVENT6  -2500105 // npc
#define EVENT7  -2500106 // player
#define EVENT8  -2500107 // npc
#define EVENT9  -2500108 // npc

//oramus
#define EVENT10 -2500109 // npc
#define EVENT11 -2500110 // player
#define EVENT12 -2500111 // npc
#define EVENT13 -2500112 // npc
#define EVENT14 -2500113 // npc
#define EVENT15 -2500114 // npc
#define EVENT16 -2500115 // npc
#define EVENT17 -2500116 // npc
#define EVENT18 -2500117 // npc

#define THE_OCULUS 578

struct Location
{
    float x, y, z;
};

static Location WayPoints[] =
{
    // female
    {1158.052f, 1013.416f, 432.515f}, // 0
    {1161.840f, 1035.842f, 432.674f}, // 1
    {1161.032f, 1042.731f, 434.053f}, // 2
    {1159.058f, 1052.501f, 434.133f}, // 3
    {1159.211f, 1062.382f, 434.061f}, // 4
    // male
    {1152.052f, 1013.416f, 432.515f}, // 5
    {1155.840f, 1035.842f, 432.674f}, // 6
    {1155.032f, 1042.731f, 434.053f}, // 7
    {1153.058f, 1052.501f, 434.133f}, // 8
    {1153.211f, 1062.382f, 434.061f}, // 9
    // fight location
    {1027.426f, 1181.787f, 439.321f}, // 10
    // oramus fly away
    {900.000f, 1300.000f, 453.000f}, // 11
    // 1
    {993.750f, 1209.360f, 450.000f}, // 12
    {1020.13f, 1225.990f, 450.000f}, // 13
    {1038.76f, 1190.340f, 450.000f}, // 14
    {1006.35f, 1176.020f, 450.000f}  // 15
};

enum
{
    SPELL_SHADOW_PRISION	= 40647,
    ENTRY_1				= 400068
};

struct MANGOS_DLL_DECL oculus_trial_intro_femaleAI : public ScriptedAI
{
    oculus_trial_intro_femaleAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiMovementTimer;
    uint32 m_uiWaypointId;

    void Reset()
    {
        m_uiWaypointId = 0;
        m_uiMovementTimer = 10;

        m_creature->GetMotionMaster()->MoveTargetedHome();
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if(m_pInstance->GetData(TYPE_TRIAL) == IN_PROGRESS)
        {
            if(m_uiMovementTimer <= uiDiff)
            {
                switch(m_uiWaypointId)
                {
                    case 0:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[0].x, WayPoints[0].y, WayPoints[0].z);
                        DoScriptText(EVENT1, m_creature);
                        m_creature->setFaction(14);
                        m_creature->CastSpell(m_creature, SPELL_SHADOW_PRISION, true);
                        m_creature->setFaction(35);
                        m_uiMovementTimer = 5000;
                        break;
                    case 1:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[1].x, WayPoints[1].y, WayPoints[1].z);
                        m_uiMovementTimer = 10000;
                        break;
                    case 2:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[2].x, WayPoints[2].y, WayPoints[2].z);
                        m_uiMovementTimer = 3000;
                        break;
                    case 3:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[3].x, WayPoints[3].y, WayPoints[3].z);
                        m_uiMovementTimer = 4500;
                        break;
                    case 4:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[4].x, WayPoints[4].y, WayPoints[4].z);
                        DoScriptText(EVENT5, m_creature);
                        m_uiMovementTimer = 4500;
                        break;
                    case 5:
                        m_uiMovementTimer = 5000;
                        break;
                    case 6:
                        m_uiMovementTimer = 5000;
                        break;
                    case 7:
                        DoScriptText(EVENT8, m_creature);
                        m_uiMovementTimer = 10000;
                        break;
                    case 8:
                        m_uiMovementTimer = 5000;
                        break;
                    case 9:
                        m_uiMovementTimer = 1000;
                        break;
                    case 10:
                        Reset();
                        return;
                }
                m_uiWaypointId++;
            }
            else m_uiMovementTimer -= uiDiff;
        }
    }
};

struct MANGOS_DLL_DECL oculus_trial_intro_maleAI : public ScriptedAI
{
    oculus_trial_intro_maleAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiMovementTimer;
    uint32 m_uiWaypointId;

    uint64 m_uiPlayerGUID;

    void Reset()
    {
        m_uiWaypointId = 0;
        m_uiMovementTimer = 10;

        m_creature->GetMotionMaster()->MoveTargetedHome();
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if(!pWho)
            return;

        if(m_pInstance->GetData(TYPE_TRIAL) == NOT_STARTED)
        {
            if(pWho->GetTypeId() != TYPEID_PLAYER)
                return;

            if(m_creature->IsWithinDistInMap(pWho, 65.0f))
            {
                if(Player* pPlayer = (Player*)m_creature->GetUnit(*m_creature, pWho->GetGUID()))
                    if(pPlayer->isGameMaster())
                        return;

                m_pInstance->SetData(TYPE_TRIAL, IN_PROGRESS);
                m_uiPlayerGUID = pWho->GetGUID();
            }
        }
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if(m_pInstance->GetData(TYPE_TRIAL) == IN_PROGRESS)
        {
            if(m_uiMovementTimer <= uiDiff)
            {
                // must be initialized here... 
                Map* pMap = NULL;
                switch(m_uiWaypointId)
                {
                    case 0:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[5].x, WayPoints[5].y, WayPoints[5].z);
                        m_uiMovementTimer = 5000;
                        break;
                    case 1:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[6].x, WayPoints[6].y, WayPoints[6].z);
                        if(Unit* pPlayer = m_creature->GetUnit(*m_creature, m_uiPlayerGUID))
                            DoScriptText(EVENT2, pPlayer);
                        m_uiMovementTimer = 10000;
                        break;
                    case 2:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[7].x, WayPoints[7].y, WayPoints[7].z);
                        DoScriptText(EVENT3, m_creature);
                        m_uiMovementTimer = 3000;
                        break;
                    case 3:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[8].x, WayPoints[8].y, WayPoints[8].z);
                        if(Unit* pPlayer = m_creature->GetUnit(*m_creature, m_uiPlayerGUID))
                            DoScriptText(EVENT4, pPlayer);
                        m_uiMovementTimer = 4500;
                        break;
                    case 4:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[9].x, WayPoints[9].y, WayPoints[9].z);
                        m_creature->setFaction(14);
                        m_creature->CastSpell(m_creature, SPELL_SHADOW_PRISION, true);
                        m_creature->setFaction(35);
                        m_uiMovementTimer = 4500;
                        break;
                    case 5:
                        DoScriptText(EVENT6, m_creature);
                        m_uiMovementTimer = 5000;
                        break;
                    case 6:
                        if(Unit* pPlayer = m_creature->GetUnit(*m_creature, m_uiPlayerGUID))
                            DoScriptText(EVENT7, pPlayer);
                        m_uiMovementTimer = 5000;
                        break;
                    case 7:
                        m_uiMovementTimer = 10000;
                        break;
                    case 8:
                        DoScriptText(EVENT9, m_creature);
                        m_uiMovementTimer = 5000;
                        break;
                    case 9:
                        pMap = m_creature->GetMap();
                        if(pMap && pMap->IsDungeon())
                        {
                            Map::PlayerList const &lPlayers = pMap->GetPlayers();
                            for (Map::PlayerList::const_iterator iter = lPlayers.begin(); iter != lPlayers.end(); ++iter)
                            {
                                Player* pPlayer = iter->getSource();

                                if(pPlayer)
                                    pPlayer->TeleportTo(THE_OCULUS, WayPoints[10].x, WayPoints[10].y, WayPoints[10].z, 2.088f); 
                            }
                        }
                        m_pInstance->SetData(TYPE_TRIAL, SPECIAL);
                        m_uiMovementTimer = 1000;
                        break;
                    case 10:
                        Reset();
                        return;
                }
                m_uiWaypointId++;
            }
            else m_uiMovementTimer -= uiDiff;
        }
    }
};

struct MANGOS_DLL_DECL oculus_trial_intro_oramusAI : public ScriptedAI
{
    oculus_trial_intro_oramusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiSpeechTimer;
    uint32 m_uiState;

    void Reset()
    {
        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
        m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
        m_creature->SetPhaseMask(128, true);

        m_uiSpeechTimer = 5000;
        m_uiState = 0;
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if(m_creature->GetPhaseMask() == 128 && m_pInstance->GetData(TYPE_TRIAL) == SPECIAL)
            m_creature->SetPhaseMask(1, true);

        if(m_pInstance->GetData(TYPE_TRIAL) == SPECIAL)
        {
            if(m_uiSpeechTimer < uiDiff)
            {
                Map *pMap = NULL;
                switch(m_uiState)
                {
                    case 0:
                        DoScriptText(EVENT10, m_creature);
                        m_uiSpeechTimer = 10000;
                        break;
                    case 1:
                        pMap = m_creature->GetMap();
                        if(pMap && pMap->IsDungeon())
                        {
                            Player *pPlayer = NULL;
                            Map::PlayerList const &lPlayers = pMap->GetPlayers();
                            for(Map::PlayerList::const_iterator iter = lPlayers.begin(); iter != lPlayers.end(); ++iter)
                            {
                                pPlayer = iter->getSource();
                                break;
                            }
                            DoScriptText(EVENT11, pPlayer);
                        }
                        m_uiSpeechTimer = 7000;
                        break;
                    case 3:
                        DoScriptText(EVENT12, m_creature);
                        m_uiSpeechTimer = 5000;
                        break;
                    case 4:
                        DoScriptText(EVENT13, m_creature);
                        m_uiSpeechTimer = 8000;
                        break;
                    case 5:
                        DoScriptText(EVENT14, m_creature);
                        m_uiSpeechTimer = 10000;
                        break;
                    case 6:
                        DoScriptText(EVENT15, m_creature);
                        m_uiSpeechTimer = 10000;
                        break;
                    case 7:
                        DoScriptText(EVENT16, m_creature);
                        m_uiSpeechTimer = 10000;
                        break;
                    case 8:
                        DoScriptText(EVENT17, m_creature);
                        m_uiSpeechTimer = 5000;
                        break;
                    case 9:
                        DoScriptText(EVENT18, m_creature);
                        if(Creature* p1 = m_creature->SummonCreature(ENTRY_1, 985.545f, 1233.076f, 438.9411f, 5.5194f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000))
                            p1->GetMotionMaster()->MovePoint(0, 1017.817f, 1201.022f, 439.321f);
                        m_uiSpeechTimer = 3000;
                        break;
                    case 10:
                        m_creature->GetMotionMaster()->MovePoint(0, WayPoints[11].x, WayPoints[11].y, WayPoints[11].z);
                        m_uiSpeechTimer = 5000;
                        m_pInstance->SetData(TYPE_TRIAL, IN_PROGRESS);
                        break;
                    case 11:
                        m_creature->GetMotionMaster()->MoveTargetedHome();
                        Reset();
                        return;
                }
                m_uiState++;
            }
            else
                m_uiSpeechTimer -= uiDiff;
        }
    }
};

enum
{
    COMBAT_PHASE_GROUND	=	1,
    COMBAT_PHASE_FLYING =	2,
    COMBAT_PHASE_FINAL	=	3,

    DISPLAY_IRONBIND_DRAKE	=	28953,

    SPELL_DISENGAGE			=	65869,
    SPELL_SHOOT				=	65868,
    SPELL_WYVERN_STING		=	65877,
    SPELL_STEADY_SHOT		=	65867,
    SPELL_AIMED_SHOT		=	65883,

    ENTRY_2					=  400069,

    SPELL_BARKSKIN			=	65860,
    SPELL_REJUVENATION		=	66065,
    SPELL_THORNS			=	66068,
    SPELL_NATURES_GRASP		=	66071,
    SPELL_NOURISH			=	66066,
    SPELL_RESURRECTION		=	9232,

    SPELL_DEEPSLEEP         =   9256
};

struct MANGOS_DLL_DECL oculus_trial_boss_1AI : public ScriptedAI
{
    oculus_trial_boss_1AI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiWaypointId;
    uint32 m_uiMovementTimer;

    uint64 m_ui2GUID;

    bool m_bHasDied;
    bool m_bFakeDeath;
    bool m_bRessurected;
    bool m_bDoOnce;

    uint32 m_uiDisengage;
    uint32 m_uiShoot;
    uint32 m_uiWyvernSting;
    uint32 m_uiSteadyShot;
    uint32 m_uiAimedShot;

    uint8 m_uiCombatPhase;

    void Reset()
    {
        m_uiWaypointId = 0;
        m_uiMovementTimer = 0;
        
        if(Creature* pTemp = m_creature->GetCreature(*m_creature, m_ui2GUID))
            pTemp->ForcedDespawn();

        m_ui2GUID = 0;

        m_bHasDied = false;
        m_bFakeDeath = false;
        m_bRessurected = false;
        m_bDoOnce = true;

        m_uiShoot = 5000;
        m_uiAimedShot = 15000;
        m_uiSteadyShot = 12000;
        m_uiWyvernSting = 12000;
        m_uiDisengage = 8000;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);

        m_uiCombatPhase = COMBAT_PHASE_GROUND;

        if(m_creature->IsMounted())
        {
            m_creature->Unmount();
            m_creature->RemoveSplineFlag(SPLINEFLAG_FLYING);
            m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
        }
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage < m_creature->GetHealth() || m_bHasDied)
            return;

        if (!m_pInstance)
            return;

        if (Creature* p2 = m_creature->SummonCreature(ENTRY_2, m_creature->GetPositionX()+rand()%5, m_creature->GetPositionY()+rand()%5, m_creature->GetPositionZ()+rand()%5, m_creature->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 300000))
        {
            m_ui2GUID = p2->GetGUID();
            p2->GetMotionMaster()->MovePoint(0, 1017.817f, 1201.022f, 439.321f);

            m_creature->GetMotionMaster()->MovementExpired();
            m_creature->GetMotionMaster()->MoveIdle();

            m_creature->SetHealth(0);

            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            m_creature->ClearComboPointHolders();
            m_creature->RemoveAllAuras();
            m_creature->ClearAllReactives();
            m_creature->Unmount();

            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetStandState(UNIT_STAND_STATE_DEAD);

            m_bHasDied = true;
            m_bFakeDeath = true;

            m_pInstance->SetData(TYPE_TRIAL, SPECIAL);

            uiDamage = 0;
        }
    }

    // doesnt' work....
    void SpellHit(Unit* pWho, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_RESURRECTION)
        {
            // TODO? say sth.
            m_bFakeDeath = false;

            m_creature->SetHealthPercent(100.0f);
        }
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if (m_bFakeDeath)
            return;

        if (m_bHasDied && !m_bRessurected && m_pInstance && m_pInstance->GetData(TYPE_TRIAL) == SPECIAL)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);

            if (m_creature->getVictim())
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());

            m_bRessurected = true;

            m_pInstance->SetData(TYPE_TRIAL, IN_PROGRESS);
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiShoot < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_SHOOT, true);
            m_uiShoot = 5000;
        }
        else
            m_uiShoot -= uiDiff;

        switch(m_uiCombatPhase)
        {
            case COMBAT_PHASE_GROUND:
                if(m_creature->GetHealthPercent() <= 60.0f)
                {
                    m_uiCombatPhase = COMBAT_PHASE_FLYING;
                    m_creature->Mount(DISPLAY_IRONBIND_DRAKE);
                    m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
                    m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                    m_creature->SetSpeedRate(MOVE_FLIGHT, 3.1f);
                    return;
                }

                if(m_uiAimedShot < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_AIMED_SHOT, true);
                    m_uiAimedShot = 8000;
                }
                else
                    m_uiAimedShot -= uiDiff;

                break;
            case COMBAT_PHASE_FLYING:
                if(m_creature->GetHealthPercent() <= 20.0f)
                {
                    if(m_bDoOnce)
                    {
                        m_creature->GetMotionMaster()->MovePoint(0, 1017.817f, 1201.022f, 439.321f);
                        m_bDoOnce = false;
                    }

                    if(m_creature->GetPositionZ() < 441.0f)
                    {
                        m_creature->RemoveSplineFlag(SPLINEFLAG_FLYING);
                        m_creature->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                        m_uiCombatPhase = COMBAT_PHASE_FINAL;
                        return;
                    }
                    return;
                }

                if(m_uiSteadyShot < uiDiff)
                {
                    if(Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_STEADY_SHOT, true);
                    m_uiSteadyShot = 12000;
                }
                else
                    m_uiSteadyShot -= uiDiff;

                if(m_uiMovementTimer <= uiDiff)
                {
                    switch(m_uiWaypointId)
                    {
                        case 0:
                            m_creature->GetMotionMaster()->MovePoint(0, WayPoints[12].x, WayPoints[12].y, WayPoints[12].z);
                            m_uiWaypointId++;
                            m_uiMovementTimer = 20000;
                            break;
                        case 1:
                            m_creature->GetMotionMaster()->MovePoint(0, WayPoints[13].x, WayPoints[13].y, WayPoints[13].z);
                            m_uiWaypointId++;
                            m_uiMovementTimer = 20000;
                            break;
                        case 2:
                            m_creature->GetMotionMaster()->MovePoint(0, WayPoints[14].x, WayPoints[14].y, WayPoints[14].z);
                            m_uiWaypointId++;
                            m_uiMovementTimer = 20000;
                            break;
                        case 3:
                            m_creature->GetMotionMaster()->MovePoint(0, WayPoints[15].x, WayPoints[15].y, WayPoints[15].z);
                            m_uiWaypointId = 0;
                            m_uiMovementTimer = 20000;
                            break;
                    }
                }
                else
                    m_uiMovementTimer -= uiDiff;
                break;
            case COMBAT_PHASE_FINAL:
                if(m_uiWyvernSting < uiDiff)
                {
                    if(Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_WYVERN_STING, true);
                    m_uiWyvernSting = 12000;
                }
                else
                    m_uiWyvernSting -= uiDiff;

                if(m_uiDisengage < uiDiff)
                {
                    DoCast(m_creature->getVictim(), SPELL_DISENGAGE, true);
                    m_uiDisengage = 8000;
                }
                else
                    m_uiDisengage -= uiDiff;
                
                break;
        }
    }
};

struct MANGOS_DLL_DECL oculus_trial_boss_2AI : public ScriptedAI
{
    oculus_trial_boss_2AI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bCanResurrectCheck;
    bool m_bCanResurrect;

    uint32 m_uiWaitTimer;

    void Reset()
    {
        m_bCanResurrectCheck = false;
        m_bCanResurrect = false;

        m_uiWaitTimer = 7000;
    }

    void MoveInLineOfSight()
    {
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage < m_creature->GetHealth())
            return;

        if (!m_bCanResurrectCheck || m_bCanResurrect)
        {
            m_creature->SetHealth(uiDamage+1);
        }
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanResurrect)
        {
            if (m_pInstance && m_uiWaitTimer < uiDiff)
            {
                if (Creature* p1 = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_1)))
                {
                    DoCast(p1, SPELL_RESURRECTION, true);
                    m_bCanResurrect = false;
                }
            }
            else
                m_uiWaitTimer -= uiDiff;
        }

        if (!m_bCanResurrectCheck && m_creature->GetHealthPercent() <= 50.0f)
        {
            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            DoCastSpellIfCan(m_creature->getVictim(), SPELL_DEEPSLEEP);
            m_bCanResurrectCheck = true;
            m_bCanResurrect = true;
            return;
        }

        if (m_bCanResurrect)
            return;
    }
};

CreatureAI* GetAI_oculus_trial_intro_female(Creature* pCreature)
{
    return new oculus_trial_intro_femaleAI(pCreature);
}

CreatureAI* GetAI_oculus_trial_intro_male(Creature* pCreature)
{
    return new oculus_trial_intro_maleAI(pCreature);
}

CreatureAI* GetAI_oculus_trial_intro_oramus(Creature* pCreature)
{
    return new oculus_trial_intro_oramusAI(pCreature);
}

CreatureAI* GetAI_oculus_trial_boss_1(Creature* pCreature)
{
    return new oculus_trial_boss_1AI(pCreature);
}

CreatureAI* GetAI_oculus_trial_boss_2(Creature* pCreature)
{
    return new oculus_trial_boss_2AI(pCreature);
}

void AddSC_oculus_trial()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_trial_intro_female";
    newscript->GetAI = &GetAI_oculus_trial_intro_female;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_trial_intro_male";
    newscript->GetAI = &GetAI_oculus_trial_intro_male;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_trial_intro_oramus";
    newscript->GetAI = &GetAI_oculus_trial_intro_oramus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_trial_boss_1";
    newscript->GetAI = &GetAI_oculus_trial_boss_1;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_trial_boss_2";
    newscript->GetAI = &GetAI_oculus_trial_boss_2;
    newscript->RegisterSelf();
}