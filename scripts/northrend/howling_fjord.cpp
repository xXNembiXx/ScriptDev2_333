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
SDName: Howling_Fjord
SD%Complete: ?
SDComment: Quest support: 11221, 11483, 11317, 11322
SDCategory: Howling Fjord
EndScriptData */

#include "precompiled.h"

/*#######################
## Deathstalker Razael ##
#######################*/

#define GOSSIP_ITEM_DEATHSTALKER_RAZAEL "Hochexekutor Anselm verlangt einen Bericht über die Situation."

enum
{
    QUEST_REPORTS_FROM_THE_FIELD       = 11221,
    SPELL_RAZAEL_KILL_CREDIT           = 42756,
    GOSSIP_TEXTID_DEATHSTALKER_RAZAEL1 = 11562,
    GOSSIP_TEXTID_DEATHSTALKER_RAZAEL2 = 11564
};

bool GossipHello_npc_deathstalker_razael(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_REPORTS_FROM_THE_FIELD) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEATHSTALKER_RAZAEL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEATHSTALKER_RAZAEL1, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_deathstalker_razael(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEATHSTALKER_RAZAEL2, pCreature->GetGUID());
            pCreature->CastSpell(pPlayer, SPELL_RAZAEL_KILL_CREDIT, true);
            break;
    }

    return true;
}

/*#####################
## Dark Ranger Lyana ##
#####################*/

#define GOSSIP_ITEM_DARK_RANGER_LYANA "Hochexekutor Anselm erbittet Euren Bericht."

enum
{
    GOSSIP_TEXTID_DARK_RANGER_LYANA1    = 11586,
    GOSSIP_TEXTID_DARK_RANGER_LYANA2    = 11588,
    SPELL_DARK_RANGER_LYANA_KILL_CREDIT = 42799
};

bool GossipHello_npc_dark_ranger_lyana(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_REPORTS_FROM_THE_FIELD) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DARK_RANGER_LYANA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DARK_RANGER_LYANA1, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_dark_ranger_lyana(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DARK_RANGER_LYANA2, pCreature->GetGUID());
            pCreature->CastSpell(pPlayer, SPELL_DARK_RANGER_LYANA_KILL_CREDIT, true);
            break;
    }

    return true;
}

/*############
## McGoyver ##
############*/

#define GOSSIP_ITEM_MCGOYVER1 "Walt hat mich geschickt, um ein paar Dunkeleisenblöcke abzuholen."
#define GOSSIP_ITEM_MCGOYVER2 "Jarp."

enum
{
    QUEST_WE_CAN_REBUILD_IT                = 11483,
    GOSSIP_TEXTID_MCGOYVER                 = 12193,
    ITEM_DARK_IRON_INGOTS                  = 34135,
    SPELL_MCGOYVER_TAXI_EXPLORERSLEAGUE    = 44280,
    SPELL_MCGOYVER_CREATE_DARK_IRON_INGOTS = 44512
};

bool GossipHello_npc_mcgoyver(Player* pPlayer, Creature* pCreature)
{
    switch(pPlayer->GetQuestStatus(QUEST_WE_CAN_REBUILD_IT))
    {
        case QUEST_STATUS_INCOMPLETE:
            if (!pPlayer->HasItemCount(ITEM_DARK_IRON_INGOTS, 1, true))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            }
            else
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_MCGOYVER, pCreature->GetGUID());
            }
            break;
        case QUEST_STATUS_COMPLETE:
            if (!pPlayer->GetQuestRewardStatus(QUEST_WE_CAN_REBUILD_IT))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_MCGOYVER, pCreature->GetGUID());
                break;
            }
        default:
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }

    return true;
}

bool GossipSelect_npc_mcgoyver(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pCreature->CastSpell(pPlayer, SPELL_MCGOYVER_CREATE_DARK_IRON_INGOTS, true);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_MCGOYVER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_MCGOYVER, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, SPELL_MCGOYVER_TAXI_EXPLORERSLEAGUE, true);
            break;
    }

    return true;
}

/*####################
## YourInnerTurmoil ##
####################*/

enum
{
	SAY_SUMMON_1			= -2500001,
	SAY_SUMMON_2			= -2500002,
	SAY_LOW_HEALTH			= -2500003,
	SAY_DEATH				= -2500004,

	SPELL_SLOW_FALL			=	50238
};

struct MANGOS_DLL_DECL npc_your_inner_turmoilAI : public ScriptedAI
{
	npc_your_inner_turmoilAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		Reset();
	}

	bool m_bSaySummon;
	bool m_bSaySummon2;
	bool m_bSayLowHealth;

	uint32 m_uiSaySummon2Timer;

	void Reset()
	{
		m_bSaySummon = true;
		m_bSaySummon2 = true;
		m_bSayLowHealth = true;

		uint32 m_uiSaySummon2Timer = 2000;
	}

	void JustDied(Unit* pKiller)
	{
		DoScriptText(SAY_DEATH, m_creature);

		if(pKiller)
		{
			if(pKiller->GetTypeId() == TYPEID_PLAYER)
				m_creature->CastSpell(pKiller, SPELL_SLOW_FALL, true);
		}
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if(!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;
		
		if(m_bSaySummon)
		{
			DoScriptText(SAY_SUMMON_1, m_creature);
			m_bSaySummon = false;
		}
		
		if(m_bSaySummon2)
		{
			if(m_uiSaySummon2Timer < uiDiff)
			{
				DoScriptText(SAY_SUMMON_2, m_creature);
				m_bSaySummon2 = false;
			}
			else
				m_uiSaySummon2Timer -= uiDiff;
		}
		
		if(m_creature->GetHealthPercent() <= 50.0f && m_bSayLowHealth)
		{
			DoScriptText(SAY_LOW_HEALTH, m_creature);
			m_bSayLowHealth = false;
		}

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_npc_your_inner_turmoil(Creature* pCreature)
{
	return new npc_your_inner_turmoilAI(pCreature);
}

void AddSC_howling_fjord()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_deathstalker_razael";
    newscript->pGossipHello = &GossipHello_npc_deathstalker_razael;
    newscript->pGossipSelect = &GossipSelect_npc_deathstalker_razael;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_dark_ranger_lyana";
    newscript->pGossipHello = &GossipHello_npc_dark_ranger_lyana;
    newscript->pGossipSelect = &GossipSelect_npc_dark_ranger_lyana;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_mcgoyver";
    newscript->pGossipHello = &GossipHello_npc_mcgoyver;
    newscript->pGossipSelect = &GossipSelect_npc_mcgoyver;
    newscript->RegisterSelf();
	
	newscript = new Script;
	newscript->Name = "npc_your_inner_turmoil";
	newscript->GetAI = &GetAI_npc_your_inner_turmoil;
	newscript->RegisterSelf();
}
