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
SDName: Guards
SD%Complete: 100
SDComment: All Guard gossip data, quite some npc_text-id's still missing, adding constantly as new id's are known. CombatAI should be organized better for future.
SDCategory: Guards
EndScriptData */

/* ContentData
guard_azuremyst
guard_bluffwatcher
guard_contested
guard_dalaran
guard_darnassus
guard_dunmorogh
guard_durotar
guard_elwynnforest
guard_eversong
guard_exodar
guard_ironforge
guard_mulgore
guard_orgrimmar
guard_shattrath
guard_shattrath_aldor
guard_shattrath_scryer
guard_silvermoon
guard_stormwind
guard_teldrassil
guard_tirisfal
guard_undercity
EndContentData */

#include "precompiled.h"
#include "guard_ai.h"

//script spesific action
#define GOSSIP_ACTION_TAVERN                  101
#define GOSSIP_ACTION_GEMMERCHANT             102
#define GOSSIP_ACTION_MANALOOM                103

//script spesific sender
#define GOSSIP_SENDER_SEC_GEMMERCHANT         101
#define GOSSIP_SENDER_SEC_AUCTIONHOUSE        102

//script spesific gossip text
#define GOSSIP_TEXT_TAVERN                    "Taverne Weltenend"
#define GOSSIP_TEXT_BANKSCYERS                "Die Bank der Seher"
#define GOSSIP_TEXT_BANKALDOR                 "Die Bank der Aldor"
#define GOSSIP_TEXT_INNSCYERS                 "Das Gasthaus der Seher"
#define GOSSIP_TEXT_INNALDOR                  "Das Gasthaus der Aldor"
#define GOSSIP_TEXT_STABLESCYERS              "Der Stall der Seher"
#define GOSSIP_TEXT_STABLEALDOR               "Der Stall der Aldor"
#define GOSSIP_TEXT_BATTLEMASTERALLIANCE      "Die Kampfmeister der Allianz"
#define GOSSIP_TEXT_BATTLEMASTERHORDE         "Die Kampfmeister der Horde"
#define GOSSIP_TEXT_BATTLEMASTERARENA         "Die Arenakampfmeister"
#define GOSSIP_TEXT_MANALOOM                  "Manawebrahmen"
#define GOSSIP_TEXT_ALCHEMYLAB                "Alchemielabor"
#define GOSSIP_TEXT_GEMMERCHANT               "Juwelenhändler"
#define GOSSIP_TEXT_GEMSCYERS                 "Juwelenhändler der Seher"
#define GOSSIP_TEXT_GEMALDOR                  "Juwelenhändler der Aldor"

#define GOSSIP_TEXT_AH_SILVERMOON_1           "Im Westen"
#define GOSSIP_TEXT_AH_SILVERMOON_2           "Im Osten"

#define GOSSIP_TEXT_INN_SILVERMOON_1          "Das Gasthaus von Silbermond"
#define GOSSIP_TEXT_INN_SILVERMOON_2          "Die Taverne Wanderers Ruh'"

/*******************************************************
 * guard_azuremyst start
 *******************************************************/

