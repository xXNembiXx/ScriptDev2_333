/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_GUARDAI_H
#define SC_GUARDAI_H

#define GENERIC_CREATURE_COOLDOWN 5000

struct MANGOS_DLL_DECL guardAI : public ScriptedAI
{
    public:
        explicit guardAI(Creature* pCreature);
        ~guardAI() {}

    uint32 GlobalCooldown;                                  //This variable acts like the global cooldown that players have (1.5 seconds)
    uint32 Bandage;
    uint32 Potion;
    uint32 Help;
    uint32 OffHand;
    uint32 ZoneAttackMsgTimer;
    bool yell;
    int _Aggro;
    float temp1;
    float temp2;
    Unit* enemy;
    Creature* Helper;

    void Reset();

    void Aggro(Unit *who);

    void JustDied(Unit *Killer);

    void DamageDeal(Unit *done_to, uint32 &damage);

    void DamageTaken(Unit *done_by, uint32 &damage);

    void UpdateAI(const uint32 diff);

    //common used for guards in main cities
    void DoReplyToTextEmote(uint32 em);

};

struct MANGOS_DLL_DECL guardAI_orgrimmar : public guardAI
{
    guardAI_orgrimmar(Creature* pCreature) : guardAI(pCreature) {}

    void ReceiveEmote(Player* pPlayer, uint32 text_emote);
};

struct MANGOS_DLL_DECL guardAI_stormwind : public guardAI
{
    guardAI_stormwind(Creature* pCreature) : guardAI(pCreature) {}

    void ReceiveEmote(Player* pPlayer, uint32 text_emote);
};

#endif
