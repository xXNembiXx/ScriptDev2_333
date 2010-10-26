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
	{900.000f, 1300.000f, 453.000f} // 11
};

enum
{
	SPELL_SHADOW_PRISION	= 40647
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
							Map::PlayerList const &lPlayers = pMap->GetPlayers();
							for(Map::PlayerList::const_iterator iter = lPlayers.begin(); iter != lPlayers.end(); ++iter)
							{
								DoScriptText(EVENT11, iter->getSource());
							}
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
						// TODO: spawn the first bastard
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
}