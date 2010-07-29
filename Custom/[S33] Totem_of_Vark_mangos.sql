DELETE FROM `creature` WHERE (`id`='17393');
UPDATE `creature_template` SET `ScriptName`='npc_ancestor_yor' WHERE (`entry`='17393');
UPDATE `creature_template` SET `ScriptName`='npc_totem_of_yor' WHERE (`entry`='17363');
UPDATE `quest_template` SET `SpecialFlags`='2', `SrcSpell`=NULL WHERE (`entry`='9542');