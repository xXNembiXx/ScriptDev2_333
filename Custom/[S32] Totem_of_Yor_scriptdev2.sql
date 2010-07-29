DELETE FROM `script_waypoint` WHERE (`entry`='17392');
INSERT INTO script_waypoint (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
( 17392, 1, -3881.70,  -13111.898,   5.81401, 0, 'Ancestor Tikti Waypoint'),
( 17392, 2, -3894.24,  -13077.400,   0.07646, 0, 'Ancestor Tikti Waypoint'),
( 17392, 3, -3899.35,  -13037.608,   -10.1982, 0, 'Ancestor Tikti Waypoint');

REPLACE INTO script_texts
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
   (-1050014, 'Follow me!', '', '', '', '', '', '', '', '', 0, 0, 0, 0, ''),
   (-1050015, '[Furbolg] Far you mixik tak come. Gaze upon the kitch\'kal river. Follow. Ilog to Yor.', '', '', '', '', '', '', '', '', 0, 0, 0, 0, ''),
   (-1050016, '[Furbolg] Go... Search yitix\'kil bottom river. South!', '', '', '', '', '', '', '', '', 0, 0, 0, 0, '');