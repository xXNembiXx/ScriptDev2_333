-- HOS - Doors should be untargable for Players

-- door to the endboss
UPDATE `gameobject_template` SET `flags` = 6553636 WHERE `entry` = 191296;
-- door to the Event (this prevents a possilbe Crash with event, so won´t open it)
UPDATE `gameobject_template` SET `flags` = 6553636 WHERE `entry` = 191293;
