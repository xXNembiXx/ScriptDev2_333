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

/* ContentData
oculus_event_edwin			Addtion to Inferna Christmas PreEvent
EndContentData */

#include "precompiled.h"
#include "oculus.h"



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


//Need: Animation!
bool GOHello_go_oculus_cannon(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_DATA_COLLISION)))
            pGate->SetGoState(GO_STATE_ACTIVE);
	if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_DATA_GATE1)))
		pGate->SetPhaseMask(0, true);

	m_pInstance->SetData(GO_DATA_CANNON, IN_PROGRESS);
    return false;

}


CreatureAI* GetAI_oculus_event_edwin(Creature* pCreature)
{
    return new oculus_event_edwinAI(pCreature);
}

void AddSC_oculus_event()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_event_edwin";
    newscript->GetAI = &GetAI_oculus_event_edwin;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_cannon";
    newscript->pGOHello = &GOHello_go_oculus_cannon;
    newscript->RegisterSelf();
}