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
SDName: Deadmines
SD%Complete: 99
SDAuthor: Nembi, Nerdrage 
SDComment: Contains GO for event at end door
SDCategory: Deadmines
EndScriptData */


/* ContentData
go_door_lever_dm				
go_defias_cannon
boss_mrsmite
EndContentData */



#include "precompiled.h"
#include "deadmines.h"

bool GOHello_go_door_lever_dm(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    GameObject* pGoDoor = pInstance->instance->GetGameObject(pInstance->GetData64(DATA_DEFIAS_DOOR));

    if (pGoDoor && pGoDoor->GetGoState() == 1)
        return false;

    return true;
}

bool GOHello_go_defias_cannon(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    if (pInstance->GetData(TYPE_DEFIAS_ENDDOOR) == DONE || pInstance->GetData(TYPE_DEFIAS_ENDDOOR) == IN_PROGRESS)
        return false;

    pInstance->SetData(TYPE_DEFIAS_ENDDOOR, IN_PROGRESS);
    return false;
}



enum
{
	SAY_AGGRO				= -1036001,
	SAY_PHASE_1				= -1036002,
	SAY_PHASE_2				= -1036003,
	
	EQUIP_ID_SWORD			= 5191,
	EQUIP_ID_AXE			= 5196,
	EQUIP_ID_HAMMER			= 7230,

	SPELL_SMITE_SLAM		= 6435, 	/* Melee stun Phase 2 */
	SPELL_SMITE_STOMP		= 6432, 	/* Phase transition stun */
	SPELL_THRASH			= 3417,		/* 10% Chance to double attack Phase 1 */
	SPELL_SMITE_HAMMER		= 6436, 	/* Hammer thing, not supported */
		SPELL_DUAL_WIELD		= 30798, 	/* Doesn't work, neither 674 */

	NPC_DEFIAS_BLACKGUARD	= 636,
};

struct MANGOS_DLL_DECL boss_mrsmiteAI : public ScriptedAI
{
	boss_mrsmiteAI(Creature* pCreature) : ScriptedAI(pCreature) 
	{	

		SpawnOrientation	=	(m_creature->GetOrientation());

		Reset();	
	}

	bool	WaitedOrNot;
	bool 	WentToChest;
	uint32	SlamTimer;
	uint32	Phase;
	uint32	WaitTimer;
	uint32	SpawnOrientation;

