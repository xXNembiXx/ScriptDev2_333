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


bool m_bIsStatue1Used;			//Used for Room2
bool m_bIsStatue2Used;			//Used for Room2
bool m_bIsStatue3Used;			//Used for Room2
bool m_bIsStatue4Used;			//Used for Room2
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

		// ????
		/*
        m_bIsStatue5Used = false;			//Used for Room2
        m_bIsStatue4Used = false;			//Used for Room2
        m_bIsStatue3Used = false;			//Used for Room2
        m_bIsStatue2Used = false;			//Used for Room2
        m_bIsStatue1Used = false;			//Used for Room2
		*/
    }

	void Aggro(Unit* pWho)
	{
		if (m_pInstance)
			m_pInstance->SetData(TYPE_EDWIN, IN_PROGRESS);
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

    if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_COLLISION)))
            pGate->SetGoState(GO_STATE_ACTIVE);
    if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_GATE1)))
        pGate->SetPhaseMask(128, true); //better than "0"

    m_pInstance->SetData(GO_DATA_CANNON, DONE);
    return false;

}
                                                            /* *** ROOM 2 *** */

#define NPC_SNAKE1		29768
#define NPC_SNAKE2		29774
#define NPC_GURLOC		29920
#define NPC_GUARD		29829
#define SPELL_FIRE		25465

/*  Logik
 *  Statue 3 > Statue 2 > Statue 4 > Statue 1 > Statue 5 
 */


/*######
## Statue 1
######*/

bool GOHello_go_oculus_event_statue1(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && m_bIsStatue2Used && m_bIsStatue3Used && m_bIsStatue4Used)
    {
        pGo->SummonGameobject(GO_LIGHT1, 1124.34f, 1109.79f, 433.538f, TEMPSUMMON_MANUAL_DESPAWN, 0);
        pGo->SummonGameobject(GO_LIGHT2, 1124.34f, 1109.79f, 432.88f, TEMPSUMMON_MANUAL_DESPAWN, 0);

        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);

        m_bIsStatue1Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_SNAKE1, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_SNAKE2, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## Statue 2
######*/

bool GOHello_go_oculus_event_statue2(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && !m_bIsStatue2Used && m_bIsStatue3Used && !m_bIsStatue4Used)
    {
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);
        m_bIsStatue2Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_GURLOC, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GURLOC, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## Statue 3
######*/

bool GOHello_go_oculus_event_statue3(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && !m_bIsStatue2Used && !m_bIsStatue3Used && !m_bIsStatue4Used)
    {
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);
        m_bIsStatue3Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_GUARD, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GUARD, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}

/*######
## Statue 4
######*/

