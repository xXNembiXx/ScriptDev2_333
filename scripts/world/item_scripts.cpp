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
SDName: Item_Scripts
SD%Complete: 100
SDComment: Items for a range of different items. See content below (in script)
SDCategory: Items
EndScriptData */

/* ContentData
item_arcane_charges                 Prevent use if player is not flying (cannot cast while on ground)
item_nether_wraith_beacon(i31742)   Summons creatures for quest Becoming a Spellfire Tailor (q10832)
item_flying_machine(i34060,i34061)  Engineering crafted flying machines
item_gor_dreks_ointment(i30175)     Protecting Our Own(q10488)
EndContentData */

#include "precompiled.h"
#include "Spell.h"

/*#####
# item_arcane_charges
#####*/

enum
{
    SPELL_ARCANE_CHARGES    = 45072
};

bool ItemUse_item_arcane_charges(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
    if (pPlayer->isInFlight())
        return false;

    pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, NULL);

    if (const SpellEntry* pSpellInfo = GetSpellStore()->LookupEntry(SPELL_ARCANE_CHARGES))
        Spell::SendCastResult(pPlayer, pSpellInfo, 1, SPELL_FAILED_NOT_ON_GROUND);

    return true;
}

/*#####
# item_nether_wraith_beacon
#####*/

bool ItemUse_item_nether_wraith_beacon(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
    if (pPlayer->GetQuestStatus(10832) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->SummonCreature(22408,pPlayer->GetPositionX() ,pPlayer->GetPositionY()+20, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,180000);
        pPlayer->SummonCreature(22408,pPlayer->GetPositionX() ,pPlayer->GetPositionY()-20, pPlayer->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN,180000);
    }
    return false;
}

/*#####
# item_flying_machine
#####*/

bool ItemUse_item_flying_machine(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
    uint32 itemId = pItem->GetEntry();

    if (itemId == 34060)
        if (pPlayer->GetBaseSkillValue(SKILL_RIDING) >= 225)
            return false;

    if (itemId == 34061)
        if (pPlayer->GetBaseSkillValue(SKILL_RIDING) == 300)
            return false;

    debug_log("SD2: Player attempt to use item %u, but did not meet riding requirement",itemId);
    pPlayer->SendEquipError(EQUIP_ERR_CANT_EQUIP_SKILL, pItem, NULL);
    return true;
}

/*#####
# item_gor_dreks_ointment
#####*/

enum
{
    NPC_TH_DIRE_WOLF        = 20748,
    SPELL_GORDREKS_OINTMENT = 32578
};

bool ItemUse_item_gor_dreks_ointment(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
    if (pTargets.getUnitTarget() && pTargets.getUnitTarget()->GetTypeId() == TYPEID_UNIT && pTargets.getUnitTarget()->HasAura(SPELL_GORDREKS_OINTMENT))
    {
        pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, NULL);

        if (const SpellEntry* pSpellInfo = GetSpellStore()->LookupEntry(SPELL_GORDREKS_OINTMENT))
            Spell::SendCastResult(pPlayer, pSpellInfo, 1, SPELL_FAILED_TARGET_AURASTATE);

        return true;
    }

    return false;
}

/*#####
# item_petrov_cluster_bombs
#####*/

enum
{
    SPELL_PETROV_BOMB           = 42406,
    AREA_ID_SHATTERED_STRAITS   = 4064,
    ZONE_ID_HOWLING             = 495
};

bool ItemUse_item_petrov_cluster_bombs(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
    if (pPlayer->GetZoneId() != ZONE_ID_HOWLING)
        return false;

    if (!pPlayer->GetTransport() || pPlayer->GetAreaId() != AREA_ID_SHATTERED_STRAITS)
    {
        pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, NULL);

        if (const SpellEntry* pSpellInfo = GetSpellStore()->LookupEntry(SPELL_PETROV_BOMB))
            Spell::SendCastResult(pPlayer, pSpellInfo, 1, SPELL_FAILED_NOT_HERE);

        return true;
    }

    return false;
}

/*#####
# item_uthers_tribute
#####*/

