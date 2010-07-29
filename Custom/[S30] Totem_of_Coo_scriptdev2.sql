DELETE FROM `script_waypoint` WHERE (`entry`='17379');
INSERT INTO script_waypoint (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
( 17379, 1, -4173.75,  -12514.605,   44.37066, 0, 'Ancestor Akida Waypoint'),
( 17379, 2, -4140.67,  -12518.501,   45.80541, 0, 'Ancestor Akida Waypoint'),
( 17379, 3, -4088.37,  -12526.445,   42.80884, 0, 'Ancestor Akida Waypoint'),
( 17379, 4, -4069.28,  -12541.747,   43.24752, 0, 'Ancestor Akida Waypoint'),
( 17379, 5, -4061.57,  -12552.793,   40.82198, 0, 'Ancestor Akida Waypoint'),
( 17379, 6, -4029.66,  -12587.724,   49.93429, 0, 'Ancestor Akida Waypoint'),
( 17379, 7, -4029.66,  -12587.724,   49.93429, 0, 'Ancestor Akida Waypoint'),
( 17379, 8, -3993.81,  -12634.629,   62.81399, 0, 'Ancestor Akida Waypoint'),
( 17379, 9, -3967.10,  -12679.759,   70.83762, 0, 'Ancestor Akida Waypoint'),
( 17379, 10, -3923.55,  -12745.004,   96.03991, 0, 'Ancestor Akida Waypoint');

REPLACE INTO script_texts
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
   (-1050010, 'Follow me I shall result you on a place!', '', '', '', '', '', '', '', '', 0, 0, 0, 0, '');