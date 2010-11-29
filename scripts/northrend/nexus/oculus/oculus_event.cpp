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
SDComment: Inferna Christmas PreEvent == Trial Phase 1
SDCategory: Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"


bool m_bIsStatue1Used;			//Used for Room2
bool m_bIsStatue2Used;			//Used for Room2
bool m_bIsStatue3Used;			//Used for Room2
bool m_bIsStatue4Used;			//Used for Room2

struct MANGOS_DLL_DECL oculus_event_kickerAI : public ScriptedAI
{
    oculus_event_kickerAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if(!pWho)
            return;

        if(pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if(Player* pPlayer = (Player*)m_creature->GetUnit(*m_creature, pWho->GetGUID()))
            {
                m_creature->MonsterSay("Die Event Instanz kann nur im heroischem Modus betreten werden!", LANG_UNIVERSAL, pPlayer->GetGUID());
                if(!pPlayer->isGameMaster())
                    pPlayer->TeleportTo(571, 3878.91f, 6984.5f, 106.321f, 3.15665f);
            }
        }
    }
};

/* ContentData
oculus_event_edwin			Addtion to Inferna Christmas PreEvent
EndContentData */
                                                    /* *** ROOM 1 *** */

/*######
## oculus_event_edwin
######*/

#define SPELL_TRASH		54913
#define NPC_DEFIAS		400055

struct MANGOS_DLL_DECL oculus_event_edwinAI : public ScriptedAI
{
    oculus_event_edwinAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiTrashTimer;
    uint32 m_uiSummonTimmer;


    void Reset()
    {
        m_uiSummonTimmer = 15000;
        m_uiTrashTimer = 8000;
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EDWIN, IN_PROGRESS);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_DEFIAS)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void JustDied(Unit* Killer)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EDWIN, DONE);
    }

    void EnterCombat(Unit* who)
    {
        m_creature->PlayDirectSound(11803,0);
        m_creature->PlayDistanceSound(11803,0);
    }


    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSummonTimmer < diff)
        {
            m_creature->SummonCreature(NPC_DEFIAS, 1091.614502f, 1125.280518f, 433.075714f, 3.911053f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
            m_creature->SummonCreature(NPC_DEFIAS, 1093.050415f, 1117.706299f, 433.076111f, 3.414335f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
            m_uiSummonTimmer = 15000;
        }else m_uiSummonTimmer -= diff;

        if (m_uiTrashTimer < diff)
        {
            DoCast(m_creature, SPELL_TRASH);
            m_uiTrashTimer = 8000;
        }else m_uiTrashTimer -= diff;

        DoMeleeAttackIfReady();
    }
};


/*######
## Room 1 EndGate1
######*/

#define NPC_COW				400061

bool GOHello_go_oculus_cannon(Player* pPlayer, GameObject* pGo)
{ 
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    pGo->SummonCreature(NPC_COW, 1088.934937f, 1103.900269f, 436.300354f, 0.839746f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);

    m_pInstance->SetData(GO_DATA_CANNON, DONE);
    return false;

}



/*######
## Room 1 Cow
######*/


#define SPELL_BUMM		29949	
#define YELL_MAMI		-2500035


struct MANGOS_DLL_DECL oculus_event_gate1_cowAI : public ScriptedAI
{
    oculus_event_gate1_cowAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiBummTimmer;
    bool m_bIsYell;

    void Reset()
    {
        m_uiBummTimmer = 2000;
        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
        m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);

