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
SDAuthor: Nembi, Shiro, Janu
SD%Complete: 100
SDComment: Version 3.0 - Insert Image of Kruul, Insert some Texts, Some Bugfixes, Special Thx to Shiro for the Gossip Menu
SDCategory: Custom
EndScriptData */

/* ContentData
event_boss_kruul							modified boss_kruul script
event_npc_succubus							addition to event_boss_kruul
event_npc_hound								addition to event_boss_kruul
event_npc_imp								addition to event_boss_kruul
event_npc_emperor							addition to event_boss_kruul
event_npc_fel_reaver						addition to event_boss_kruul
event_npc_image_kruul						addition to event_boss_kruul
EndContentData */

#include "precompiled.h"

/*######
## event_boss_kruul
######*/

#define SPELL_TWISTEDREFLECTION     21063
#define SPELL_VOIDBOLT              21066
#define SPELL_RAGE                  21340
#define SPELL_CAPTURESOUL           21054
#define SPELL_MANA_DETONATION       27819
#define SPELL_LIGHTNING_WHIRL       63483
#define SPELL_FROST_BOLT_NOVA       28478
#define SPELL_FROST_BLAST           27808
#define SPELL_FROZEN_BLOWS			63512
#define SPELL_SHADOW_CRASH			62660
#define SPELL_ENRAGE				47008
#define SPELL_CURSE					60121 
#define SPELL_POLYMORPH				68311

#define SAY_KILL					-1000295
#define SAY_COMBAT1					-1619040				
#define SAY_COMBAT2					-1619041
#define SAY_COMBAT3					-1619042
#define SAY_COMBAT4					-1619043
#define SAY_COMBAT5					-1619044
#define SAY_COMBAT6					-1619045
#define SAY_COMBAT7					-1619046
#define SAY_ENDE					-1619047

struct MANGOS_DLL_DECL event_boss_kruulAI : public ScriptedAI
{
    event_boss_kruulAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 TwistedReflection_Timer;
    uint32 VoidBolt_Timer;
    uint32 Hound_Timer;
	uint32 ManaDetonation_Timer;
	uint32 LightningWhirl_Timer;
	uint32 FrozenBlows_Timer;
	uint32 ShadowCrash_Timer;
	uint32 FrostBlast_Timer;
	uint32 FrostBoltNova_Timer;
	uint32 Curse_Timer;
	uint32 Enrage_Timer;
	uint32 Polymorph_Timer;
    uint32 Rand;
    uint32 RandX;
    uint32 RandY;

    Creature* Summoned;

	bool m_bRage;

	bool m_bCombat1;
	bool m_bCombat2;
	bool m_bCombat3;
	bool m_bCombat4;
	
    void Reset()
    {
        TwistedReflection_Timer = 30000;
        VoidBolt_Timer = 35000;
        Hound_Timer = 8000;
		ManaDetonation_Timer = 20000;
		LightningWhirl_Timer = 25000;
		FrozenBlows_Timer = 40000;
		ShadowCrash_Timer = 55000;
		FrostBlast_Timer = (rand()%60)*1000;
		FrostBoltNova_Timer = 15000;
		Enrage_Timer = 900000;
		Curse_Timer = 38000;
		Polymorph_Timer = 4000;

		m_creature->SetDisplayId(18650);
		m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
		m_bRage = false;

		m_bCombat1 = false;
		m_bCombat2 = false;
		m_bCombat3 = false;
		m_bCombat4 = false;
    }