bool GOHello_go_oculus_event_statue4(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

    if (!m_bIsStatue1Used && m_bIsStatue2Used && m_bIsStatue3Used && !m_bIsStatue4Used)
    {
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);
        m_bIsStatue4Used = true;
    }
    else
    {
        pGo->SummonCreature(NPC_GURLOC, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GUARD, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## Statue 5
######*/

bool GOHello_go_oculus_event_statue5(Player* pPlayer, GameObject* pGo)
{
    if(!pPlayer && !pGo)
    return false;

	ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();
	
	if(!pInstance)
		return false;

    if (m_bIsStatue1Used && m_bIsStatue2Used && m_bIsStatue3Used && m_bIsStatue4Used)
    {
		if(Creature* pOssirian = pPlayer->GetCreature(*pPlayer, pInstance->GetData64(DATA_OSSIRIAN)))
			pOssirian->SetPhaseMask(1, true);
        pPlayer->CastSpell(pPlayer, SPELL_FIRE, true);

		//reset booleans, GO's need to be reuseable in case of group wipe...
        m_bIsStatue1Used = false;
		m_bIsStatue2Used = false;
		m_bIsStatue3Used = false;
		m_bIsStatue4Used = false;

    }
    else
    {
        pGo->SummonCreature(NPC_SNAKE1, 1120.019653f, 1098.877563f, 433.075684f, 1.103422f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        pGo->SummonCreature(NPC_GUARD, 1128.290894f, 1119.614258f, 433.024811f, 4.289958f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
    }

    return true;
}


/*######
## oculus_event_ossirian
######*/

#define SPELL_CURSE		25195
#define SPELL_WIND		25189

#define SAY_AGGRO			-2500032
#define SAY_GATE_PHASE1		-2500033
#define SAY_GATE_PHASE2		-2500034


struct MANGOS_DLL_DECL oculus_event_ossirianAI : public Scripted_NoMovementAI
{
    oculus_event_ossirianAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

	uint32 m_uiCurseTimer;
	uint32 m_uiWindTimer;
	uint32 m_uiAttackTimer;

	bool m_bIsPhase2;
	bool m_bResetEventRoom2;

	void Reset()
	{
		m_uiCurseTimer = 30000;
		m_uiWindTimer = 12000;
		m_uiAttackTimer = 5000;

		m_bIsPhase2 = false;
		m_bResetEventRoom2 = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

		if(!m_pInstance)
			return;

		Map* pMap = m_creature->GetMap();
		if(pMap)
		{
			Map::PlayerList const &lPlayers = pMap->GetPlayers();
			for (Map::PlayerList::const_iterator iter = lPlayers.begin(); iter != lPlayers.end(); ++iter)
			{
				Player* pPlayer = iter->getSource();

				if(pPlayer->isAlive())
					continue;

				m_bResetEventRoom2 = true;
			}
		}

		if(m_bResetEventRoom2)
		{
			// make GO's useable again
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE1)))
				pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE2)))
				pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE3)))
				pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE4)))
				pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE5)))
				pTemp->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);

			// despawn lights
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_LIGHT1)))
				pTemp->Delete();
			if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_LIGHT2)))
				pTemp->Delete();

			// close root door
			if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_GATE2_ROOTS)))
				pGate->SetGoState(GO_STATE_READY);	

			m_creature->SetPhaseMask(128, true);
		}
	}
	

    void JustDied(Unit* Killer)
    {
		if(!m_pInstance)
			return;
		
		if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_GATE2)))
            pGate->SetGoState(GO_STATE_ACTIVE);

		m_pInstance->SetData(TYPE_OSSIRIAN, DONE);

		DoScriptText(SAY_GATE_PHASE2, m_creature);
    }

	void Aggro (Unit* pWho)
	{
		DoScriptText(SAY_AGGRO, m_creature);

		if(!m_pInstance)
			return;

        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE1)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE2)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE3)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE4)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
        if (GameObject* pTemp = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_OCULUS_STATUE5)))
            pTemp->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);

		m_pInstance->SetData(TYPE_OSSIRIAN, IN_PROGRESS);
	}


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiWindTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_WIND);

            m_uiWindTimer = 12000;
        }
		else 
			m_uiWindTimer -= uiDiff;

        if (m_uiCurseTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_CURSE);

            m_uiCurseTimer = 30000;
        }
		else 
			m_uiCurseTimer -= uiDiff;

		if (!m_pInstance)
			return;

        if (!m_bIsPhase2 && (m_creature->GetHealthPercent() < 40.0f))
        {
			if (GameObject* pGate = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_GATE2_ROOTS)))
				pGate->SetGoState(GO_STATE_ACTIVE);	

			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

			DoScriptText(SAY_GATE_PHASE1, m_creature);
			m_bIsPhase2 = true;
        }

		if(m_bIsPhase2 && m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
		{
			if (m_bIsPhase2 && (m_uiAttackTimer < uiDiff))
			{
				m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			}
			else 
				m_uiAttackTimer -= uiDiff;
		}

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_oculus_event_edwin(Creature* pCreature)
{
    return new oculus_event_edwinAI(pCreature);
}

CreatureAI* GetAI_oculus_event_ossirian(Creature* pCreature)
{
    return new oculus_event_ossirianAI(pCreature);
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

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue1";
    newscript->pGOHello = &GOHello_go_oculus_event_statue1;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue2";
    newscript->pGOHello = &GOHello_go_oculus_event_statue2;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue3";
    newscript->pGOHello = &GOHello_go_oculus_event_statue3;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue4";
    newscript->pGOHello = &GOHello_go_oculus_event_statue4;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_event_statue5";
    newscript->pGOHello = &GOHello_go_oculus_event_statue5;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_event_ossirian";
    newscript->GetAI = &GetAI_oculus_event_ossirian;
    newscript->RegisterSelf();
}