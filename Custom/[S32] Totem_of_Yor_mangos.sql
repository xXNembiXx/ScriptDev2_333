DELETE FROM `creature` WHERE (`id`='17392');
UPDATE `creature_template` SET `ScriptName`='npc_ancestor_tikti' WHERE (`entry`='17392');
UPDATE `creature_template` SET `ScriptName`='npc_totem_of_tikti' WHERE (`entry`='17362');
UPDATE `quest_template` SET `SpecialFlags`='2', `SrcSpell`=NULL WHERE (`entry`='9541');


