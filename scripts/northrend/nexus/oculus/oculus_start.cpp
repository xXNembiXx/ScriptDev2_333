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

/* ContentData
oculus_start_image_oramus1				Addtion to Inferna Christmas PreEvent
oculus_start_image_oramus1_trigger1		Addtion to Inferna Christmas PreEvent
EndContentData */

#include "precompiled.h"
#include "oculus.h"

/*######
## Image of Oramus TRIGGER 1 WP START
######*/

#define NPC_IMAGE_ORAMUS1		400056


struct MANGOS_DLL_DECL oculus_start_image_oramus1_trigger1AI : public ScriptedAI
{
    oculus_start_image_oramus1_trigger1AI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

	ScriptedInstance* m_pInstance;

	void Reset()
	{
	}

	void MoveInLineOfSight(Unit *pWho) 
	{
		if(pWho->GetTypeId() != TYPEID_PLAYER)
		  return;
		m_creature->SummonCreature(NPC_IMAGE_ORAMUS1, 1180.405029f, 969.289368f, 323.325226f, 3.053628f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 999000);
		m_creature->ForcedDespawn();
	}

	void UpdateAI(const uint32 diff)
	{
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

		DoMeleeAttackIfReady();
	}
};


/*######
## Image of Oramus 1
######*/

#define WP_START	-1000000
#define WP_MIDDLE	-1000000

struct MANGOS_DLL_DECL oculus_start_image_oramus1AI : public ScriptedAI
{
    oculus_start_image_oramus1AI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

	ScriptedInstance* m_pInstance;


	void Reset()
	{
		m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
		m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
	}

	void EnterCombat()
	{
		return;
	}
};

CreatureAI* GetAI_oculus_start_image_oramus1_trigger1(Creature* pCreature)
{
    return new oculus_start_image_oramus1_trigger1AI(pCreature);
}

CreatureAI* GetAI_oculus_start_image_oramus1(Creature* pCreature)
{
    return new oculus_start_image_oramus1AI(pCreature);
}

void AddSC_oculus_start()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_start_image_oramus1_trigger1";
    newscript->GetAI = &GetAI_oculus_start_image_oramus1_trigger1;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_start_image_oramus1";
    newscript->GetAI = &GetAI_oculus_start_image_oramus1;
    newscript->RegisterSelf();
}