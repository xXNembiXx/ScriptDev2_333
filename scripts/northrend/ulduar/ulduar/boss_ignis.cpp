/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: boss_ignis
SD%Complete: 100%
SDComment:
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "def_ulduar.h"

enum
{
    //yells
    SAY_AGGRO								= -1603001, // Insolent whelps! Your blood will temper the weapons used to reclaim this world!
    SAY_SCORCH_1							= -1603002, // Let the inferno consume you!
    SAY_SCORCH_2							= -1603003, // BURN! Burn in the makers fire!
    SAY_SLAG_POT							= -1603004, // I will burn away your impurities!
    SAY_ACTIVATE_CONSTRUCT					= -1603005, // Arise, soldiers of the Iron Crucible! The Makers' will be done!
    SAY_KILL_1								= -1603006, // More scraps for the scrapheap!
    SAY_KILL_2								= -1603007, // Your bones will serve as kindling!
    SAY_BERSERK								= -1603008, // Let it be finished!
    SAY_DEATH								= -1603009, // I. Have. Failed.

    //ignis the furnace master
    SPELL_FLAME_JETS						= 62680,
    SPELL_FLAME_JETS_H						= 63472,
    SPELL_SLAG_POT							= 62717,
    SPELL_SLAG_POT_H						= 63477,
    SPELL_SLAG_POT_DMG						= 65722,
    SPELL_SLAG_POT_DMG_H					= 65723,
    SPELL_SCORCH							= 62546,
    SPELL_SCORCH_H							= 63474,
	SPELL_SUMMON_SCORCH						= 62551,
	SPELL_ACTIVATE_CONSTRUCT                = 62488,
    BUFF_STRENGHT_OF_CREATOR				= 64473,
	//SPELL_STRENGTH_OF_THE_CREATOR         = 64474,
	//SPELL_STRENGTH_OF_THE_CREATOR_REMOVE  = 64475,
    SPELL_HASTE								= 66045,
	SPELL_BERSERK                           = 47008,

    //iron construct
    SPELL_HEAT								= 65667,
	SPELL_HEAT_BUFF							= 65667,
    SPELL_MOLTEN							= 62373,
    SPELL_BRITTLE							= 62382,
    SPELL_SHATTER							= 62383,

    //scorch target
    AURA_SCORCH								= 62548,
    AURA_SCORCH_H							= 63476,

	//magma rager
	SPELL_FIRE_BLAST						= 64773,
	SPELL_SUPERHEATED_WINDS					= 64746,

    //npc ids
    MOB_IRON_CONSTRUCT						= 33121,
    MOB_SCORCH_TARGET						= 33221,

	//achievements
	ACHIEV_STOKIN							= 2930,
	ACHIEV_STOKIN_H							= 2929,
	ACHIEV_SHATTERED						= 2925,
	ACHIEV_SHATTERED_H						= 2926
};

// magma rager
struct MANGOS_DLL_DECL mob_magma_ragerAI : public ScriptedAI
{
    mob_magma_ragerAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 Fire_Blast_Timer;
    uint32 Superheated_Winds_Timer;

    void Reset()
	{
		Fire_Blast_Timer = 10000;
		Superheated_Winds_Timer = 15000;
	}

	void UpdateAI(const uint32 diff)
	{
        if (Fire_Blast_Timer < diff)
        {
            DoCast(m_creature, SPELL_FIRE_BLAST);
            Fire_Blast_Timer = 10000;
        }else Fire_Blast_Timer -= diff;

        if (Superheated_Winds_Timer < diff)
        {
            DoCast(m_creature, SPELL_SUPERHEATED_WINDS);
            Superheated_Winds_Timer = 15000;
        }else Superheated_Winds_Timer -= diff;   
	}
};

CreatureAI* GetAI_mob_magma_rager(Creature* pCreature)
{
    return new mob_magma_ragerAI(pCreature);
}

//ignis the furnace master
struct MANGOS_DLL_DECL boss_ignisAI : public ScriptedAI
{
    boss_ignisAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    bool m_bIsRegularMode;
    ScriptedInstance* m_pInstance;

