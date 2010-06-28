-- Feast of Winter Veil Fixes

UPDATE `creature_template` SET `ScriptName`= 'npc_winter_reveler' WHERE `entry`='15760';
UPDATE `creature_template` SET npcflag = '1' WHERE entry = '15664';
UPDATE `creature_template` SET ScriptName = 'npc_metzen' WHERE entry = '15664';
UPDATE `quest_template` SET ReqCreatureOrGOId1 = '15665' WHERE entry = '8762';
UPDATE `quest_template` SET ReqCreatureOrGOId1 = '15665' WHERE entry = '8746';