enum
{
	SPELL_HUMAN_TRIBUTE		= 24105,
	SPELL_DWARF_TRIBUTE		= 24107,
	SPELL_NIGHTELF_TRIBUTE	= 24108,
	SPELL_GNOME_TRIBUTE		= 24106,
	SPELL_DRAENEI_TRIBUTE	= 69533,
	GO_HUMAN_TRIBUTE		= 180210,
	GO_NIGHTELF_TRIBUTE		= 180213,
	GO_DWARF_TRIBUTE		= 180214,
	GO_GNOME_TRIBUTE		= 180211,
	GO_DRAENEI_TRIBUTE		= 201294,
	AREA_UTHERS_TOMB_STATUE	= 196,
	ITEM_UTHERS_TRIBUTE		= 19850
};

bool ItemUse_item_uthers_tribute(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
	if (pPlayer->GetTeam() != ALLIANCE)
		return false;
	if (pPlayer->GetAreaId() != AREA_UTHERS_TOMB_STATUE)
		return false;

	switch (pPlayer->getRace()) {

		case RACE_HUMAN:
			pPlayer->CastSpell(pPlayer, SPELL_HUMAN_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_HUMAN_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_DWARF:
			pPlayer->CastSpell(pPlayer, SPELL_DWARF_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_DWARF_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_NIGHTELF:
			pPlayer->CastSpell(pPlayer, SPELL_NIGHTELF_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_NIGHTELF_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_GNOME:
			pPlayer->CastSpell(pPlayer, SPELL_GNOME_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_GNOME_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_DRAENEI:
			pPlayer->CastSpell(pPlayer, SPELL_DRAENEI_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_DRAENEI_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
	}
	pPlayer->DestroyItemCount(ITEM_UTHERS_TRIBUTE, 1, true);
	return true;
}

/*#####
# item_uthers_tribute
#####*/

enum
{
	SPELL_ORC_TRIBUTE		= 24104,
	SPELL_UNDEAD_TRIBUTE	= 24103,
	SPELL_TAUREN_TRIBUTE	= 24102,
	SPELL_TROLL_TRIBUTE		= 24101,
	SPELL_BLOODELF_TRIBUTE	= 69530,
	GO_ORC_TRIBUTE			= 180207,
	GO_UNDEAD_TRIBUTE		= 180208,
	GO_TAUREN_TRIBUTE		= 180209,
	GO_TROLL_TRIBUTE		= 180206,
	GO_BLOODELF_TRIBUTE		= 180212,
	GO_GROMS_MONUMENT		= 21004,
	ITEM_GROMS_TRIBUTE		= 19851
};

bool ItemUse_item_groms_tribute(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
	if (pPlayer->GetTeam() != HORDE)
		return false;

	if (GameObject* MonumentGO = GetClosestGameObjectWithEntry(pPlayer, GO_GROMS_MONUMENT, 10.0f)) {
		switch (pPlayer->getRace()) {

		case RACE_ORC:
			pPlayer->CastSpell(pPlayer, SPELL_ORC_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_ORC_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
			case RACE_UNDEAD_PLAYER:
			pPlayer->CastSpell(pPlayer, SPELL_UNDEAD_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_UNDEAD_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_TAUREN:
			pPlayer->CastSpell(pPlayer, SPELL_TAUREN_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_TAUREN_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_TROLL:
			pPlayer->CastSpell(pPlayer, SPELL_TROLL_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_TROLL_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		case RACE_BLOODELF:
			pPlayer->CastSpell(pPlayer, SPELL_BLOODELF_TRIBUTE, false);
			pPlayer->SummonGameobject(GO_BLOODELF_TRIBUTE,pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0, 5);
			break;
		}
		pPlayer->DestroyItemCount(ITEM_GROMS_TRIBUTE, 1, true);
		return true;
	}
	else
		return false;
}
  
void AddSC_item_scripts()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "item_arcane_charges";
    newscript->pItemUse = &ItemUse_item_arcane_charges;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_nether_wraith_beacon";
    newscript->pItemUse = &ItemUse_item_nether_wraith_beacon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_flying_machine";
    newscript->pItemUse = &ItemUse_item_flying_machine;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_gor_dreks_ointment";
    newscript->pItemUse = &ItemUse_item_gor_dreks_ointment;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "item_petrov_cluster_bombs";
    newscript->pItemUse = &ItemUse_item_petrov_cluster_bombs;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "item_uthers_tribute";
    newscript->pItemUse = &ItemUse_item_uthers_tribute;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "item_groms_tribute";
    newscript->pItemUse = &ItemUse_item_groms_tribute;
    newscript->RegisterSelf();
}
