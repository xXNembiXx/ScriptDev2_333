-- Ulduar Ignis

-- Magma Rager
UPDATE `creature_template` SET
ScriptName = 'mob_magma_rager'
WHERE entry = 34086;

-- Iron Construct
UPDATE `creature_template` SET
ScriptName='mob_iron_construct',
mechanic_immune_mask = 617299803
WHERE entry = 33121;

-- Scorch Target
UPDATE `creature_template` SET
modelid_A = 169,
modelid_H = 169,
minlevel = 83,
maxlevel = 83,
faction_A = 14,
faction_h = 14,
unit_flags = 33554434,
type_flags = 2,
flags_extra = 2
WHERE entry = 33221;
