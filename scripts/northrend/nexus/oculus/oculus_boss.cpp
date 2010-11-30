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
SDComment: Inferna Christmas PreEvent == The last Stand (Endboss)
SDCategory: Oculus
EndScriptData */

/* ContentData
oculus_boss_oramus				Addtion to Inferna Christmas PreEvent
oculus_boss_ragnaros			Addtion to Inferna Christmas PreEvent
EndContentData */

#include "precompiled.h"
#include "oculus.h"
#include "WorldPacket.h"


    uint32 m_uiPhase;
    bool m_bIsLetsGo;

/*######
## oculus_boss_oramus
######*/

#define THE_OCULUS						578
#define SPELL_FLAME_BREATH				57570

#define START1							-2500130
#define START2							-2500131
#define START3							-2500132
#define START4							-2500133
#define START5							-2500134
#define SECOND							-2500135
#define THIRD							-2500136
#define FOURTH							-2500137

#define SPELL_ARKAN						58455
#define SPELL_DAZED						8672
#define SPELL_DIES						29357
#define SPELL_TOTAL_DEATH				5

#define SPELL_ARMY						67761
#define SPELL_SHADOW_PAIN				59864
#define SPELL_CURSE						69404
#define SPELL_SHADOW_BOLT				36972
#define SPELL_HOT_EARTH					22191
#define SPELL_SILENCE					18278

#define SANTA3							-2500172

//Britzel Phase
#define CREATURE_ARCANE_SPHERE			400082
#define SPELL_GRAVITY_LAPSE_INITIAL		44224                 // Cast at the beginning of every Gravity Lapse
#define SPELL_GRAVITY_LAPSE_CHANNEL		44251                 // Channeled; blue beam animation to every enemy in range
#define SPELL_ARCANE_SPHERE_PASSIVE		44263                 // Passive auras on Arcane Spheres
#define SPELL_POWER_FEEDBACK			44233                 // Stuns him, making him take 50% more damage for 10 seconds. Cast after Gravity Lapse





struct Location
{
    float x, y, z;
};


static Location WayPoints[] =
{
    //Oramus Movements
    {1088.114380f, 989.888245f, 441.605164f},  // 0 to the Players
    {1040.636597f, 937.819885f, 470.055634f},  // 1 to Ragnaros
    {999.482605f, 1047.853516f, 543.647217f},  // 2 to Princess
    {1082.609253f, 1016.369934f, 601.843323f}, // 3 to the Top Plattform
    {1105.163574f, 1059.876343f, 510.849365f}, // 4 to the Middle
    {1108.812012f, 1040.247070f, 607.637451f}, // 5 to the Top
    //Player Teleports
    {1048.228760f, 925.094055f, 438.941345f},  // 6
    {986.237976f, 997.005432f, 526.810974f},   // 7
    {1126.063843f, 1178.769653f, 526.811707f}, // 8
    {1065.169922f, 1046.453613f, 602.709045f}, // 9
    {1058.607056f, 1048.523193f, 508.360901f}, // 10
    //Endfight
    {1105.947998f, 1016.980225f, 602.266113f}, // 11
    {1104.032715f, 1043.515869f, 614.740845f}  // 12
};


