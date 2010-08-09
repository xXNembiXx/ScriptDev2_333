

-- Scriptname
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='646';
UPDATE `creature_template` SET `AIName`='',`ScriptName`='boss_mrsmite' WHERE (`entry`='646');