bool GossipHello_guard_azuremyst(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(10066, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_azuremyst(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(-3918.95f, -11544.7f, 7, 6, 0, "Bank");
            pPlayer->SEND_GOSSIP_MENU(10067, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hippogryph Master
            pPlayer->SEND_POI(-4057.15f, -11788.6f, 7, 6, 0, "Stephanos");
            pPlayer->SEND_GOSSIP_MENU(10071, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(-4092.43f, -11626.6f, 7, 6, 0, "Funaam");
            pPlayer->SEND_GOSSIP_MENU(10073, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-4129.43f, -12469.0f, 7, 6, 0, "Versorgerin Chellan");
            pPlayer->SEND_GOSSIP_MENU(10074, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
            pPlayer->SEND_POI(-4146.42f, -12492.7f, 7, 6, 0, "Esbina");
            pPlayer->SEND_GOSSIP_MENU(10075, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(10076, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU(10087, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_azuremyst(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(-4274.81f, -11495.3f, 7, 6, 0, "Shalannius");
            pPlayer->SEND_GOSSIP_MENU(10077, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(-4203.65f, -12526.5f, 7, 6, 0, "Acteon");
            pPlayer->SEND_GOSSIP_MENU(10078, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(-4149.62f, -12530.1f, 7, 6, 0, "Semid");
            pPlayer->SEND_GOSSIP_MENU(10081, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
            pPlayer->SEND_POI(-4138.98f, -12468.5f, 7, 6, 0, "Tullas");
            pPlayer->SEND_GOSSIP_MENU(10083, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(-4131.66f, -12478.6f, 7, 6, 0, "Guvan");
            pPlayer->SEND_GOSSIP_MENU(10084, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Shaman
            pPlayer->SEND_POI(-4162.33f, -12456.1f, 7, 6, 0, "Tuluun");
            pPlayer->SEND_GOSSIP_MENU(10085, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(-4165.05f, -12536.4f, 7, 6, 0, "Ruada");
            pPlayer->SEND_GOSSIP_MENU(10086, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_azuremyst(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-4191.15f, -12470.0f, 7, 6, 0, "Daedal");
            pPlayer->SEND_GOSSIP_MENU(10088, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-4726.29f, -12387.0f, 7, 6, 0, "Schmied Calypso");
            pPlayer->SEND_GOSSIP_MENU(10089, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-4710.87f, -12400.6f, 7, 6, 0, "'Kräcka' Aschebäscha");
            pPlayer->SEND_GOSSIP_MENU(10090, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-3882.85f, -11496.7f, 7, 6, 0, "Nahogg");
            pPlayer->SEND_GOSSIP_MENU(10091, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-4157.57f, -12470.2f, 7, 6, 0, "Konstrukteur Daelo");
            pPlayer->SEND_GOSSIP_MENU(10092, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-4199.11f, -12469.9f, 7, 6, 0, "Anachoret Fateema");
            pPlayer->SEND_GOSSIP_MENU(10093, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-4266.38f, -12985.1f, 7, 6, 0, "Diktynna");
            pPlayer->SEND_GOSSIP_MENU(10094, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_GOSSIP_MENU(10095, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Jewelcrafting
            pPlayer->SEND_POI(-3781.55f, -11541.8f, 7, 6, 0, "Farii");
            pPlayer->SEND_GOSSIP_MENU(10097, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Leatherworking
            pPlayer->SEND_POI(-3442.68f, -12322.2f, 7, 6, 0, "Moordo");
            pPlayer->SEND_GOSSIP_MENU(10098, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Mining
            pPlayer->SEND_POI(-4179.89f, -12493.1f, 7, 6, 0, "Dulvi");
            pPlayer->SEND_GOSSIP_MENU(10097, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Skinning
            pPlayer->SEND_POI(-3431.17f, -12316.5f, 7, 6, 0, "Gurf");
            pPlayer->SEND_GOSSIP_MENU(10098, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //Tailoring
            pPlayer->SEND_POI(-4711.54f, -12386.7f, 7, 6, 0, "Erin Kelly");
            pPlayer->SEND_GOSSIP_MENU(10099, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_azuremyst(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_azuremyst(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_azuremyst(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_azuremyst(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_azuremyst end
 *******************************************************/

CreatureAI* GetAI_guard_azuremyst(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_bluffwatcher start
 *******************************************************/

bool GossipHello_guard_bluffwatcher(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(3543, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(-1257.8f, 24.14f, 7, 6, 0, "Bank von Donnerfels");
            pPlayer->SEND_GOSSIP_MENU(1292, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind master
            pPlayer->SEND_POI(-1196.43f, 28.26f, 7, 6, 0, "Windreiterhorst");
            pPlayer->SEND_GOSSIP_MENU(1293, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(-1296.5f, 127.57f, 7, 6, 0, "Gildenmeister von Donnerfels");
            pPlayer->SEND_GOSSIP_MENU(1291, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-1296.0f, 39.7f, 7, 6, 0, "Gasthaus von Donnerfels");
            pPlayer->SEND_GOSSIP_MENU(3153, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(-1263.59f, 44.36f, 7, 6, 0, "Briefkasten von Donnerfels");
            pPlayer->SEND_GOSSIP_MENU(3154, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Auction House
            pPlayer->SEND_POI(1381.77f, -4371.16f, 7, 6, 0, GOSSIP_TEXT_AUCTIONHOUSE);
            pPlayer->SEND_GOSSIP_MENU(3155, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Weapon master
            pPlayer->SEND_POI(-1282.31f, 89.56f, 7, 6, 0, "Ansekhwa");
            pPlayer->SEND_GOSSIP_MENU(4520, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable master
            pPlayer->SEND_POI(-1270.19f, 48.84f, 7, 6, 0, "Bulrug");
            pPlayer->SEND_GOSSIP_MENU(5977, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY       , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7527, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(3542, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(3541, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-1387.82f, -97.55f, 7, 6, 0, "Taim Rachtotem");
            pPlayer->SEND_GOSSIP_MENU(7522, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-997.0f, 214.12f, 7, 6, 0, "Martin Lindsey");
            pPlayer->SEND_GOSSIP_MENU(7648, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(-1384.94f, -75.91f, 7, 6, 0, "Kergul Blutaxt");
            pPlayer->SEND_GOSSIP_MENU(7523, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(-1054.47f, -285.0f, 7, 6, 0, "Anhöhe der Ältesten");
            pPlayer->SEND_GOSSIP_MENU(1294, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(-1416.32f, -114.28f, 7, 6, 0, "Anhöhe der Jäger");
            pPlayer->SEND_GOSSIP_MENU(1295, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(-1061.2f, 195.5f, 7, 6, 0, "Teiche der Visionen");
            pPlayer->SEND_GOSSIP_MENU(1296, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
            pPlayer->SEND_POI(-1061.2f, 195.5f, 7, 6, 0, "Teiche der Visionen");
            pPlayer->SEND_GOSSIP_MENU(1297, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Shaman
            pPlayer->SEND_POI(-989.54f, 278.25f, 7, 6, 0, "Anhöhe der Geister");
            pPlayer->SEND_GOSSIP_MENU(1298, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warrior
            pPlayer->SEND_POI(-1416.32f, -114.28f, 7, 6, 0, "Anhöhe der Jäger");
            pPlayer->SEND_GOSSIP_MENU(1299, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-1085.56f, 27.29f, 7, 6, 0, "Benas Alchimie");
            pPlayer->SEND_GOSSIP_MENU(1332, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-1239.75f, 104.88f, 7, 6, 0, "Karns Schmiede");
            pPlayer->SEND_GOSSIP_MENU(1333, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-1214.5f, -21.23f, 7, 6, 0, "Askas Küche");
            pPlayer->SEND_GOSSIP_MENU(1334, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-1112.65f, 48.26f, 7, 6, 0, "Morgenwandlers Verzauberungen");
            pPlayer->SEND_GOSSIP_MENU(1335, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-996.58f, 200.5f, 7, 6, 0, "Spirituelle Heilung");
            pPlayer->SEND_GOSSIP_MENU(1336, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
            pPlayer->SEND_POI(-1169.35f, -68.87f, 7, 6, 0, "Gipfelbergs Köder und Ausrüstung");
            pPlayer->SEND_GOSSIP_MENU(1337, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
            pPlayer->SEND_POI(-1137.7f, -1.51f, 7, 6, 0, "Ganzheitliche Kräuterkunde");
            pPlayer->SEND_GOSSIP_MENU(1338, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Leatherworking
            pPlayer->SEND_POI(-1156.22f, 66.86f, 7, 6, 0, "Rüstungsschmiede von Donnerfels");
            pPlayer->SEND_GOSSIP_MENU(1339, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mining
            pPlayer->SEND_POI(-1249.17f, 155.0f, 7, 6, 0, "Steinhufgeologie");
            pPlayer->SEND_GOSSIP_MENU(1340, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Skinning
            pPlayer->SEND_POI(-1148.56f, 51.18f, 7, 6, 0, "Mooranta");
            pPlayer->SEND_GOSSIP_MENU(1343, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Tailoring
            pPlayer->SEND_POI(-1156.22f, 66.86f, 7, 6, 0, "Rüstungsschmiede von Donnerfels");
            pPlayer->SEND_GOSSIP_MENU(1341, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_bluffwatcher end
 *******************************************************/

CreatureAI* GetAI_guard_bluffwatcher(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_contested start
 *******************************************************/

enum eguard_contested
{
	PVP_GUARD_SAY1 = -1000198,
	PVP_GUARD_SAY2 = -1000199,
	PVP_GUARD_SAY3 = -1000200
 
};

struct MANGOS_DLL_DECL guard_contested : public guardAI
{
    guard_contested(Creature* pCreature) : guardAI(pCreature) {Reset();}
	

	void Reset()
    {
		m_creature->AttackStop();
		m_creature->DeleteThreatList();
		m_creature->setFaction(121);
	}

    void MoveInLineOfSight(Unit* pUnit)
    {
        if ( pUnit->isInCombat() && pUnit->isAttackingPlayer())
        {
            if(pUnit->GetTypeId() == TYPEID_PLAYER || pUnit->GetOwnerGUID() && GUID_HIPART(pUnit->GetOwnerGUID())==HIGHGUID_PLAYER)
            {
				Unit* pVictim = pUnit->getVictim();
				if(pVictim->GetTypeId() == TYPEID_PLAYER)
				{
					m_creature->AddThreat(pUnit, 0.0f);
					if(Unit* owner = pUnit->GetOwner())
						m_creature->AddThreat(owner, 0.0f);
			    	m_creature->Attack(pUnit,true);
			    	m_creature->setFaction(72);

					DoStartMovement(pUnit);
                    SpellEntry const *spell = m_creature->reachWithSpellAttack(pUnit);
                    DoCastSpell(pUnit, spell);
						

					if(!m_creature->isInCombat())
					{
						if (m_creature->GetEntry() == 15184)    //Cenarion Hold Infantry
						{
							srand (time(NULL));
							if (rand()%100 <= 30)
							{
								DoScriptText(PVP_GUARD_SAY1,m_creature);
	                            //DoSay("Taste blade, mongrel!", LANG_UNIVERSAL,NULL);
		                    }
			                else if (rand()%100 > 30 && rand()%100 < 50)
				            {
								DoScriptText(PVP_GUARD_SAY2,m_creature);
						        //DoSay("Please tell me that you didn`t just do what I think you just did. Please tell me that I`m not going to have to hurt you...", LANG_UNIVERSAL,NULL);
							}
							else if (rand()%100 >= 50)
							{
								DoScriptText(PVP_GUARD_SAY3,m_creature);
								//DoSay("As if we don`t have enough problems, you go and create more!", LANG_UNIVERSAL,NULL);
							}
						}
					}
                }
                
            }
			m_creature->AttackStop();
			m_creature->DeleteThreatList();
			m_creature->setFaction(121);
        }
    }
};

/*******************************************************
 * guard_contested end
 *******************************************************/

CreatureAI* GetAI_guard_contested(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_darnassus start
 *******************************************************/

bool GossipHello_guard_darnassus(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(3016, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
            pPlayer->SEND_POI(9861.23f, 2334.55f, 7, 6, 0, "Auktionshaus Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3833, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(9938.45f, 2512.35f, 7, 6, 0, "Bank von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3017, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Wind master
            pPlayer->SEND_POI(9945.65f, 2618.94f, 7, 6, 0, "Rut'theran");
            pPlayer->SEND_GOSSIP_MENU(3018, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Guild master
            pPlayer->SEND_POI(10076.40f, 2199.59f, 7, 6, 0, "Gildenmeister von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3019, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Inn
            pPlayer->SEND_POI(10133.29f, 2222.52f, 7, 6, 0, "Gasthaus von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3020, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Mailbox
            pPlayer->SEND_POI(9942.17f, 2495.48f, 7, 6, 0, "Briefkasten von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3021, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Stable master
            pPlayer->SEND_POI(10167.20f, 2522.66f, 7, 6, 0, "Alassin");
            pPlayer->SEND_GOSSIP_MENU(5980, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon trainer
            pPlayer->SEND_POI(9907.11f, 2329.70f, 7, 6, 0, "Ilyenia Mondfeuer");
            pPlayer->SEND_GOSSIP_MENU(4517, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(4264, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(4273, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(9923.61f, 2327.43f, 7, 6, 0, "Brogun Steinschild");
            pPlayer->SEND_GOSSIP_MENU(7518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(9977.37f, 2324.39f, 7, 6, 0, "Keras Wolfsherz");
            pPlayer->SEND_GOSSIP_MENU(7651,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(9979.84f, 2315.79f, 7, 6, 0, "Aethalas");
            pPlayer->SEND_GOSSIP_MENU(7482, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(10186.0f, 2570.46f, 7, 6, 0, "Druidenlehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3024, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(10177.29f, 2511.10f, 7, 6, 0, "Jägerlehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3023, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(9659.12f, 2524.88f, 7, 6, 0, "Tempel des Mondes");
            pPlayer->SEND_GOSSIP_MENU(3025, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
            pPlayer->SEND_POI(10122.0f, 2599.12f, 7, 6, 0, "Schurkenlehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3026, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(9951.91f, 2280.38f, 7, 6, 0, "Die Terrasse der Krieger");
            pPlayer->SEND_GOSSIP_MENU(3033, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(10075.90f, 2356.76f, 7, 6, 0, "Alchemielehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3035, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Cooking
            pPlayer->SEND_POI(10088.59f, 2419.21f, 7, 6, 0, "Kochkunstlehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3036, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Enchanting
            pPlayer->SEND_POI(10146.09f, 2313.42f, 7, 6, 0, "Verzauberungskunstlehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3337, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //First Aid
            pPlayer->SEND_POI(10150.09f, 2390.43f, 7, 6, 0, "Lehrer für Erste Hilfe von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3037, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Fishing
            pPlayer->SEND_POI(9836.20f, 2432.17f, 7, 6, 0, "Angellehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3038, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Herbalism
            pPlayer->SEND_POI(9757.17f, 2430.16f, 7, 6, 0, "Kräuterkundelehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3039, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(10086.59f, 2255.77f, 7, 6, 0, "Lederverarbeitungslehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3040, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(10081.40f, 2257.18f, 7, 6, 0, "Kürschnerlehrer von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3042, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Tailoring
            pPlayer->SEND_POI(10079.70f, 2268.19f, 7, 6, 0, "Schneider von Darnassus");
            pPlayer->SEND_GOSSIP_MENU(3044, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_darnassus end
 *******************************************************/

CreatureAI* GetAI_guard_darnassus(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_dunmorogh start
 *******************************************************/

bool GossipHello_guard_dunmorogh(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN              , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(4287, pCreature->GetGUID());

    return true;
}

void SendDefaultMenu_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4288, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Gryphon master
            pPlayer->SEND_GOSSIP_MENU(4289, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(4290, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-5582.66f, -525.89f, 7, 6, 0, "Donnerbräu Brauerei");
            pPlayer->SEND_GOSSIP_MENU(4291, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
            pPlayer->SEND_POI(-5604.0f, -509.58f, 7, 6, 0, "Shelby Steinflinte");
            pPlayer->SEND_GOSSIP_MENU(5985, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(4292, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4300, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(-5618.29f, -454.25f, 7, 6, 0, "Grif Wildherz");
            pPlayer->SEND_GOSSIP_MENU(4293, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(-5585.6f, -539.99f, 7, 6, 0, "Magis Funkelmantel");
            pPlayer->SEND_GOSSIP_MENU(4294, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Paladin
            pPlayer->SEND_POI(-5585.6f, -539.99f, 7, 6, 0, "Azar Hammerkraft");
            pPlayer->SEND_GOSSIP_MENU(4295, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
            pPlayer->SEND_POI(-5591.74f, -525.61f, 7, 6, 0, "Maxan Anvol");
            pPlayer->SEND_GOSSIP_MENU(4296, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
            pPlayer->SEND_POI(-5602.75f, -542.4f, 7, 6, 0, "Hogral Bakkan");
            pPlayer->SEND_GOSSIP_MENU(4297, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(-5641.97f, -523.76f, 7, 6, 0, "Gimrizz Schattenrad");
            pPlayer->SEND_GOSSIP_MENU(4298, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(-5604.79f, -529.38f, 7, 6, 0, "Granis Flinkaxt");
            pPlayer->SEND_GOSSIP_MENU(4299, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_GOSSIP_MENU(4301, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-5584.72f, -428.41f, 7, 6, 0, "Bengus Tiefenschmied");
            pPlayer->SEND_GOSSIP_MENU(4302, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-5596.85f, -541.43f, 7, 6, 0, "Daryl Riknussun");
            pPlayer->SEND_GOSSIP_MENU(4303, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4304, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-5531.0f, -666.53f, 7, 6, 0, "Sprungspindel Zischelgang");
            pPlayer->SEND_GOSSIP_MENU(4305, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-5603.67f, -523.57f, 7, 6, 0, "Nissa Feuerstein");
            pPlayer->SEND_GOSSIP_MENU(4306, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-5199.9f, 58.58f, 7, 6, 0, "Grimnur Steinmal");
            pPlayer->SEND_GOSSIP_MENU(4307, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_GOSSIP_MENU(4308, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_GOSSIP_MENU(4310, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(-5531.0f, -666.53f, 7, 6, 0, "Geofram Geröllzeh");
            pPlayer->SEND_GOSSIP_MENU(4311, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_GOSSIP_MENU(4312, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4313, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_dunmorogh(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_dunmorogh(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_dunmorogh(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_dunmorogh end
 *******************************************************/

CreatureAI* GetAI_guard_dunmorogh(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_durotar start
 *******************************************************/

bool GossipHello_guard_durotar(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(4037, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4032, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind rider
            pPlayer->SEND_GOSSIP_MENU(4033, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(338.7f, -4688.87f, 7, 6, 0, "Gasthaus von Klingenhügel");
            pPlayer->SEND_GOSSIP_MENU(4034, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable master
            pPlayer->SEND_POI(330.31f, -4710.66f, 7, 6, 0, "Shoja'my");
            pPlayer->SEND_GOSSIP_MENU(5973, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(4035, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4036, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(276.0f, -4706.72f, 7, 6, 0, "Thotar");
            pPlayer->SEND_GOSSIP_MENU(4013, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(-839.33f, -4935.6f, 7, 6, 0, "Un'Thuwa");
            pPlayer->SEND_GOSSIP_MENU(4014, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(296.22f, -4828.1f, 7, 6, 0, "Tai'jin");
            pPlayer->SEND_GOSSIP_MENU(4015, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
            pPlayer->SEND_POI(265.76f, -4709.0f, 7, 6, 0, "Kaplak");
            pPlayer->SEND_GOSSIP_MENU(4016, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Shaman
            pPlayer->SEND_POI(307.79f, -4836.97f, 7, 6, 0, "Swart");
            pPlayer->SEND_GOSSIP_MENU(4017, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(355.88f, -4836.45f, 7, 6, 0, "Dhugru Blutgiert");
            pPlayer->SEND_GOSSIP_MENU(4018, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(312.3f, -4824.66f, 7, 6, 0, "Tarshaw Raunarbe");
            pPlayer->SEND_GOSSIP_MENU(4019, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-800.25f, -4894.33f, 7, 6, 0, "Miao'zan");
            pPlayer->SEND_GOSSIP_MENU(4020, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(373.24f, -4716.45f, 7, 6, 0, "Dwukk");
            pPlayer->SEND_GOSSIP_MENU(4021, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_GOSSIP_MENU(4022, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4023, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(368.95f, -4723.95f, 7, 6, 0, "Mukdrak");
            pPlayer->SEND_GOSSIP_MENU(4024, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(327.17f, -4825.62f, 7, 6, 0, "Rawrk");
            pPlayer->SEND_GOSSIP_MENU(4025, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-1065.48f, -4777.43f, 7, 6, 0, "Lau'Tiki");
            pPlayer->SEND_GOSSIP_MENU(4026, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-836.25f, -4896.89f, 7, 6, 0, "Mishiki");
            pPlayer->SEND_GOSSIP_MENU(4027, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_GOSSIP_MENU(4028, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(366.94f, -4705.0f, 7, 6, 0, "Krunn");
            pPlayer->SEND_GOSSIP_MENU(4029, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_GOSSIP_MENU(4030, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4031, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_durotar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_durotar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_durotar(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_durotar end
 *******************************************************/

CreatureAI* GetAI_guard_durotar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_elwynnforest start
 *******************************************************/

bool GossipHello_guard_elwynnforest(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(933, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4260, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Gryphon master
            pPlayer->SEND_GOSSIP_MENU(4261, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(4262, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-9459.34f, 42.08f, 7, 6, 0, "Gasthaus Zur Höhle des Löwen");
            pPlayer->SEND_GOSSIP_MENU(4263, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
            pPlayer->SEND_POI(-9466.62f, 45.87f, 7, 6, 0, "Erma");
            pPlayer->SEND_GOSSIP_MENU(5983, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(4264, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4273, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_GOSSIP_MENU(4265, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_GOSSIP_MENU(4266, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(-9471.12f, 33.44f, 7, 6, 0, "Zaldimar Wefhellt");
            pPlayer->SEND_GOSSIP_MENU(4268, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
            pPlayer->SEND_POI(-9469.0f, 108.05f, 7, 6, 0, "Bruder Wilhelm");
            pPlayer->SEND_GOSSIP_MENU(4269, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(-9461.07f, 32.6f, 7, 6, 0, "Priesterin Josetta");
            pPlayer->SEND_GOSSIP_MENU(4267, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
            pPlayer->SEND_POI(-9465.13f, 13.29f, 7, 6, 0, "Keryn Sylvius");
            pPlayer->SEND_GOSSIP_MENU(4270, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
            pPlayer->SEND_POI(-9473.21f, -4.08f, 7, 6, 0, "Maximillian Raab");
            pPlayer->SEND_GOSSIP_MENU(4272, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Warrior
            pPlayer->SEND_POI(-9461.82f, 109.50f, 7, 6, 0, "Lyria Du Lac");
            pPlayer->SEND_GOSSIP_MENU(4271, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-9057.04f, 153.63f, 7, 6, 0, "Alchemist Mallory");
            pPlayer->SEND_GOSSIP_MENU(4274, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-9456.58f, 87.90f, 7, 6, 0, "Schmied Argus");
            pPlayer->SEND_GOSSIP_MENU(4275, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-9467.54f, -3.16f, 7, 6, 0, "Tomas");
            pPlayer->SEND_GOSSIP_MENU(4276, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4277, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_GOSSIP_MENU(4278, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-9456.82f, 30.49f, 7, 6, 0, "Michelle Belle");
            pPlayer->SEND_GOSSIP_MENU(4279, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-9386.54f, -118.73f, 7, 6, 0, "Lee Braun");
            pPlayer->SEND_GOSSIP_MENU(4280, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-9060.70f, 149.23f, 7, 6, 0, "Kräuterkundige Pomeroy");
            pPlayer->SEND_GOSSIP_MENU(4281, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(-9376.12f, -75.23f, 7, 6, 0, "Adele Fädler");
            pPlayer->SEND_GOSSIP_MENU(4282, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_GOSSIP_MENU(4283, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(-9536.91f, -1212.76f, 7, 6, 0, "Helene Pelzschneider");
            pPlayer->SEND_GOSSIP_MENU(4284, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(-9376.12f, -75.23f, 7, 6, 0, "Eldrin");
            pPlayer->SEND_GOSSIP_MENU(4285, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_elwynnforest(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_elwynnforest(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_elwynnforest(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_elwynnforest end
 *******************************************************/

CreatureAI* GetAI_guard_elwynnforest(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_eversong start
 *******************************************************/

bool GossipHello_guard_eversong(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(10180, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_eversong(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bat Handler
            pPlayer->SEND_POI(9371.93f, -7164.80f, 7, 6, 0, "Flugmeister von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(10181, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(10182, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(9483.74f, -6844.58f, 7, 6, 0, "Gastwirt vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10183, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable Master
            pPlayer->SEND_POI(9489.62f, -6829.93f, 7, 6, 0, "Stallmeister vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10184, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(10180, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(10180, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_eversong(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_GOSSIP_MENU(10185, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(9527.44f, -6865.25f, 7, 6, 0, "Jägerlehrer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10186, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(9464.24f, -6855.52f, 7, 6, 0, "Magielehrer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10187, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
            pPlayer->SEND_POI(9517.61f, -6871.04f, 7, 6, 0, "Paladinlehrer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10189, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(9467.39f, -6845.72f, 7, 6, 0, "Priesterlehrer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10190, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
            pPlayer->SEND_POI(9533.67f, -6877.39f, 7, 6, 0, "Schurkenlehrer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10191, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
            pPlayer->SEND_POI(9468.99f, -6865.60f, 7, 6, 0, "Hexenmeisterlehrer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10192, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_eversong(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(8659.90f, -6368.12f, 7, 6, 0, "Alchemist von Saltherils Hafen");
            pPlayer->SEND_GOSSIP_MENU(10193, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(8984.21f, -7419.21f, 7, 6, 0, "Schmied der Zuflucht der Weltenwanderer");
            pPlayer->SEND_GOSSIP_MENU(10194, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(9494.04f, -6881.51f, 7, 6, 0, "Koch vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10195, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Engineering
            pPlayer->SEND_GOSSIP_MENU(10197, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(9479.46f, -6879.16f, 7, 6, 0, "Lehrer für Erste Hilfe vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10198, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
            pPlayer->SEND_GOSSIP_MENU(10199, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
            pPlayer->SEND_POI(8678.92f, -6329.09f, 7, 6, 0, "Kräuterkundiger von Saltherils Hafen");
            pPlayer->SEND_GOSSIP_MENU(10200, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Jewelcrafting
            pPlayer->SEND_POI(9484.32f, -6874.98f, 7, 6, 0, "Juwelenschleifer vom Falkenplatz");
            pPlayer->SEND_GOSSIP_MENU(10203, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(9362.04f, -7130.33f, 7, 6, 0, "Lederer des Immersangwalds");
            pPlayer->SEND_GOSSIP_MENU(10204, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_GOSSIP_MENU(10205, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(9362.04f, -7130.33f, 7, 6, 0, "Kürschner des Immersangwals");
            pPlayer->SEND_GOSSIP_MENU(10206, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(8680.36f, -6327.51f, 7, 6, 0, "Schneider von Saltherils Hafen");
            pPlayer->SEND_GOSSIP_MENU(10207, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_eversong(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_eversong(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_eversong(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_eversong(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_eversong end
 *******************************************************/

CreatureAI* GetAI_guard_eversong(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_exodar start
 *******************************************************/

bool GossipHello_guard_exodar(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(9551, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_exodar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
            pPlayer->SEND_POI(-4023.6f, -11739.3f, 7, 6, 0, "Auktionator der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9528, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-3923.89f, -11544.5f, 7, 6, 0, "Bank der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9529, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(-4092.57f, -11626.5f, 7, 6, 0, "Gildenmeister der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9539, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Hippogryph master
            pPlayer->SEND_POI(-4060.46f, -11787.1f, 7, 6, 0, "Hippogryphenmeister der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9530, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Inn
            pPlayer->SEND_POI(-3741.87f, -11695.1f, 7, 6, 0, "Gasthaus der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9545, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Mailbox
            pPlayer->SEND_POI(-3972.5f, -11696.0f, 7, 6, 0, "Briefkasten der Exodar");
            pPlayer->SEND_GOSSIP_MENU(10254, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Stable master
            pPlayer->SEND_POI(-3786.5f, -11702.5f, 7, 6, 0, "Stallmeister der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9558, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon trainer
            pPlayer->SEND_POI(-4215.68f, -11628.9f, 7, 6, 0, "Waffenmeister der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9565, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY       , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARENA               , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_EYEOFTHESTORM       , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(9531, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(9533, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU(9555, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_exodar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-3978.1f, -11357.0f, 7, 6, 0, "Kampfmeister für das Alteractal");
            pPlayer->SEND_GOSSIP_MENU(9531, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-3998.9f, -11345.2f, 7, 6, 0, "Kampfmeister für das Alteractal");
            pPlayer->SEND_GOSSIP_MENU(9531,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //A
            pPlayer->SEND_POI(-3759.27f, -11695.63f, 7, 6, 0, "Arenakampfmeister der Exodar");
            pPlayer->SEND_GOSSIP_MENU(10223, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //EOS
            pPlayer->SEND_POI(-3978.1f, -11357.0f, 7, 6, 0, "Kampfmeister für das Auge des Sturms");
            pPlayer->SEND_GOSSIP_MENU(9531, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //WSG
            pPlayer->SEND_POI(-3977.5f, -11381.2f, 7, 6, 0, "Kampfmeister für die Kriegshymnenschlucht");
            pPlayer->SEND_GOSSIP_MENU(9531, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_exodar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(-4276.0f, -11495.0f, 7, 6, 0, "Druidenlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9534, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(-4210.6f, -11575.2f, 7, 6, 0, "Jägerlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9544, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(-4057.32f, -11556.5f, 7, 6, 0, "Magierlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9550, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
            pPlayer->SEND_POI(-4191.2f, -11470.4f, 7, 6, 0, "Paladinlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9553, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(-3969.63f, -11482.8f, 7, 6, 0, "Priesterlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9554, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Shaman
            pPlayer->SEND_POI(-3805.5f, -11380.7f, 7, 6, 0, "Schamanenlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9556, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(-4189.43f, -11653.7f, 7, 6, 0, "Kriegerlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9562, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_exodar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-4040.6f, -11364.5f, 7, 6, 0, "Alchimilehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9527, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-4229.5f, -11706.0f, 7, 6, 0, "Schmiedekunstlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9532, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-3798.3f, -11651.7f, 7, 6, 0, "Koch der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9551, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-3889.3f, -11495.0f, 7, 6, 0, "Verzauberer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9535, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-4257.68f, -11640.3f, 7, 6, 0, "Ingenieurskunst der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9536, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-3769.5f, -11479.6f, 7, 6, 0, "Lehrer für Erste Hilfe der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9537, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-3725.5f, -11385.2f, 7, 6, 0, "Angellehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9538, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Jewelcrafting
            pPlayer->SEND_POI(-3783.0f, -11546.0f, 7, 6, 0, "Juwelenschleifer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9547, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Herbalism
            pPlayer->SEND_POI(-4040.6f, -11364.5f, 7, 6, 0, "Kräuterkundelehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9543, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Leatherworking
            pPlayer->SEND_POI(-4140.6f, -11776.7f, 7, 6, 0, "Lederverarbeitung der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9549, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Mining
            pPlayer->SEND_POI(-4228.0f, -11697.0f, 7, 6, 0, "Bergbaulehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9552, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Skinning
            pPlayer->SEND_POI(-4134.97f, -11760.5f, 7, 6, 0, "Kürschnerlehrer der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9557, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //Tailoring
            pPlayer->SEND_POI(-4092.5f, -11744.5f, 7, 6, 0, "Schneider der Exodar");
            pPlayer->SEND_GOSSIP_MENU(9559, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_exodar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_exodar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_exodar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_exodar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_exodar(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_exodar end
 *******************************************************/

CreatureAI* GetAI_guard_exodar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_ironforge start
 *******************************************************/

bool GossipHello_guard_ironforge(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_IRONFORGE_BANK    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DEEPRUNTRAM       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN               , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->SEND_GOSSIP_MENU(2760, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction House
            pPlayer->SEND_POI(-4957.39f, -911.6f, 7, 6, 0, "Auktionshaus von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(3014, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-4891.91f, -991.47f, 7, 6, 0, "Das Gewölbe");
            pPlayer->SEND_GOSSIP_MENU(2761, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Tram
            pPlayer->SEND_POI(-4835.27f, -1294.69f, 7, 6, 0, "Die Tiefenbahn");
            pPlayer->SEND_GOSSIP_MENU(3814, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Gryphon Master
            pPlayer->SEND_POI(-4821.52f, -1152.3f, 7, 6, 0, "Greifenmeister von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2762, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Guild Master
            pPlayer->SEND_POI(-5021.0f, -996.45f, 7, 6, 0, "Besucherzentrum von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2764, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Inn
            pPlayer->SEND_POI(-4850.47f, -872.57f, 7, 6, 0, "Steinfeuertaverne");
            pPlayer->SEND_GOSSIP_MENU(2768, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Mailbox
            pPlayer->SEND_POI(-4845.7f, -880.55f, 7, 6, 0, "Briefkasten von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2769, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable Master
            pPlayer->SEND_POI(-5010.2f, -1262.0f, 7, 6, 0, "Ulbrek Feuerhand");
            pPlayer->SEND_GOSSIP_MENU(5986, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Weapons Trainer
            pPlayer->SEND_POI(-5040.0f, -1201.88f, 7, 6, 0, "Bixi und Buliwyf");
            pPlayer->SEND_GOSSIP_MENU(4518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7529, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Class Trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE            , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(2766, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Profession Trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING   , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING     , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(2793, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-5047.87f, -1263.77f, 7, 6, 0, "Glordrum Stahlbart");
            pPlayer->SEND_GOSSIP_MENU(7483, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-5038.37f, -1266.39f, 7, 6, 0, "Donal Gutmark");
            pPlayer->SEND_GOSSIP_MENU(7649, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(-5037.24f, -1274.82f, 7, 6, 0, "Lylandris");
            pPlayer->SEND_GOSSIP_MENU(7528, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(-5023.0f, -1253.68f, 7, 6, 0, "Halle der Waffen");
            pPlayer->SEND_GOSSIP_MENU(2770, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(-4627.0f, -926.45f, 7, 6, 0, "Halle der Mysterien");
            pPlayer->SEND_GOSSIP_MENU(2771, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Paladin
            pPlayer->SEND_POI(-4627.02f, -926.45f, 7, 6, 0, "Halle der Mysterien");
            pPlayer->SEND_GOSSIP_MENU(2773, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
            pPlayer->SEND_POI(-4627.0f, -926.45f, 7, 6, 0, "Halle der Mysterien");
            pPlayer->SEND_GOSSIP_MENU(2772, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
            pPlayer->SEND_POI(-4647.83f, -1124.0f, 7, 6, 0, "Schurkenlehrer von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2774, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(-4605.0f, -1110.45f, 7, 6, 0, "Hexenmeisterlehrer von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2775, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(-5023.08f, -1253.68f, 7, 6, 0, "Halle der Waffen");
            pPlayer->SEND_GOSSIP_MENU(2776, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Shaman
            pPlayer->SEND_POI(-4732.0f, -1147.0f, 7, 6, 0, "Schamanenlehrer von Eisenschmiede");
                                                            //incorrect id
            pPlayer->SEND_GOSSIP_MENU(2766, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-4858.5f, -1241.83f, 7, 6, 0, "Brausefitz' Tränke und Mischgetränke");
            pPlayer->SEND_GOSSIP_MENU(2794, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-4796.97f, -1110.17f, 7, 6, 0, "Die große Schmiede");
            pPlayer->SEND_GOSSIP_MENU(2795, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-4767.83f, -1184.59f, 7, 6, 0, "Zum Bronzekessel");
            pPlayer->SEND_GOSSIP_MENU(2796, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-4803.72f, -1196.53f, 7, 6, 0, "Arkanarien Distelflaum");
            pPlayer->SEND_GOSSIP_MENU(2797, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-4799.56f, -1250.23f, 7, 6, 0, "Gerätehandel Sprungspindel");
            pPlayer->SEND_GOSSIP_MENU(2798, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-4881.6f, -1153.13f, 7, 6, 0, "Heiler von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2799, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-4597.91f, -1091.93f, 7, 6, 0, "Reisender Angler");
            pPlayer->SEND_GOSSIP_MENU(2800, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-4876.9f, -1151.92f, 7, 6, 0, "Heiler von Eisenschmiede");
            pPlayer->SEND_GOSSIP_MENU(2801, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(-4745.0f, -1027.57f, 7, 6, 0, "Lederwaren Feinspindel");
            pPlayer->SEND_GOSSIP_MENU(2802, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Minning
            pPlayer->SEND_POI(-4705.06f, -1116.43f, 7, 6, 0, "Tiefenbergbaugilde");
            pPlayer->SEND_GOSSIP_MENU(2804, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(-4745.0f, -1027.57f, 7, 6, 0, "Lederwaren Feinspindel");
            pPlayer->SEND_GOSSIP_MENU(2805, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(-4719.60f, -1056.96f, 7, 6, 0, "Tuchmacherei Steinbraue");
            pPlayer->SEND_GOSSIP_MENU(2807, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_ironforge end
 *******************************************************/

CreatureAI* GetAI_guard_ironforge(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_mulgore start
 *******************************************************/

bool GossipHello_guard_mulgore(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(3543, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4051, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind rider
            pPlayer->SEND_GOSSIP_MENU(4052, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(-2361.38f, -349.19f, 7, 6, 0, "Gasthaus der Bluthufe");
            pPlayer->SEND_GOSSIP_MENU(4053, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable master
            pPlayer->SEND_POI(-2338.86f, -357.56f, 7, 6, 0, "Seikwa");
            pPlayer->SEND_GOSSIP_MENU(5976, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(4069, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING   , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(4070, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(-2312.15f, -443.69f, 7, 6, 0, "Gennia Runentotem");
            pPlayer->SEND_GOSSIP_MENU(4054, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(-2178.14f, -406.14f, 7, 6, 0, "Yaw Scharfmäne");
            pPlayer->SEND_GOSSIP_MENU(4055, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Shaman
            pPlayer->SEND_POI(-2301.5f, -439.87f, 7, 6, 0, "Narm Himmelsjäger");
            pPlayer->SEND_GOSSIP_MENU(4056, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Warrior
            pPlayer->SEND_POI(-2345.43f, -494.11f, 7, 6, 0, "Krang Steinhuf");
            pPlayer->SEND_GOSSIP_MENU(4057, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_GOSSIP_MENU(4058, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_GOSSIP_MENU(4059, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-2263.34f, -287.91f, 7, 6, 0, "Pyall Leisetreter");
            pPlayer->SEND_GOSSIP_MENU(4060, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4061, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-2353.52f, -355.82f, 7, 6, 0, "Vira Junghuf");
            pPlayer->SEND_GOSSIP_MENU(4062, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
            pPlayer->SEND_POI(-2349.21f, -241.37f, 7, 6, 0, "Uthan Stillwasser");
            pPlayer->SEND_GOSSIP_MENU(4063, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
            pPlayer->SEND_GOSSIP_MENU(4064, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Leatherworking
            pPlayer->SEND_POI(-2257.12f, -288.63f, 7, 6, 0, "Chaw Starkfell");
            pPlayer->SEND_GOSSIP_MENU(4065, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mining
            pPlayer->SEND_GOSSIP_MENU(4066, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Skinning
            pPlayer->SEND_POI(-2252.94f, -291.32f, 7, 6, 0, "Yonn Pelzscherer");
            pPlayer->SEND_GOSSIP_MENU(4067, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4068, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_mulgore(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_mulgore(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_mulgore(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_mulgore end
 *******************************************************/

CreatureAI* GetAI_guard_mulgore(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_orgrimmar start
 *******************************************************/

bool GossipHello_guard_orgrimmar(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ZEPPLINMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_OFFICERS      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
    pPlayer->SEND_GOSSIP_MENU(2593, pCreature->GetGUID());

    return true;
}

void SendDefaultMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(1631.51f, -4375.33f, 7, 6, 0, "Bank von Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(2554, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //wind rider
            pPlayer->SEND_POI(1676.6f, -4332.72f, 7, 6, 0, "Der Himmelsturm");
            pPlayer->SEND_GOSSIP_MENU(2555, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //guild master
            pPlayer->SEND_POI(1576.93f, -4294.75f, 7, 6, 0, "Botschaft der Horde");
            pPlayer->SEND_GOSSIP_MENU(2556, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(1644.51f, -4447.27f, 7, 6, 0, "Gasthaus von Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(2557, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //mailbox
            pPlayer->SEND_POI(1622.53f, -4388.79f, 7, 6, 0, "Briefkasten von Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(2558, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //auction house
            pPlayer->SEND_POI(1679.21f, -4450.1f, 7, 6, 0, "Auktionshaus von Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(3075, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //zeppelin
            pPlayer->SEND_POI(1337.36f, -4632.7f, 7, 6, 0, "Zeppelinturm von Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(3173, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //weapon master
            pPlayer->SEND_POI(2092.56f, -4823.95f, 7, 6, 0, "Sayoc und Hanashi");
            pPlayer->SEND_GOSSIP_MENU(4519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //stable master
            pPlayer->SEND_POI(2133.12f, -4663.93f, 7, 6, 0, "Xon'cha");
            pPlayer->SEND_GOSSIP_MENU(5974, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //officers lounge
            pPlayer->SEND_POI(1633.56f, -4249.37f, 7, 6, 0, "Die Halle der Legenden");
            pPlayer->SEND_GOSSIP_MENU(7046, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY       , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(2599, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(2594, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Das Tal der Ehre");
            pPlayer->SEND_GOSSIP_MENU(7484, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Das Tal der Ehre");
            pPlayer->SEND_GOSSIP_MENU(7644, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Das Tal der Ehre");
            pPlayer->SEND_GOSSIP_MENU(7520, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(2114.84f, -4625.31f, 7, 6, 0, "Jägerhalle von Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(2559, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(1451.26f, -4223.33f, 7, 6, 0, "Dunkeldornenlodge");
            pPlayer->SEND_GOSSIP_MENU(2560, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(1442.21f, -4183.24f, 7, 6, 0, "Geisterlodge");
            pPlayer->SEND_GOSSIP_MENU(2561, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Shaman
            pPlayer->SEND_POI(1925.34f, -4181.89f, 7, 6, 0, "Thralls Festung");
            pPlayer->SEND_GOSSIP_MENU(2562, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
            pPlayer->SEND_POI(1773.39f, -4278.97f, 7, 6, 0, "Bruderschaft der Schattenläufer");
            pPlayer->SEND_GOSSIP_MENU(2563, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(1849.57f, -4359.68f, 7, 6, 0, "Dunkelfeuerenklave");
            pPlayer->SEND_GOSSIP_MENU(2564, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Halle der Kriegerhelden");
            pPlayer->SEND_GOSSIP_MENU(2565, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Paladin
            pPlayer->SEND_POI(1906.65f, -4134.26f, 7, 6, 0, "Tal der Weisheit");
            pPlayer->SEND_GOSSIP_MENU(10843, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(1955.17f, -4475.79f, 7, 6, 0, "Yelmaks Alchimie und Getränke");
            pPlayer->SEND_GOSSIP_MENU(2497, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(2054.34f, -4831.85f, 7, 6, 0, "Der brennende Amboss");
            pPlayer->SEND_GOSSIP_MENU(2499, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(1780.96f, -4481.31f, 7, 6, 0, "Borstans Feuergrube");
            pPlayer->SEND_GOSSIP_MENU(2500, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(1917.5f, -4434.95f, 7, 6, 0, "Godans Runenarbeiten");
            pPlayer->SEND_GOSSIP_MENU(2501, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(2038.45f, -4744.75f, 7, 6, 0, "Noggs Meistermaschinen");
            pPlayer->SEND_GOSSIP_MENU(2653, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(1485.21f, -4160.91f, 7, 6, 0, "Der Stärkste überlebt");
            pPlayer->SEND_GOSSIP_MENU(2502, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(1994.15f, -4655.7f, 7, 6, 0, "Lumaks Angeln");
            pPlayer->SEND_GOSSIP_MENU(2503, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(1898.61f, -4454.93f, 7, 6, 0, "Jandis Arboretum");
            pPlayer->SEND_GOSSIP_MENU(2504, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(1852.82f, -4562.31f, 7, 6, 0, "Kodolederer");
            pPlayer->SEND_GOSSIP_MENU(2513, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(2029.79f, -4704.0f, 7, 6, 0, "Bergbauunternehmen Rotschlucht");
            pPlayer->SEND_GOSSIP_MENU(2515, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(1852.82f, -4562.31f, 7, 6, 0, "Kodolederer");
            pPlayer->SEND_GOSSIP_MENU(2516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(1802.66f, -4560.66f, 7, 6, 0, "Magars Tuchwaren");
            pPlayer->SEND_GOSSIP_MENU(2518, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_orgrimmar end
 *******************************************************/

CreatureAI* GetAI_guard_orgrimmar(Creature* pCreature)
{
    return new guardAI_orgrimmar (pCreature);
}

/*******************************************************
 * guard_shattrath start
 *******************************************************/

bool GossipHello_guard_shattrath(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAVERN                       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK                         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN                          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHTMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX                      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MANALOOM                     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMYLAB                   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMMERCHANT                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(10321, pCreature->GetGUID());

    return true;
}

void SendDefaultMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Tavern
            pPlayer->SEND_POI(-1759.5f, 5165.0f, 7, 6, 0, "Wirtshaus von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10394, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKALDOR            , GOSSIP_SENDER_SEC_BANK, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKSCYERS           , GOSSIP_SENDER_SEC_BANK, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(10379, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNALDOR             , GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNSCYERS            , GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(10382, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Flight master
            pPlayer->SEND_POI(-1832.0f, 5299.0f, 7, 6, 0, "Taxi von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10385, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKALDOR           , GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNALDOR            , GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANKSCYERS          , GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INNSCYERS           , GOSSIP_SENDER_SEC_MAILBOX, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(10386, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEALDOR          , GOSSIP_SENDER_SEC_STABLEMASTER, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLESCYERS         , GOSSIP_SENDER_SEC_STABLEMASTER, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(10387, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERALLIANCE , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERHORDE    , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERARENA    , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(10388, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Profession master
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(10391, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mana Loom
            pPlayer->SEND_POI(-2070.0f, 5265.5f, 7, 6, 0, "Manawebrahmen");
            pPlayer->SEND_GOSSIP_MENU(10503, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Alchemy Lab
            pPlayer->SEND_POI(-1648.5f, 5540.0f, 7, 6, 0, "Alchemielabor");
            pPlayer->SEND_GOSSIP_MENU(10321, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Gem Merchant
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMALDOR             , GOSSIP_SENDER_SEC_GEMMERCHANT, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMSCYERS            , GOSSIP_SENDER_SEC_GEMMERCHANT, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(10697, pCreature->GetGUID());
            break;
    }
}

void SendBankMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_POI(-1730.5f, 5496.0f, 7, 6, 0, "Bank der Aldor von Shattrath");
        pPlayer->SEND_GOSSIP_MENU(10380,  pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_POI(-1997.7f, 5363.0f, 7, 6, 0, "Seherbank von Shattrath");
        pPlayer->SEND_GOSSIP_MENU(10381, pCreature->GetGUID());
    }
}

void SendInnMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_POI(-1895.0f, 5767.0f, 7, 6, 0, "Gasthaus der Aldor von Shattrath");
        pPlayer->SEND_GOSSIP_MENU(10383,  pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_POI(-2178.0f, 5405.0f, 7, 6, 0, "Gasthaus der Seher von Shattrath");
        pPlayer->SEND_GOSSIP_MENU(10384, pCreature->GetGUID());
    }
}

void SendMailboxMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->SEND_POI(-1730.5f, 5496.0f, 7, 6, 0, "Bank der Aldor von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10380,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->SEND_POI(-1895.0f, 5767.0f, 7, 6, 0, "Gasthaus der Aldor");
            pPlayer->SEND_GOSSIP_MENU(10383,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_POI(-1997.7f, 5363.0f, 7, 6, 0, "Seherbank von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10381, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            pPlayer->SEND_POI(-2178.0f, 5405.0f, 7, 6, 0, "Gasthaus der Seher");
            pPlayer->SEND_GOSSIP_MENU(10384, pCreature->GetGUID());
            break;
    }
}

void SendStableMasterMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_POI(-1888.5f, 5761.0f, 7, 6, 0, "Stall der Aldor von Shattrath");
        pPlayer->SEND_GOSSIP_MENU(10321,  pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_POI(-2170.0f, 5404.0f, 7, 6, 0, "Stall der Seher von Shattrath");
        pPlayer->SEND_GOSSIP_MENU(10321, pCreature->GetGUID());
    }
}

void SendBattleMasterMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->SEND_POI(-1774.0f, 5251.0f, 7, 6, 0, "Kampfmeister der Allianz von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10389, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->SEND_POI(-1963.0f, 5263.0f, 7, 6, 0, "Kapfmeister der Horde von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10390,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->SEND_POI(-1960.0f, 5175.0f, 7, 6, 0, "Arenakampfmeister von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(12510,  pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-1648.5f, 5534.0f, 7, 6, 0, "Alchemist von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10392, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-1847.0f, 5222.0f, 7, 6, 0, "Rüstungs- und Waffenmacher von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10400, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-2067.4f, 5316.5f, 7, 6, 0, "Koch von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10393, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-2263.5f, 5563.5f, 7, 6, 0, "Verzauberer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10395, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-1591.0f, 5265.5f, 7, 6, 0, "Erste Hilfe von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10396, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Jewelcrafting
            pPlayer->SEND_POI(-1654.0f, 5667.5f, 7, 6, 0, "Juwelenschleifer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10397, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(-2060.5f, 5256.5f, 7, 6, 0, "Lederer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10399, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(-2048.0f, 5300.0f, 7, 6, 0, "Kürschner von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10398, pCreature->GetGUID());
            break;
    }
}

void SendGemMerchantMenu_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_POI(-1645.0f, 5669.5f, 7, 6, 0, "Edelsteinhändler der Aldor");
        pPlayer->SEND_GOSSIP_MENU(10698,  pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_POI(-2193.0f, 5424.5f, 7, 6, 0, "Edelsteinhändler der Seher");
        pPlayer->SEND_GOSSIP_MENU(10699, pCreature->GetGUID());
    }
}

bool GossipSelect_guard_shattrath(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:              SendDefaultMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BANK:          SendBankMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_INN:           SendInnMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_STABLEMASTER:  SendStableMasterMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_GEMMERCHANT:   SendGemMerchantMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_MAILBOX:       SendMailboxMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:     SendProfTrainerMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:    SendBattleMasterMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_shattrath end
 *******************************************************/

CreatureAI* GetAI_guard_shattrath(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_shattrath_aldor
 *******************************************************/

#define SPELL_BANISHED_SHATTRATH_A  36642
#define SPELL_BANISHED_SHATTRATH_S  36671
#define SPELL_BANISH_TELEPORT       36643
#define SPELL_EXILE                 39533

struct MANGOS_DLL_DECL guard_shattrath_aldorAI : public guardAI
{
    guard_shattrath_aldorAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 Exile_Timer;
    uint32 Banish_Timer;
    uint64 playerGUID;
    bool CanTeleport;

    void Reset()
    {
        Banish_Timer = 5000;
        Exile_Timer = 8500;
        playerGUID = 0;
        CanTeleport = false;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (CanTeleport)
        {
            if (Exile_Timer < diff)
            {
                if (Unit* temp = Unit::GetUnit(*m_creature,playerGUID))
                {
                    temp->CastSpell(temp,SPELL_EXILE,true);
                    temp->CastSpell(temp,SPELL_BANISH_TELEPORT,true);
                }
                playerGUID = 0;
                Exile_Timer = 8500;
                CanTeleport = false;
            }else Exile_Timer -= diff;
        }
        else if (Banish_Timer < diff)
        {
            Unit* temp = m_creature->getVictim();
            if (temp && temp->GetTypeId() == TYPEID_PLAYER)
            {
                DoCast(temp,SPELL_BANISHED_SHATTRATH_A);
                Banish_Timer = 9000;
                playerGUID = temp->GetGUID();
                if (playerGUID)
                    CanTeleport = true;
            }
        }else Banish_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_guard_shattrath_aldor(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAVERN                       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK                         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN                          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHTMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX                      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MANALOOM                     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMYLAB                   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMMERCHANT                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(10524, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_shattrath_aldor(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Tavern
            pPlayer->SEND_POI(-1759.5f, 5165.0f, 7, 6, 0, "Wirtshaus von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10394, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-1730.5f, 5496.0f, 7, 6, 0, "Bank der Aldor von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10380, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(-1895.0f, 5767.0f, 7, 6, 0, "Gasthaus der Aldor von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10525,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Flight master
            pPlayer->SEND_POI(-1832.0f, 5299.0f, 7, 6, 0, "Taxi von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10402, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(0, 0, 7, 6, 0, "Gasthaus der Aldor von Shattrath");
                                                            //unknown
            pPlayer->SEND_GOSSIP_MENU(10524, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
            pPlayer->SEND_POI(-1888.5f, 5761.0f, 7, 6, 0, "Stall der Aldor von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10527, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERALLIANCE , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERHORDE    , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERARENA    , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(10388, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Profession master
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(10391, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mana Loom
            pPlayer->SEND_POI(-2070.0f, 5265.5f, 7, 6, 0, "Manawebrahmen");
            pPlayer->SEND_GOSSIP_MENU(10522, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Alchemy Lab
            pPlayer->SEND_POI(-1648.5f, 5540.0f, 7, 6, 0, "Alchemielabor");
            pPlayer->SEND_GOSSIP_MENU(10696, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Gem Merchant
            pPlayer->SEND_POI(-1645.0f, 5669.5f, 7, 6, 0, "Juwelenhändler der Aldor");
            pPlayer->SEND_GOSSIP_MENU(10411, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_shattrath_aldor(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-1648.5f, 5534.0f, 7, 6, 0, "Alchemist von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10392, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-1847.0f, 5222.0f, 7, 6, 0, "Rüstungs- und Waffenmacher von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10400, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-2067.4f, 5316.5f, 7, 6, 0, "Koch von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10393, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-2263.5f, 5563.5f, 7, 6, 0, "Verzauberer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10528, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-1591.0f, 5265.5f, 7, 6, 0, "Erste Hilfe von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10396, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Jewelcrafting
            pPlayer->SEND_POI(-1654.0f, 5667.5f, 7, 6, 0, "Juwelenschleifer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10529, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(-2060.5f, 5256.5f, 7, 6, 0, "Lederer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10399, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(-2048.0f, 5300.0f, 7, 6, 0, "Kürschner von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10419, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_shattrath_aldor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_shattrath_aldor(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_shattrath_aldor(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_shattrath_aldor end
 *******************************************************/

CreatureAI* GetAI_guard_shattrath_aldor(Creature* pCreature)
{
    return new guard_shattrath_aldorAI(pCreature);
}

/*******************************************************
 * guard_shattrath_scryer
 *******************************************************/

struct MANGOS_DLL_DECL guard_shattrath_scryerAI : public guardAI
{
    guard_shattrath_scryerAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 Exile_Timer;
    uint32 Banish_Timer;
    uint64 playerGUID;
    bool CanTeleport;

    void Reset()
    {
        Banish_Timer = 5000;
        Exile_Timer = 8500;
        playerGUID = 0;
        CanTeleport = false;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (CanTeleport)
        {
            if (Exile_Timer < diff)
            {
                if (Unit* temp = Unit::GetUnit(*m_creature,playerGUID))
                {
                    temp->CastSpell(temp,SPELL_EXILE,true);
                    temp->CastSpell(temp,SPELL_BANISH_TELEPORT,true);
                }
                playerGUID = 0;
                Exile_Timer = 8500;
                CanTeleport = false;
            }else Exile_Timer -= diff;
        }
        else if (Banish_Timer < diff)
        {
            Unit* temp = m_creature->getVictim();
            if (temp && temp->GetTypeId() == TYPEID_PLAYER)
            {
                DoCast(temp,SPELL_BANISHED_SHATTRATH_S);
                Banish_Timer = 9000;
                playerGUID = temp->GetGUID();
                if (playerGUID)
                    CanTeleport = true;
            }
        }else Banish_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_guard_shattrath_scryer(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAVERN                       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK                         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN                          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHTMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX                      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER                 , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MANALOOM                     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMYLAB                   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GEMMERCHANT                  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(10430, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_shattrath_scryer(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Tavern
            pPlayer->SEND_POI(-1759.5f, 5165.0f, 7, 6, 0, "Wirtshaus von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10431, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-1996.6f, 5363.7f, 7, 6, 0, "Seherbank von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10432, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(-2176.6f, 5405.8f, 7, 6, 0, "Gasthaus der Seher von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10433,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Flight master
            pPlayer->SEND_POI(-1832.0f, 5299.0f, 7, 6, 0, "Taxi von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10435, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(-2174.3f, 5411.4f, 7, 6, 0, "Gasthaus der Seher von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10436, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
            pPlayer->SEND_POI(-2169.9f, 5405.1f, 7, 6, 0, "Stall der Seher von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10437, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERALLIANCE , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERHORDE    , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERARENA    , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(10438, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Profession master
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(10504, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mana Loom
            pPlayer->SEND_POI(-2070.0f, 5265.5f, 7, 6, 0, "Manawebrahmen");
            pPlayer->SEND_GOSSIP_MENU(10522, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Alchemy Lab
            pPlayer->SEND_POI(-1648.5f, 5540.0f, 7, 6, 0, "Alchemielabor");
            pPlayer->SEND_GOSSIP_MENU(10701, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Gem Merchant
            pPlayer->SEND_POI(-1645.0f, 5669.5f, 7, 6, 0, "Edelsteinhändler der Seher");
            pPlayer->SEND_GOSSIP_MENU(10702, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_shattrath_scryer(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-1648.5f, 5534.0f, 7, 6, 0, "Alchemist von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-1847.0f, 5222.0f, 7, 6, 0, "Rüstungs- und Waffenmacher von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10517, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-2067.4f, 5316.5f, 7, 6, 0, "Koch von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-2263.5f, 5563.5f, 7, 6, 0, "Verzauberer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-1591.0f, 5265.5f, 7, 6, 0, "Erste Hilfe von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10520, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Jewelcrafting
            pPlayer->SEND_POI(-1654.0f, 5667.5f, 7, 6, 0, "Juwelenschleifer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(-2060.5f, 5256.5f, 7, 6, 0, "Lederer von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10523, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(-2048.0f, 5300.0f, 7, 6, 0, "Kürschner von Shattrath");
            pPlayer->SEND_GOSSIP_MENU(10523, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_shattrath_scryer(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_shattrath_scryer(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_shattrath_scryer(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_shattrath(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_shattrath_scryer end
 *******************************************************/

CreatureAI* GetAI_guard_shattrath_scryer(Creature* pCreature)
{
    return new guard_shattrath_scryerAI(pCreature);
}

/*******************************************************
 * guard_silvermoon start
 *******************************************************/

bool GossipHello_guard_silvermoon(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AH_SILVERMOON_1 , GOSSIP_SENDER_SEC_AUCTIONHOUSE, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AH_SILVERMOON_2 , GOSSIP_SENDER_SEC_AUCTIONHOUSE, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(9317, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(9808.4f, -7488.16f, 7, 6, 0, "Bank von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9322, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(9474.97f, -7345.21f, 7, 6, 0, "Gildenhaus von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9324, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN_SILVERMOON_1 , GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN_SILVERMOON_2 , GOSSIP_SENDER_SEC_INN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(9602, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(9658.33f, -7492.17f, 7, 6, 0, "Briefkasten von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9326, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Stable master
            pPlayer->SEND_POI(9904.95f, -7404.31f, 7, 6, 0, "Stallmeister von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9327, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Weapon trainer
            pPlayer->SEND_POI(9841.17f, -7505.13f, 7, 6, 0, "Waffenmeister von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9328, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Wind master
            pPlayer->SEND_POI(9378.45f, -7163.94f, 7, 6, 0, "Flugmeister von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(10181, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARENA           , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_EYEOFTHESTORM   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(9329, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(9331, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_JEWELCRAFTING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU(9338, pCreature->GetGUID());
            break;
    }
}

void SendAuctionhouseMenu_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_POI(9644.47f, -7140.22f, 7, 6, 0, "Auktionshaus von Silbermond");
        pPlayer->SEND_GOSSIP_MENU(9318, pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_POI(9683.27f, -7521.22f, 7, 6, 0, "Auktionshaus von Silbermond");
        pPlayer->SEND_GOSSIP_MENU(9319, pCreature->GetGUID());
    }
}

void SendInnMenu_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->SEND_POI(9677.7f, -7368.0f, 7, 6, 0, "Gasthaus von Silbermond");
        pPlayer->SEND_GOSSIP_MENU(9325, pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_POI(9561.1f, -7517.5f, 7, 6, 0, "Gasthaus von Silbermond");
        pPlayer->SEND_GOSSIP_MENU(9603, pCreature->GetGUID());
    }
}

void SendBattleMasterMenu_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(9850.49f, -7572.26f, 7, 6, 0, "Gurak");
            pPlayer->SEND_GOSSIP_MENU(9329, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(9857.18f, -7564.36f, 7, 6, 0, "Karen Ehrenpfand");
            pPlayer->SEND_GOSSIP_MENU(9329,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //A
            pPlayer->SEND_POI(9850.6f, -7559.25f, 7, 6, 0, "Bipp Glizzitor");
            pPlayer->SEND_GOSSIP_MENU(9329, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //EOS
            pPlayer->SEND_POI(9857.18f, -7564.36f, 7, 6, 0, "Karen Ehrenpfand");
            pPlayer->SEND_GOSSIP_MENU(9329, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //WSG
            pPlayer->SEND_POI(9845.45f, -7562.58f, 7, 6, 0, "Krukk");
            pPlayer->SEND_GOSSIP_MENU(9329, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(9700.55f, -7262.57f, 7, 6, 0, "Druidenlehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9330, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(9927.48f, -7426.14f, 7, 6, 0, "Jägerlehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9332, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(9995.07f, -7118.17f, 7, 6, 0, "Magielehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9333, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
            pPlayer->SEND_POI(9850.22f, -7516.93f, 7, 6, 0, "Paladinlehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9334, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(9926.79f, -7066.66f, 7, 6, 0, "Priesterlehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9335, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
            pPlayer->SEND_POI(9739.88f, -7374.33f, 7, 6, 0, "Schurkenlehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9336, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
            pPlayer->SEND_POI(9787.57f, -7284.63f, 7, 6, 0, "Hexenmeisterlehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9337, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(9998.09f, -7214.36f, 7, 6, 0, "Alchemielehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(9841.43f, -7361.53f, 7, 6, 0, "Schmiedekunst von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9340, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(9577.26f, -7243.6f, 7, 6, 0, "Kochen in Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(9962.57f, -7246.18f, 7, 6, 0, "Verzauberkunst von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9341, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(9820.18f, -7329.56f, 7, 6, 0, "Ingenieurskunst von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(9579.8f, -7343.71f, 7, 6, 0, "Erste Hilfe von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(9602.73f, -7328.3f, 7, 6, 0, "Angellehrer von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Jewelcrafting
            pPlayer->SEND_POI(9553.54f, -7506.43f, 7, 6, 0, "Juwelenschleifen von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9346, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Herbalism
            pPlayer->SEND_POI(10004.4f, -7216.86f, 7, 6, 0, "Kräuterkunde von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Leatherworking
            pPlayer->SEND_POI(9503.72f, -7430.16f, 7, 6, 0, "Lederverarbeitung von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9347, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Mining
            pPlayer->SEND_POI(9805.1f, -7355.56f, 7, 6, 0, "Bergbau von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9348, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Skinning
            pPlayer->SEND_POI(9513.37f, -7429.4f, 7, 6, 0, "Kürschnerei von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9316, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //Tailoring
            pPlayer->SEND_POI(9750.55f, -7095.28f, 7, 6, 0, "Schneiderei von Silbermond");
            pPlayer->SEND_GOSSIP_MENU(9350, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_silvermoon(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:                SendDefaultMenu_guard_silvermoon(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_AUCTIONHOUSE:    SendAuctionhouseMenu_guard_silvermoon(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_INN:             SendInnMenu_guard_silvermoon(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:      SendClassTrainerMenu_guard_silvermoon(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:       SendProfTrainerMenu_guard_silvermoon(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:      SendBattleMasterMenu_guard_silvermoon(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_silvermoon end
 *******************************************************/

CreatureAI* GetAI_guard_silvermoon(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_stormwind start
 *******************************************************/

bool GossipHello_guard_stormwind(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STORMWIND_BANK    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DEEPRUNTRAM       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN               , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_OFFICERS          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
    pPlayer->SEND_GOSSIP_MENU(933, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction House
            pPlayer->SEND_POI(-8811.46f, 667.46f, 7, 6, 0, "Auktionshaus von Sturmwind");
            pPlayer->SEND_GOSSIP_MENU(3834, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-8916.87f, 622.87f, 7, 6, 0, "Bank von Sturmwind");
            pPlayer->SEND_GOSSIP_MENU(764, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Deeprun tram
            pPlayer->SEND_POI(-8378.88f, 554.23f, 7, 6, 0, "Die Tiefenbahn");
            pPlayer->SEND_GOSSIP_MENU(3813, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-8869.0f, 675.4f, 7, 6, 0, "Die güldene Rose");
            pPlayer->SEND_GOSSIP_MENU(3860, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Gryphon Master
            pPlayer->SEND_POI(-8837.0f, 493.5f, 7, 6, 0, "Greifenmeister von Sturmwind");
            pPlayer->SEND_GOSSIP_MENU(879, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Guild Master
            pPlayer->SEND_POI(-8894.0f, 611.2f, 7, 6, 0, "Besucherzentrum von Sturmwind");
            pPlayer->SEND_GOSSIP_MENU(882, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Mailbox
            pPlayer->SEND_POI(-8876.48f, 649.18f, 7, 6, 0, "Briefkasten von Sturmwind");
            pPlayer->SEND_GOSSIP_MENU(3861, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable Master
            pPlayer->SEND_POI(-8433.0f, 554.7f, 7, 6, 0, "Jenova Steinschild");
            pPlayer->SEND_GOSSIP_MENU(5984, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Weapon Trainer
            pPlayer->SEND_POI(-8797.0f, 612.8f, 7, 6, 0, "Woo Ping");
            pPlayer->SEND_GOSSIP_MENU(4516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Officers Lounge
            pPlayer->SEND_POI(-8759.92f, 399.69f, 7, 6, 0, "Die Halle der Champions");
            pPlayer->SEND_GOSSIP_MENU(7047, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Battlemasters
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY        , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN          , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH          , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7499, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Class trainers
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(898, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //Profession trainers
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(918, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-8443.88f, 335.99f, 7, 6, 0, "Thelman Fausttadel");
            pPlayer->SEND_GOSSIP_MENU(7500, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-8443.88f, 335.99f, 7, 6, 0, "Lady Hoteshem");
            pPlayer->SEND_GOSSIP_MENU(7650, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(-8443.88f, 335.99f, 7, 6, 0, "Elfarran");
            pPlayer->SEND_GOSSIP_MENU(7501, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
            pPlayer->SEND_POI(-9012.0f, 867.6f, 7, 6, 0, "Magiersanktum");
            pPlayer->SEND_GOSSIP_MENU(899, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Rogue
            pPlayer->SEND_POI(-8753.0f, 367.8f, 7, 6, 0, "Schurkenhaus von Sturmwind");
            pPlayer->SEND_GOSSIP_MENU(900, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Warrior
            pPlayer->SEND_POI(-8624.54f, 402.61f, 7, 6, 0, "Gasthaus zum pfeifenden Schwein");
            pPlayer->SEND_GOSSIP_MENU(901, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Druid
            pPlayer->SEND_POI(-8751.0f, 1124.5f, 7, 6, 0, "Der Park");
            pPlayer->SEND_GOSSIP_MENU(902, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(-8512.0f, 862.4f, 7, 6, 0, "Kathedrale des Lichts");
            pPlayer->SEND_GOSSIP_MENU(903, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Paladin
            pPlayer->SEND_POI(-8577.0f, 881.7f, 7, 6, 0, "Kathedrale des Lichts");
            pPlayer->SEND_GOSSIP_MENU(904, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Hunter
            pPlayer->SEND_POI(-8413.0f, 541.5f, 7, 6, 0, "Jägerlodge");
            pPlayer->SEND_GOSSIP_MENU(905, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Warlock
            pPlayer->SEND_POI(-8948.91f, 998.35f, 7, 6, 0, "Zum geschlachtetem Lamm");
            pPlayer->SEND_GOSSIP_MENU(906, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Shaman
            pPlayer->SEND_POI(-9033.0f, 550.0f, 7, 6, 0, "Tal der Helden");
                                                            //incorrect id
            pPlayer->SEND_GOSSIP_MENU(2593, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-8988.0f, 759.60f, 7, 6, 0, "Alchimiebedarf");
            pPlayer->SEND_GOSSIP_MENU(919, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-8424.0f, 616.9f, 7, 6, 0, "Therum Tiefenschmied");
            pPlayer->SEND_GOSSIP_MENU(920, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-8611.0f, 364.6f, 7, 6, 0, "Taverne zum pfeifenden Schwein");
            pPlayer->SEND_GOSSIP_MENU(921, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-8858.0f, 803.7f, 7, 6, 0, "Lucan Cordell");
            pPlayer->SEND_GOSSIP_MENU(941, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-8347.0f, 644.1f, 7, 6, 0, "Lilliam Spindelfunks");
            pPlayer->SEND_GOSSIP_MENU(922, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-8513.0f, 801.8f, 7, 6, 0, "Shaina Fuller");
            pPlayer->SEND_GOSSIP_MENU(923, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-8803.0f, 767.5f, 7, 6, 0, "Arnold Leland");
            pPlayer->SEND_GOSSIP_MENU(940, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-8967.0f, 779.5f, 7, 6, 0, "Alchimiebedarf");
            pPlayer->SEND_GOSSIP_MENU(924, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(-8726.0f, 477.4f, 7, 6, 0, "Der schützende Balg");
            pPlayer->SEND_GOSSIP_MENU(925, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(-8434.0f, 692.8f, 7, 6, 0, "Gelman Steinhand");
            pPlayer->SEND_GOSSIP_MENU(927, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(-8716.0f, 469.4f, 7, 6, 0, "Der schützende Balg");
            pPlayer->SEND_GOSSIP_MENU(928, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(-8938.0f, 800.7f, 7, 6, 0, "Duncans Textilien");
            pPlayer->SEND_GOSSIP_MENU(929, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_stormwind end
 *******************************************************/

CreatureAI* GetAI_guard_stormwind(Creature* pCreature)
{
    return new guardAI_stormwind (pCreature);
}

/*******************************************************
 * guard_teldrassil start
 *******************************************************/

bool GossipHello_guard_teldrassil(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FERRY        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(4316, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4317, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Rut`theran
            pPlayer->SEND_GOSSIP_MENU(4318, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(4319, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(9821.49f, 960.13f, 7, 6, 0, "Gasthaus Dolanaar");
            pPlayer->SEND_GOSSIP_MENU(4320, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //stable master
            pPlayer->SEND_POI(9808.37f, 931.1f, 7, 6, 0, "Seriadne");
            pPlayer->SEND_GOSSIP_MENU(5982, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(4264, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(4273, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(9741.58f, 963.7f, 7, 6, 0, "Kal");
            pPlayer->SEND_GOSSIP_MENU(4323, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(9815.12f, 926.28f, 7, 6, 0, "Dazalar");
            pPlayer->SEND_GOSSIP_MENU(4324, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(9906.16f, 986.63f, 7, 6, 0, "Laurna Morgenglanz");
            pPlayer->SEND_GOSSIP_MENU(4325, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
            pPlayer->SEND_POI(9789.0f, 942.86f, 7, 6, 0, "Jannok Windsang");
            pPlayer->SEND_GOSSIP_MENU(4326, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(9821.96f, 950.61f, 7, 6, 0, "Kyra Windklinge");
            pPlayer->SEND_GOSSIP_MENU(4327, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(9767.59f, 878.81f, 7, 6, 0, "Cyndra Samtwisper");
            pPlayer->SEND_GOSSIP_MENU(4329, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Cooking
            pPlayer->SEND_POI(9751.19f, 906.13f, 7, 6, 0, "Zarrin");
            pPlayer->SEND_GOSSIP_MENU(4330, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Enchanting
            pPlayer->SEND_POI(10677.59f, 1946.56f, 7, 6, 0, "Alanna Rabenauge");
            pPlayer->SEND_GOSSIP_MENU(4331, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //First Aid
            pPlayer->SEND_POI(9903.12f, 999.0f, 7, 6, 0, "Byancie");
            pPlayer->SEND_GOSSIP_MENU(4332, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Fishing
            pPlayer->SEND_GOSSIP_MENU(4333, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Herbalism
            pPlayer->SEND_POI(9773.78f, 875.88f, 7, 6, 0, "Malorne Messerblatt");
            pPlayer->SEND_GOSSIP_MENU(4334, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(10152.59f, 1681.46f, 7, 6, 0, "Nadyia Schopfweber");
            pPlayer->SEND_GOSSIP_MENU(4335, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(10135.59f, 1673.18f, 7, 6, 0, "Radnaal Schopfweber");
            pPlayer->SEND_GOSSIP_MENU(4336, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4337, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_teldrassil(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_teldrassil(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_teldrassil(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_teldrassil end
 *******************************************************/

CreatureAI* GetAI_guard_teldrassil(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_tirisfal start
 *******************************************************/

bool GossipHello_guard_tirisfal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(4097, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4074, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //bat handler
            pPlayer->SEND_GOSSIP_MENU(4075, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(2246.68f, 241.89f, 7, 6, 0, "Taverne zur Galgenschlinge");
            pPlayer->SEND_GOSSIP_MENU(4076, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable Master
            pPlayer->SEND_POI(2267.66f, 319.32f, 7, 6, 0, "Morganus");
            pPlayer->SEND_GOSSIP_MENU(5978, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(4292, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4096, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Cain Feuerlied");
            pPlayer->SEND_GOSSIP_MENU(4077, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Priest
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Dunkler Kleriker Beryll");
            pPlayer->SEND_GOSSIP_MENU(4078, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Rogue
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Marion Kall");
            pPlayer->SEND_GOSSIP_MENU(4079, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Warlock
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Rupert Boch");
            pPlayer->SEND_GOSSIP_MENU(4080, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(2256.48f, 240.32f, 7, 6, 0, "Austil de Mon");
            pPlayer->SEND_GOSSIP_MENU(4081, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(2263.25f, 344.23f, 7, 6, 0, "Carolai Anise");
            pPlayer->SEND_GOSSIP_MENU(4082, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_GOSSIP_MENU(4083, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_GOSSIP_MENU(4084, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(2250.35f, 249.12f, 7, 6, 0, "Vance Niederglimm");
            pPlayer->SEND_GOSSIP_MENU(4085, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_GOSSIP_MENU(4086, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(2246.68f, 241.89f, 7, 6, 0, "Schwester Neela");
            pPlayer->SEND_GOSSIP_MENU(4087, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(2292.37f, -10.72f, 7, 6, 0, "Clyde Kellen");
            pPlayer->SEND_GOSSIP_MENU(4088, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(2268.21f, 331.69f, 7, 6, 0, "Faruza");
            pPlayer->SEND_GOSSIP_MENU(4089, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(2027.0f, 78.72f, 7, 6, 0, "Shelene Rhobart");
            pPlayer->SEND_GOSSIP_MENU(4090, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_GOSSIP_MENU(4091, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(2027.0f, 78.72f, 7, 6, 0, "Rand Rhobart");
            pPlayer->SEND_GOSSIP_MENU(4092, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(2160.45f, 659.93f, 7, 6, 0, "Bowen Brisboise");
            pPlayer->SEND_GOSSIP_MENU(4093, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_tirisfal(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_tirisfal(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_tirisfal(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_tirisfal end
 *******************************************************/

CreatureAI* GetAI_guard_tirisfal(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_undercity start
 *******************************************************/

bool GossipHello_guard_undercity(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ZEPPLINMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->SEND_GOSSIP_MENU(3543, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(1595.64f, 232.45f, 7, 6, 0, "Bank von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3514, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bat handler
            pPlayer->SEND_POI(1565.9f, 271.43f, 7, 6, 0, "Fledermausführer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3515, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(1594.17f, 205.57f, 7, 6, 0, "Gildenmeister von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(1639.43f, 220.99f, 7, 6, 0, "Gasthaus von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3517, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(1632.68f, 219.4f, 7, 6, 0, "Briefkasten von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Auction House
            pPlayer->SEND_POI(1647.9f, 258.49f, 7, 6, 0, "Auktionshaus von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Zeppelin
            pPlayer->SEND_POI(2059.0f, 274.86f, 7, 6, 0, "Zeppelin von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3520, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon Master
            pPlayer->SEND_POI(1670.31f, 324.66f, 7, 6, 0, "Archibald");
            pPlayer->SEND_GOSSIP_MENU(4521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Stable master
            pPlayer->SEND_POI(1634.18f, 226.76f, 7, 6, 0, "Anya Maulray");
            pPlayer->SEND_GOSSIP_MENU(5979, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7527, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE            , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(3542, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING   , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING     , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(3541, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(1329.0f, 333.92f, 7, 6, 0, "Grizzle Halbskalb");
            pPlayer->SEND_GOSSIP_MENU(7525, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(1283.3f, 287.16f, 7, 6, 0, "Sir Malory Wagner");
            pPlayer->SEND_GOSSIP_MENU(7646, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(1265.0f, 351.18f, 7, 6, 0, "Kurden Blutklaue");
            pPlayer->SEND_GOSSIP_MENU(7526, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
            pPlayer->SEND_POI(1781.0f, 53.0f, 7, 6, 0, "Magielehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3513, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Priest
            pPlayer->SEND_POI(1758.33f, 401.5f, 7, 6, 0, "Priesterlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Rogue
            pPlayer->SEND_POI(1418.56f, 65.0f, 7, 6, 0, "Schurkenlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3524, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Warlock
            pPlayer->SEND_POI(1780.92f, 53.16f, 7, 6, 0, "Hexenmeisterlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3526, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(1775.59f, 418.19f, 7, 6, 0, "Kriegerlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3527, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(1419.82f, 417.19f, 7, 6, 0, "Das Apothekarium");
            pPlayer->SEND_GOSSIP_MENU(3528, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(1696.0f, 285.0f, 7, 6, 0, "Schmiedekunstlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3529, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(1596.34f, 274.68f, 7, 6, 0, "Kochkunstlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3530, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(1488.54f, 280.19f, 7, 6, 0, "Verzauberkunstlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3531, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(1408.58f, 143.43f, 7, 6, 0, "Ingenieurskunstlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3532, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(1519.65f, 167.19f, 7, 6, 0, "Lehrer für Erste Hilfe von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3533, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(1679.9f, 89.0f, 7, 6, 0, "Angellehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3534, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(1558.0f, 349.36f, 7, 6, 0, "Kräuterkundelehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3535, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(1498.76f, 196.43f, 7, 6, 0, "Lederverarbeitungslehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3536, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(1642.88f, 335.58f, 7, 6, 0, "Bergbaulehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3537, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(1498.6f, 196.46f, 7, 6, 0, "Kürschnerlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3538, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(1689.55f, 193.0f, 7, 6, 0, "Schneiderlehrer von Unterstadt");
            pPlayer->SEND_GOSSIP_MENU(3539, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_undercity end
 *******************************************************/

CreatureAI* GetAI_guard_undercity(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_dalaran start
 *******************************************************/

enum{
	GOSSIP_SENDER_ARENA=					2,
	GOSSIP_SENDER_Q=						3,
	GOSSIP_SENDER_BANK=						4,
	GOSSIP_SENDER_I=						5,
	GOSSIP_SENDER_MAIL=						6,
	GOSSIP_SENDER_POI=						7,
	GOSSIP_SENDER_TRAINERS=					8,
	GOSSIP_SENDER_VENDORS=					9,
	GOSSIP_SENDER_ARMOR=					10,
	GOSSIP_SENDER_WEAPONS=					11,
	GOSSIP_SENDER_PROFTRAINER=				12
};

#define GOSSIP_TEXT_ARENA					"Arena"
#define GOSSIP_TEXT_BARBER					"Barbier"
#define GOSSIP_TEXT_CAPITAL_PORTALS			"Portale zu den Hauptst�dten"
#define GOSSIP_TEXT_FLIGHT_MASTER			"Den Flugmeister"
#define GOSSIP_TEXT_LOCKSMITH				"Schlosser"
#define GOSSIP_TEXT_POINTS_OF_INTEREST		"Sehensw�rdigkeiten"
#define GOSSIP_TEXT_ACTION_HOUSE			"Auktionshaus"
#define GOSSIP_TEXT_BANK					"Die Bank"
#define GOSSIP_TEXT_BATTLEMASTERS			"Kampfmeister"
#define GOSSIP_TEXT_GUILDMASTER				"Gildenmeister"
#define GOSSIP_TEXT_INN						"Gasthaus"
#define GOSSIP_TEXT_MAILBOX					"Einen Briefkasten"
#define GOSSIP_TEXT_STABLEMASTER			"Der Stallmeister"
#define GOSSIP_TEXT_TRAINERS				"Lehrer"
#define GOSSIP_TEXT_VENDOR					"Verk�ufer"

//Arena
#define GOSSIP_TEXT_E_S_E					"�stlicher Eingang zur Kanalisation"
#define GOSSIP_TEXT_W_S_E					"Westlicher Eingang zur Kanalisation"
#define GOSSIP_TEXT_W_E						"Brunneneingang"
//Action House
#define GOSSIP_TEXT_A_Q						"Das Viertel der Allianz"
#define GOSSIP_TEXT_H_Q						"Das Viertel der Horde"
//Bank
#define GOSSIP_TEXT_N_B						"N�rdliche Bank"
#define GOSSIP_TEXT_S_B						"S�dliche Bank"
#define GOSSIP_TEXT_SE						"Die Kanalisation"
//Inn
#define GOSSIP_TEXT_A_I						"Allianzgasthaus"
#define GOSSIP_TEXT_H_I						"Hordengasthaus"
//Mail
#define GOSSIP_TEXT_K_L						"Krasus' Landeplatz"
//Points of Inetrest
#define GOSSIP_TEXT_V_C						"Die Violette Zitadelle"
#define GOSSIP_TEXT_V_H						"Die Violette Festung"
#define GOSSIP_TEXT_T						"Handelsdistrikt"
#define GOSSIP_TEXT_A_M						"Antonidas' Denkmal"
#define GOSSIP_TEXT_R_S						"Runenweberplatz"
#define GOSSIP_TEXT_T_E						"Die Abendruh"
#define GOSSIP_TEXT_C						"Friedhof"
#define GOSSIP_TEXT_L_o_P					"Lexikon der Macht"
//Trainers
#define GOSSIP_TEXT_C_T						"Ein Lehrer f�r eine Klasse"
#define GOSSIP_TEXT_C_W_F_T					"Lehrer f�r Kaltwetterflug"
#define GOSSIP_TEXT_Po_T					"Portallehrer"
#define GOSSIP_TEXT_Pr_T					"Ein Lehrer f�r einen Beruf"
//Vendors
#define GOSSIP_TEXT_A						"R�stung"
#define GOSSIP_TEXT_Cl						"Kleidung"
#define GOSSIP_TEXT_E_G						"Emblemausr�stung"
#define GOSSIP_TEXT_F						"Blumen"
#define GOSSIP_TEXT_Fr						"Obst"
#define GOSSIP_TEXT_G_G						"Gemischtwaren"
#define GOSSIP_TEXT_J						"Juwelier"
#define GOSSIP_TEXT_P_S_A_E_M				"Tierbedarf & exotische Reittiere"
#define GOSSIP_TEXT_P_P_A_C					"Kuchen, Geb�ck & Torten"
#define GOSSIP_TEXT_R_A_M_G					"Reagenzien & magischen Gegenst�nde"
#define GOSSIP_TEXT_T						"Spielzeug"
#define GOSSIP_TEXT_T_S						"Handwerksbedarf"
#define GOSSIP_TEXT_T_R_A_O_I				"Schmuckst�cke, Relikte & Schildhandgegenst�nde"
#define GOSSIP_TEXT_W						"Waffen"
#define GOSSIP_TEXT_W_A_C					"Wein & K�se"
//Vendor 
#define GOSSIP_TEXT_C_A						"Stoffr�stung"
#define GOSSIP_TEXT_L_A						"Lederr�stung"
#define GOSSIP_TEXT_M_A						"Schwere R�stung"
#define GOSSIP_TEXT_P_A						"Plattenr�stung"
#define GOSSIP_TEXT_S						"Schilde"
#define GOSSIP_TEXT_M_W						"Nahkampfwaffen"
#define GOSSIP_TEXT_R_A_T_W					"Fernkampf- & Wurfwaffen"
#define GOSSIP_TEXT_S_A_W					"St�be und Zauberst�be"

//Trainer 
#define GOSSIP_TEXT_Al						"Alchemie"
#define GOSSIP_TEXT_Bl						"Schmiedekunst"
#define GOSSIP_TEXT_Co						"Kochkunst"
#define GOSSIP_TEXT_En						"Verzauberkunst"
#define GOSSIP_TEXT_Eng						"Ingenieurskunst"
#define GOSSIP_TEXT_F_A						"Erste Hilfe"
#define GOSSIP_TEXT_Fi						"Angeln"
#define GOSSIP_TEXT_He						"Kr�uterkunde"
#define GOSSIP_TEXT_In						"Inschriftenkunde"
#define GOSSIP_TEXT_Jew						"Juwelenschleifen"
#define GOSSIP_TEXT_Le						"Lederverarbeitung"
#define GOSSIP_TEXT_Min						"Bergbau"
#define GOSSIP_TEXT_Skin					"K�rschnerei"
#define GOSSIP_TEXT_Ta						"Schneiderei"

bool GossipHello_guard_dalaran(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARENA				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ACTION_HOUSE			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BARBER				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERS		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CAPITAL_PORTALS		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHT_MASTER		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LOCKSMITH			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_POINTS_OF_INTEREST	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TRAINERS				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_VENDOR				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
    pPlayer->SEND_GOSSIP_MENU(14014, pCreature->GetGUID());
    return true;
}
void SendDefaultMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch (action)
	{
		//Arena
		case GOSSIP_ACTION_INFO_DEF + 1: 
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_E_S_E, GOSSIP_SENDER_ARENA, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W_S_E, GOSSIP_SENDER_ARENA, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W_E	, GOSSIP_SENDER_ARENA, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->SEND_GOSSIP_MENU(13976, pCreature->GetGUID());
			break;
		//Action House
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(14010, pCreature->GetGUID());
			break;
		//Bank
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_N_B, GOSSIP_SENDER_BANK, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_S_B, GOSSIP_SENDER_BANK, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->SEND_GOSSIP_MENU(14007, pCreature->GetGUID());
			break;
		//Barber
		case GOSSIP_ACTION_INFO_DEF + 4: 
			pPlayer->SEND_POI(5892.12f, 618.577f, 7, 6, 0, "Barbier von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14003, pCreature->GetGUID());
			break;
		//Battlemasters
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(13977, pCreature->GetGUID());
			break;
		//Portals
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(13977, pCreature->GetGUID());
		break;
		//Flight Master
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5813.37f, 453.403f, 7, 6, 0, "Der Flugmeister von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14004, pCreature->GetGUID());
		break;
		//Guild Master
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5767.96f, 627.193f, 7, 6, 0, "Das Besucherzentrum von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14015, pCreature->GetGUID());
			break;
		//Inn
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_I, GOSSIP_SENDER_I   , GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_I, GOSSIP_SENDER_I	  , GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->SEND_POI(5859.86f, 634.46f, 7, 6, 0, "Gasthaus von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14002, pCreature->GetGUID());
			break;
		//Locksmith
		case GOSSIP_ACTION_INFO_DEF + 10:
			pPlayer->SEND_POI(5934.13f, 575.821f, 7, 6, 0, "Der Schlosser von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14251, pCreature->GetGUID());
			break;
		//Mailbox
		case GOSSIP_ACTION_INFO_DEF + 11:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_K_L , GOSSIP_SENDER_MAIL, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->SEND_GOSSIP_MENU(14008, pCreature->GetGUID());
			break;
	   //Points of Inetrest
		case GOSSIP_ACTION_INFO_DEF + 12:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q	, GOSSIP_SENDER_Q	, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q	, GOSSIP_SENDER_Q	, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_V_C	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_V_H	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SE	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_K_L	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_M	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_R_S	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_E	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 8);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_L_o_P, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->SEND_GOSSIP_MENU(13975, pCreature->GetGUID());
			break;
		//Stable Master
		case GOSSIP_ACTION_INFO_DEF + 13: pPlayer->SEND_POI(5859.68f, 557.571f, 7, 6, 0, "Der Stallmeister von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14001, pCreature->GetGUID());
			break;
		//Trainer
		case GOSSIP_ACTION_INFO_DEF + 14:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C_T	  , GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C_W_F_T, GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Po_T	  , GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Pr_T	  , GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->SEND_GOSSIP_MENU(14000, pCreature->GetGUID());
			break;
		//Vendors
		case GOSSIP_ACTION_INFO_DEF + 15:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Cl		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_E_G		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_F		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Fr		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_G_G		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_J		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_P_S_A_E_M, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 8);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_P_P_A_C	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_R_A_M_G	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 10);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 11);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_S		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 12);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_R_A_O_I, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 13);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 14);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W_A_C	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 15);
			pPlayer->SEND_GOSSIP_MENU(14117, pCreature->GetGUID());
			break;
	}

}

void SendArenaMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5805.33f, 556.04f, 7, 6, 0, "�stlicher Eingang zur Kanalisation");
			pPlayer->SEND_GOSSIP_MENU(13961, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5816.37f, 758.51f, 7, 6, 0, "Westlicher Eingang zur Kanalisation");
			pPlayer->SEND_GOSSIP_MENU(13960, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5885.96f, 647.26f, 7, 6, 0, "Brunnen von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13969, pCreature->GetGUID());
			break;
	}

}
void SendQuarterMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action){

		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5762.29f, 712.98f, 7, 6, 0, "Die Silberne Enklave");
			pPlayer->SEND_GOSSIP_MENU(13973, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5857.64f, 593.74f, 7, 6, 0, "Sonnenh�schers Zuflucht");
			pPlayer->SEND_GOSSIP_MENU(13973, pCreature->GetGUID());
			break;
	}
}

void SendBankMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action){

		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5926.78f, 646.52f, 7, 6, 0, "Die S�dliche Bank von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14005, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5679.18f, 666.92f, 7, 6, 0, "Die N�rdliche Bank von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14006, pCreature->GetGUID());
			break;
	}

}
void SendInnMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
	case GOSSIP_ACTION_INFO_DEF + 1:
		pPlayer->SEND_POI(5735.24f, 676.15f, 7, 6, 0, "Das Allianzgasthaus von Dalaran");
		pPlayer->SEND_GOSSIP_MENU(13992, pCreature->GetGUID());
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		pPlayer->SEND_POI(5885.10f, 527.30f, 7, 6, 0, "Das Hordengasthaus von Dalaran");
		pPlayer->SEND_GOSSIP_MENU(13993, pCreature->GetGUID());
		break;
	}

}
void SendMailMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
	case GOSSIP_ACTION_INFO_DEF + 1:
		pPlayer->SEND_POI(5831.95f, 507.86f, 7, 6, 0, GOSSIP_TEXT_K_L);
		pPlayer->SEND_GOSSIP_MENU(14009, pCreature->GetGUID());
		break;
	}
}
void SendPoiMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5790.33f, 737.05f, 7, 6, 0, "Die Violette Zitadelle");
			pPlayer->SEND_GOSSIP_MENU(13971, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5692.27f, 500.17f, 7, 6, 0, "Die Violette Festung");
			pPlayer->SEND_GOSSIP_MENU(13970, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5897.56f, 733.24f, 7, 6, 0, "Handelsdistrikt");
			pPlayer->SEND_GOSSIP_MENU(13980, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5831.99f, 657.70f, 7, 6, 0, "Krasus' Landeplatz");
			pPlayer->SEND_GOSSIP_MENU(14009, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->SEND_POI(5949.71f, 669.26f, 7, 6, 0, "Antonidas' Denkmal");
			pPlayer->SEND_GOSSIP_MENU(13968, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->SEND_POI(5805.78f, 647.68f, 7, 6, 0, "Runenweberplatz");
			pPlayer->SEND_GOSSIP_MENU(13967, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5713.84f, 646.22f, 7, 6, 0, "Die Abendruh");
			pPlayer->SEND_GOSSIP_MENU(13966, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5856.75f, 697.99f, 7, 6, 0, "Der Friedhof von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13965, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->SEND_POI(5848.27f, 766.34f, 7, 6, 0, "Lexikon der Macht");
			pPlayer->SEND_GOSSIP_MENU(14174, pCreature->GetGUID());
			break;
	}
}
void SendTrainersMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5807.69f, 586.88f, 7, 6, 0, "Der Magierlehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13999, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5815.27f, 473.49f, 7, 6, 0, "Krasus' Landeplatz");
			pPlayer->SEND_GOSSIP_MENU(13998, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5807.69f, 586.88f, 7, 6, 0, "Der Portallehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13999, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Al  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Bl  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Co  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_En  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Eng , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_F_A , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Fi  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_He  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 8);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_In  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Jew , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 10);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Le  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 11);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Min , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 12);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Skin, GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 13);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Ta  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 14);
			pPlayer->SEND_GOSSIP_MENU(13996, pCreature->GetGUID());
	}

}
void SendVendorsMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{

	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_L_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_M_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_P_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_S  , GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->SEND_GOSSIP_MENU(14114, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5786.20f, 647.08f, 7, 6, 0, "Stoffr�stung & Kleidung in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14112, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(14108, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5773.01f, 577.11f, 7, 6, 0, "Blumen in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14107, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->SEND_POI(5753.19f, 694.93f, 7, 6, 0, "Obstverk�ufer in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14106, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->SEND_POI(5688.13f, 648.05f, 7, 6, 0, "Gemischt- & Handwerkswaren in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14105, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5871.58f, 725.30f, 7, 6, 0, "Juwelenschleifen von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13984, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5833.19f, 571.80f, 7, 6, 0, "Tierbedarf in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14103, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->SEND_POI(5906.07f, 627.51f, 7, 6, 0, "Kuchen, Geb�ck und Torten in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14102, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 10:
			pPlayer->SEND_POI(5767.48f, 732.60f, 7, 6, 0, "Reagenzien in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14104, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 11:
			pPlayer->SEND_POI(5819.48f, 696.89f, 7, 6, 0, "Spielzeug in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14100, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 12:
			pPlayer->SEND_POI(5690.12f, 621.70f, 7, 6, 0, "Gemischt- & Handwerkswaren in Dalaran");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Pr_T, GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->SEND_GOSSIP_MENU(14101, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 13:
			pPlayer->SEND_POI(5762.18f, 638.81f, 7, 6, 0, "Schmuckst�cke in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14110, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 14:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_M_W	  , GOSSIP_SENDER_WEAPONS, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_R_A_T_W, GOSSIP_SENDER_WEAPONS, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_S_A_W  , GOSSIP_SENDER_WEAPONS, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->SEND_GOSSIP_MENU(14113, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 15:
			pPlayer->SEND_POI(5879.49f, 612.42f, 7, 6, 0, "Wein & K�se in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14095, pCreature->GetGUID());
			break;
	}
}
void SendArmorMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5786.20f, 647.08f, 7, 6, 0, "Stoffr�stung & Kleidung");
			pPlayer->SEND_GOSSIP_MENU(14112, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5675.09f, 630.65f, 7, 6, 0, "Leder & Schwere R�stung");
			pPlayer->SEND_GOSSIP_MENU(14111, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5675.09f, 630.65f, 7, 6, 0, "Plattenr�stung & Schilde");
			pPlayer->SEND_GOSSIP_MENU(14109, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5675.09f, 630.65f, 7, 6, 0, "Plattenr�stung & Schilde");
			pPlayer->SEND_GOSSIP_MENU(14109, pCreature->GetGUID());
			break;
	}

}
void SendWeaponsMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5731.85f, 608.23f, 7, 6, 0, "Nahkampfwaffen");
			pPlayer->SEND_GOSSIP_MENU(14098, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5783.44f, 561.81f, 7, 6, 0, "Fernkampfwaffen");
			pPlayer->SEND_GOSSIP_MENU(14097, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5674.73f, 647.00f, 7, 6, 0, "St�be & Zauberst�be");
			pPlayer->SEND_GOSSIP_MENU(14096, pCreature->GetGUID());
			break;
	}

}
void SendProfTrainerMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5895.75f, 711.08f, 7, 6, 0, "Alchemielehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13995, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5900.17f, 686.36f, 7, 6, 0, "Schmiedekunst von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13994, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_I, GOSSIP_SENDER_I, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_I, GOSSIP_SENDER_I, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(13991, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5835.09f, 719.40f, 7, 6, 0, "Verzauberkunst von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13990, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->SEND_POI(5914.88f, 728.24f, 7, 6, 0, "Ingenieurskunst von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13989, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->SEND_POI(5864.82f, 737.73f, 7, 6, 0, "Erste Hilfe von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13988, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5703.40f, 615.44f, 7, 6, 0, "Angellehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13987, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5872.11f, 687.78f, 7, 6, 0, "Kr�uterkunde von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13986, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->SEND_POI(5859.55f, 700.48f, 7, 6, 0, "Inschriftenkunde von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13985, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 10:
			pPlayer->SEND_POI(5872.69f, 724.94f, 7, 6, 0, "Juwelenschleifen von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13984, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 11:
			pPlayer->SEND_POI(5902.58f, 746.44f, 7, 6, 0, "Lederverarbeitung von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13982, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 12:
			pPlayer->SEND_POI(5914.93f, 710.01f, 7, 6, 0, "Bergbau von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13983, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 13:
			pPlayer->SEND_POI(5902.58f, 746.44f, 7, 6, 0, "K�rschnerei von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13982, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 14:
			pPlayer->SEND_POI(5883.58f, 741.38f, 7, 6, 0, "Schneiderei von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13981, pCreature->GetGUID());
			break;
	}
}

bool GossipSelect_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (sender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_dalaran(pPlayer, pCreature, action); break;
		case GOSSIP_SENDER_ARENA:           SendArenaMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_Q:               SendQuarterMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_BANK:			SendBankMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_I:               SendInnMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_MAIL:            SendMailMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_POI:             SendPoiMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_TRAINERS:        SendTrainersMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_VENDORS:         SendVendorsMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_ARMOR:           SendArmorMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_WEAPONS:         SendWeaponsMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_PROFTRAINER:     SendProfTrainerMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
    }
    return true;
}

/*******************************************************
 * guard_dalaran end
 *******************************************************/

CreatureAI* GetAI_guard_dalaran(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * AddSC
 *******************************************************/

void AddSC_guards()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "guard_azuremyst";
    //newscript->pGossipHello          = &GossipHello_guard_azuremyst;
    //newscript->pGossipSelect         = &GossipSelect_guard_azuremyst;
    newscript->GetAI = &GetAI_guard_azuremyst;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_bluffwatcher";
    //newscript->pGossipHello          = &GossipHello_guard_bluffwatcher;
    //newscript->pGossipSelect         = &GossipSelect_guard_bluffwatcher;
    newscript->GetAI = &GetAI_guard_bluffwatcher;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_contested";
    newscript->GetAI = &GetAI_guard_contested;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_darnassus";
    //newscript->pGossipHello          = &GossipHello_guard_darnassus;
    //newscript->pGossipSelect         = &GossipSelect_guard_darnassus;
    newscript->GetAI = &GetAI_guard_darnassus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_dunmorogh";
    //newscript->pGossipHello          = &GossipHello_guard_dunmorogh;
    //newscript->pGossipSelect         = &GossipSelect_guard_dunmorogh;
    newscript->GetAI = &GetAI_guard_dunmorogh;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_durotar";
    //newscript->pGossipHello          = &GossipHello_guard_durotar;
    //newscript->pGossipSelect         = &GossipSelect_guard_durotar;
    newscript->GetAI = &GetAI_guard_durotar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_elwynnforest";
    //newscript->pGossipHello          = &GossipHello_guard_elwynnforest;
    //newscript->pGossipSelect         = &GossipSelect_guard_elwynnforest;
    newscript->GetAI = &GetAI_guard_elwynnforest;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_eversong";
    //newscript->pGossipHello          = &GossipHello_guard_eversong;
    //newscript->pGossipSelect         = &GossipSelect_guard_eversong;
    newscript->GetAI = &GetAI_guard_eversong;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_exodar";
    //newscript->pGossipHello          = &GossipHello_guard_exodar;
    //newscript->pGossipSelect         = &GossipSelect_guard_exodar;
    newscript->GetAI = &GetAI_guard_exodar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_ironforge";
    //newscript->pGossipHello          = &GossipHello_guard_ironforge;
    //newscript->pGossipSelect         = &GossipSelect_guard_ironforge;
    newscript->GetAI = &GetAI_guard_ironforge;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_mulgore";
    //newscript->pGossipHello          = &GossipHello_guard_mulgore;
    //newscript->pGossipSelect         = &GossipSelect_guard_mulgore;
    newscript->GetAI = &GetAI_guard_mulgore;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_orgrimmar";
    //newscript->pGossipHello          = &GossipHello_guard_orgrimmar;
    //newscript->pGossipSelect         = &GossipSelect_guard_orgrimmar;
    newscript->GetAI = &GetAI_guard_orgrimmar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_shattrath";
    //newscript->pGossipHello          = &GossipHello_guard_shattrath;
    //newscript->pGossipSelect         = &GossipSelect_guard_shattrath;
    newscript->GetAI = &GetAI_guard_shattrath;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_shattrath_aldor";
    newscript->GetAI = &GetAI_guard_shattrath_aldor;
    newscript->pGossipHello          = &GossipHello_guard_shattrath_aldor;
    newscript->pGossipSelect         = &GossipSelect_guard_shattrath_aldor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_shattrath_scryer";
    newscript->GetAI = &GetAI_guard_shattrath_scryer;
    newscript->pGossipHello          = &GossipHello_guard_shattrath_scryer;
    newscript->pGossipSelect         = &GossipSelect_guard_shattrath_scryer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_silvermoon";
    //newscript->pGossipHello          = &GossipHello_guard_silvermoon;
    //newscript->pGossipSelect         = &GossipSelect_guard_silvermoon;
    newscript->GetAI = &GetAI_guard_silvermoon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_stormwind";
    //newscript->pGossipHello          = &GossipHello_guard_stormwind;
    //newscript->pGossipSelect         = &GossipSelect_guard_stormwind;
    newscript->GetAI = &GetAI_guard_stormwind;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_teldrassil";
    //newscript->pGossipHello          = &GossipHello_guard_teldrassil;
    //newscript->pGossipSelect         = &GossipSelect_guard_teldrassil;
    newscript->GetAI = &GetAI_guard_teldrassil;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_tirisfal";
    //newscript->pGossipHello          = &GossipHello_guard_tirisfal;
    //newscript->pGossipSelect         = &GossipSelect_guard_tirisfal;
    newscript->GetAI = &GetAI_guard_tirisfal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_undercity";
    //newscript->pGossipHello          = &GossipHello_guard_undercity;
    //newscript->pGossipSelect         = &GossipSelect_guard_undercity;
    newscript->GetAI = &GetAI_guard_undercity;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_dalaran";
    newscript->pGossipHello          = &GossipHello_guard_dalaran;
    newscript->pGossipSelect         = &GossipSelect_guard_dalaran;
    newscript->GetAI = &GetAI_guard_undercity;
    newscript->RegisterSelf();
}