struct MANGOS_DLL_DECL oculus_boss_oramusAI : public ScriptedAI
{
    oculus_boss_oramusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }


    ScriptedInstance* m_pInstance;


    uint32 m_uiSayTimer;
    uint32 m_uiSayPoint;
    uint32 m_uiSay2Timer;
    uint32 m_uiSay2Point;
    uint32 m_uiSay3Timer;
    uint32 m_uiSay3Point;
    uint32 m_uiSay5Timer;
    uint32 m_uiSay5Point;
    uint32 m_uiSay6Timer;
    uint32 m_uiSay6Point;

    uint32 m_uiArmyTimer;
    uint32 m_uiCurseTimer;
    uint32 m_uiShadowTimer;
    uint32 m_uiShadowBoltTimer;
    uint32 m_uiHotEarthTimer;
    uint32 m_uiSecondPhaseTimer;
    uint32 m_uiSecondPhasePoint;
	uint32 m_uiSilenceTimer;

	bool m_bIsFirstMorph;
	bool m_bIsSecondMorph;
	bool m_bIsThirdMorph;


    void Reset()
    {
		m_uiSilenceTimer = 0;
        m_uiArmyTimer = 0;
        m_uiShadowTimer = 0;
        m_uiCurseTimer = 0;
        m_uiShadowBoltTimer = 0;
        m_uiHotEarthTimer = 0;
        m_uiSecondPhaseTimer = 0;
        m_uiSecondPhasePoint = 0;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetStandState(UNIT_STAND_STATE_SLEEP);

        m_uiPhase = 1;
        m_uiSayTimer = 1000;
        m_uiSayPoint = 0;
        m_uiSay2Timer = 3000;
        m_uiSay2Point = 0;
        m_uiSay3Timer = 3000;
        m_uiSay3Point = 0;
        m_uiSay5Timer = 1000;
        m_uiSay5Point = 0;
        m_uiSay6Timer = 2000;
        m_uiSay6Point = 0;

        m_creature->SetDisplayId(26752);
        m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
        m_creature->GetMotionMaster()->MoveTargetedHome();

        m_bIsLetsGo = false;

		m_bIsFirstMorph = false;
		m_bIsSecondMorph = false;
		m_bIsThirdMorph = false;

    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_ORAMUS, DONE);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();	
    }

    void EnterCombat(Unit* pWho)
    {
       if(Creature* pRagnaros = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_RAGNAROS)))
            pRagnaros->Respawn();
       if(Creature* pTheradras = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_THERADRAS)))
            pTheradras->Respawn();
       if(Creature* pTrigger = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_TRIGGER2)))
            pTrigger->Respawn();
       if(Creature* pSanta = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_SANTA)))
            pSanta->Respawn();

       if(Creature* pRagnaros = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_RAGNAROS)))
            pRagnaros->SetPhaseMask(1, true);
       if(Creature* pTheradras = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_THERADRAS)))
            pTheradras->SetPhaseMask(1, true);
       if(Creature* pSanta = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_SANTA)))
            pSanta->SetPhaseMask(128, true);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
        m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MoveIdle();
        m_uiPhase = 1;	
        m_creature->MonsterMove(WayPoints[0].x, WayPoints[0].y, WayPoints[0].z, 500);
    }

    void KilledUnit(Unit* pKiller)
    {
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiPhase == 1)
        {
            if(m_uiSayTimer <= uiDiff)
            {
                Map* pMap = NULL;
                switch(m_uiSayPoint)
                {
                    case 0:
                        DoScriptText(START1, m_creature);
                        if (Creature* pTrigger = m_creature->GetCreature(*m_creature,m_pInstance->GetData64(DATA_TRIGGER)))
                            DoCast(pTrigger,SPELL_FLAME_BREATH,true);
                        m_uiSayTimer = 5000;
                        break;
                    case 1:
                        DoScriptText(START2, m_creature);
                        m_uiSayTimer = 5000;
                        break;
                    case 2:
                        DoScriptText(START3, m_creature);
                        m_uiSayTimer = 5000;
                        break;
                    case 3:
                        DoScriptText(START4, m_creature);
                        m_uiSayTimer = 5000;
                        break;
                    case 4:
                        DoScriptText(START5, m_creature);
                        m_creature->MonsterMove(WayPoints[1].x, WayPoints[1].y, WayPoints[1].z, 3000);
                        m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                        m_uiSayTimer = 2000;
                        break;
                    case 5:
                        Map* pMap = m_creature->GetMap();
                        if (pMap && pMap->IsDungeon())
                        {
                            Map::PlayerList const &players = pMap->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                                itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[6].x, WayPoints[6].y, WayPoints[6].z, 4.363545f);
                        }
                        break;
                }m_uiSayPoint++;
            }else m_uiSayTimer -= uiDiff;
        }

        //Ragnaros down
        if (m_uiPhase == 2)
        {
            if(m_uiSay2Timer <= uiDiff)
            {
                Map* pMap2 = NULL;
                switch(m_uiSay2Point)
                {
                    case 0:
                        DoScriptText(SECOND, m_creature);
                        m_uiSay2Timer = 5000;
                        break;
                    case 1:
                        m_creature->MonsterMove(WayPoints[2].x, WayPoints[2].y, WayPoints[2].z, 2000);
                        Map* pMap2 = m_creature->GetMap();
                        if (pMap2 && pMap2->IsDungeon())
                        {
                            Map::PlayerList const &players2 = pMap2->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = players2.begin(); itr != players2.end(); ++itr)
                                itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[7].x, WayPoints[7].y, WayPoints[7].z, 1.831856f);
                        }
                        m_uiSay2Timer = 3000;
                        break;
                }m_uiSay2Point++;
            }else m_uiSay2Timer -= uiDiff;
        }
        
        //Princess down
        if (m_uiPhase == 3)
        {
            if(m_uiSay3Timer <= uiDiff)
            { 
                Map* pMap3 = NULL;
                switch(m_uiSay3Point)
                {
                    case 0:
                        DoScriptText(FOURTH, m_creature);
                        m_uiSay3Timer = 5000;
                        break;
                    case 1:
                        m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
                        m_uiPhase = 4;
                        m_creature->MonsterMove(WayPoints[4].x, WayPoints[4].y, WayPoints[4].z, 800);
                        Map* pMap3 = m_creature->GetMap();
                        if (pMap3 && pMap3->IsDungeon())
                        {
                            Map::PlayerList const &players3 = pMap3->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = players3.begin(); itr != players3.end(); ++itr)
                                itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[10].x, WayPoints[10].y, WayPoints[10].z, 4.274161f);
                        }
                        m_uiSay3Timer = 1000;
                        break;
                        break;
                }m_uiSay3Point++;
            }else m_uiSay3Timer -= uiDiff;
        }


        if (m_uiPhase == 4)
        {
            if(m_uiSay5Timer <= uiDiff)
            {
                Map* pMap5 = NULL;
                switch(m_uiSay5Point)
                {
                case 0:
                    m_creature->MonsterMove(WayPoints[5].x, WayPoints[5].y, WayPoints[5].z, 1000);
                    m_uiSay5Timer = 500;
                    break;
                case 1:
                        Map* pMap5 = m_creature->GetMap();
                        if (pMap5 && pMap5->IsDungeon())
                        {
                            Map::PlayerList const &players5 = pMap5->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = players5.begin(); itr != players5.end(); ++itr)
                                itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[9].x, WayPoints[9].y, WayPoints[9].z, 6.000292f);
                        }
                        break;
                }m_uiSay5Point++;
            }else m_uiSay5Timer -= uiDiff;
        }

        if (m_uiPhase == 5)
        {
            m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);

            m_uiPhase = 6;
        }

        if (m_uiPhase == 6)
        {
            if(m_uiSay6Timer <= uiDiff)
            {
                switch(m_uiSay6Point)
                {
                case 0:
                    m_creature->MonsterMove(WayPoints[3].x, WayPoints[3].y, WayPoints[3].z, 100);
                    m_creature->RemoveSplineFlag(SPLINEFLAG_FLYING);
                    DoCast(m_creature->getVictim(), SPELL_ARKAN, true);
                    m_uiSay6Timer = 1000;
                    break;
                case 1:
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                    m_creature->SetDisplayId(22460);
                    m_uiSay6Timer = 1000;
                    break;
                case 2:
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.3f);
                    m_uiSay6Timer = 1000;
                    break;
                case 3:
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.8f);
                    m_uiSay6Timer = 1000;
                    break;
                case 4:
                    DoScriptText(THIRD, m_creature);
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
                    m_uiSay6Timer = 1000;
                    break;
                case 5:
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.6f);
                    m_uiSay6Timer = 1000;
                    break;
                case 6:
                    m_creature->SetDisplayId(8752);
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 3);
                    m_uiSay6Timer = 500;
                    break;
                case 7:
                    DoCast(m_creature->getVictim(), SPELL_ARKAN, true);
                    m_uiSay6Timer = 1000;
                    break;
                case 8:
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    SetCombatMovement(true);
                    if (m_creature->getVictim())
                        m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_uiSay6Timer = 1000;
                    break;
                case 9:
					m_uiSilenceTimer = 8000;
                    m_uiArmyTimer = 40000;
                    m_uiShadowTimer = 19000;
                    m_uiCurseTimer = 22000;
                    m_uiShadowBoltTimer = 5000;
                    m_uiHotEarthTimer = 20000;
                    m_uiPhase = 7;
                    m_uiSay6Timer = 500;
                    break;

                }m_uiSay6Point++;
            }else m_uiSay6Timer -= uiDiff;
        }

        if (m_uiPhase == 7)
        {
            if (m_uiSilenceTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_SILENCE, true);

                m_uiSilenceTimer = 8000;
            }else m_uiSilenceTimer -= uiDiff;

            if (m_uiHotEarthTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_HOT_EARTH, true);

                m_uiHotEarthTimer = 20000;
            }else m_uiHotEarthTimer -= uiDiff;

            if (m_uiArmyTimer < uiDiff)
            {
                DoCast(m_creature->getVictim(), SPELL_ARMY, true);

                m_uiArmyTimer = 40000;
            }else m_uiArmyTimer -= uiDiff;

            if (m_uiShadowTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_SHADOW_PAIN, true);

                m_uiShadowTimer = 19000;
            }else m_uiShadowTimer -= uiDiff;

            if (m_uiCurseTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_CURSE, true);

                m_uiCurseTimer = 22000;
            }else m_uiCurseTimer -= uiDiff;

            if (m_uiShadowBoltTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                    DoCast(pTarget,SPELL_SHADOW_BOLT, true);

                m_uiShadowBoltTimer = 5000;
            }else m_uiShadowBoltTimer -= uiDiff;
            
            if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 15) &&(m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 10))
            {
                m_uiPhase = 8;
                m_uiArmyTimer = 0;
                m_uiCurseTimer = 0;
                m_uiShadowTimer = 0;
                m_uiShadowBoltTimer = 0;
            }
            
            //Secondphase
            if (!m_bIsFirstMorph && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 70))
            {
				m_bIsFirstMorph = true;
                m_uiArmyTimer = 0;
                m_uiCurseTimer = 0;
                m_uiShadowTimer = 0;
                m_uiShadowBoltTimer = 0;
                m_uiSecondPhaseTimer = 2000;
                m_uiPhase = 15;
            }

            if (!m_bIsSecondMorph && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 50))
            {
				m_bIsSecondMorph = true;
                m_uiArmyTimer = 0;
                m_uiCurseTimer = 0;
                m_uiShadowTimer = 0;
                m_uiShadowBoltTimer = 0;
                m_uiSecondPhaseTimer = 2000;
				m_uiSecondPhasePoint = 0;
                m_uiPhase = 15;
            }

            if (!m_bIsThirdMorph && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 30))
            {
				m_bIsThirdMorph = true;
                m_uiArmyTimer = 0;
                m_uiCurseTimer = 0;
                m_uiShadowTimer = 0;
                m_uiShadowBoltTimer = 0;
                m_uiSecondPhaseTimer = 2000;
				m_uiSecondPhasePoint = 0;
                m_uiPhase = 15;
            }
        }

        if (m_uiPhase == 8)
        {
            SetCombatMovement(false);
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->RemoveAllAuras();
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_uiPhase = 9;
        }

        if (m_uiPhase == 9)
        {
            DoCast (m_creature, SPELL_DAZED, true);

            if(Creature* pSanta = m_creature->GetCreature(*m_creature, m_pInstance->GetData64(DATA_SANTA)))
                pSanta->SetPhaseMask(1, true);

            if(Player* pPlayer = (Player*)m_creature->getVictim())
            {
                pPlayer->TeleportTo(THE_OCULUS, pPlayer->GetPositionX() + 2, pPlayer->GetPositionY() + 2, pPlayer->GetPositionZ(), 5.635f);
            }

            m_uiPhase = 10;
        }

        if(m_uiPhase == 11)
        {
            DoScriptText(SANTA3, m_creature);
            m_uiPhase = 12;
        }

        if(m_uiPhase == 13)
        {
            DoCast(m_creature, SPELL_DIES, true);
            DoCast(m_creature, SPELL_TOTAL_DEATH, true);
            m_uiPhase = 14;
        }

        if (m_uiPhase == 15)
        {
            if(m_uiSecondPhaseTimer <= uiDiff)
            {
                switch(m_uiSecondPhasePoint)
                {
                case 0:
                    SetCombatMovement(false);
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    m_creature->GetMotionMaster()->MoveIdle();
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
                    m_creature->SetDisplayId(22460);
                    m_uiSecondPhaseTimer = 1000;
                    break;
                case 1:
                    m_creature->SetDisplayId(26752);
                    m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
                    m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
                    m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
                    m_creature->MonsterMove(WayPoints[12].x, WayPoints[12].y, WayPoints[12].z, 3000);
                    m_uiSecondPhaseTimer = 4000;
                    break;
                case 2:
                    DoCast(m_creature, SPELL_GRAVITY_LAPSE_INITIAL, true);
                    m_uiSecondPhaseTimer = 2500;
                    break;
                case 3:
                    for(uint8 i = 0; i < 3; ++i)
                    {
                        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                        {
                            if (Creature* Orb = DoSpawnCreature(CREATURE_ARCANE_SPHERE, 5, 5, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
                                Orb->AI()->AttackStart(pTarget);
                        }
                    }
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_GRAVITY_LAPSE_CHANNEL);
                    m_uiSecondPhaseTimer = 32000;
                    break;
                case 4:
                    m_uiPhase = 6;
                    m_uiSay6Timer = 2000;
                    m_uiSay6Point = 0;

                    break;

                }m_uiSecondPhasePoint++;
            }else m_uiSecondPhaseTimer -= uiDiff;
        }
        DoMeleeAttackIfReady();
    }
};



