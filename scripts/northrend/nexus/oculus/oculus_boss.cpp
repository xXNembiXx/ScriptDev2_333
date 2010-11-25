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


	uint16 m_uiPhase;

/*######
## oculus_boss_oramus
######*/

#define THE_OCULUS				578
#define SPELL_FLAME_BREATH		18435

#define START1					-2500130
#define START2					-2500131
#define START3					-2500132
#define START4					-2500133
#define START5					-2500134
#define SECOND					-2500135
#define THIRD					-2500136





struct Location
{
	float x, y, z;
};


static Location WayPoints[] =
{
	//Oramus Movements
	{1088.114380f, 989.888245f, 441.605164f},  // 0 to the Players
	{1040.636597f, 937.819885f, 470.055634f},  // 1 to Ragnaros
	{1006.930115f, 1014.784302f, 544.198364f}, // 2 to Princess
	{1103.853882f, 1141.653442f, 564.757813f}, // 3 to Hakkar
	{1105.064087f, 1050.933838f, 561.571899f}, // 4 to the Middle
	{1108.812012f, 1040.247070f, 607.637421f}, // 5 to the Top
	//Player Teleports
	{1048.228760f, 925.094055f, 438.941345f}, // 6
	{986.237976f, 997.005432f, 526.810974f}, // 7
	{1126.063843f, 1178.769653f, 526.811707f}, // 8
	{1153.211f, 1062.382f, 434.061f}  // 9
};


struct MANGOS_DLL_DECL oculus_boss_oramusAI : public ScriptedAI
{
    oculus_boss_oramusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }


    ScriptedInstance* m_pInstance;


	uint32 m_uiSayTimer;
	uint32 m_uiSayPoint;
	uint32 m_uiSay2Timer;
	uint32 m_uiSay2Point;
	uint32 m_uiSay3Timer;
	uint32 m_uiSay3Point;

//ToDo: After Wipe Respawn Ragnaros || phaseMask 128
    void Reset()
    {
       m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
       m_creature->SetStandState(UNIT_STAND_STATE_SLEEP);

	   m_uiPhase = 1;
	   m_uiSayTimer = 1000;
	   m_uiSayPoint = 0;
	   m_uiSay2Timer = 3000;
	   m_uiSay2Point = 0;
	   m_uiSay3Timer = 3000;
	   m_uiSay3Point = 0;

	   m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);

	   m_creature->GetMotionMaster()->MoveTargetedHome();

    }

    void JustDied(Unit* pKiller)
    {
    }

    void EnterCombat(Unit* pWho)
    {
	   if(Creature* pRagnaros = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_RAGNAROS)))
			pRagnaros->SetPhaseMask(1, true);
	   if(Creature* pTheradras = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_THERADRAS)))
			pTheradras->SetPhaseMask(1, true);
	   if(Creature* pHakkar = m_creature->GetCreature(*pWho, m_pInstance->GetData64(DATA_HAKKAR)))
			pHakkar->SetPhaseMask(1, true);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
		m_creature->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
		SetCombatMovement(false);
		m_creature->GetMotionMaster()->MoveIdle();
		m_uiPhase = 1;	

		m_creature->MonsterMove(WayPoints[0].x, WayPoints[0].y, WayPoints[0].z, 500);
    }

    void KilledUnit(Unit* pKiller)
    {
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

		if (m_uiPhase == 1)
		{
			if(m_uiSayTimer <= uiDiff)
			{
				// must be initialized here... 
				Map* pMap = NULL;
				switch(m_uiSayPoint)
				{
					case 0:
						DoScriptText(START1, m_creature);
						if (Creature* pTrigger = m_creature->GetCreature(*m_creature,m_pInstance->GetData64(DATA_TRIGGER)))
							DoCast(pTrigger,SPELL_FLAME_BREATH,true);
						m_uiSayTimer = 5000;
						break;
					case 1:
						DoScriptText(START2, m_creature);
						m_uiSayTimer = 5000;
						break;
					case 2:
						DoScriptText(START3, m_creature);
						m_uiSayTimer = 5000;
						break;
					case 3:
						DoScriptText(START4, m_creature);
						m_uiSayTimer = 5000;
						break;
					case 4:
						DoScriptText(START5, m_creature);
						m_creature->MonsterMove(WayPoints[1].x, WayPoints[1].y, WayPoints[1].z, 5000);
						m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
						m_uiSayTimer = 2000;
						break;
					case 5:
						Map* pMap = m_creature->GetMap();
						if (pMap && pMap->IsDungeon())
						{
							Map::PlayerList const &players = pMap->GetPlayers();
							for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
								itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[6].x, WayPoints[6].y, WayPoints[6].z, 4.363545f);
						}
						break;
				}m_uiSayPoint++;
			}else m_uiSayTimer -= uiDiff;
		}

		if (m_uiPhase == 2)
		{
			if(m_uiSay2Timer <= uiDiff)
			{
				// must be initialized here... 
				Map* pMap2 = NULL;
				switch(m_uiSay2Point)
				{
					case 0:
						DoScriptText(SECOND, m_creature);
						m_uiSayTimer = 5000;
						break;
					case 1:
						m_creature->MonsterMove(WayPoints[2].x, WayPoints[2].y, WayPoints[2].z, 5000);
						Map* pMap2 = m_creature->GetMap();
						if (pMap2 && pMap2->IsDungeon())
						{
							Map::PlayerList const &players2 = pMap2->GetPlayers();
							for (Map::PlayerList::const_iterator itr = players2.begin(); itr != players2.end(); ++itr)
								itr->getSource()->TeleportTo (THE_OCULUS, WayPoints[7].x, WayPoints[7].y, WayPoints[7].z, 1.831856f);
						}
						m_uiSayTimer = 3000;
						break;
				}m_uiSay2Point++;
			}else m_uiSay2Timer -= uiDiff;
		}
