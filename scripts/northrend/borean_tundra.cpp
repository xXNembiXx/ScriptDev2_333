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
SDName: Borean_Tundra
SD%Complete: 100
SDComment: Quest support: 11708, 11692, 11608, 11881, 11961. Taxi vendors. 11570
SDCategory: Borean Tundra
EndScriptData */

/* ContentData
npc_fizzcrank_fullthrottle
npc_iruk
npc_kara_thricestar
npc_surristrasz
npc_tiare
npc_lurgglbr
npc_fezzix_geartwist
npc_nerubar_sinkhole
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_fizzcrank_fullthrottle
######*/

#define GOSSIP_ITEM_GO_ON   "Weiter."
#define GOSSIP_ITEM_TELL_ME "Erzähl mir, was hier vor sich geht, Kurbelzisch."

enum
{
    GOSSIP_TEXTID_FIZZCRANK1    = 12456,
    GOSSIP_TEXTID_FIZZCRANK2    = 12457,
    GOSSIP_TEXTID_FIZZCRANK3    = 12458,
    GOSSIP_TEXTID_FIZZCRANK4    = 12459,
    GOSSIP_TEXTID_FIZZCRANK5    = 12460,
    GOSSIP_TEXTID_FIZZCRANK6    = 12461,
    GOSSIP_TEXTID_FIZZCRANK7    = 12462,
    GOSSIP_TEXTID_FIZZCRANK8    = 12463,
    GOSSIP_TEXTID_FIZZCRANK9    = 12464,

    QUEST_THE_MECHAGNOMES       = 11708
};

bool GossipHello_npc_fizzcrank_fullthrottle(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_MECHAGNOMES) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELL_ME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_fizzcrank_fullthrottle(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK3, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK4, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK5, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK6, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK7, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GO_ON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK8, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FIZZCRANK9, pCreature->GetGUID());
            pPlayer->AreaExploredOrEventHappens(QUEST_THE_MECHAGNOMES);
            break;
    }
    return true;
}

/*######
## npc_iruk
######*/

#define GOSSIP_ITEM_IRUK        "<Durchsucht die Leiche nach Issliruks Totem.>"

enum
{
    QUEST_SPIRITS_WATCH_OVER_US     = 11961,
    SPELL_CREATE_TOTEM              = 46816
};

bool GossipHello_npc_iruk(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_SPIRITS_WATCH_OVER_US) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_IRUK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_iruk(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer,SPELL_CREATE_TOTEM,true);
    }

    return true;
}

/*######
## npc_kara_thricestar
######*/

#define GOSSIP_ITEM_THRICESTAR1      "Glaubt Ihr, ich könnte eine dieser Flugmaschinen benutzen?"
#define GOSSIP_ITEM_THRICESTAR2      "Kara, Ich muss zu den Höhlen des Todes ausgeflogen werden, um Bixie zu finden."

enum
{
    QUEST_CHECK_IN_WITH_BIXIE       = 11692,
    SPELL_FIZZCRANK_AIRSTRIP        = 51446
};

bool GossipHello_npc_kara_thricestar(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isTaxi())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_ITEM_THRICESTAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    if (pPlayer->GetQuestStatus(QUEST_CHECK_IN_WITH_BIXIE) == QUEST_STATUS_COMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THRICESTAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_kara_thricestar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->GetSession()->SendTaxiMenu(pCreature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer, SPELL_FIZZCRANK_AIRSTRIP, false);
            break;
    }

    return true;
}

/*######
## npc_surristrasz
######*/

#define GOSSIP_ITEM_FREE_FLIGHT "Ich möchte Durchgang zum Titusschild."
#define GOSSIP_ITEM_FLIGHT      "Darf ich den Drachen benutzen, um woanders hinzufliegen?"

enum
{
    SPELL_ABMER_TO_COLDARRA     = 46064
};