/*######
## oculus_arcane_sphere
######*/

#define SPELL_ARCANE_SPHERE_PASSIVE   44263   // Passive auras on Arcane Spheres 


struct MANGOS_DLL_DECL oculus_arcane_sphereAI : public ScriptedAI
{
    oculus_arcane_sphereAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 DespawnTimer;
    uint32 ChangeTargetTimer;

    void Reset()
    {
        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
        m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);

        DespawnTimer = 30000;
        ChangeTargetTimer = urand(6000, 12000);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        DoCastSpellIfCan(m_creature, SPELL_ARCANE_SPHERE_PASSIVE, CAST_TRIGGERED);
    }

    void UpdateAI(const uint32 diff)
    {
        if (DespawnTimer < diff)
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        else DespawnTimer -= diff;

        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget())
            return;

        if (ChangeTargetTimer < diff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                m_creature->TauntApply(pTarget);
                AttackStart(pTarget);
            }

            ChangeTargetTimer = urand(5000, 15000);
        }else ChangeTargetTimer -= diff;
    }
};


/*######
## oculus_boss_santa
######*/

#define SANTA1					-2500170
#define SANTA2					-2500171
#define SANTA4					-2500173
#define SANTA5					-2500174
#define SANTA6					-2500175
#define GO_DALARAN				400016



