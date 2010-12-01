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
SDAuthor: Nembi
SD%Complete: 100
SDComment: Inferna Christmas PreEvent == Entry
SDCategory: Oculus
EndScriptData */


#include "precompiled.h"
#include "oculus.h"


/*######
## Portale || Teleports
######*/


bool GOHello_go_oculus_dalaran(Player* pPlayer, GameObject* pGo)
{ 
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pGo->GetInstanceData();


    pPlayer->TeleportTo(571, 5807.797f, 588.338f, 660.939f, 1.685162f);
    return false;

}


bool GOHello_go_oculus_exit(Player* pPlayer, GameObject* pGo)
{ 
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pGo->GetInstanceData();


    pPlayer->TeleportTo(571, 3878.909f, 6984.500f, 106.320f, 3.156650f);
    return false;

}


bool GOHello_go_oculus_port(Player* pPlayer, GameObject* pGo)
{ 
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pGo->GetInstanceData();


    pPlayer->TeleportTo(578, 945.987f, 1085.985f, 359.476f, 5.068471f);
    return false;

}


//Teleporter vs Lift

bool GossipHello_oculus_lift(Player* pPlayer, Creature* pCreature)
{
	ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
	if(m_pInstance->GetData64(DATA_HAKKAR) != ALIVE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bringt mich nach Oben!" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
};

bool GossipSelect_oculus_lift(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(578, 1035.594f, 1069.591f, 433.075f, 0.669807f);
            break;
    };
    return true;
};

//Teleporter Ragnaros

bool GossipHello_oculus_lift_ragnaros(Player* pPlayer, Creature* pCreature)
{
	ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bringt mich zur Prinzessin" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
};

bool GossipSelect_oculus_lift_ragnaros(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(578, 982.291f, 985.031f, 526.811f, 1.669533f);
            break;
    };
    return true;
};

//Teleporter Princess

bool GossipHello_oculus_lift_princess(Player* pPlayer, Creature* pCreature)
{
	ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Bringt mich zu Oramus" , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
};

bool GossipSelect_oculus_lift_princess(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->TeleportTo(578, 1064.387f, 1045.343f, 602.261f, 0.639345f);
            break;
    };
    return true;
};






                            /* ********* Gedönns ********* */


/*######
## Khaoz
######*/


#define KHAOZ_AGGRO				-2500176
#define KHAOZ_DIED				-2500177
#define KHAOZ_KILLED			-2500178
#define KHAOZ_SIGHT				-2500179
#define KHAOZ_RANDOM1			-2500180
#define KHAOZ_RANDOM2			-2500181

#define SPELL_ATTACK			16979
#define SPELL_ALK				11009


struct MANGOS_DLL_DECL christmas_eve_khaozAI : public ScriptedAI
{
    christmas_eve_khaozAI(Creature *pCreature) : ScriptedAI(pCreature)    
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiAttackTimer;
    uint32 m_uiAlkTimer;
    bool m_bIsHasYelled;

    
    void Reset()
    {
        m_uiAttackTimer = 10000;
        m_uiAlkTimer = 17000;

        m_bIsHasYelled = false;
    }


    void MoveInLineOfSight(Unit *pWho) 
    {
        if(!pWho)
            return;

        if (!m_bIsHasYelled && (m_creature->IsWithinDistInMap(pWho, 100.0f)))
        {
            if(pWho->GetTypeId() != TYPEID_PLAYER)
                return;

            if(Player* pPlayer = (Player*)m_creature->GetUnit(*m_creature, pWho->GetGUID()))
                if(pPlayer->isGameMaster())
                    return;

            DoScriptText(KHAOZ_SIGHT, m_creature);
        }
        m_bIsHasYelled = true;
    }


    void JustDied(Unit* pKiller)
    {
        DoScriptText(KHAOZ_DIED, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(KHAOZ_AGGRO, m_creature);	
    }

    void KilledUnit (Unit* pWho)
    {
        DoScriptText(KHAOZ_KILLED, m_creature);
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiAttackTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_ATTACK);
            DoScriptText(KHAOZ_RANDOM1, m_creature);

            m_uiAttackTimer = 10000;
        } else m_uiAttackTimer -= uiDiff;


        if (m_uiAlkTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_ALK);
            DoScriptText(KHAOZ_RANDOM2, m_creature);

            m_uiAlkTimer = 17000;
        } else m_uiAlkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};



/*######
## Marrvin
######*/


#define MARRVIN_RANDOM1			-2500182
#define MARRVIN_RANDOM2			-2500183
#define MARRVIN_AGGRO			-2500185
#define MARRVIN_DIED			-2500184

#define SPELL_SHADOWFORM		15473
#define SPELL_SHADOWPAIN		589
#define SPELL_FEAR				8122


struct MANGOS_DLL_DECL christmas_eve_marrvinAI : public ScriptedAI
{
    christmas_eve_marrvinAI(Creature *pCreature) : ScriptedAI(pCreature)    
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiShadowPainTimer;
    uint32 m_uiFearTimer;


    void Reset()
    {
        DoCast(m_creature, SPELL_SHADOWFORM, true);

        m_uiShadowPainTimer = 10000;
        m_uiFearTimer = 16000;
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(MARRVIN_AGGRO, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(MARRVIN_DIED, m_creature);	
        DoCast(m_creature, SPELL_SHADOWFORM, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiShadowPainTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_SHADOWPAIN, true);
            DoScriptText(MARRVIN_RANDOM1, m_creature);

            m_uiShadowPainTimer = 10000;
        } else m_uiShadowPainTimer -= uiDiff;

        if (m_uiFearTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCast(pTarget,SPELL_FEAR, true);
            DoScriptText(MARRVIN_RANDOM2, m_creature);

            m_uiFearTimer = 16000;
        } else m_uiFearTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};



CreatureAI* GetAI_christmas_eve_khaoz(Creature* pCreature)
{
    return new christmas_eve_khaozAI(pCreature);
}

CreatureAI* GetAI_christmas_eve_marrvin(Creature* pCreature)
{
    return new christmas_eve_marrvinAI(pCreature);
}

void AddSC_oculus_start()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "christmas_eve_marrvin";
    newscript->GetAI = &GetAI_christmas_eve_marrvin;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "christmas_eve_khaoz";
    newscript->GetAI = &GetAI_christmas_eve_khaoz;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_exit";
    newscript->pGOHello = &GOHello_go_oculus_exit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_port";
    newscript->pGOHello = &GOHello_go_oculus_port;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_oculus_dalaran";
    newscript->pGOHello = &GOHello_go_oculus_dalaran;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_lift";
    newscript->pGossipHello = &GossipHello_oculus_lift;
    newscript->pGossipSelect = &GossipSelect_oculus_lift;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_lift_ragnaros";
    newscript->pGossipHello = &GossipHello_oculus_lift_ragnaros;
    newscript->pGossipSelect = &GossipSelect_oculus_lift_ragnaros;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "oculus_lift_princess";
    newscript->pGossipHello = &GossipHello_oculus_lift_princess;
    newscript->pGossipSelect = &GossipSelect_oculus_lift_princess;
    newscript->RegisterSelf();
}
