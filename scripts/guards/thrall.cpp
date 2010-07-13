/* 
############
 Thrall v 1
############

by Myav
*/

#include "precompiled.h"
#include "../../base/guard_ai.h"

#define GENERIC_CREATURE_COOLDOWN 5000

#define HEALINGPOTION 54572
#define POTIONCD 60000


struct MANGOS_DLL_DECL thrallAI : public ScriptedAI
{
    thrallAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset(); ZoneAttackMsgTimer = 0;}

    uint32 GlobalCooldown;      //This variable acts like the global cooldown that players have (1.5 seconds)
    uint32 Help;
    uint32 ZoneAttackMsgTimer;
    uint32 Potioncd;
    float temp1;
    float temp2;
    Unit* enemy;
    Creature* Helper;

void Reset()
{
    GlobalCooldown = 0;
    Help = 5000;
    Potioncd = 0;

    m_creature->setPowerType(POWER_RAGE); 
    m_creature->SetMaxPower(POWER_RAGE,500);
    m_creature->SetPower(POWER_RAGE,0);    
//    m_creature->SetMaxHealth(360000);
//    m_creature->SetHealth(360000);
    m_creature->SetArmor(11520);
    m_creature->SetResistance(SPELL_SCHOOL_NORMAL,810);
    m_creature->SetResistance(SPELL_SCHOOL_NATURE,810);
    m_creature->SetResistance(SPELL_SCHOOL_HOLY,810);
    m_creature->SetResistance(SPELL_SCHOOL_FIRE,810);
    m_creature->SetResistance(SPELL_SCHOOL_FROST,810);
    m_creature->SetResistance(SPELL_SCHOOL_SHADOW,810);
    m_creature->SetResistance(SPELL_SCHOOL_ARCANE,810);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISARM, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM , true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR , true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SILENCE, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DAZE, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SLEEP, true);
    m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_BANISH, true);
    m_creature->HandleStatModifier(UNIT_MOD_DAMAGE_MAINHAND,BASE_VALUE,+3000,true);
}

void Aggro(Unit *who)
{
    //Send Zone Under Attack message to the LocalDefense and WorldDefense Channels
    if (who->GetTypeId() == TYPEID_PLAYER && !ZoneAttackMsgTimer)
    {
        m_creature->SendZoneUnderAttackMessage((Player*)who);
        ZoneAttackMsgTimer = 30000;
    }
}

void DamageDeal(Unit *done_to, uint32 &damage)
{
   int temp1 = m_creature->GetPower(POWER_RAGE);
   int temp2 = 0;
   temp2 = temp1;
   switch(urand(0, 4))
   {
      case 0:temp1 = temp2 + 40;break;
      case 1:temp1 = temp2 + 50;break;
      case 2:temp1 = temp2 + 60;break;
      case 3:temp1 = temp2 + 70;break;
   }
   if(temp1 > 500)
      m_creature->SetPower(POWER_RAGE,500);   
   else
      m_creature->SetPower(POWER_RAGE,temp1);
}

void DamageTaken(Unit *done_by, uint32 &damage)
{
    if(damage > m_creature->GetHealth())
        return;

   int temp1 = m_creature->GetPower(POWER_RAGE);
   int temp2 = 0;
   temp2 = temp1;
   switch(urand(0, 4))
   {
      case 0:temp1 = temp2 + 20;break;
      case 1:temp1 = temp2 + 30;break;
      case 2:temp1 = temp2 + 40;break;
      case 3:temp1 = temp2 + 50;break;
   }
   if(temp1 > 500)
      m_creature->SetPower(POWER_RAGE,500);   
   else
      m_creature->SetPower(POWER_RAGE,temp1); 
}


void UpdateAI(const uint32 diff)
{
      if (m_creature->GetHealthPercent() < 30.0f && Potioncd<diff)
      {
         DoCastSpellIfCan (m_creature,HEALINGPOTION);
         Potioncd = POTIONCD;
      }

    //Always decrease our global cooldown first
    if (GlobalCooldown > diff)
        GlobalCooldown -= diff;
    else GlobalCooldown = 0;

    //Always decrease ZoneAttackMsgTimer
    if (ZoneAttackMsgTimer > diff)
        ZoneAttackMsgTimer -= diff;
    else ZoneAttackMsgTimer = 0;

      if(!(Potioncd < diff))
         Potioncd -= diff;

    if(!m_creature->isAlive())
        return;

    //Buff timer (only buff when we are alive and not in combat
    if (!m_creature->isInCombat())
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

    if(!m_creature->HasAura(41447,EFFECT_INDEX_0)) // Enrage
    {
       DoCastSpellIfCan(m_creature,41447);
       return;
    }

    //If we are within range melee the target
    if( m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
    {
        //Make sure our attack is ready and we arn't currently casting
        if( m_creature->isAttackReady() && !m_creature->IsNonMeleeSpellCasted(false))
        {
           int Change = 0;
           int info = 0;



                if(!m_creature->getVictim()->HasAura(29584,EFFECT_INDEX_0) && m_creature->GetPower(POWER_RAGE) > 50)
                {
                    info = 29584;  // Demoralizing Shout
                }
                else

           if(enemy && m_creature->GetPower(POWER_RAGE) > 60)
           {
              switch(urand(0, 7))
              {
               case 0:
                  info = 37476; // Cleave
                  break;
               case 1:
                  info = 36706; // Thunderclap
                  break;
               case 2:
                  info = 38618; // Whirlwind
                  break;
               case 3:
                  info = 12975; // Last Stand
                  Change = 1;
                  break;
               case 4:
                  info = 12809; // Concussion Blow
                  break;
               case 5:
                  info = 36138; // Hammer Stun 
                  break;
               case 6:
                  info = 47486; // Mortal Strike
                  break;
               case 7:
                  info = 34620; // Slam
                  break;
               } //switch
            } //if rage

            //65% chance to replace our white hit with a spell
            if (info && urand(0, 1) == 0 && !GlobalCooldown)
            {
                //Cast the spell   
                if (Change == 1)DoCastSpellIfCan(m_creature, info);
                else DoCastSpellIfCan(enemy, info);

                //Set our global cooldown
                GlobalCooldown = GENERIC_CREATURE_COOLDOWN;
            }//end 50% change
            else m_creature->AttackerStateUpdate(m_creature->getVictim());

            m_creature->resetAttackTimer();
        }//end attack ready
    }// end attack distance

}
};
CreatureAI* GetAI_thrall(Creature* pCreature)
{
    return new thrallAI (pCreature);
}
void AddSC_thrall()
{   
    Script *newscript;

    newscript = new Script;
    newscript->Name = "thrall";
    newscript->GetAI = &GetAI_thrall;
    newscript->RegisterSelf();
}