struct MANGOS_DLL_DECL oculus_boss_santaAI : public ScriptedAI
{
    oculus_boss_santaAI(Creature *pCreature) : ScriptedAI(pCreature){Reset();}

    ScriptedInstance* m_pInstance;

    uint32 m_uiMovementTimer;
    uint8  m_uiWaypointId;
    uint64 m_uiPlayerGUID;
    bool   m_bIsPlayer;
    uint64 m_uiOramusGUID;

    void Reset()
    {
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MoveIdle();
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_uiMovementTimer = 3000;
        m_uiWaypointId = 0;
        m_creature->setFaction(14);
        m_bIsPlayer = false;
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        m_uiOramusGUID = 0;
    }

    void MoveInLineOfSight(Unit *pWho) 
    {
        if(!pWho)
            return;

        if(!m_bIsLetsGo && (m_creature->IsWithinDistInMap(pWho, 120.0f)))
        {
            if(pWho->GetTypeId() != TYPEID_PLAYER)
                return;

            if(Player* pPlayer = (Player*)m_creature->GetUnit(*m_creature, pWho->GetGUID()))
                if(pPlayer->isGameMaster())
                    return;

            m_creature->MonsterMove(pWho->GetPositionX()+ urand(0.2, 0.5) , pWho->GetPositionY()+ urand(0.2, 0.5), pWho->GetPositionZ(), 2000);
            m_uiPlayerGUID = pWho->GetGUID();
        }
        m_bIsLetsGo = true;
    }

