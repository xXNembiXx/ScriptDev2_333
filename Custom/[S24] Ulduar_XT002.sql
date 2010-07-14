-- Ulduar XT002

-- Cleanup of NPC's
DELETE FROM creature WHERE id IN(33344,33346,33343,33329,34004);

-- XM-024 Pummeller
UPDATE `creature_template` SET
ScriptName = 'mob_pummeler',
speed_walk = '0.5',
speed_run = '0.5'
WHERE entry = '33344';

-- XE-321 Boombot
UPDATE `creature_template` SET
ScriptName = 'mob_boombot',
speed_walk = '0.5',
speed_run = '0.5'
WHERE entry = '33346';

-- XS-013 Scrapbot
UPDATE `creature_template` SET
ScriptName = 'mob_scrapbot',
speed_walk = '0.5',
speed_run = '0.5'
WHERE entry = '33343';

-- Heart of the Deconstructor
UPDATE `creature_template` SET
unit_flags = '8',
ScriptName = 'mob_xtheart'
WHERE entry = '33329';

-- Void Zone
UPDATE `creature_template` SET
speed_walk = 0,
speed_run = 0,
faction_A = '16',
faction_H = '16',
ScriptName = 'mob_void_zone',
unit_flags = '33587200'
WHERE entry = '34001';

-- Life Spark
UPDATE `creature_template` SET
ScriptName = 'mob_life_spark',
faction_A = '16',
faction_H = '16',
modelid_A = '18996', -- Display ID not blizzlike but otherwise Players cannot see them
modelid_H = '18996' -- Display ID not blizzlike but otherwise Players cannot see them
WHERE entry = '34004';