        m_bIsYell = false;
    }

        
    void MoveInLineOfSight(Unit *pWho) 
    {
        if(!m_bIsYell)
        {
            if(pWho->GetTypeId() != TYPEID_PLAYER)
              return;

            m_creature->MonsterMove (1097.573364f, 1112.313354f, 438.803986f, 2000);
            DoScriptText(YELL_MAMI, m_creature);
            m_bIsYell = true;
        }
    }
    

    void UpdateAI(const uint32 uiDiff)
    {
        //if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        //    return;

        if (m_uiBummTimmer < uiDiff)
        {
            DoCast(m_creature, SPELL_BUMM, true);

            ScriptedInstance* m_pInstance = (ScriptedInstance*)m_creature->GetInstanceData();

            if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_COLLISION)))
                    pGate->SetGoState(GO_STATE_ACTIVE);
            if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_GATE1)))
                pGate->SetPhaseMask(128, true); //better than "0"

            m_creature->SummonGameobject (GO_RANCID_MEAT, 1097.295898f, 1112.084839f, 432.515350f, TEMPSUMMON_MANUAL_DESPAWN, 0); 
            m_creature->ForcedDespawn(100);

            //m_uiBummTimmer = 2000;
        }
        else
            m_uiBummTimmer -= uiDiff;

       DoMeleeAttackIfReady();
    }
};

                                                            /* *** ROOM 2 *** */

#define NPC_SNAKE1		29768
#define NPC_SNAKE2		29774
#define NPC_GURLOC		29920
#define NPC_GUARD		29829
#define SPELL_FIRE		25465

/*  Logik
 *  Statue 3 > Statue 2 > Statue 4 > Statue 1 > Statue 5 
 */


/*######
## Statue 1
######*/

bool GOHello_go_oculus_event_statue1(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && m_bIsStatue2Used && m_bIsStatue3Used && m_bIsStatue4Used)
    {
        pGo->SummonGameobject(GO_LIGHT1, 1124.34f, 1109.79f, 433.538f, TEMPSUMMON_MANUAL_DESPAWN, 0);
        pGo->SummonGameobject(GO_LIGHT2, 1124.34f, 1109.79f, 432.88f, TEMPSUMMON_MANUAL_DESPAWN, 0);

        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);

        m_bIsStatue1Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_SNAKE1, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_SNAKE2, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## Statue 2
######*/

bool GOHello_go_oculus_event_statue2(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && !m_bIsStatue2Used && m_bIsStatue3Used && !m_bIsStatue4Used)
    {
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);
        m_bIsStatue2Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_GURLOC, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GURLOC, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## Statue 3
######*/

bool GOHello_go_oculus_event_statue3(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && !m_bIsStatue2Used && !m_bIsStatue3Used && !m_bIsStatue4Used)
    {
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);
        m_bIsStatue3Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_GUARD, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GUARD, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}

/*######
## Statue 4
######*/

bool GOHello_go_oculus_event_statue4(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && m_bIsStatue2Used && m_bIsStatue3Used && !m_bIsStatue4Used)
    {
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);
        m_bIsStatue4Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_GURLOC, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GUARD, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## Statue 5
######*/

