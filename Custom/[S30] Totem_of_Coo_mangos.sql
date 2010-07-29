DELETE FROM `creature` WHERE (`id`='17379');
UPDATE `creature_template` SET `ScriptName`='npc_ancestor_akida' WHERE (`entry`='17379');
UPDATE `creature_template` SET `ScriptName`='npc_totem_of_akida' WHERE (`entry`='17360');
UPDATE `quest_template` SET `SpecialFlags`='2' WHERE (`entry`='9539');
