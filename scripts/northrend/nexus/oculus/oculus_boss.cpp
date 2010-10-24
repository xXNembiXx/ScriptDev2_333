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
oculus_boss_ragnaros			Addtion to Inferna Christmas PreEvent
EndContentData */

#include "precompiled.h"
#include "oculus.h"

bool m_bIsRagnarosDead;

/*######
## oculus_boss_oramus
######*/

enum
{
	SAY_TEST = -1000000

};

struct MANGOS_DLL_DECL oculus_boss_oramusAI : public ScriptedAI
{
    oculus_boss_oramusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }


    ScriptedInstance* m_pInstance;

	bool m_bIsTeleport1;

	uint32 m_uiTeleport1Timer;

//ToDo: After Wipe Respawn Ragnaros || phaseMask 128
    void Reset()
    {
       m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
       m_creature->SetStandState(UNIT_STAND_STATE_SLEEP);

	   m_bIsTeleport1 = false;
	   m_uiTeleport1Timer = 6000;

	   m_bIsRagnarosDead = false;
    }

    void JustDied(Unit* pKiller)
    {
    }

    void EnterCombat(Unit* pWho)
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
		m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
		m_creature->MonsterMove(1040.636597f, 937.819885f, 470.055634f, 5000);
        SetCombatMovement(false);
        m_creature->GetMotionMaster()->MoveIdle();

	   if(Creature* pRagnaros = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_RAGNAROS)))
			pRagnaros->SetPhaseMask(1, true);

		m_bIsTeleport1 = true;
    }

    void KilledUnit(Unit* pKiller)
    {
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

		if (m_bIsTeleport1)
		{
			if (m_uiTeleport1Timer < uiDiff)
			{
                Map* pMap = m_creature->GetMap();
                if (pMap && pMap->IsDungeon())
                {
                    Map::PlayerList const &players = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        itr->getSource()->TeleportTo (578, 1043.908936f +rand()%5, 925.630066f +rand()%5, 439.049805f, 4.363545f);

				}
				m_bIsTeleport1 = false;
				DoScriptText(SAY_TEST, m_creature);
				m_uiTeleport1Timer = 0;
			}else m_uiTeleport1Timer -= uiDiff;
		}
        DoMeleeAttackIfReady();
    }
};


/*######
## oculus_boss_ragnaros
######*/

#define SPELL_LEGION_FLAME			66197	
#define SPELL_FEL_LIGHTNING			46479
#define SPELL_BURNING_SPRAY			66902

#define SAY_KILL                    -1409017
#define SAY_MAGMABURST              -1409018


struct MANGOS_DLL_DECL oculus_boss_ragnarosAI : public ScriptedAI
{
    oculus_boss_ragnarosAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
		m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

	ScriptedInstance* m_pInstance;

	uint32 m_uiLegionFlameTimmer;
	uint32 m_uiFelLightningTimer;
	uint32 m_uiBurningSprayTimer;

    void Reset()
    {
		m_creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_FIRE, true);
        m_uiLegionFlameTimmer = 15000;
		m_uiFelLightningTimer = 11000;
		m_uiBurningSprayTimer = 23000;
	}

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
		m_bIsRagnarosDead = true;
    }

    void EnterCombat(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiLegionFlameTimmer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_LEGION_FLAME);

            m_uiLegionFlameTimmer = 15000;
        }
		else 
			m_uiLegionFlameTimmer -= uiDiff;

        if (m_uiFelLightningTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_FEL_LIGHTNING);

            m_uiFelLightningTimer = 11000;
        }
		else 
			m_uiFelLightningTimer -= uiDiff;

        if (m_uiBurningSprayTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_BURNING_SPRAY);
			DoScriptText(SAY_MAGMABURST, m_creature);

            m_uiBurningSprayTimer = 23000;
        }
		else 
			m_uiBurningSprayTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_oculus_boss_oramus(Creature* pCreature)
{
    return new oculus_boss_oramusAI(pCreature);
}


CreatureAI* GetAI_oculus_boss_ragnaros(Creature* pCreature)
{
    return new oculus_boss_ragnarosAI(pCreature);
}


void AddSC_oculus_boss()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "oculus_boss_oramus";
    newscript->GetAI = &GetAI_oculus_boss_oramus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_boss_ragnaros";
    newscript->GetAI = &GetAI_oculus_boss_ragnaros;
    newscript->RegisterSelf();
}