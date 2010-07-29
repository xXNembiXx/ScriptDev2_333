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
SDName: Bloodmyst_Isle
SD%Complete: 80
SDComment: Quest support: 9670, 9711, 9756(gossip items text needed).
SDCategory: Bloodmyst Isle
EndScriptData */

/* ContentData
mob_webbed_creature
npc_captured_sunhawk_agent
npc_tracker_of_the_hand
item_flare_gun
npc_vindicator_kuros
EndContentData */

#include "precompiled.h"

/*######
## mob_webbed_creature
######*/

//possible creatures to be spawned
const uint32 possibleSpawns[32] = {17322, 17661, 17496, 17522, 17340, 17352, 17333, 17524, 17654, 17348, 17339, 17345, 17359, 17353, 17336, 17550, 17330, 17701, 17321, 17680, 17325, 17320, 17683, 17342, 17715, 17334, 17341, 17338, 17337, 17346, 17344, 17327};

struct MANGOS_DLL_DECL mob_webbed_creatureAI : public ScriptedAI
{
    mob_webbed_creatureAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset()
    {
    }

    void JustDied(Unit* Killer)
    {
        uint32 spawnCreatureID = 0;

        switch(urand(0, 2))
        {
            case 0:
                spawnCreatureID = 17681;
                if (Killer->GetTypeId() == TYPEID_PLAYER)
                    ((Player*)Killer)->KilledMonsterCredit(spawnCreatureID, m_creature->GetGUID());
                break;
            case 1:
            case 2:
                spawnCreatureID = possibleSpawns[urand(0, 31)];
                break;
        }

        if (spawnCreatureID)
            m_creature->SummonCreature(spawnCreatureID, 0.0f, 0.0f, 0.0f, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
    }
};
CreatureAI* GetAI_mob_webbed_creature(Creature* pCreature)
{
    return new mob_webbed_creatureAI(pCreature);
}

/*######
## npc_captured_sunhawk_agent
######*/

#define C_SUNHAWK_TRIGGER 17974

bool GossipHello_npc_captured_sunhawk_agent(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasAura(31609, EFFECT_INDEX_1) && pPlayer->GetQuestStatus(9756) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich bin ein Gefangener, was denn sonst? Der Draeneiabschaum hat mich gefangengenommen, als ich das Sonnentor verließ. Anschließend töteten sie unsere Portalaufseher und zerstörten das Tor. Der Sonnenkönig wird von dieser Wendung der Ergebnisse nicht begeistert sein.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(9136, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(9134, pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_captured_sunhawk_agent(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ah ja, Sironas. Ich hätte beinahe vergessen, dass sie dort war. In der Scherbenwelt diente ich unter Sironas. Allerdings hatte ich keine Ahnung von der Existenz ihrer Monstrosität; Ich war noch nicht vollständig auf dieser Welt materialisiert, da nahmen mich diese verdammten Draenei schon gefangen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(9137, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Unglaublich. Wie ist Sironas etwas Derartiges gelungen?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(9138, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Sironas ist eine Eredar... Ich meine, ja, offensichtlich.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(9139, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Die Vektorspule ist gigantisch. Ich hoffe, wir verfügen über mehr als eine Monstrosität, um die zahlreichen Schwachpunkte zu bewachen.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(9140, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Das habe ich getan und Ihr habt mir geglaubt. Vielen Dank für die Informationen, Blutelf. Ihr habt uns weit mehr geholfen, als Ihr es für möglich haltet.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(9141, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TalkedToCreature(C_SUNHAWK_TRIGGER, pCreature->GetGUID());
            break;
    }
    return true;
}

/*#######
#npc_tracker_of_the_hand
#######*/

enum
{
	TRACKER_OF_THE_HAND_SAY_1	=	-1055000,
	MATIS_SAY					=	-1055001,
	TRACKER_OF_THE_HAND_SAY_2	=	-1055002,
	NPC_MATIS_THE_CRUEL			=	17664,
	QUEST_MATIS_THE_CRUEL		=	9711
};

struct MANGOS_DLL_DECL npc_tracker_of_the_handAI : public ScriptedAI
{
	npc_tracker_of_the_handAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 m_uiLifeTimer;
	uint32 m_uiPhase;
	Creature* pMatis;
	uint32 matisFaction;
	Player* pPlayer;
	uint32 playerGUID;

	void Reset()
	{
		playerGUID =0;
		m_uiPhase=1;
		m_uiLifeTimer = 300000;
	}

	void setPlayer(Player* newOwner)
	{
		pPlayer = newOwner;
	}

	void UpdateAI(const uint32 uiDiff)
	{
		switch (m_uiPhase)
		{	
			case 1:
				if (!m_creature->SelectHostileTarget())
				{
					if (m_uiLifeTimer >= uiDiff)
					{
						m_uiLifeTimer -= uiDiff;
					}
				
					if (pMatis=GetClosestCreatureWithEntry(m_creature, NPC_MATIS_THE_CRUEL, 100.0f))
					{
						matisFaction = pMatis->getFaction();
						m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
						m_creature->Attack(pMatis, true);
						m_uiPhase=2;	
					}
					else
						return;
				}
				break;
			case 2:
				if ((pMatis->GetHealth()*100 / pMatis->GetMaxHealth()) < 50)
				{
					pMatis->setFaction(35);
					m_creature->setFaction(35);
					pMatis->DeleteThreatList();
                    pMatis->CombatStop(true);
                    pMatis->AttackStop();
					m_creature->DeleteThreatList();
					m_creature->CombatStop(true);
					m_creature->AttackStop();
					DoScriptText(TRACKER_OF_THE_HAND_SAY_1, m_creature);
					m_uiLifeTimer =5000;
					m_uiPhase=3;
				}
				else
					DoMeleeAttackIfReady();
				break;
			case 3:
				if (m_uiLifeTimer >= uiDiff)
				{
					m_uiLifeTimer -= uiDiff;
					return;
				}
				DoScriptText(MATIS_SAY, pMatis);
				m_uiLifeTimer =5000;
				m_uiPhase=4;
				break;
			case 4:
				if (m_uiLifeTimer >= uiDiff)
				{
					m_uiLifeTimer -= uiDiff;
					return;
				}
				DoScriptText(TRACKER_OF_THE_HAND_SAY_2, m_creature);
				m_uiLifeTimer =7000;
				m_uiPhase=5;
				break;
			case 5:
				if (m_uiLifeTimer >= uiDiff)
				{
					m_uiLifeTimer -= uiDiff;
					return;
				}
				pPlayer->GroupEventHappens(QUEST_MATIS_THE_CRUEL,pMatis);
				pMatis->setFaction(matisFaction);

				pMatis->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNT);
				//pMatis->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				pMatis->setDeathState(JUST_DIED); 
				pMatis->RemoveCorpse();
				m_creature->setDeathState(JUST_DIED);
				m_creature->RemoveCorpse();
				break;
		}
	}
};

CreatureAI* GetAI_npc_tracker_of_the_hand(Creature* pCreature)
{
    return new  npc_tracker_of_the_handAI(pCreature);
}

/*#######
#item_flare_gun
#######*/

bool ItemItem_Flare_Gun(Player *pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
	if (GetClosestCreatureWithEntry(pPlayer, NPC_MATIS_THE_CRUEL, 30.0f)){
		Creature* pTracker=pPlayer->SummonCreature(17853,pPlayer->GetPositionX(),pPlayer->GetPositionY(),pPlayer->GetPositionZ(),0, TEMPSUMMON_CORPSE_DESPAWN, 3000000);
		if (npc_tracker_of_the_handAI* pTrackerAI = dynamic_cast<npc_tracker_of_the_handAI*>(pTracker->AI()))
		{
			pTrackerAI->setPlayer(pPlayer);
			pPlayer->DestroyItemCount(pItem->GetEntry(),1,true,false);
		}
	}
	else
	{
		 pPlayer->GetSession()->SendAreaTriggerMessage("Kann hier nicht verwendet werden");
		 return false;
	}
	return true;
};

/*#######
#npc_vindicator_kuros
#######*/

enum
{
	NPC_VELEN_IMAGE				= 17874,
	NPC_BLADE_OF_ARGUS			= 17659,
	NPC_MATIS					= 17865,
	SPELL_HAMMER_OF_VINDICATION	= 31008,
	VELEN_IMAGE_1				= -1055005,
	VELEN_IMAGE_2				= -1055006,
	VELEN_IMAGE_3				= -1055007,
	VELEN_IMAGE_4				= -1055008,
	MATIS_JUDGED_1				= -1055009,
	MATIS_JUDGED_2				= -1055010,
	MATIS_JUDGED_3				= -1055011,
	VINDICATOR_KUROS_1			= -1055012,
	MATIS_JUDGED_4				= -1055013,
	VELEN_IMAGE_5				= -1055014,
	BLADE_OF_ARGUS				= -1055015,
	MATIS_JUDGED_5				= -1055016,
	VINDICATOR_KUROS_2			= -1055017,
	VELEN_IMAGE_6				= -1055018
};

struct MANGOS_DLL_DECL npc_vindicator_kurosAI : public ScriptedAI
{
	npc_vindicator_kurosAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	bool MatisCompleteEvent;
	uint32 m_uiLifeTimer;
	uint32 m_uiEventPhase;
	Creature* pVelenImage;
	Creature* pMatis;
	Creature* pBladeOfArgus;

	float x,y,z,o;

	void Reset()
	{
		MatisCompleteEvent =false;
		m_uiLifeTimer=0;
		m_uiEventPhase=0;
	}

	void StartMatisEvent(Creature* VelenImage, Creature* Matis, Creature* BladeOfArgus)
	{
		pVelenImage = VelenImage;
		pMatis = Matis;
		pMatis->setFaction(35);
		pBladeOfArgus = BladeOfArgus;
		pBladeOfArgus->setFaction(35);
		MatisCompleteEvent=true;
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (MatisCompleteEvent)
		{
			if (m_uiLifeTimer >= uiDiff)
			{
				m_uiLifeTimer -= uiDiff;
				return;
			}
			switch(m_uiEventPhase)
			{
				case 0: 
					m_uiEventPhase=1;
					x = m_creature->GetPositionX();
					y = m_creature->GetPositionY();
					z = m_creature->GetPositionZ();
					o = m_creature->GetOrientation();
					break;
				case 1:
					DoScriptText(VELEN_IMAGE_1,pVelenImage);
					pMatis->GetMotionMaster()->MovePoint(pMatis->GetGUID(), -1956.00f,-11886.00f,49.2f);
					pBladeOfArgus->GetMotionMaster()->MovePoint(pBladeOfArgus->GetGUID(),-1951.19f,-11885.34f, 49.895f);
					m_uiLifeTimer =15000;
					m_uiEventPhase=2;
					break;
				case 2:
					pMatis->SetFacingToObject(pVelenImage);
					pBladeOfArgus->SetFacingToObject(pVelenImage);
					DoScriptText(VELEN_IMAGE_2,pVelenImage);
					m_uiLifeTimer =6000;
					m_uiEventPhase=3;
					break;
				case 3:
					DoScriptText(VELEN_IMAGE_3,pVelenImage);
					m_uiLifeTimer =6000;
					m_uiEventPhase=4;
					break;
				case 4:
					pMatis->MonsterTextEmote("Matis spits at the image of Velen.",pVelenImage->GetGUID());
					DoScriptText(VELEN_IMAGE_4,pVelenImage);
					m_uiLifeTimer =6000;
					m_uiEventPhase=5;
					break;
				case 5:
					//Matis glares at Image?
					DoScriptText(MATIS_JUDGED_1,pMatis);
					m_uiLifeTimer =6000;
					m_uiEventPhase=6;
					break;
				case 6:
					//Matis laughes
					pMatis->MonsterTextEmote("Matis laughs.",pVelenImage->GetGUID());
					DoScriptText(MATIS_JUDGED_2,pMatis);
					m_uiLifeTimer =8000;
					m_uiEventPhase=7;
					break;
				case 7:
					DoScriptText(MATIS_JUDGED_3,pMatis);
					m_uiLifeTimer =10000;
					m_uiEventPhase=8;
					break;
				case 8:
					DoScriptText(VINDICATOR_KUROS_1,m_creature);
					m_uiLifeTimer =8000;
					m_uiEventPhase=9;
					break;
				case 9:
					//DoScriptText(VINDICATOR_KUROS_1,m_creature);
					m_uiLifeTimer =8000;
					m_uiEventPhase=10;
					break;
				case 10:
					DoScriptText(MATIS_JUDGED_4,pMatis);
					m_uiLifeTimer =18000;
					m_uiEventPhase=11;
					break;
				case 11:
					DoScriptText(VELEN_IMAGE_5,pVelenImage);
					m_uiLifeTimer =8000;
					m_uiEventPhase=12;
					break;
				case 12:
					//blade of argus step forward
					pBladeOfArgus->GetMotionMaster()->MovePoint(pBladeOfArgus->GetGUID(), -1955.67f,-11886.42f,49.27f);
					DoScriptText(BLADE_OF_ARGUS,pBladeOfArgus);
					m_uiLifeTimer =6000;
					m_uiEventPhase=13;
					break;
				case 13:
					//Matis walks back and stops on half the way
					pMatis->GetMotionMaster()->MovePoint(pMatis->GetGUID(), -1951.33f,-11876.004f,50.32f);
					m_uiLifeTimer =8000;
					m_uiEventPhase=14;
					break;
				case 14:
					pMatis->SetFacingToObject(pVelenImage);
					DoScriptText(MATIS_JUDGED_5,pMatis);
					m_uiLifeTimer =10000;
					m_uiEventPhase=15;
					break;
				case 15:
					DoScriptText(VINDICATOR_KUROS_2,m_creature);
					m_creature->GetMotionMaster()->MovePoint(m_creature->GetGUID(),-1953.42f,-11880.19f,49.79f);
					
					m_uiLifeTimer =6000;
					m_uiEventPhase=16;
					break;
				case 16:
					m_creature->CastSpell(pMatis,SPELL_HAMMER_OF_VINDICATION,false); 
					m_creature->MonsterTextEmote("Vindicator Kuros spits on the corpse of Matis.",pMatis->GetGUID());
					m_uiLifeTimer =6000;
					m_uiEventPhase=17;
					break;
				case 17:
					DoScriptText(VELEN_IMAGE_6,pVelenImage);
					m_uiLifeTimer =8000;
					m_uiEventPhase=18;
					break;
				case 18:
					//Fade image, remove corpses etc, matis despawns after the kill, no remove needed here
					pMatis->setDeathState(JUST_DIED);
					pMatis->RemoveCorpse();
					pBladeOfArgus->setDeathState(JUST_DIED);
					pBladeOfArgus->RemoveCorpse();
					pVelenImage->setDeathState(JUST_DIED); 
					pVelenImage->RemoveCorpse();
					m_uiLifeTimer =6000;
					m_uiEventPhase=0;
					MatisCompleteEvent=false;
					m_creature->GetMotionMaster()->MoveTargetedHome();
					Reset();
					break;
			}
		}
	}
};

bool QuestComplete_npc_vindicator_kuros(Player* pPlayer, Creature* pCreature, const Quest* pQuest, uint32 item)
{
	if (pQuest->GetQuestId() != QUEST_MATIS_THE_CRUEL)
		return true;

	if (Creature* pMatis=pCreature->SummonCreature(NPC_MATIS,-1939.11f,-11848.7f,51.4f,4.41f,TEMPSUMMON_DEAD_DESPAWN,150000))
	{	
		if (Creature* pBladeOfArgus=pCreature->SummonCreature(NPC_BLADE_OF_ARGUS,-1937.56f,-11852.5f,51.5f,4.1f,TEMPSUMMON_CORPSE_DESPAWN,150000))
		{
			if (Creature* pVelenImage = pCreature->SummonCreature(NPC_VELEN_IMAGE,-1959.74f,-11886.9f,50.7536f,0.841101f,TEMPSUMMON_CORPSE_DESPAWN,150000))
			{
				if (npc_vindicator_kurosAI* pKurosAI = dynamic_cast<npc_vindicator_kurosAI*>(pCreature->AI()))
				{  
					if (!pKurosAI->MatisCompleteEvent)
						pKurosAI->StartMatisEvent(pVelenImage,pMatis,pBladeOfArgus);
					return true;
				}
			}
		}
	}
	return true;
}

CreatureAI* GetAI_npc_vindicator_kuros(Creature* pCreature)
{
    return new  npc_vindicator_kurosAI(pCreature);
}

void AddSC_bloodmyst_isle()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mob_webbed_creature";
    newscript->GetAI = &GetAI_mob_webbed_creature;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_captured_sunhawk_agent";
    newscript->pGossipHello =  &GossipHello_npc_captured_sunhawk_agent;
    newscript->pGossipSelect = &GossipSelect_npc_captured_sunhawk_agent;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_tracker_of_the_hand";
    newscript->GetAI = &GetAI_npc_tracker_of_the_hand;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "item_flare_gun";
	newscript->pItemUse = &ItemItem_Flare_Gun;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_vindicator_kuros";
    newscript->GetAI = &GetAI_npc_vindicator_kuros;
	newscript->pChooseReward = &QuestComplete_npc_vindicator_kuros;
    newscript->RegisterSelf();
}