    uint32 m_uiFlameJetsTimer;
    uint32 m_uiScorchTimer;
    uint32 m_uiSlagPotTimer;
    uint32 m_uiActivateConstructTimer;
    uint32 m_uiBerserkTimer;
	uint32 m_uiStokinTimer;
	uint32 m_uiShatteredTimer;
	uint32 m_uiShatteredCount;
    bool m_bBerserk;
	bool stokin;
	bool shattered;

    std::set<uint64> m_lConstructs;

    void Reset()
    {
        m_bBerserk = false;
		stokin = true;
		shattered = false;
        m_uiFlameJetsTimer = 35000;
        m_uiScorchTimer = 12000;
        m_uiSlagPotTimer = 30000;
        m_uiActivateConstructTimer = m_bIsRegularMode ? 40000 : 30000;
        m_uiBerserkTimer = m_uiActivateConstructTimer;
		m_uiStokinTimer = 240000;
		m_uiShatteredTimer = 5000;
		m_uiShatteredCount = 0;
    }

    void RespawnAdds()
    {
        if (m_pInstance)
        {
            for(std::set<uint64>::const_iterator itr = m_lConstructs.begin(); itr != m_lConstructs.end(); ++itr)
            {
                if (Creature* pCreature = m_pInstance->instance->GetCreature(*itr))
                {
                    if (pCreature->isAlive())
                    {
                        if (pCreature->isInCombat())
                            pCreature->AI()->EnterEvadeMode();
                    }
                    else
                    {
                        pCreature->Respawn();
                        pCreature->SendMonsterMove(pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ(), SPLINETYPE_NORMAL, SPLINEFLAG_NONE, EFFECT_INDEX_0);
                    }
                }
            }
        }

        m_lConstructs.clear();
    }

    void JustDied(Unit*)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IGNIS, DONE);

        DoScriptText(SAY_DEATH, m_creature);
        RespawnAdds();

		if (stokin)
		{
			AchievementEntry const *AchievStokin = GetAchievementStore()->LookupEntry(m_bIsRegularMode ? ACHIEV_STOKIN : ACHIEV_STOKIN_H);
            if (AchievStokin)
            {
                Map* pMap = m_creature->GetMap();
                if (pMap && pMap->IsDungeon())
                {
                    Map::PlayerList const &players = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        itr->getSource()->CompletedAchievement(AchievStokin);
                }
            }
		}

		if (shattered)
		{
			AchievementEntry const *AchievShattered = GetAchievementStore()->LookupEntry(m_bIsRegularMode ? ACHIEV_SHATTERED : ACHIEV_SHATTERED_H);
            if (AchievShattered)
            {
                Map* pMap = m_creature->GetMap();
                if (pMap && pMap->IsDungeon())
                {
                    Map::PlayerList const &players = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        itr->getSource()->CompletedAchievement(AchievShattered);
                }
            }
		}
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == MOB_SCORCH_TARGET)
        {
            pSummoned->SetDisplayId(11686);
            pSummoned->CastSpell(pSummoned, m_bIsRegularMode ? AURA_SCORCH : AURA_SCORCH_H, true, NULL, NULL, m_creature->GetGUID());
            pSummoned->ForcedDespawn(40000);
        }
    }

    void Aggro(Unit*)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IGNIS, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->SetInCombatWithZone();
    }

    void KilledUnit(Unit*)
    {
        DoScriptText(urand(0, 1) ? SAY_KILL_1 : SAY_KILL_2, m_creature);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IGNIS, FAIL);

        RespawnAdds();
    }

    void SpellHitTarget(Unit* pUnit, const SpellEntry* pSpellEntry)
    {
        if (pSpellEntry->Id == SPELL_ACTIVATE_CONSTRUCT)
        {
            m_lConstructs.insert(pUnit->GetGUID());
            m_creature->CastSpell(m_creature, BUFF_STRENGHT_OF_CREATOR, true);
        }
    }

	void AchievShattered()
	{
		if (!shattered)
		{
			++m_uiShatteredCount;
			m_uiShatteredTimer = 5000;
		}
	}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bBerserk)
        {
            if (m_uiActivateConstructTimer < diff)
            {
                if (m_lConstructs.size() < 20)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_ACTIVATE_CONSTRUCT) == CAST_OK)
                    {
                        DoScriptText(SAY_ACTIVATE_CONSTRUCT, m_creature);
                        m_uiActivateConstructTimer = m_bIsRegularMode ? 40000 : 30000;
                    }
                }
                else
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
                    {
                        DoScriptText(SAY_BERSERK, m_creature);
                        m_bBerserk = true;
                    }
                }
            }
            else
                m_uiActivateConstructTimer -= diff;
        }

        if (m_uiFlameJetsTimer < diff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FLAME_JETS : SPELL_FLAME_JETS_H) == CAST_OK)
                m_uiFlameJetsTimer = 32000;
        }
        else
            m_uiFlameJetsTimer -= diff;

        if (m_uiScorchTimer < diff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_SCORCH : SPELL_SCORCH_H) == CAST_OK)
            {
				m_creature->CastSpell(m_creature->getVictim(), SPELL_SUMMON_SCORCH, true);
                DoScriptText(urand(0, 1) ? SAY_SCORCH_1 : SAY_SCORCH_2, m_creature);
                m_uiScorchTimer = urand(20000, 25000);
            }
        }
        else
            m_uiScorchTimer -= diff;

        if (m_uiSlagPotTimer < diff)
        {
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
            {
                if (DoCastSpellIfCan(target, m_bIsRegularMode ? SPELL_SLAG_POT : SPELL_SLAG_POT_H) == CAST_OK)
                {
                    DoScriptText(SAY_SLAG_POT, m_creature);
                    m_uiSlagPotTimer = 30000;
                }
            }
        }
        else
            m_uiSlagPotTimer -= diff;

        if (m_uiStokinTimer < diff)
        {
            stokin = false;
        }else m_uiStokinTimer -= diff;

        if (!shattered && m_uiShatteredTimer < diff)
        {
			if (m_uiShatteredCount >= 2)
				shattered = true;
			m_uiShatteredCount = 0;
        }else m_uiShatteredTimer -= diff;

        DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea(diff);
    }
};