bool GossipHello_npc_surristrasz(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isTaxi())
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FREE_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_GOSSIP);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_ITEM_FLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_TAXIVENDOR);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_surristrasz(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_OPTION_GOSSIP)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        //TaxiPath 795 (amber to coldarra)
        pPlayer->CastSpell(pPlayer, SPELL_ABMER_TO_COLDARRA, true);
    }

    if (uiAction == GOSSIP_OPTION_TAXIVENDOR)
        pPlayer->GetSession()->SendTaxiMenu(pCreature);

    return true;
}

/*######
## npc_tiare
######*/

#define GOSSIP_ITEM_TELEPORT    "Teleportiert mich zum Bernsteinflöz, bitte."

enum
{
    SPELL_TELEPORT_COLDARRA     = 50135
};

bool GossipHello_npc_tiare(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TELEPORT, GOSSIP_SENDER_MAIN, GOSSIP_OPTION_GOSSIP);
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tiare(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_OPTION_GOSSIP)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, SPELL_TELEPORT_COLDARRA, true);
    }
    return true;
}

/*######
## npc_lurgglbr
######*/

enum
{
    QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS = 11570,
    GO_CAGE                             = 187369,

    SAY_START_1                         = -1000575,
    SAY_START_2                         = -1000576,
    SAY_END_1                           = -1000577,
    SAY_END_2                           = -1000578
};

