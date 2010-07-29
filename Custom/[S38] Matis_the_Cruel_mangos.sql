-- update script for questitem, quest-npc, end-quest-npc
UPDATE `item_template` SET ScriptName='item_flare_gun' WHERE entry=24278;
UPDATE `creature_template` SET ScriptName='npc_vindicator_kuros' WHERE entry=17843;
UPDATE `creature_template` SET ScriptName='npc_tracker_of_the_hand' WHERE entry=17853;

-- anpassen der geschwindigkeiten damit die npcs synchron laufen, der 2. eintrag ist für matis, und wirkt nur bei diesem event
UPDATE `creature_template` SET `MovementType`='0' WHERE (`entry`='17659');
UPDATE `creature_template` SET `speed_walk` = '1.48' WHERE (`entry` = '17865');