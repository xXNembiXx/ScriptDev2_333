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
SDName: CUSTOM_EVENTS
SDAuthor: Nembi
SD%Complete: 100
SDComment: Just for Inferna Christmas PreEvent
SDCategory: Gnomeregan
EndScriptData */


#include "precompiled.h"
#include "gnomeregan.h"

#define SPELL_POLYMORPH			13323
#define SPELL_FEAR				12096
#define SPELL_HEALING			12039
#define SPELL_SHADOW_BOLT		15245
#define NPC_MURLOCS				400042

#define SAY_AGGRO				-2500027
#define SAY_WAVE				-2500028
#define SAY_WAIT				-2500029
#define SAY_COMBAT				-2500030
#define SAY_DEATH				-2500031


struct MANGOS_DLL_DECL event_boss_puckyAI : public Scripted_NoMovementAI
{
    event_boss_puckyAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiPolymorphTimer;
    uint32 m_uiFearTimer;
    uint32 m_uiHealingTimer;
    uint32 m_uiShadowBoltTimer;

    bool m_bIsPhase1;
    bool m_bIsPhase2;
    bool m_bIsOpenGate1;
    bool m_bIsOpenGate2;
    bool m_bIsWaitCombat;
    bool m_bIsClose;

    uint32 m_uiPhaseEnd1;
    uint32 m_uiPhaseEnd2;
    uint32 m_uiPhaseEnd3;
    uint32 m_uiPhaseEnd4;

    void Reset()
    {
        m_uiPolymorphTimer = 18000;
        m_uiFearTimer = 12000;
        m_uiHealingTimer = 36000;
        m_uiShadowBoltTimer = 8000;

        m_uiPhaseEnd1 = 10000;
        m_uiPhaseEnd2 = 50000;
        m_uiPhaseEnd3 = 90000;
        m_uiPhaseEnd4 = 100000;

        m_bIsPhase1 = false;
        m_bIsPhase2 = false;
        m_bIsOpenGate1 = false;
        m_bIsOpenGate2 = false;
        m_bIsWaitCombat = false;
        m_bIsClose = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_PUCKY, NOT_STARTED);

        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_PUCKY_RIGHT)))
            pGate->SetGoState(GO_STATE_READY);

        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_PUCKY_LEFT)))
            pGate->SetGoState(GO_STATE_READY);
        
    }


    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_MURLOCS)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void JustDied(Unit* Killer)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_PUCKY, DONE);

		DoScriptText(SAY_DEATH, m_creature);

		m_creature->PlayDirectSound(11802,0);
        m_creature->PlayDistanceSound(11802,0);
    }

    void EnterCombat(Unit* who)
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		DoScriptText(SAY_AGGRO, m_creature);

        m_bIsPhase1 = true;

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_PUCKY, IN_PROGRESS);
        }

    }

    void UpdateAI(const uint32 diff)
    {
        if (m_bIsPhase1)
        {
                if (!m_bIsOpenGate1 && (m_uiPhaseEnd1 < diff))
                {
                    {
                        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_PUCKY_RIGHT)))
                            pGate->SetGoState(GO_STATE_ACTIVE);
                    }
					DoScriptText(SAY_WAVE, m_creature);
                    m_creature->SummonCreature(NPC_MURLOCS, -488.305756f, -88.404900f, -147.639145f, 3.409739f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -488.305756f, -88.404900f, -147.639145f, 3.409739f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -488.305756f, -88.404900f, -147.639145f, 3.409739f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -488.305756f, -88.404900f, -147.639145f, 3.409739f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -488.305756f, -88.404900f, -147.639145f, 3.409739f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -488.305756f, -88.404900f, -147.639145f, 3.409739f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_bIsOpenGate1 = true;
                }else m_uiPhaseEnd1 -= diff;

                if (!m_bIsOpenGate2 && (m_uiPhaseEnd2 < diff))
                {
                    {
                        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_PUCKY_LEFT)))
                            pGate->SetGoState(GO_STATE_ACTIVE);
                    }
					DoScriptText(SAY_WAVE, m_creature);
                    m_creature->SummonCreature(NPC_MURLOCS, -574.457947f, -108.685684f, -150.613327f, 5.469820f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -574.457947f, -108.685684f, -150.613327f, 5.469820f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -574.457947f, -108.685684f, -150.613327f, 5.469820f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -574.457947f, -108.685684f, -150.613327f, 5.469820f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -574.457947f, -108.685684f, -150.613327f, 5.469820f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_creature->SummonCreature(NPC_MURLOCS, -574.457947f, -108.685684f, -150.613327f, 5.469820f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    m_bIsOpenGate2 = true;
                }else m_uiPhaseEnd2 -= diff;

                if (!m_bIsWaitCombat && (m_uiPhaseEnd3 < diff))
                {
                    {
                        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_PUCKY_LEFT)))
                        pGate->SetGoState(GO_STATE_READY);
                    }

                    {
                        if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_GO_PUCKY_RIGHT)))
                            pGate->SetGoState(GO_STATE_READY);
                    }
                    //DoScriptText(SAY_MURLOC, m_creature);
                    m_bIsWaitCombat = true;
                }else m_uiPhaseEnd3 -= diff;

                if (!m_bIsPhase2 && (m_uiPhaseEnd4 < diff))
                {
					DoScriptText(SAY_WAIT, m_creature);
                    m_bIsPhase2 = true;
                }else m_uiPhaseEnd4 -= diff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bIsPhase2)
        {
            if (!m_bIsClose)
            {
				DoScriptText(SAY_COMBAT, m_creature);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_bIsClose = true;
            }

            if (m_uiPolymorphTimer < diff)
            {
				if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
					DoCast(pTarget, SPELL_POLYMORPH);
                m_uiPolymorphTimer = 18000;
            }else m_uiPolymorphTimer -= diff;

            if (m_uiFearTimer < diff)
            {
				if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
					DoCast(pTarget, SPELL_FEAR);
                m_uiFearTimer = 12000;
            }else m_uiFearTimer -= diff;

            if (m_uiHealingTimer < diff)
            {
                DoCast(m_creature, SPELL_HEALING, true);
                m_uiHealingTimer = 36000;
            }else m_uiHealingTimer -= diff;

            if (m_uiShadowBoltTimer < diff)
            {
				if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
					DoCast(pTarget, SPELL_SHADOW_BOLT);
                m_uiShadowBoltTimer = 8000;
            }else m_uiShadowBoltTimer -= diff;

        }
        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_event_boss_pucky(Creature* pCreature)
{
    return new event_boss_puckyAI(pCreature);
}

void AddSC_event_boss_pucky()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "event_boss_pucky";
    newscript->GetAI = &GetAI_event_boss_pucky;
    newscript->RegisterSelf();
}