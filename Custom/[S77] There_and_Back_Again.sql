UPDATE `creature_template` SET `ScriptName`='npc_flynn_firebrew' WHERE (`entry`='24364');
UPDATE `creature_template` SET `ScriptName`='npc_slurpo_fizzykeg' WHERE (`entry`='28329');
UPDATE `creature_template` SET `ScriptName`='npc_brewfest_delivery_bunny' WHERE (`entry`='24337');
UPDATE `quest_template` SET `SpecialFlags`='0' WHERE (`entry`='11122');
INSERT INTO creature
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES
   (9327999, 24364, 0, 1, 1, 0, 0, -5603.14, -458.224, 403.838, 5.219, 25, 5, 0, 1003, 0, 0, 0),
   (9328000, 24337, 0, 1, 1, 0, 3001, -5200.12, -491.74, 388.464, 2.69553, 25, 5, 0, 1, 0, 0, 0),
   (9328001, 24337, 1, 1, 1, 0, 3001, 1279.63, -4411.31, 26.3942, 1.73176, 25, 5, 0, 1, 0, 0, 0);