CreatureAI* GetAI_boss_ignis(Creature* pCreature)
{
    return new boss_ignisAI(pCreature);
}

// iron construct
struct MANGOS_DLL_DECL mob_iron_constructAI : public ScriptedAI
{
    ScriptedInstance* m_pInstance;
    bool m_bActivated;

    mob_iron_constructAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    void Reset()
    {
        m_bActivated = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho || !m_bActivated)
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!pWho || !m_bActivated)
            return;

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (m_creature->HasAura(SPELL_BRITTLE) && uiDamage > 5000)
        {
			if (Creature* pIgnis = m_pInstance->instance->GetCreature(m_pInstance->GetData64(NPC_IGNIS)))
			{
				pIgnis->RemoveSingleAuraFromStack(BUFF_STRENGHT_OF_CREATOR, EFFECT_INDEX_0);
				CAST_AI(boss_ignisAI, pIgnis->AI())->AchievShattered();
			}
			m_creature->CastSpell(m_creature, SPELL_SHATTER, true);
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
    }

    void JustDied(Unit *victim)
    {
        if (!m_pInstance)
            return;
    }

    void SpellHit(Unit* who, const SpellEntry* spell)
    {
        if (spell->Id == SPELL_HEAT)
        {
            Aura* aura = m_creature->GetAura(SPELL_HEAT_BUFF, EFFECT_INDEX_0);

            if (aura && aura->GetStackAmount() >= 10)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_HEAT_BUFF);
                m_creature->CastSpell(m_creature, SPELL_MOLTEN, true);
            }
        }
        else if (spell->Id == SPELL_ACTIVATE_CONSTRUCT)
        {
            m_bActivated = true;
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetInCombatWithZone();
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_bActivated || !m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->HasAura(SPELL_MOLTEN))
        {
            if (m_creature->IsWithinDist2d(522.0f, 277.5f, 25.0f) || m_creature->IsWithinDist2d(651.0f, 277.5f, 25.0f))
            {
                m_creature->RemoveAurasDueToSpell(SPELL_MOLTEN);
                m_creature->CastSpell(m_creature, SPELL_BRITTLE, true);
                return;
            }
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_iron_construct(Creature* pCreature)
{
    return new mob_iron_constructAI(pCreature);
}

void AddSC_boss_ignis()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_ignis";
    NewScript->GetAI = GetAI_boss_ignis;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_iron_construct";
    NewScript->GetAI = &GetAI_mob_iron_construct;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_magma_rager";
    NewScript->GetAI = &GetAI_mob_magma_rager;
    NewScript->RegisterSelf();
}
