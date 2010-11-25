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


	uint16 m_uiPhase;

/*######
## oculus_boss_oramus
######*/

#define THE_OCULUS				578
#define SPELL_FLAME_BREATH		18435

#define START1					-2500130
#define START2					-2500131
#define START3					-2500132
#define START4					-2500133
#define START5					-2500134
#define SECOND					-2500135
#define THIRD					-2500136
#define FOURTH					-2500137					





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
	{1152.091187f, 1147.081421f, 545.351807f}, // 3 to Hakkar
	{1105.163574f, 1059.876343f, 510.849365f}, // 4 to the Middle
	{1108.812012f, 1040.247070f, 607.637421f}, // 5 to the Top
	//Player Teleports
	{1048.228760f, 925.094055f, 438.941345f},  // 6
	{986.237976f, 997.005432f, 526.810974f},   // 7
	{1126.063843f, 1178.769653f, 526.811707f}, // 8
	{1065.169922f, 1046.453613f, 602.709045f}, // 9
	{1110.735962f, 1087.392578f, 508.361786f}  // 10
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
	uint32 m_uiSay4Timer;
	uint32 m_uiSay4Point;
	uint32 m_uiSay5Timer;
	uint32 m_uiSay5Point;


    void Reset()
    {
       m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
       m_creature->SetStandState(UNIT_STAND_STATE_SLEEP);

	   m_uiPhase = 1;
	   m_uiSayTimer = 1000;
	   m_uiSayPoint = 0;
	   m_uiSay2Timer = 3000;
	   m_uiSay2Point = 0;
	   m_uiSay3Timer = 3000;
	   m_uiSay3Point = 0;
	   m_uiSay4Timer = 3000;
	   m_uiSay4Point = 0;
	   m_uiSay5Timer = 1000;
	   m_uiSay5Point = 0;


	   m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);

	   m_creature->GetMotionMaster()->MoveTargetedHome();

    }

    void JustDied(Unit* pKiller)
    {
    }

    void EnterCombat(Unit* pWho)
    {
	   if(Creature* pRagnaros = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_RAGNAROS)))
			pRagnaros->Respawn();
	   if(Creature* pTheradras = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_THERADRAS)))
			pTheradras->Respawn();
	   if(Creature* pHakkar = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_HAKKAR)))
			pHakkar->Respawn();

	   if(Creature* pRagnaros = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_RAGNAROS)))
			pRagnaros->SetPhaseMask(1, true);
	   if(Creature* pTheradras = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_THERADRAS)))
			pTheradras->SetPhaseMask(1, true);
	   if(Creature* pHakkar = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_HAKKAR)))
			pHakkar->SetPhaseMask(1, true);

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
				// must be initialized here... 
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

		if (m_uiPhase == 2)
		{
			if(m_uiSay2Timer <= uiDiff)
			{
				// must be initialized here... 
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

		if (m_uiPhase == 3)
		{
			if(m_uiSay3Timer <= uiDiff)
			{
				// must be initialized here... 
				Map* pMap3 = NULL;
				switch(m_uiSay3Point)
				{
					case 0:
						DoScriptText(THIRD, m_creature);
						m_uiSay3Timer = 5000;
						break;
					case 1:
						m_creature->MonsterMove(WayPoints[3].x, WayPoints[3].y, WayPoints[3].z, 2000);
						Map* pMap3 = m_creature->GetMap();
						if (pMap3 && pMap3->IsDungeon())
						{
							Map::PlayerList const &players3 = pMap3->GetPlayers();
							for (Map::PlayerList::const_iterator itr = players3.begin(); itr != players3.end(); ++itr)
								itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[8].x, WayPoints[8].y, WayPoints[8].z, 0.058313f);
						}
						m_uiSay3Timer = 3000;
						break;
				}m_uiSay3Point++;
			}else m_uiSay3Timer -= uiDiff;
		}

		if (m_uiPhase == 4)
		{
			if(m_uiSay4Timer <= uiDiff)
			{
				// must be initialized here... 
				Map* pMap4 = NULL;
				switch(m_uiSay4Point)
				{
					case 0:
						DoScriptText(FOURTH, m_creature);
						m_uiSay4Timer = 5000;
						break;
					case 1:
						m_uiPhase = 5;
						m_creature->MonsterMove(WayPoints[4].x, WayPoints[4].y, WayPoints[4].z, 1000);
						m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
						Map* pMap4 = m_creature->GetMap();
						if (pMap4 && pMap4->IsDungeon())
						{
							Map::PlayerList const &players4 = pMap4->GetPlayers();
							for (Map::PlayerList::const_iterator itr = players4.begin(); itr != players4.end(); ++itr)
								itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[10].x, WayPoints[10].y, WayPoints[10].z, 4.274161f);
						}
						m_uiSay4Timer = 1000;
						break;
				}m_uiSay4Point++;
			}else m_uiSay4Timer -= uiDiff;
		}

		if (m_uiPhase == 5)
		{
			if(m_uiSay5Timer <= uiDiff)
			{
				// must be initialized here... 
				Map* pMap5 = NULL;
				switch(m_uiSay5Point)
				{
				case 0:
					m_creature->MonsterMove(WayPoints[5].x, WayPoints[5].y, WayPoints[5].z, 2000);
					m_uiSay5Timer = 1000;
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
        DoMeleeAttackIfReady();
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
		m_uiPhase = 4;
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

    void Reset()
    {
		m_creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_FIRE, true);
        m_uiLegionFlameTimmer = 15000;
		m_uiFelLightningTimer = 11000;
		m_uiBurningSprayTimer = 23000;
	}

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
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
}