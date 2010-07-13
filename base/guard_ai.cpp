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
SDName: Guard_AI
SD%Complete: 90
SDComment:
SDCategory: Guards
EndScriptData */

#include "precompiled.h"
#include "guard_ai.h"

// **** This script is for use within every single guard to save coding time ****

#define GENERIC_CREATURE_COOLDOWN 5000

#define SAY_GUARD_SIL_AGGRO1        -1000198
#define SAY_GUARD_SIL_AGGRO2        -1000199
#define SAY_GUARD_SIL_AGGRO3        -1000200

guardAI::guardAI(Creature* pCreature) : ScriptedAI(pCreature),
    GlobalCooldown(0),
    ZoneAttackMsgTimer(0),
    _Aggro(0)
{}

void guardAI::Reset()
{
    if(_Aggro == 2)
     _Aggro = 1;
    GlobalCooldown = 0;
    Bandage = 0;
    Potion = 0;
    OffHand = 0;
    Help = urand(30000, 50000);
    yell = false;
    //m_creature->HandleStatModifier(UNIT_MOD_DAMAGE_MAINHAND,BASE_VALUE,+750,true);
    if(!(m_creature->GetEntry() == 2041 || m_creature->GetEntry() == 4423))
    {
       m_creature->setPowerType(POWER_RAGE); 
       m_creature->SetMaxPower(POWER_RAGE,500);
       m_creature->SetPower(POWER_RAGE,0); 
       bool elite = false;
       int temp3 = 0;
       int temp4 = 0;
       int temp5 = 0; 
       int temp6 = 0;
       temp3 = m_creature->getLevel();
       elite = m_creature->isElite();
       if(elite)
       {
          temp4 = temp3 * 200;
          temp5 = temp3 * 120;          
          temp6 = temp3 * 8;
       }
        else
        {
           if(temp3 < 71)
           {
               temp4 = temp3 * 125;
               temp5 = temp3 * 75;
               temp6 = temp3 * 5;
           }
           else
           {
              temp4 = temp3 * 175;
              temp5 = temp3 * 105;          
              temp6 = temp3 * 7;
           }       
        }
       if(m_creature->GetEntry() == 12481)
        temp4 = temp4 * 4;
       if(m_creature->GetEntry() == 12480)
        temp4 = temp4 * 6;
       if(m_creature->GetEntry() == 5624)
        temp4 = temp4 * 3;
       m_creature->SetMaxHealth(temp4);
       m_creature->SetHealth(temp4);
       m_creature->SetArmor(temp5);
       m_creature->SetResistance(SPELL_SCHOOL_NORMAL,temp6);
       m_creature->SetResistance(SPELL_SCHOOL_HOLY,temp6);
       m_creature->SetResistance(SPELL_SCHOOL_FIRE,temp6);
       m_creature->SetResistance(SPELL_SCHOOL_NATURE,temp6);
       m_creature->SetResistance(SPELL_SCHOOL_FROST,temp6);
       m_creature->SetResistance(SPELL_SCHOOL_SHADOW,temp6);
       m_creature->SetResistance(SPELL_SCHOOL_ARCANE,temp6);
    } 
}

void guardAI::Aggro(Unit *who)
{
    //Send Zone Under Attack message to the LocalDefense and WorldDefense Channels
    if (who->GetTypeId() == TYPEID_PLAYER && !ZoneAttackMsgTimer)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_GUARD_SIL_AGGRO1, m_creature, who); break;
            case 1: DoScriptText(SAY_GUARD_SIL_AGGRO2, m_creature, who); break;
            case 2: DoScriptText(SAY_GUARD_SIL_AGGRO3, m_creature, who); break;
        }
        m_creature->SendZoneUnderAttackMessage((Player*)who);
        ZoneAttackMsgTimer = 30000;
    }
}

void guardAI::DamageDeal(Unit *done_to, uint32 &damage)
{
   if(m_creature->GetEntry() == 4423)
       return;
   int temp1 = m_creature->GetPower(POWER_RAGE);
   int temp2 = 0;
   temp2 = temp1;
   switch(urand(0, 3))
   {
      case 0: temp1 = temp2 + 40;break;
      case 1: temp1 = temp2 + 50;break;
      case 2: temp1 = temp2 + 60;break;
      case 3: temp1 = temp2 + 70;break;
   }
   if(temp1 > 500)
      m_creature->SetPower(POWER_RAGE,500);   
   else
      m_creature->SetPower(POWER_RAGE,temp1);
}

