
-- deleting ytdb quest support for compatible reason

DELETE FROM `creature_ai_scripts` WHERE creature_id=17318;


-- adding event handling for spell event

DELETE FROM `event_scripts` WHERE (`id`='10675');
INSERT INTO event_scripts () VALUES
   (10675, 0, 10, 17243, 80000, 0, -5029.91, -11291.79, 8.096, 6.27609),
   (10675, 90, 8, 17243, 1, 0, 0, 0, 0, 0),
   (10675, 1, 10, 17318, 80000, 0, -5152.65, -11250.14, 3.6, 2.82662);

UPDATE `creature_template` SET `ScriptName`='npc_geezle' WHERE (`entry`='17318');