    void UpdateAI(uint32 const uiDiff)
    {
        if(m_bIsLetsGo)
        {
            if(m_uiMovementTimer <= uiDiff)
            {
                switch(m_uiWaypointId)
                {
                    case 0:
                        DoScriptText(SANTA1, m_creature);
                        m_uiMovementTimer = 6000;
                        break;
                    case 1:
                        DoScriptText(SANTA2, m_creature);
                        m_uiMovementTimer = 6000;
                        break;
                    case 2:
                        m_uiPhase = 11;
                        m_uiMovementTimer = 6000;
                        break;
                    case 3:
                        DoScriptText(SANTA4, m_creature);
                        m_uiMovementTimer = 6000;
                        break;
                    case 4:
                        if(Unit* pPlayer = m_creature->GetUnit(*m_creature, m_uiPlayerGUID))
                            DoScriptText(SANTA5, pPlayer);
                        m_bIsPlayer = true;
                        m_uiMovementTimer = 6000;
                        break;
                    case 5:
                        DoScriptText(SANTA6, m_creature);
                        m_uiMovementTimer = 6000;
                        break;
                    case 6:
                        m_uiPhase = 13;
                        m_uiMovementTimer = 6000;
                        break;
                    case 7:
                        m_creature->SummonGameobject(GO_DALARAN, 1124.058f, 1021.299f, 602.709f, TEMPSUMMON_MANUAL_DESPAWN, 0);
                        m_creature->SummonGameobject(GO_DALARAN, 1073.956f, 1049.259f, 602.709f, TEMPSUMMON_MANUAL_DESPAWN, 0);
                        m_creature->SummonGameobject(GO_DALARAN, 1120.714f, 1080.630f, 602.709f, TEMPSUMMON_MANUAL_DESPAWN, 0);
                        m_uiMovementTimer = 3000;
                    case 8:
                        m_creature->ForcedDespawn();
                        m_uiMovementTimer = 1000;

                }m_uiWaypointId++;
            }else m_uiMovementTimer -= uiDiff;
        }
    }
};