bool GOHello_go_oculus_event_statue5(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();
    
    if(!pInstance)
        return false;

    if (m_bIsStatue1Used && m_bIsStatue2Used && m_bIsStatue3Used && m_bIsStatue4Used)
    {
        if(Creature* pOssirian = pPlayer->GetCreature(*pPlayer, pInstance->GetData64(DATA_OSSIRIAN)))
            pOssirian->SetPhaseMask(1, true);
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);

        //reset booleans, GO's need to be reuseable in case of group wipe...
        m_bIsStatue1Used = false;
        m_bIsStatue2Used = false;
        m_bIsStatue3Used = false;
        m_bIsStatue4Used = false;

    }
    else
    {
        pGo->SummonCreature(NPC_SNAKE1, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GUARD, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}

//============================================= ROOM 4 ==============================================//
//need: mangos.npc_text 2x ID

/*
Event : 1067

- SD2 cusotm text IDs: -2500140 bis -2500170 (6 Abbild von Altvater Winter - 13 Verderbter Schneemann)
- Gob Entry Door : 400015
- GOB GUID: 2012701 RESERVED for CJ Room 
- NPCs: 400072 - 400078 reserved CJ Room
- NPC GUID: 2000603


GOB Tür HDS: 191459
Geisteraussehen: http://www.mobmap.de/spell?id=9036



<13:46:07> "l| Dev |l Nembi": NPC 13636: seltsamer schneemann
<13:47:00> "l| Dev |l Nembi": strange snowman modelid: 13730

*/
/*######
## Geist der zukümftigem Weinacht
######*/

//Globale Variable zur bestimmt des levels (für speak,spell,cd)
uint32 mob_level = 0;

enum
{
    SCHNEEMAN_ENTRY_1		=	400073,
    SCHNEEMAN_ENTRY_5		=	400074,
    SCHNEEMAN_ENTRY_10		=	400075,
    SCHNEEMAN_ENTRY_25		=	400076,
    SCHNEEMAN_ENTRY_40		=	400077,
};

enum
{
    SAY_HP      = -2500140,
    SPELL_HP    =    67973,
    SAY_MP      = -2500141,
    SPELL_MP    =    29166,
    SAY_SLEEP   = -2500142,
    SPELL_SLEEP =    28504,
    SAY_MONY    = -2500143,
    SAY_GIFT    = -2500144,
    SAY_BUFF    = -2500145
};

/* 
m_pInstance->SetData(TYPE_TRIAL, NOT_STARTED);
m_pInstance->SetData(TYPE_TRIAL, IN_PROGRESS);
m_pInstance->SetData(TYPE_TRIAL, FAIL);
m_pInstance->SetData(TYPE_TRIAL, DONE);
m_pInstance->SetData(TYPE_TRIAL, SPECIAL);
*/

bool GossipHello_inferna(Player* pPlayer, Creature* pCreature)
{
	ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
	switch(m_pInstance->GetData(TYPE_TRIAL))
	{
		case IN_PROGRESS:
			pCreature->MonsterSay("Wir unterhalten uns später $N, besiege zuerst diesen Schneemann dort!", LANG_UNIVERSAL, pPlayer->GetGUID());
		break;

		default:
	        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich brauche Leben.", 1, GOSSIP_ACTION_INFO_DEF+1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich brauche Mana.", 1, GOSSIP_ACTION_INFO_DEF+2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich brauche Schlaf.", 1, GOSSIP_ACTION_INFO_DEF+3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich brauche Geld.", 1, GOSSIP_ACTION_INFO_DEF+4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich will mein Geschenke!", 1, GOSSIP_ACTION_INFO_DEF+5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ich brauche Buffs.", 1, GOSSIP_ACTION_INFO_DEF+6);
			switch(m_pInstance->GetData(TYPE_TRIAL))
			{
				case NOT_STARTED: pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lass uns mal was verruecktes machen, komm wir bauen einen Schneemann.", 1, GOSSIP_ACTION_INFO_DEF+7); break;
				case FAIL: pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Der letzte Schneemann war ein bischen Groß... Wir wollen lieber einen anderen Bauen.", 1, GOSSIP_ACTION_INFO_DEF+7); break;
			}
			pPlayer->SEND_GOSSIP_MENU(724100, pCreature->GetGUID());
		break;
	}
    return true;
}