void guardAI::DamageTaken(Unit *done_by, uint32 &damage)
{
    if(damage > m_creature->GetHealth())
        return;

   if(m_creature->GetEntry() == 4423)
       return;

   int temp1 = m_creature->GetPower(POWER_RAGE);
   int temp2 = 0;
   temp2 = temp1;
   switch(urand(0, 3))
   {
      case 0: temp1 = temp2 + 20;break;
      case 1: temp1 = temp2 + 30;break;
      case 2: temp1 = temp2 + 40;break;
      case 3: temp1 = temp2 + 50;break;
   }
   if(temp1 > 500)
      m_creature->SetPower(POWER_RAGE,500);   
   else
      m_creature->SetPower(POWER_RAGE,temp1); 
}

void guardAI::JustDied(Unit *Killer)
{
    //Send Zone Under Attack message to the LocalDefense and WorldDefense Channels
    if (Player* pKiller = Killer->GetCharmerOrOwnerPlayerOrPlayerItself())
        m_creature->SendZoneUnderAttackMessage(pKiller);
}

void guardAI::UpdateAI(const uint32 diff)
{
    //Always decrease our global cooldown first
    if (GlobalCooldown > diff)
        GlobalCooldown -= diff;
    else GlobalCooldown = 0;

    //Always decrease ZoneAttackMsgTimer
    if (ZoneAttackMsgTimer > diff)
        ZoneAttackMsgTimer -= diff;
    else ZoneAttackMsgTimer = 0;

    //Always decrease Bandage
    if (Bandage > diff)
        Bandage -= diff;
    else Bandage = 0;

    //Always decrease OffHand
    if (OffHand > diff)
        OffHand -= diff;
    else OffHand = 0;

    //Always decrease Potion
    if (Potion > diff)
        Potion -= diff;
    else Potion = 0;

    if(!m_creature->isAlive())
        return;

	if (!m_creature->isInCombat() && !(m_creature->GetEntry() == 2041 || m_creature->GetEntry() == 4423))
    {
       int temp1 = m_creature->GetPower(POWER_RAGE);
       int temp2 = temp1;
       temp1 = temp2 - 3;
       if(temp1 > 0)
          m_creature->SetPower(POWER_RAGE,temp1);
       else
          m_creature->SetPower(POWER_RAGE,0);
    }

    //Return since we have no target
    if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
        return;

    Unit *target = m_creature->getVictim();

       if(target == m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO,0) && !target->isAlive() && !m_creature->IsNonMeleeSpellCasted(false))
       {
          Unit* target2 = NULL;
          target2 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO,1);
          m_creature->getThreatManager().modifyThreatPercent(target,-100);
          if(target2 && target2->isAlive())
              {
                 m_creature->AddThreat(target2,1);
                 m_creature->Attack(target2,true);
                 AttackStart(target2);
                 return;
              }
          else
          {
              Reset();
              return;
          }
       }

    if(m_creature->IsHostileTo(target))
           enemy = target;

    if(enemy)
        if(!enemy->isAlive())
            enemy = NULL;


    //Always decrease Help when in combat
    if (Help > diff)
        Help -= diff;
    else Help = 0;

    if(!Help && !(m_creature->GetEntry() == 2041 || m_creature->GetEntry() == 4423))
    {
       int entry = m_creature->GetEntry();
       float x;
       float y;
       float z;
       float X;
       float Y;
       float Z;
       m_creature->GetPosition(x,y,z);
       m_creature->getVictim()->GetPosition(X,Y,Z);
       if(x > X)
           X = x + 20;
       else
           X = x - 20;
       if(y > Y)
           Y = y + 20;
       else
           Y = y - 20;
       m_creature->GetRespawnCoord(x,y,z); 

          if(entry != 12480 && entry != 12481)
           {
       Helper = DoSpawnCreature(entry, (float) (X - x), (float) (Y - y), (float) (Z -z), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
    /*   Helper = DoSpawnCreature(entry, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000); */
       if(Helper && enemy)
          ((CreatureAI*)Helper->AI())->AttackStart(enemy); 
           }else
             {
       Helper = DoSpawnCreature(68, (float) (X - x + 3), (float) (Y - y - 3), (float) (Z -z), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
           if(Helper && enemy)
           ((CreatureAI*)Helper->AI())->AttackStart(enemy); 
           Creature* Helper2 = NULL;
       Helper2 = DoSpawnCreature(68, (float) (X - x - 3), (float) (Y - y + 3), (float) (Z -z), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
           if(Helper2 && enemy)
           ((CreatureAI*)Helper2->AI())->AttackStart(enemy); 
            Creature* Helper3 = NULL;
       Helper3 = DoSpawnCreature(68, (float) (X - x + 3), (float) (Y - y + 3), (float) (Z -z), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
           if(Helper3 && enemy)
           ((CreatureAI*)Helper3->AI())->AttackStart(enemy); 
             }

       Help = urand(45000, 75000);
    }

    // Make sure our attack is ready and we arn't currently casting
    if (m_creature->isAttackReady() && !m_creature->IsNonMeleeSpellCasted(false))
    {
            if(m_creature->getVictim() && m_creature->SelectHostileTarget() && m_creature->GetEntry() == 3084 && OffHand > 0 && OffHand < 500)
            {
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_ATTACKOFF);
                m_creature->AttackerStateUpdate(m_creature->getVictim());
                m_creature->resetAttackTimer();
                OffHand = 0;
            }
        //If we are within range melee the target
        if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
        {

           if(_Aggro != 2 && m_creature->GetEntry() != 2041 && m_creature->GetEntry() != 5624)
           {
              _Aggro = 2;
              DoCastSpellIfCan(m_creature,2457);
              return;
           }

           if(m_creature->GetHealthPercent() > 39.0f && m_creature->HasAura(2458,EFFECT_INDEX_0) && m_creature->GetEntry() != 2041 && m_creature->GetEntry() != 5624)
           {
              DoCastSpellIfCan(m_creature,2457);
              return; 
           }

            bool Healing = false;
            int info = 0;
            int Change = 0;

            //Select a healing spell if less than 30% hp
            if (m_creature->GetHealthPercent() < 40.0f)
            {
               if(Potion == 0 && !Healing)
               {
                  Potion = 60000;
                  info = 17534;
                  Healing = true;
               }
               else
               {
                  if(Bandage == 0 && !Healing)
                  {
                     Bandage = 60000;
                     info = 38919;
                     Healing = true;
                  }
                  else
                      if(m_creature->HasAura(2457,EFFECT_INDEX_0))
                      {
                         info = 2458;
                         Change = 3;
                      }  
               }//if bandage
            }//if health <40%
            else
            {
                         if(!m_creature->HasAura(2048,EFFECT_INDEX_0) && m_creature->GetPower(POWER_RAGE) > 100)
                         {
                            info = 2048;
                            Change = 3;    
                         }
                         else
                         {
                            if(enemy && !enemy->HasAura(25203,EFFECT_INDEX_0) && m_creature->GetPower(POWER_RAGE) > 100)
                            {
                               info = 25203;
                               Change = 4;    
                            }
                            //select a hostile spell
                            else
                            {
                               if(enemy && m_creature->GetPower(POWER_RAGE) > 100)
                               {
                                  switch(urand(0, 7))
                                  {
                                     case 0:
                                        info = 29707;
                                        break;
                                     case 1:
                                        info = 11574;
                                        break;
                                     case 2:
                                        info = 30022;
                                        break;
                                     case 3:
                                        info = 11597;
                                        break;
                                     case 4:
                                        if(m_creature->HasAura(2457,EFFECT_INDEX_0))
                                           info = 25248;
                                        else info = 20569;
                                        break;
                                     case 5:
                                        if(m_creature->HasAura(2457,EFFECT_INDEX_0))
                                           info = 20560;
                                        else info = 6554;
                                        break;
                                     case 6:
                                        if(m_creature->HasAura(2457,EFFECT_INDEX_0))
                                           info = 11581;
                                        else info = 1680;
                                        break;
                                     case 7:
                                        info = 11597;
                                        break;
                                  }//switch
                               }//if rage
                            }//else hostile spell
                         }//if no demoralizing
                     }//if no battle shout

            if(m_creature->GetEntry() == 4423)
               info = 0;

            if(m_creature->GetEntry() == 5624)
            {
                info = 0;
                if(!m_creature->HasAura(41924,EFFECT_INDEX_0))
                    DoCastSpellIfCan(m_creature, 41924);
            }

            //50% chance to replace our white hit with a spell
            if (info && urand(0, 1) == 0 && !GlobalCooldown)
            {
                //Cast the spell
                if (Healing)DoCastSpellIfCan(m_creature, info);
                else
                {
                         if(Change == 3)
                         {
                            DoCastSpellIfCan(m_creature, info);                            
                         }
                         else
                         {
                            if(Change == 4)
                               DoCastSpellIfCan(enemy, info);
                            else
                                DoCastSpellIfCan(enemy, info);
                         }              
                }
                //Set our global cooldown
                GlobalCooldown = GENERIC_CREATURE_COOLDOWN;
            }
            else m_creature->AttackerStateUpdate(m_creature->getVictim());

            m_creature->resetAttackTimer();
            if(m_creature->GetEntry() == 3084)
                OffHand = 1000;
        }
    }
    else
    {
        //Only run this code if we arn't already casting
        if (!m_creature->IsNonMeleeSpellCasted(false))
        {
            bool Healing = false;
            SpellEntry const *info = NULL;

            //Select a healing spell if less than 30% hp ONLY 33% of the time
            if (m_creature->GetHealthPercent() < 30.0f && !urand(0, 2))
                info = SelectSpell(m_creature, -1, -1, SELECT_TARGET_ANY_FRIEND, 0, 0, 0, 0, SELECT_EFFECT_HEALING);

            //No healing spell available, See if we can cast a ranged spell (Range must be greater than ATTACK_DISTANCE)
            if (info) Healing = true;
            else info = SelectSpell(m_creature->getVictim(), -1, -1, SELECT_TARGET_ANY_ENEMY, 0, 0, ATTACK_DISTANCE, 0, SELECT_EFFECT_DONTCARE);

            //Found a spell, check if we arn't on cooldown
            if (info && !GlobalCooldown)
            {
                //If we are currently moving stop us and set the movement generator
                if ((*m_creature).GetMotionMaster()->GetCurrentMovementGeneratorType()!=IDLE_MOTION_TYPE)
                {
                    (*m_creature).GetMotionMaster()->Clear(false);
                    (*m_creature).GetMotionMaster()->MoveIdle();
                }

                //Cast spell
                if (Healing) DoCastSpell(m_creature,info);
                else DoCastSpell(m_creature->getVictim(),info);

                //Set our global cooldown
                GlobalCooldown = GENERIC_CREATURE_COOLDOWN;

            }                                               //If no spells available and we arn't moving run to target
			else if ((*m_creature).GetMotionMaster()->GetCurrentMovementGeneratorType()!=CHASE_MOTION_TYPE)
            {
                //Cancel our current spell and then mutate new movement generator
                m_creature->InterruptNonMeleeSpells(false);
                (*m_creature).GetMotionMaster()->Clear(false);
                (*m_creature).GetMotionMaster()->MoveChase(m_creature->getVictim());
            }
        }
    }
}

void guardAI::DoReplyToTextEmote(uint32 em)
{
    switch(em)
    {
        case TEXTEMOTE_KISS:    m_creature->HandleEmoteCommand(EMOTE_ONESHOT_BOW);    break;
        case TEXTEMOTE_WAVE:    m_creature->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);   break;
        case TEXTEMOTE_SALUTE:  m_creature->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE); break;
        case TEXTEMOTE_SHY:     m_creature->HandleEmoteCommand(EMOTE_ONESHOT_FLEX);   break;
        case TEXTEMOTE_RUDE:
        case TEXTEMOTE_CHICKEN: m_creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);  break;
    }
}

void guardAI_orgrimmar::ReceiveEmote(Player* pPlayer, uint32 text_emote)
{
    if (pPlayer->GetTeam()==HORDE)
        DoReplyToTextEmote(text_emote);
}

void guardAI_stormwind::ReceiveEmote(Player* pPlayer, uint32 text_emote)
{
    if (pPlayer->GetTeam() == ALLIANCE)
        DoReplyToTextEmote(text_emote);
}