    void KilledUnit()
    {
        DoCast(m_creature,SPELL_CAPTURESOUL);
		DoScriptText(SAY_KILL, m_creature);
    }

	
    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_COMBAT1, m_creature);
    }

	void JustDied(Unit* pKiller)
    {
		DoScriptText(SAY_ENDE, m_creature);
    }

    void SummonHounds(Unit* victim)
    {
        Rand = rand()%10;

        switch(urand(0, 1))
        {
            case 0: RandX = 0 - Rand; break;
            case 1: RandX = 0 + Rand; break;
        }

        Rand = 0;
        Rand = rand()%10;

        switch(urand(0, 1))
        {
            case 0: RandY = 0 - Rand; break;
            case 1: RandY = 0 + Rand; break;
        }

        Rand = 0;
        Summoned = DoSpawnCreature(19207, RandX, RandY, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);    // Hund
		Summoned = DoSpawnCreature(400000, RandX, RandY, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);  // Sukkubus

        if (Summoned)
            ((CreatureAI*)Summoned->AI())->AttackStart(victim);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (ManaDetonation_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_MANA_DETONATION);

            ManaDetonation_Timer = 20000;
        }else ManaDetonation_Timer -= diff;

        if (Curse_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_CURSE);

            Curse_Timer = 38000;
        }else Curse_Timer -= diff;

        if (Polymorph_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_POLYMORPH);

            Polymorph_Timer = 12000;
        }else Polymorph_Timer -= diff;

        if (FrostBlast_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget, SPELL_FROST_BLAST);

            FrostBlast_Timer = (rand()%60)*1000;
        }else FrostBlast_Timer -= diff;

        if (FrostBoltNova_Timer < diff)
        {
            DoCast(m_creature, SPELL_FROST_BOLT_NOVA);
            FrostBoltNova_Timer = 15000;
        }else FrostBoltNova_Timer -= diff;

		if (Enrage_Timer < diff)
		{
            DoCast(m_creature, SPELL_ENRAGE);
			DoScriptText(SAY_COMBAT6, m_creature);
			Enrage_Timer = 900000;
		}else Enrage_Timer -= diff;

		if (FrozenBlows_Timer < diff)
		{
			DoCast (m_creature, SPELL_FROZEN_BLOWS);
			FrozenBlows_Timer = 40000;
		}else FrozenBlows_Timer -= diff;

		if (LightningWhirl_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_LIGHTNING_WHIRL);

			LightningWhirl_Timer = 25000;
        }else LightningWhirl_Timer -= diff;
		
		if (ShadowCrash_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_SHADOW_CRASH);

			ShadowCrash_Timer = 21000;
        }else ShadowCrash_Timer -= diff;
		
        if (TwistedReflection_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_TWISTEDREFLECTION);
            TwistedReflection_Timer = 30000;
        }else TwistedReflection_Timer -= diff;

        if (VoidBolt_Timer < diff)
        {
            if (rand()%100 < 40)
                DoCast(m_creature->getVictim(),SPELL_VOIDBOLT);

            VoidBolt_Timer = 18000;
        }else VoidBolt_Timer -= diff;

        if (Hound_Timer < diff)
        {
			SummonHounds(m_creature->getVictim());
		    SummonHounds(m_creature->getVictim());
			DoScriptText(SAY_COMBAT7, m_creature);
            
            Hound_Timer = 45000;
        }else Hound_Timer -= diff;

		if (!m_bCombat1 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 80))
        {
             m_creature->SetDisplayId(21069);
			 DoScriptText(SAY_COMBAT2, m_creature);
			 m_bCombat1 = true;

        }

		if (!m_bCombat2 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 60))
        {
             m_creature->SetDisplayId(14173);
			 DoScriptText(SAY_COMBAT3, m_creature);
			 m_bCombat2 = true;
        }

		if (!m_bCombat3 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 40))
        {
             m_creature->SetDisplayId(1912);
             m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 3);
			 DoScriptText(SAY_COMBAT4, m_creature);
			 m_bCombat3 = true;
        }

		if (!m_bCombat4 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 20))
        {
             m_creature->SetDisplayId(18650);
             m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
			 DoScriptText(SAY_COMBAT5, m_creature);
			 m_bCombat4 = true;
        }

	    if (!m_bRage && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 10)
        {
            DoCast(m_creature, SPELL_RAGE);
			DoScriptText(SAY_COMBAT5, m_creature);
            m_bRage = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_event_boss_kruul(Creature* pCreature)
{
    return new event_boss_kruulAI(pCreature);
}

/*######
## event_npc_image_kruul
######*/

#define SPELL_ROCK_SHOWER			60923
#define	SPELL_ROCK_RUMBLE			38777
#define SPELL_PUMPKIN				44212
#define	SPELL_FIREBALL_BARRAGE		37540
#define SPELL_FLAME_VENTS			63847
#define SPELL_ABYSSAL_STRIKE		37633

#define SAY_START					-1575018
#define SAY_FIGHT1					-1619034				
#define SAY_FIGHT2					-1619035
#define SAY_FIGHT3					-1619036
#define SAY_FIGHT4					-1619037
#define SAY_END						-1619038

struct MANGOS_DLL_DECL event_npc_image_kruulAI : public ScriptedAI
{
    event_npc_image_kruulAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 RockShower_Timer;
	uint32 RockRumble_Timer;
	uint32 Pumpkin_Timer;
	uint32 FireballBarrage_Timer;
	uint32 FlameVents_Timer;
	uint32 AbyssalStrike_Timer;

	bool m_bFight2;
	bool m_bFight3;
	bool m_bFight4;
	bool m_bEnd;

	void Reset()
    {
		RockShower_Timer = 11000;
		RockRumble_Timer = 15000;
		Pumpkin_Timer = 4000;
		FireballBarrage_Timer = 17000;
		FlameVents_Timer = 28000;
		AbyssalStrike_Timer = 14000;

		m_bFight2 = false;
		m_bFight3 = false;
		m_bFight4 = false;
		m_bEnd = false;

		m_creature->setFaction(14);
		m_creature->SetDisplayId(18650);
		m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
	}

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_START, m_creature);
		DoScriptText(SAY_FIGHT1, m_creature);
    }

	void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (RockShower_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_ROCK_SHOWER);
				
            RockShower_Timer = 11000;
        }else RockShower_Timer -= diff;

		if (AbyssalStrike_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_ABYSSAL_STRIKE);

            AbyssalStrike_Timer = 14000;
        }else AbyssalStrike_Timer -= diff;

        if (RockRumble_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_ROCK_RUMBLE);

            RockRumble_Timer = 15000;
        }else RockRumble_Timer -= diff;

        if (Pumpkin_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_PUMPKIN);

            Pumpkin_Timer = 25000;
        }else Pumpkin_Timer -= diff;

        if (FireballBarrage_Timer < diff)
        {
                DoCast(m_creature->getVictim(),SPELL_FIREBALL_BARRAGE);

            FireballBarrage_Timer = 17000;
        }else FireballBarrage_Timer -= diff;

        if (FlameVents_Timer < diff)
        {
                DoCast(m_creature->getVictim(),SPELL_FLAME_VENTS);

            FlameVents_Timer = 28000;
        }else FlameVents_Timer -= diff;
	
		if (!m_bFight2 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 70))
        {
			DoScriptText(SAY_FIGHT2, m_creature);
			m_bFight2 = true;
		}

		if (!m_bFight3 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 50))
        {
			DoScriptText(SAY_FIGHT3, m_creature);
			m_bFight3 = true;
		}

		if (!m_bFight4 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 30))
        {
			DoScriptText(SAY_FIGHT4, m_creature);
			m_bFight4 = true;
		}

		/* Here we will support the Teleport Gossip Menu */
		if (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 10)
        {
             m_creature->SetDisplayId(28186);
             m_creature->setFaction(35);
			 m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 2);
			 m_creature->DeleteThreatList();
			 m_creature->CombatStop(true);
			 m_creature->AttackStop();
			 m_creature->GetMotionMaster()->MovePoint(0, -100.458000f, 149.860992f,  -40.382599f);
		 	 DoScriptText(SAY_END, m_creature);
			 m_bEnd = true;
        }
	
		DoMeleeAttackIfReady();
    }
};

