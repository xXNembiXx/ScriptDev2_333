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
SDComment: Inferna Christmas PreEvent == The last Stand (Endboss)
SDCategory: Oculus
EndScriptData */

/* ContentData
oculus_boss_oramus				Addtion to Inferna Christmas PreEvent
EndContentData */

#include "precompiled.h"
#include "oculus.h"


/*######
## oculus_boss_oramus
######*/

enum
{

};

struct MANGOS_DLL_DECL oculus_boss_oramusAI : public ScriptedAI
{
    oculus_boss_oramusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }


    ScriptedInstance* m_pInstance;


    void Reset()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void JustDied(Unit* pKiller)
    {
    }

    void EnterCombat(Unit* pWho)
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void KilledUnit(Unit* pKiller)
    {
    }


    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_oculus_boss_oramus(Creature* pCreature)
{
    return new oculus_boss_oramusAI(pCreature);
}

void AddSC_oculus_boss()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_boss_oramus";
    newscript->GetAI = &GetAI_oculus_boss_oramus;
    newscript->RegisterSelf();
}