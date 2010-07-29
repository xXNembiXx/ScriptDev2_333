DELETE FROM `creature` WHERE (`id`='17391');
UPDATE `creature_template` SET `ScriptName`='npc_ancestor_coo' WHERE (`entry`='17391');
UPDATE `creature_template` SET `ScriptName`='npc_totem_of_coo' WHERE (`entry`='17361');
UPDATE `quest_template` SET `SpecialFlags`='2', `SrcSpell`=NULL WHERE (`entry`='9540');