struct MANGOS_DLL_DECL npc_lurgglbrAI : public npc_escortAI
{
    npc_lurgglbrAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_uiSayTimer = 0;
        m_uiSpeech = 0;
        Reset();
    }

    uint32 m_uiSayTimer;
    uint8 m_uiSpeech;

    void Reset()
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            m_uiSayTimer = 0;
            m_uiSpeech = 0;
        }
    }

    void JustStartedEscort()
    {
        if (GameObject* pCage = GetClosestGameObjectWithEntry(m_creature, GO_CAGE, INTERACTION_DISTANCE))
        {
            if (pCage->GetGoState() == GO_STATE_READY)
                pCage->Use(m_creature);
        }
    }

    void WaypointStart(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 1:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_START_2, m_creature, pPlayer);

                // Cage actually closes here, however it's normally determined by GO template and auto close time

                break;
        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    m_creature->SetFacingToObject(pPlayer);
                    DoScriptText(SAY_START_1, m_creature, pPlayer);
                }
                break;
            case 25:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    DoScriptText(SAY_END_1, m_creature, pPlayer);
                    m_uiSayTimer = 3000;
                }
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        {
            if (m_uiSayTimer)
            {
                if (m_uiSayTimer <= uiDiff)
                {
                    Player* pPlayer = GetPlayerForEscort();

                    if (!pPlayer)
                    {
                        m_uiSayTimer = 0;
                        return;
                    }

                    m_creature->SetFacingToObject(pPlayer);

                    switch(m_uiSpeech)
                    {
                        case 0:
                            DoScriptText(SAY_END_2, m_creature, pPlayer);
                            m_uiSayTimer = 3000;
                            break;
                        case 1:
                            pPlayer->GroupEventHappens(QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS, m_creature);
                            m_uiSayTimer = 0;
                            break;
                    }

                    ++m_uiSpeech;
                }
                else
                    m_uiSayTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_lurgglbr(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ESCAPE_FROM_WINTERFIN_CAVERNS)
    {
        if (npc_lurgglbrAI* pEscortAI = dynamic_cast<npc_lurgglbrAI*>(pCreature->AI()))
        {
            pCreature->setFaction(FACTION_ESCORT_N_NEUTRAL_PASSIVE);
            pEscortAI->Start(true, false, pPlayer->GetGUID(), pQuest);
        }
    }
    return true;
}

CreatureAI* GetAI_npc_lurgglbr(Creature* pCreature)
{
    return new npc_lurgglbrAI(pCreature);
}

/*######
## npc_fezzix_geartwist
######*/

struct MANGOS_DLL_DECL npc_fezzix_geartwistAI : public ScriptedAI
{
    npc_fezzix_geartwistAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset()
    {
    }

	void MoveInLineOfSight(Unit* pWho)
    {
        if (!pWho || pWho->GetEntry() != 25969)
            return;

        if (!m_creature->IsWithinDist(pWho, 5.0f))
            return;

        Player *pPlayer = pWho->GetCharmerOrOwnerPlayerOrPlayerItself();

		pPlayer->KilledMonsterCredit(pWho->GetEntry(),pWho->GetGUID());

		pWho->RemoveFromWorld();

        return;
    }

};

CreatureAI* GetAI_npc_fezzix_geartwist(Creature* pCreature)
{
    return new npc_fezzix_geartwistAI(pCreature);
}

/*######
## npc_nerubar_sinkhole
######*/

enum nerubar_sinkhole
{
	SPELL_SEAFORIUM_DEPTH_CHARGE_EXPLOSION	= 45502,	//spell doesn't effect Player
	SPELL_EXPLOSION_EFFECT					= 46419,	//find the right spell or fix first, this is only temp

	GO_RUBBLE								= 187669,

	NPC_SEAFORIUM_DEPTH_CHARGE				= 25401
};

struct MANGOS_DLL_DECL npc_nerubar_sinkholeAI : public ScriptedAI
{
    npc_nerubar_sinkholeAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 BombTimer;
	uint32 m_uiEventPhase;
	float x,y,z;

    void Reset()
    {
		BombTimer = urand(5000,10000);
		m_uiEventPhase = 1;
		x=y=z=0;
    }

	void UpdateAI(const uint32 diff)
	{
		Creature* pChargeBundle = m_creature->GetClosestCreatureWithEntry(m_creature,NPC_SEAFORIUM_DEPTH_CHARGE,20.0f);

		if(pChargeBundle)
		{
	        if (BombTimer < diff)
	        {
				pChargeBundle->CastSpell(pChargeBundle, SPELL_EXPLOSION_EFFECT, true);

				x = m_creature->GetPositionX();
				y = m_creature->GetPositionY();
				z = m_creature->GetPositionZ();
						
				pChargeBundle->CastSpell(pChargeBundle, SPELL_SEAFORIUM_DEPTH_CHARGE_EXPLOSION, true);
				
				m_creature->GetMotionMaster()->MoveTargetedHome();

				pChargeBundle->setDeathState(JUST_DIED);
				pChargeBundle->RemoveFromWorld();

				GameObject* pRubble = pChargeBundle->SummonGameobject(GO_RUBBLE, x, y, z, 0, 20000);
				pRubble->SetGoType(GAMEOBJECT_TYPE_GENERIC);
				
				Unit* pPlayer = pChargeBundle->GetCharmerOrOwnerPlayerOrPlayerItself();
				if (pPlayer)
				{
					((Player*)pPlayer)->KilledMonsterCredit(m_creature->GetEntry(),m_creature->GetGUID());
				}

				m_creature->GetMotionMaster()->MoveTargetedHome();

				Reset();
			}else BombTimer -= diff;
		}
	}
};

CreatureAI* GetAI_npc_nerubar_sinkhole(Creature* pCreature)
{
    return new npc_nerubar_sinkholeAI(pCreature);
}

/*######
## trident_of_nazjan
######*/

enum
{
	AREA_LEVIROTH	= 4029	,
	LEVIROTH_ENTRY	= 26452
};

bool ItemUse_trident_of_nazjan(Player* pPlayer, Item* pItem, SpellCastTargets const& scTargets)
{
	Creature *c = GetClosestCreatureWithEntry(pPlayer,LEVIROTH_ENTRY,9.0f);

	if( pPlayer->GetAreaId() != AREA_LEVIROTH )
	{
		pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL);
		return true;
	}
	else if( !c )
	{
		pPlayer->SendEquipError(EQUIP_ERR_OUT_OF_RANGE, pItem, NULL);
		return true;
	}
	else
	{
		return false;
	}
}

/*######
## npc_leviroth
######*/ 

struct MANGOS_DLL_DECL npc_levirothAI : public ScriptedAI
{
    bool spellHit;

