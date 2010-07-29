DELETE FROM `script_waypoint` WHERE (`entry`='17391');
INSERT INTO script_waypoint (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
( 17391, 1, -3926.08,  -12755.158,   99.08043, 0, 'Ancestor Coo Waypoint'),
( 17391, 2, -3924.02,  -12763.896,   101.54787, 0, 'Ancestor Coo Waypoint');

REPLACE INTO script_texts
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
   (-1050014, 'Follow me!', '', '', '', '', '', '', '', '', 0, 0, 0, 0, ''),
   (-1050015, 'Ritk kin\'chikx azul azure summit...', '', '', '', '', '', '', '', '', 0, 0, 0, 0, ''),
   (-1050016, 'Coo xip fly... Jump ilos river. Find Tikti.', '', '', '', '', '', '', '', '', 0, 0, 0, 0, '');