	void Reset()
	{
		const CreatureInfo *cinfo = m_creature->GetCreatureInfo();
		m_creature->SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE, 0*cinfo->mindmg);
        m_creature->SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE, 0*cinfo->maxdmg);
        m_creature->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, cinfo->mindmg);
        m_creature->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, cinfo->maxdmg);
        m_creature->UpdateDamagePhysical(BASE_ATTACK);
		m_creature->SetStandState(UNIT_STAND_STATE_STAND);

		m_creature->SetStandState(UNIT_STAND_STATE_STAND);
		m_creature->SetAttackTime(BASE_ATTACK, 2000);
		SetEquipmentSlots(false, EQUIP_ID_SWORD, EQUIP_UNEQUIP, EQUIP_UNEQUIP);
		SetCombatMovement(true);
		
		WaitTimer		= 3000;
		WaitedOrNot		= false;
		WentToChest		= false;
		SlamTimer		= 10000;
		Phase			= 0;
	}
	
	void JustReachedHome()
    {
		m_creature->SetFacingTo(SpawnOrientation);
    }

	void Aggro(Unit* pWho)
	{
		m_creature->SetAttackTime(BASE_ATTACK, 2000);
		DoCastSpellIfCan(m_creature, SPELL_DUAL_WIELD);
		DoScriptText(SAY_AGGRO, m_creature);

		if (Creature* pDefias_Blackguard = GetClosestCreatureWithEntry(m_creature, NPC_DEFIAS_BLACKGUARD, 29.0f))
		{
			pDefias_Blackguard->AddThreat(pWho,5);
			pDefias_Blackguard->CallForHelp(8);
		}
	}

	void UpdateAI(const uint32 uiDiff)
	{
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
            
		if (m_creature->GetHealthPercent() < 66.6f && m_creature->GetHealthPercent() > 33.3f) 
		{
			if (Phase == 0)
			{
				DoCastSpellIfCan(m_creature, SPELL_SMITE_STOMP);

				DoScriptText(SAY_PHASE_1, m_creature);

				m_creature->AttackStop();
				Phase = 1;
			}
		}
		else if (m_creature->GetHealthPercent() < 33.3f)
		{
			if (Phase == 1 || Phase == 0)
			{
				DoCastSpellIfCan(m_creature, SPELL_SMITE_STOMP);
				DoCastSpellIfCan(m_creature, SPELL_SMITE_HAMMER);

				DoScriptText(SAY_PHASE_2, m_creature);

				m_creature->AttackStop();

				WaitedOrNot = false;
				WentToChest = false;
				Phase = 2;	
			}

		}
			
		if (Phase == 1)
		{
			if (WentToChest == false)
			{
				m_creature->GetMotionMaster()->MovePoint(0, 1.337549f, -780.446716f, 9.8376685f);
				SetCombatMovement(false);
				WentToChest = true;
			}

			if (m_creature->IsStopped() == true && m_creature->isAttackingPlayer() == false )
			{
				// Only there so this part doesn't repeat a hundred times
				if (m_creature->IsStandState())
				{
					m_creature->SetOrientation(1.337549f);
					m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
					SetEquipmentSlots(false, EQUIP_ID_AXE, EQUIP_ID_AXE, EQUIP_NO_CHANGE);

					const CreatureInfo *cinfo = m_creature->GetCreatureInfo();
					m_creature->SetAttackTime(OFF_ATTACK, 2000);
					m_creature->setAttackTimer(OFF_ATTACK, 0);
					m_creature->SetBaseWeaponDamage(OFF_ATTACK, MINDAMAGE, cinfo->mindmg*0.6);
					m_creature->SetBaseWeaponDamage(OFF_ATTACK, MAXDAMAGE, cinfo->maxdmg*0.6);
					m_creature->UpdateDamagePhysical(OFF_ATTACK);

					// Should hit normal damage with one weapon, 60% with other one
					// If he still has the same speed, that's 160% of base damage, update to mindmg*1 when dual-wield
					m_creature->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, cinfo->mindmg*1.6);
					m_creature->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, cinfo->maxdmg*1.6);
					m_creature->UpdateDamagePhysical(BASE_ATTACK);
					m_creature->SetAttackTime(BASE_ATTACK, 2000);
				}

				if (WaitTimer < uiDiff && WaitedOrNot == false)
				{
					m_creature->SetStandState(UNIT_STAND_STATE_STAND);

					DoCastSpellIfCan(m_creature, SPELL_THRASH);

					SetCombatMovement(true);
					m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());

					WaitedOrNot = true;
					WaitTimer = 3000;
				}
				else
				{
					WaitTimer -= uiDiff;
				}
			}
		}
		else if (Phase == 2)
		{
			if (WentToChest == false)
			{
				m_creature->RemoveAurasDueToSpell(SPELL_THRASH);
				m_creature->GetMotionMaster()->MovePoint(0, 1.337549f, -780.446716f, 9.8376685f);
				SetCombatMovement(false);
				WentToChest = true;
			}

			if (SlamTimer < uiDiff)
			{
				// Cast Slam in phase two handed, maybe timer a bit incorrect
				DoCastSpellIfCan(m_creature->getVictim(), SPELL_SMITE_SLAM);
				SlamTimer = urand(8000, 15000);
			}
			else
			{
				SlamTimer -= uiDiff;
			}
			if (m_creature->IsStopped() == true && m_creature->isAttackingPlayer() == false )
			{
				if (m_creature->IsStandState())
				{
					m_creature->SetAttackTime(BASE_ATTACK, 3200);
					m_creature->SetSheath(SHEATH_STATE_UNARMED);
					SetEquipmentSlots(false, EQUIP_ID_HAMMER, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);

					m_creature->SetOrientation(1.337549f);
					m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);

					const CreatureInfo *cinfo = m_creature->GetCreatureInfo();
					m_creature->SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE, 0*cinfo->mindmg);
					m_creature->SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE, 0*cinfo->maxdmg);
					m_creature->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 1.7*cinfo->mindmg);
					m_creature->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 1.7*cinfo->maxdmg);
					m_creature->UpdateDamagePhysical(BASE_ATTACK);
				}
				if (WaitTimer < uiDiff && WaitedOrNot == false)
				{
					m_creature->SetStandState(UNIT_STAND_STATE_STAND);

					SetCombatMovement(true);
					m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());

					WaitedOrNot = true;
				}
				else
				{
					WaitTimer -= uiDiff;
				}
			}
		}

		DoMeleeAttackIfReady();
	}
};
	
	
CreatureAI* GetAI_boss_mrsmite(Creature* pCreature)
{
	return new boss_mrsmiteAI(pCreature);
}


void AddSC_deadmines()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "go_door_lever_dm";
    newscript->pGOHello = &GOHello_go_door_lever_dm;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_defias_cannon";
    newscript->pGOHello = &GOHello_go_defias_cannon;
    newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "boss_mrsmite";
	newscript->GetAI = &GetAI_boss_mrsmite;
	newscript->RegisterSelf();
}
