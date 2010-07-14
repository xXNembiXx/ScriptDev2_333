-- Rite of Vision

UPDATE `creature_template` SET `MovementType`='0', `flags_extra`='64', `speed_walk`='1' WHERE (`entry`='2983');
UPDATE `quest_template` SET `SpecialFlags`='2' WHERE (`entry`='772');
UPDATE `creature_template` SET `ScriptName`='npc_plains_vision' WHERE (`entry`='2983');