    npc_levirothAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		Reset();
	}

    void Reset()
    {
		m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
        spellHit = false;
    }

    void MoveInLineOfSight(Unit *who)
	{
	
	}

    void UpdateAI(const uint32 diff)
    {
		if(spellHit)
			DoMeleeAttackIfReady();
    }

    void SpellHit(Unit *Hitter, const SpellEntry *spellkind)
    {
        if (spellkind->Id == 47170)
        {
			m_creature->SetHealthPercent(8.0);
			m_creature->SetStandState(UNIT_STAND_STATE_STAND);
			m_creature->AI()->AttackStart(Hitter);

            spellHit = true;
        }
	}
};

CreatureAI* GetAI_npc_leviroth(Creature* pCreature)
{
    return new npc_levirothAI(pCreature);
}

/*######
## npc_scourged_flamespitter
######*/

struct MANGOS_DLL_DECL npc_scourged_flamespitterAI : public ScriptedAI
{
    npc_scourged_flamespitterAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		Reset();
	}

    void Reset()
    {
    }

    void UpdateAI(const uint32 diff)
    {
		DoMeleeAttackIfReady();
    }

    void SpellHit(Unit *hitter, const SpellEntry *spellkind)
    {
        if (spellkind->Id == 46361)
        {
			m_creature->AI()->AttackStart(hitter);
        }
	}
};

CreatureAI* GetAI_npc_scourged_flamespitter(Creature* pCreature)
{
    return new npc_scourged_flamespitterAI(pCreature);
}

/*######
## npc_gnome_soul
######*/

struct MANGOS_DLL_DECL npc_gnome_soulAI : public ScriptedAI
{
    npc_gnome_soulAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		Reset();
	}

	uint32 m_uiWaitTimer;
	Player* pPlayer;

    void Reset()
    {
		pPlayer = NULL;
		pPlayer = GetPlayerAtMinimumRange(20.0f);
		m_uiWaitTimer = 3000;
    }

    void UpdateAI(const uint32 diff)
    {
		if(pPlayer)
		{
			if(m_uiWaitTimer <= diff)
			{
				m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL,DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL ,false); 
				pPlayer->KilledMonsterCredit(m_creature->GetEntry(), pPlayer->GetGUID());
			}
			else
				m_uiWaitTimer-=diff;
		}
    }
};

CreatureAI* GetAI_npc_gnome_soul(Creature* pCreature)
{
    return new npc_gnome_soulAI(pCreature);
}

void AddSC_borean_tundra()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_fizzcrank_fullthrottle";
    newscript->pGossipHello = &GossipHello_npc_fizzcrank_fullthrottle;
    newscript->pGossipSelect = &GossipSelect_npc_fizzcrank_fullthrottle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_iruk";
    newscript->pGossipHello = &GossipHello_npc_iruk;
    newscript->pGossipSelect = &GossipSelect_npc_iruk;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_kara_thricestar";
    newscript->pGossipHello = &GossipHello_npc_kara_thricestar;
    newscript->pGossipSelect = &GossipSelect_npc_kara_thricestar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_surristrasz";
    newscript->pGossipHello = &GossipHello_npc_surristrasz;
    newscript->pGossipSelect = &GossipSelect_npc_surristrasz;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tiare";
    newscript->pGossipHello = &GossipHello_npc_tiare;
    newscript->pGossipSelect = &GossipSelect_npc_tiare;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_lurgglbr";
    newscript->GetAI = &GetAI_npc_lurgglbr;
    newscript->pQuestAccept = &QuestAccept_npc_lurgglbr;
    newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "npc_fezzix_geartwist";
	newscript->GetAI = &GetAI_npc_fezzix_geartwist;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "npc_nerubar_sinkhole";
	newscript->GetAI = &GetAI_npc_nerubar_sinkhole;
	newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "trident_of_nazjan";
    newscript->pItemUse = &ItemUse_trident_of_nazjan;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_leviroth";
    newscript->GetAI = &GetAI_npc_leviroth;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_scourged_flamespitter";
    newscript->GetAI = &GetAI_npc_scourged_flamespitter;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_gnome_soul";
    newscript->GetAI = &GetAI_npc_gnome_soul;
    newscript->RegisterSelf();
}