bool GossipHello_event_npc_image_kruul(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->getFaction() == 35)
    	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bringt mich zu Kruul!" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
};

bool GossipSelect_event_npc_image_kruul(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
		case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
			pPlayer->TeleportTo(1, 5628.802734f, -3011.315430f, 1560.144653f, 0.046409f);
            break;
    };
    return true;
};

CreatureAI* GetAI_event_npc_image_kruul(Creature* pCreature)
{
    return new event_npc_image_kruulAI(pCreature);
}

/*######
## event_npc_succubus
######*/

#define SPELL_SHADOW_SHOCK			54889	
#define SPELL_LASH					59678
#define SPELL_INFECTION				39032
#define SPELL_SINGED				65280

struct MANGOS_DLL_DECL event_npc_succubusAI : public ScriptedAI
{
    event_npc_succubusAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 ShadowShock_Timer;
	uint32 Lash_Timer;
	uint32 Infection_Timer;
	uint32 Singed_Timer;

	void Reset()
    {
		ShadowShock_Timer = 4000;
		Lash_Timer = 10000;
		Infection_Timer = 4000;
		Singed_Timer = 8000;
	}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (ShadowShock_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_SHADOW_SHOCK);

            ShadowShock_Timer = 4000;
        }else ShadowShock_Timer -= diff;

        if (Lash_Timer < diff)
        {
                DoCast(m_creature->getVictim(),SPELL_LASH);

            Lash_Timer = 10000;
        }else Lash_Timer -= diff;

        if (Infection_Timer < diff)
        {
                DoCast(m_creature->getVictim(),SPELL_INFECTION);

            Infection_Timer = 4000;
        }else Infection_Timer -= diff;

        if (Singed_Timer < diff)
        {
                DoCast(m_creature->getVictim(),SPELL_INFECTION);

            Singed_Timer = 8000;
        }else Singed_Timer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_event_npc_succubus(Creature* pCreature)
{
    return new event_npc_succubusAI(pCreature);
}

/*######
## event_npc_hound
######*/

#define SPELL_FIRE_SPIT				67634
#define SPELL_FLAME_BREATH			59469
#define SPELL_CAUTERIZING_FLAMES	59466
#define SPELL_FLAME_VENTS			63847