/*######
## oculus_boss_hakkar
######*/

#define SPELL_INSANITY			24327
#define SPELL_BLOOD				24328
#define SPELL_POISEN			43364


struct MANGOS_DLL_DECL oculus_boss_hakkarAI : public ScriptedAI
{
    oculus_boss_hakkarAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    ScriptedInstance* m_pInstance;

    uint32 m_uiInsanityTimer;
    uint32 m_uiBloodTimer;
    uint32 m_uiPoisenTimer;


    void Reset()
    {
        m_uiBloodTimer = 10000;
        m_uiPoisenTimer = 18000;
        m_uiInsanityTimer = 22000;
    }

    void JustDied(Unit* pKiller)
    {
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBloodTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_BLOOD, true);

            m_uiBloodTimer = 10000;
        }else m_uiBloodTimer -= uiDiff;

        if (m_uiPoisenTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_POISEN, true);

            m_uiPoisenTimer = 18000;
        }else m_uiPoisenTimer -= uiDiff;

        if (m_uiInsanityTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_INSANITY, true);

            m_uiInsanityTimer = 22000;
        }else m_uiInsanityTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};



/*######
## oculus_boss_theradras
######*/

#define SPELL_FEAR					30615
#define SPELL_BOULDER				50999
#define SPELL_TRASH					3391


struct MANGOS_DLL_DECL oculus_boss_theradrasAI : public ScriptedAI
{
    oculus_boss_theradrasAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    ScriptedInstance* m_pInstance;

    uint32 m_uiFearTimer;
    uint32 m_uiBoulderTimer;
    uint32 m_uiTrashTimer;


    void Reset()
    {
        m_uiFearTimer = 10000;
        m_uiBoulderTimer = 8000;
        m_uiTrashTimer = 17000;
    }

    void JustDied(Unit* pKiller)
    {
        m_uiPhase = 3;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFearTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_FEAR, true);

            m_uiFearTimer = 10000;
        }else m_uiFearTimer -= uiDiff;

        if (m_uiBoulderTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_BOULDER, true);

            m_uiBoulderTimer = 8000;
        }else m_uiBoulderTimer -= uiDiff;

        if (m_uiTrashTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(),SPELL_TRASH, true);

            m_uiTrashTimer = 17000;
        }else m_uiTrashTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## oculus_boss_ragnaros