void summon_schneeman(int level,Player* pPlayer)
{
    mob_level = level;
    switch(level)
    {
        case 0: pPlayer->SummonCreature(SCHNEEMAN_ENTRY_1, 1112.58f, 988.83f, 432.52f, 0.111f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000); break;
        case 1: pPlayer->SummonCreature(SCHNEEMAN_ENTRY_5, 1112.58f, 988.83f, 432.52f, 0.111f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000); break;
        case 2: pPlayer->SummonCreature(SCHNEEMAN_ENTRY_10, 1112.58f, 988.83f, 432.52f, 0.111f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000); break;
        case 3: pPlayer->SummonCreature(SCHNEEMAN_ENTRY_25, 1112.58f, 988.83f, 432.52f, 0.111f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000); break;
        case 4: pPlayer->SummonCreature(SCHNEEMAN_ENTRY_40, 1112.58f, 988.83f, 432.52f, 0.111f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000); break;
    }
	Creature pCreature;
	ScriptedInstance* m_pInstance = (ScriptedInstance*)pPlayer->GetInstanceData();
	m_pInstance->SetData(TYPE_TRIAL, IN_PROGRESS);

    pPlayer->CLOSE_GOSSIP_MENU();
}
bool GossipSelect_inferna(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            //debug_log("Ich brauche Leben.");
            DoScriptText(SAY_HP, pCreature, pPlayer);
            pCreature->CastSpell(pPlayer, SPELL_HP, true);
            pPlayer->CLOSE_GOSSIP_MENU();
        break;

        case GOSSIP_ACTION_INFO_DEF+2:
            //debug_log("Ich brauche Mana.");
            DoScriptText(SAY_MP, pCreature, pPlayer);
            pCreature->CastSpell(pPlayer, SPELL_MP, true);
            pPlayer->ModifyPower(pPlayer->getPowerType(), 35000);
            pPlayer->CLOSE_GOSSIP_MENU();
        break;

        case GOSSIP_ACTION_INFO_DEF+3:
            //debug_log("Ich brauche Schlaf.");
            DoScriptText(SAY_SLEEP, pCreature, pPlayer);
            pPlayer->CastSpell(pPlayer, SPELL_SLEEP, true);
            pPlayer->CLOSE_GOSSIP_MENU();
        break;

        case GOSSIP_ACTION_INFO_DEF+4:
            //debug_log("Ich brauche Geld.");
            DoScriptText(SAY_MONY, pCreature, pPlayer);
            pPlayer->CLOSE_GOSSIP_MENU();
        break;

        case GOSSIP_ACTION_INFO_DEF+5:
            //debug_log("Ich will mein Geschenke!");
            DoScriptText(SAY_GIFT, pCreature, pPlayer);
            pPlayer->CLOSE_GOSSIP_MENU();
        break;

        case GOSSIP_ACTION_INFO_DEF+6:
            //debug_log("Ich brauche Buffs.");
            DoScriptText(SAY_BUFF, pCreature, pPlayer);
            pCreature->CastSpell(pPlayer, 58451, true); //+30 Bew
            pCreature->CastSpell(pPlayer, 58449, true); //+30 Str
            pCreature->CastSpell(pPlayer, 48100, true); //+30 Int
            pCreature->CastSpell(pPlayer, 48104, true); //+30 Wil
            pCreature->CastSpell(pPlayer, 48102, true); //+30 Aus
            pCreature->CastSpell(pPlayer, 58453, true); //+750 armor
            pPlayer->CLOSE_GOSSIP_MENU();
        break;

        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->PlayerTalkClass->ClearMenus();
            //ohne diese Funktion werden die nächsten Einträge mit angehangen
            //debug_log("Lass uns mal was verruecktes machen, komm wir bauen einen Schneemann.");
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,  "1", 2, GOSSIP_ACTION_INFO_DEF+8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,  "5", 2, GOSSIP_ACTION_INFO_DEF+9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "10", 2, GOSSIP_ACTION_INFO_DEF+10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "25", 2, GOSSIP_ACTION_INFO_DEF+11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "40", 2, GOSSIP_ACTION_INFO_DEF+12);
            pPlayer->SEND_GOSSIP_MENU(724101, pCreature->GetGUID());
        break;

        case GOSSIP_ACTION_INFO_DEF+8:
            //debug_log("1er");
            summon_schneeman(0,pPlayer);
        break;

        case GOSSIP_ACTION_INFO_DEF+9:
            //debug_log("5er");
            summon_schneeman(1,pPlayer);
        break;

        case GOSSIP_ACTION_INFO_DEF+10:
            //debug_log("10er");
            summon_schneeman(2,pPlayer);
        break;

        case GOSSIP_ACTION_INFO_DEF+11:
            //debug_log("25er");
            summon_schneeman(3,pPlayer);
        break;

        case GOSSIP_ACTION_INFO_DEF+12:
            //debug_log("40er");
            summon_schneeman(4,pPlayer);
        break;
    }
    return true;
}

/*######
## Verderbter Schneemann
######*/

//Serverdown bei Bossfight. Nochmal möglich?

