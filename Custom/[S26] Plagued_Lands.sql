-- Plagued Lands

UPDATE `quest_template` SET `ReqCreatureOrGOId1`='11836' WHERE (`entry`='2118');
UPDATE `creature_template` SET ScriptName='npc_captured_rabid_thistle_bear' where entry=11836;
UPDATE `creature_template` SET ScriptName='npc_rabid_thistle_bear' where entry='2164';
