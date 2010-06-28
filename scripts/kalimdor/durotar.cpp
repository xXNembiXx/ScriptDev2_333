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
SDName: Durotar
SD%Complete: 100
SDComment: Quest support: 5441
SDCategory: Durotar
EndScriptData */

/* ContentData
npc_lazy_peon
EndContentData */

#include "precompiled.h"

/*######
## npc_lazy_peon
######*/

#define SPELL_AWAKEN_PEON	19938
#define SPELL_PEON_SLEEPING	17743

struct MANGOS_DLL_DECL npc_lazy_peonAI : public ScriptedAI
{
    npc_lazy_peonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
		Reset();
    }

	uint32 Emote_Timer;
	bool m_bEmote;

    void Reset()
	{
		m_bEmote = false;
	}

	void UpdateAI(const uint32 diff)
    {
		if (m_bEmote)
		{
			if (Emote_Timer < diff)
			{
				m_creature->CastSpell(m_creature,SPELL_PEON_SLEEPING,true);
				m_bEmote = false;
			}
			else 
			{
				Emote_Timer -= diff;
				m_creature->HandleEmoteCommand(28);
			}
		}
	}

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
		if ( pCaster->GetTypeId() == TYPEID_PLAYER && m_creature->isAlive() &&  pSpell->Id == SPELL_AWAKEN_PEON )
        {
            if(((Player*)pCaster)->GetQuestStatus(5441) == QUEST_STATUS_INCOMPLETE && m_creature->HasAura(SPELL_PEON_SLEEPING))
            {
                ((Player*)pCaster)->KilledMonsterCredit(10556,0);
				m_creature->RemoveAurasDueToSpell(SPELL_PEON_SLEEPING);
				
				Emote_Timer = 120000;
				m_bEmote = true;
            }
        }
    }
};

CreatureAI* GetAI_npc_lazy_peon(Creature* pCreature)
{
    return new npc_lazy_peonAI(pCreature);
}

void AddSC_durotar()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "npc_lazy_peon";
    newscript->GetAI = &GetAI_npc_lazy_peon;
    newscript->RegisterSelf();
}