/*
HEAL:
28306		Große Heilung		2 s			19-21%
54337		Große Heilung		2 s			33-37%

67969: Heilt ein befreundetes Ziel um 28350 to 31650 und über 21 Sek. um weitere 45325 to 52675.
67968: Heilt ein befreundetes Ziel um 56700 to 63300 und über 21 Sek. um weitere 129500 to 150500.
67970: Heilt ein befreundetes Ziel um 85050 to 94950 und über 21 Sek. um weitere 194250 to 225750.

//	Verjüngung:																
//	66065: Heilt das Ziel im Verlauf von 15 Sek. um 92500 to 107500.		
//	67972: Heilt das Ziel im Verlauf von 15 Sek. um 138750 to 161250.		
//	67971: Heilt das Ziel im Verlauf von 15 Sek. um 277500 to 322500.		

DAMAGE:
31249		Eisblitz			inst		5000 4sek 10000
71331		Eisgrab				1,5 s		2600/2sek + stun
72268		Eisschuss			inst		4500 + 2sek stun
65807: Schleudert einen Frostblitz auf den Feind, der 7863 to 9137 Frostschaden verursacht und 9 Sek. lang das Bewegungstempo um 40% reduziert.
68003: Schleudert einen Frostblitz auf den Feind, der 8788 to 10212 Frostschaden verursacht und 9 Sek. lang das Bewegungstempo um 40% reduziert.
68005: Schleudert einen Frostblitz auf den Feind, der 11563 to 13437 Frostschaden verursacht und 9 Sek. lang das Bewegungstempo um 40% reduziert.
    
Schneeball:
65516		KnockBack 50		inst
25995		KnockBack 200		inst

Aura:
ID		TICK
71387	1200	28531
55799	1600
70084	3000
71051	4500
71052	6000
*/

#define SAY_KILLED_PLAYER	-2500159
#define SAY_DIED			-2500160

uint32 SKILL[5][4] =
{
//	{ SPELL_HEAL,	SPELL_DAMAGE_ONE,	SPELL_DAMAGE_TWO,	AURA  }, //level
    { 28306,		65516,				71331,				28531}, //1er
    { 54337,		25995,				72268,				55799}, //5er
    { 67969,		31249,				65807,				70084}, //10er
    { 67968,		31249,				68003,				71051}, //25er
    { 67970,		31249,				68005,				71052}  //40er
};

uint32 COOLDOWN[5][3] =
{
//	{ CD_HEAL,		CD_DAMAGE_ONE,		CD_DAMAGE_TWO  }, //level
    { 60000,		5000,				10000}, //1er
    { 60000,		5000,				12500}, //5er
    { 60000,		10000,				15000}, //10er
    { 60000,		10000,				15000}, //25er
    { 60000,		10000,				15000}  //40er
};

int32 SAY[5][3] =
{
//	{ ID_HEAL,		ID_DAMAGE_ONE,		ID_DAMAGE_TWO  }, //level
    { -2500146,		-2500147,			-2500148}, //1er
    { -2500149,		-2500150,			-2500151}, //5er
    { -2500152,		-2500153,			-2500154}, //10er
    { -2500155,		-2500153,			-2500156}, //25er
    { -2500157,		-2500153,			-2500158}  //40er
};

struct MANGOS_DLL_DECL inferna_schneemannAI : public ScriptedAI
{
	inferna_schneemannAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
		m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

