-- Ulduar Razorscale

-- Devouring Flame Target
UPDATE `creature_template` SET
ScriptName = 'mob_devouring_flame_target',
speed_walk = 0,
speed_run = 0,
unit_flags = 33554434,
type_flags = 2,
flags_extra = 2,
minlevel = 83,
maxlevel = 83
WHERE entry = '34188';

-- Dark Rune Watcher
UPDATE `creature_template` SET
ScriptName = 'mob_dark_rune_watcher'
WHERE entry = '33453';

-- Dark Rune Guardian
UPDATE `creature_template` SET
ScriptName = 'mob_dark_rune_watcher'
WHERE entry = '33388';

-- Dark Rune Sentinel
UPDATE `creature_template` SET
ScriptName = 'mob_dark_rune_watcher'
WHERE entry = '33846';

-- Expedition Commander
UPDATE `creature_template` SET
ScriptName = 'npc_expedition_commander'
WHERE entry = '33210';