/*
		if (m_uiPhase == 3)
		{
			if(m_uiSay3Timer <= uiDiff)
			{
				// must be initialized here... 
				Map* pMap3 = NULL;
				switch(m_uiSay3Point)
				{
					case 0:
						DoScriptText(THIRD, m_creature);
						m_uiSayTimer = 5000;
						break;
					case 1: */










        DoMeleeAttackIfReady();
    }
};



/*######
## oculus_boss_theradras
######*/

#define SPELL_FEAR					30615
#define SPELL_BOULDER				50999
#define SPELL_TRASH					3391


struct MANGOS_DLL_DECL oculus_boss_theradrasAI : public ScriptedAI
{
    oculus_boss_theradrasAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	ScriptedInstance* m_pInstance;

	uint32 m_uiFearTimer;
	uint32 m_uiBoulderTimer;
	uint32 m_uiTrashTimer;


	void Reset()
    {
		m_uiFearTimer = 10000;
		m_uiBoulderTimer = 8000;
		m_uiTrashTimer = 17000;
	}

    void JustDied(Unit* pKiller)
    {
		m_uiPhase = 3;
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFearTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_FEAR);

            m_uiFearTimer = 10000;
        }else m_uiFearTimer -= uiDiff;

        if (m_uiBoulderTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_BOULDER);

            m_uiBoulderTimer = 8000;
        }else m_uiBoulderTimer -= uiDiff;

        if (m_uiTrashTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(),SPELL_TRASH);

            m_uiTrashTimer = 17000;
        }else m_uiTrashTimer -= uiDiff;

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
		m_uiPhase = 2;
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

CreatureAI* GetAI_oculus_boss_theradras(Creature* pCreature)
{
    return new oculus_boss_theradrasAI(pCreature);
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

    newscript = new Script;
    newscript->Name = "oculus_boss_theradras";
    newscript->GetAI = &GetAI_oculus_boss_theradras;
    newscript->RegisterSelf();
}