        m_creature->MonsterYell("Ihr werdet nie wieder Weihnachten feiern !", LANG_UNIVERSAL, pCreature->GetGUID());
        //mob_level = 1; // 0 - 4 (+1)
        Reset();
    }

	~inferna_schneemannAI()
    {
		if(m_pInstance->GetData(TYPE_TRIAL) != DONE)
			m_pInstance->SetData(TYPE_TRIAL, FAIL);
    }

    ScriptedInstance* m_pInstance;

    Unit* pTarget;
    uint32 TIMER_HEAL, TIMER_DAMAGE_ONE, TIMER_DAMAGE_TWO;
    //uint32 mob_level;
    uint32 i_globalCD;
    bool b_healing;

    void Reset()
    {
        TIMER_HEAL = COOLDOWN[mob_level][0];
        TIMER_DAMAGE_ONE = COOLDOWN[mob_level][1];
        TIMER_DAMAGE_TWO = COOLDOWN[mob_level][2];
        i_globalCD = 2700;

        if (m_pInstance)
			m_pInstance->SetData(TYPE_TRIAL, IN_PROGRESS);
	}

	void JustDied(Unit * pkiller)
	{
		DoScriptText(SAY_DIED, m_creature, pkiller);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TRIAL, DONE);
	}

    void Aggro(Unit *who) 
    {
		DoCast(m_creature, SKILL[mob_level][3], true);
    }

    void KilledUnit(Unit* pvictim)
    {
        DoScriptText(SAY_KILLED_PLAYER, m_creature, pvictim);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //debug_log("TIMER_DAMAGE_ONE: %d TIMER_DAMAGE_TWO: %d TIMER_HEAL: %d",TIMER_DAMAGE_ONE,TIMER_DAMAGE_TWO,TIMER_HEAL);

        if(b_healing)
        {
            if( i_globalCD < uiDiff)
            {
                b_healing = false;
                i_globalCD = 2700;
                TIMER_DAMAGE_ONE = COOLDOWN[mob_level][1];
                TIMER_DAMAGE_TWO = COOLDOWN[mob_level][2];
            }
            else
                i_globalCD -= uiDiff;
        }

        if((m_creature->GetHealthPercent() < 100.0f) && (TIMER_HEAL < uiDiff))
        {
                //debug_log("\t\tSPELL_HEAL");
                DoScriptText(SAY[mob_level][0], m_creature);
                m_creature->CastStop();
                DoCastSpellIfCan(m_creature, SKILL[mob_level][0]);
                TIMER_HEAL = COOLDOWN[mob_level][0];
                b_healing = true;
        }
        else if(TIMER_DAMAGE_ONE < uiDiff)
        {
            //random
            pTarget = m_creature->SelectRandomUnfriendlyTarget(0, 60);
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {
                //debug_log("\t\tSPELL_DAMAGE_ONE");
                DoScriptText(SAY[mob_level][1], m_creature);
                DoCastSpellIfCan(pTarget, SKILL[mob_level][1]);
                TIMER_DAMAGE_ONE = COOLDOWN[mob_level][1];
            }
        }
        else if(TIMER_DAMAGE_TWO < uiDiff)
        {
            pTarget = m_creature->SelectRandomUnfriendlyTarget(0, 60);
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {
                //debug_log("\t\tSPELL_DAMAGE_TWO");
                DoScriptText(SAY[mob_level][2], m_creature);
                DoCastSpellIfCan(pTarget, SKILL[mob_level][2]);
                TIMER_DAMAGE_TWO = COOLDOWN[mob_level][2];
            }
        }
        else
        {
            TIMER_DAMAGE_ONE -= uiDiff;
            TIMER_DAMAGE_TWO -= uiDiff;
            TIMER_HEAL -= uiDiff;
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_inferna_schneemann(Creature* pCreature)
{
    return new inferna_schneemannAI(pCreature);
}


/*######
## oculus_event_ossirian
######*/

#define SPELL_CURSE		25195
#define SPELL_WIND		25189
#define SPELL_SHADOW	39026

#define SAY_AGGRO			-2500032
#define SAY_GATE_PHASE1		-2500033
#define SAY_GATE_PHASE2		-2500034


struct MANGOS_DLL_DECL oculus_event_ossirianAI : public Scripted_NoMovementAI
{
    oculus_event_ossirianAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiCurseTimer;
    uint32 m_uiWindTimer;
    uint32 m_uiAttackTimer;
    uint32 m_uiShadowTimer;

    bool m_bIsPhase2;
    bool m_bResetEventRoom2;

    void Reset()
    {
        m_uiShadowTimer = 5000;
        m_uiCurseTimer = 30000;
        m_uiWindTimer = 12000;
        m_uiAttackTimer = 5000;

        m_bIsPhase2 = false;
        m_bResetEventRoom2 = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if(!m_pInstance)
            return;

        Map* pMap = m_creature->GetMap();
        if(pMap)
        {
            Map::PlayerList const &lPlayers = pMap->GetPlayers();
            for (Map::PlayerList::const_iterator iter = lPlayers.begin(); iter != lPlayers.end(); ++iter)
            {
                Player* pPlayer = iter->getSource();

                if(pPlayer->isAlive())
                    continue;

                m_bResetEventRoom2 = true;
            }
        }

        if(m_bResetEventRoom2)
        {
            // make GO's useable again
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE1)))
                pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE2)))
                pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE3)))
                pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE4)))
                pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE5)))
                pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);

            // despawn lights
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_LIGHT1)))
                pTemp->Delete();
            if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_LIGHT2)))
                pTemp->Delete();

            // close root door
            if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_GATE2_ROOTS)))
                pGate->SetGoState(GO_STATE_READY);	

            m_creature->SetPhaseMask(128, true);
        }
    }
    

    void JustDied(Unit* Killer)
    {
        if(!m_pInstance)
            return;
        
        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_GATE2)))
            pGate->SetGoState(GO_STATE_ACTIVE);

        m_pInstance->SetData(TYPE_OSSIRIAN, DONE);

        DoScriptText(SAY_GATE_PHASE2, m_creature);
    }

    void Aggro (Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if(!m_pInstance)
            return;

        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE1)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE2)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE3)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE4)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE5)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);

        m_pInstance->SetData(TYPE_OSSIRIAN, IN_PROGRESS);
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiWindTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_WIND);

            m_uiWindTimer = 12000;
        } else m_uiWindTimer -= uiDiff;

        if (m_uiCurseTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_CURSE);

            m_uiCurseTimer = 30000;
        }else m_uiCurseTimer -= uiDiff;

        if (m_uiShadowTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_SHADOW);

            m_uiShadowTimer = 5000;
        }else m_uiShadowTimer -= uiDiff;

        if (!m_pInstance)
            return;

        if (!m_bIsPhase2 && (m_creature->GetHealthPercent() < 40.0f))
        {
            if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_GATE2_ROOTS)))
                pGate->SetGoState(GO_STATE_ACTIVE);	

            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            DoScriptText(SAY_GATE_PHASE1, m_creature);
            m_bIsPhase2 = true;
        }

        if(m_bIsPhase2 && m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
        {
            if (m_bIsPhase2 && (m_uiAttackTimer < uiDiff))
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }else m_uiAttackTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_oculus_event_kicker(Creature* pCreature)
{
    return new oculus_event_kickerAI(pCreature);
}

CreatureAI* GetAI_oculus_event_edwin(Creature* pCreature)
{
    return new oculus_event_edwinAI(pCreature);
}

CreatureAI* GetAI_oculus_event_ossirian(Creature* pCreature)
{
    return new oculus_event_ossirianAI(pCreature);
}

CreatureAI* GetAI_oculus_event_gate1_cow(Creature* pCreature)
{
    return new oculus_event_gate1_cowAI(pCreature);
}

void AddSC_oculus_event()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_event_kicker";
    newscript->GetAI = &GetAI_oculus_event_kicker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_event_edwin";
    newscript->GetAI = &GetAI_oculus_event_edwin;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_cannon";
    newscript->pGOHello = &GOHello_go_oculus_cannon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue1";
    newscript->pGOHello = &GOHello_go_oculus_event_statue1;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue2";
    newscript->pGOHello = &GOHello_go_oculus_event_statue2;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue3";
    newscript->pGOHello = &GOHello_go_oculus_event_statue3;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue4";
    newscript->pGOHello = &GOHello_go_oculus_event_statue4;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue5";
    newscript->pGOHello = &GOHello_go_oculus_event_statue5;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_event_christmas_room4_npc";
    newscript->pGossipHello = &GossipHello_inferna;
    newscript->pGossipSelect = &GossipSelect_inferna;
    newscript->RegisterSelf();

    newscript->Name = "oculus_event_christmas_room4_boss";
    newscript->GetAI = &GetAI_inferna_schneemann;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_event_ossirian";
    newscript->GetAI = &GetAI_oculus_event_ossirian;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "oculus_event_gate1_cow";
    newscript->GetAI = &GetAI_oculus_event_gate1_cow;
    newscript->RegisterSelf();
}