struct MANGOS_DLL_DECL event_npc_houndAI : public ScriptedAI
{
    event_npc_houndAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 FireSpit_Timer;
	uint32 FlameBreath_Timer;
	uint32 CauterizingFlames_Timer;
	uint32 FlameVents_Timer;

	void Reset()
    {
		FireSpit_Timer = 15000;
		FlameBreath_Timer = 5000;
		CauterizingFlames_Timer = 10000;
		FlameVents_Timer = 8000;
	}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (FireSpit_Timer < diff)
        {
			DoCast(m_creature->getVictim(),SPELL_FIRE_SPIT);

            FireSpit_Timer = 15000;
        }else FireSpit_Timer -= diff;

        if (FlameBreath_Timer < diff)
        {
			DoCast(m_creature->getVictim(),SPELL_FLAME_BREATH);

            FlameBreath_Timer = 5000;
        }else FlameBreath_Timer -= diff;

        if (FlameVents_Timer < diff)
        {
			DoCast(m_creature->getVictim(),SPELL_FLAME_VENTS);

            FlameVents_Timer = 8000;
        }else FlameVents_Timer -= diff;

        if (CauterizingFlames_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_CAUTERIZING_FLAMES);

            CauterizingFlames_Timer = 10000;
        }else CauterizingFlames_Timer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_event_npc_hound(Creature* pCreature)
{
    return new event_npc_houndAI(pCreature);
}

/*######
## event_npc_imp
######*/

#define SPELL_FIRE_BOLT				68926

struct MANGOS_DLL_DECL event_npc_impAI : public ScriptedAI
{
    event_npc_impAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 FireBolt_Timer;

	void Reset()
    {
		FireBolt_Timer = 4000;
	}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (FireBolt_Timer < diff)
        {
			DoCast(m_creature->getVictim(),SPELL_FIRE_BOLT);

            FireBolt_Timer = 4000;
        }else FireBolt_Timer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_event_npc_imp(Creature* pCreature)
{
    return new event_npc_impAI(pCreature);
}

/*######
## npc_emperor
######*/

#define SPELL_WOUND					66620
#define SPELL_SHADOW_PAST			67678
#define SPELL_UNBALANCING_STRIKE	55470

struct MANGOS_DLL_DECL event_npc_emperorAI : public ScriptedAI
{
    event_npc_emperorAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 Wound_Timer;
	uint32 ShadowPast_Timer;
	uint32 UnbalancingStrike_Timer;

	void Reset()
    {
		Wound_Timer = 5000;
		ShadowPast_Timer = 8000;
		UnbalancingStrike_Timer = 10000;
	}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (UnbalancingStrike_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_UNBALANCING_STRIKE);
            UnbalancingStrike_Timer = 10000;
        }else UnbalancingStrike_Timer -= diff;

        if (Wound_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget, SPELL_WOUND);

            Wound_Timer = 5000;
        }else Wound_Timer -= diff;

        if (ShadowPast_Timer < diff)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                DoCast(pTarget, SPELL_SHADOW_PAST);

            ShadowPast_Timer = 8000;
        }else ShadowPast_Timer -= diff;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_event_npc_emperor(Creature* pCreature)
{
    return new event_npc_emperorAI(pCreature);
}

/*######
## event_npc_fel_reaver
######*/

#define SPELL_CRUSADER_STRIKE		66003

struct MANGOS_DLL_DECL event_npc_fel_reaverAI : public ScriptedAI
{
    event_npc_fel_reaverAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	uint32 CrusaderStrike_Timer;

	void Reset()
    {
		CrusaderStrike_Timer = 7000;
	}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (CrusaderStrike_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_CRUSADER_STRIKE);
            CrusaderStrike_Timer = 10000;
        }else CrusaderStrike_Timer -= diff;

		DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_event_npc_fel_reaver(Creature* pCreature)
{
    return new event_npc_fel_reaverAI(pCreature);
}

void AddSC_custom_events()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "event_boss_kruul";
    newscript->GetAI = &GetAI_event_boss_kruul;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "event_npc_succubus";
    newscript->GetAI = &GetAI_event_npc_succubus;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "event_npc_hound";
    newscript->GetAI = &GetAI_event_npc_hound;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "event_npc_imp";
    newscript->GetAI = &GetAI_event_npc_imp;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "event_npc_emperor";
    newscript->GetAI = &GetAI_event_npc_emperor;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "event_npc_fel_reaver";
    newscript->GetAI = &GetAI_event_npc_fel_reaver;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "event_npc_image_kruul";
    newscript->GetAI = &GetAI_event_npc_image_kruul;
    newscript->pGossipHello = &GossipHello_event_npc_image_kruul;
    newscript->pGossipSelect = &GossipSelect_event_npc_image_kruul;
    newscript->RegisterSelf();
}