######*/

#define SPELL_LEGION_FLAME			66197	
#define SPELL_FEL_LIGHTNING			46479
#define SPELL_BURNING_SPRAY			66902
#define SPELL_RAIN_FIRE				39024

#define SAY_KILL                    -1409017
#define SAY_MAGMABURST              -1409018


struct MANGOS_DLL_DECL oculus_boss_ragnarosAI : public ScriptedAI
{
    oculus_boss_ragnarosAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiLegionFlameTimmer;
    uint32 m_uiFelLightningTimer;
    uint32 m_uiBurningSprayTimer;
	uint32 m_uiRainFireTimer;

    void Reset()
    {
        m_creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_FIRE, true);
        m_uiLegionFlameTimmer = 15000;
        m_uiFelLightningTimer = 11000;
        m_uiBurningSprayTimer = 23000;
		m_uiRainFireTimer = 8000;
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }

    void JustDied(Unit* pKiller)
    {
        m_uiPhase = 2;
    }

    void EnterCombat(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiRainFireTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_RAIN_FIRE, true);

            m_uiRainFireTimer = 8000;
        }
        else 
            m_uiRainFireTimer -= uiDiff;

        if (m_uiLegionFlameTimmer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_LEGION_FLAME, true);

            m_uiLegionFlameTimmer = 15000;
        }
        else 
            m_uiLegionFlameTimmer -= uiDiff;

        if (m_uiFelLightningTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_FEL_LIGHTNING, true);

            m_uiFelLightningTimer = 11000;
        }
        else 
            m_uiFelLightningTimer -= uiDiff;

        if (m_uiBurningSprayTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_BURNING_SPRAY, true);
            DoScriptText(SAY_MAGMABURST, m_creature);

            m_uiBurningSprayTimer = 23000;
        }else m_uiBurningSprayTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};


/*######
## Oramus PHASE 5 TRIGGER
######*/


struct MANGOS_DLL_DECL oculus_boss_phase5_triggerAI : public ScriptedAI
{
    oculus_boss_phase5_triggerAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if(!pWho)
            return;

        if(pWho->GetTypeId() != TYPEID_PLAYER)
            return;

        if(m_creature->IsWithinDistInMap(pWho, 2))
        {
            m_uiPhase = 5;
            m_creature->ForcedDespawn();
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_oculus_boss_oramus(Creature* pCreature)
{
    return new oculus_boss_oramusAI(pCreature);
}


CreatureAI* GetAI_oculus_boss_ragnaros(Creature* pCreature)
{
    return new oculus_boss_ragnarosAI(pCreature);
}

CreatureAI* GetAI_oculus_boss_theradras(Creature* pCreature)
{
    return new oculus_boss_theradrasAI(pCreature);
}

CreatureAI* GetAI_oculus_boss_hakkar(Creature* pCreature)
{
    return new oculus_boss_hakkarAI(pCreature);
}

CreatureAI* GetAI_oculus_boss_phase5_trigger(Creature* pCreature)
{
    return new oculus_boss_phase5_triggerAI(pCreature);
}

CreatureAI* GetAI_oculus_boss_santa(Creature* pCreature)
{
    return new oculus_boss_santaAI(pCreature);
}

CreatureAI* GetAI_oculus_arcane_sphere(Creature* pCreature)
{
    return new oculus_arcane_sphereAI(pCreature);
}

void AddSC_oculus_boss()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_boss_oramus";
    newscript->GetAI = &GetAI_oculus_boss_oramus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_boss_ragnaros";
    newscript->GetAI = &GetAI_oculus_boss_ragnaros;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_boss_theradras";
    newscript->GetAI = &GetAI_oculus_boss_theradras;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_boss_hakkar";
    newscript->GetAI = &GetAI_oculus_boss_hakkar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_boss_phase5_trigger";
    newscript->GetAI = &GetAI_oculus_boss_phase5_trigger;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_boss_santa";
    newscript->GetAI = &GetAI_oculus_boss_santa;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_arcane_sphere";
    newscript->GetAI = &GetAI_oculus_arcane_sphere;
    newscript->RegisterSelf();
}