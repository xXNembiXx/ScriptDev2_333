
DELETE FROM `script_waypoint` WHERE (`entry`='17393');
INSERT INTO script_waypoint (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
( 17393, 1, -4649.38,  -13007.5576,   0.162367, 0, 'Ancestor Yor Waypoint'),
( 17393, 2, -4604.53,  -12942.9570,   2.922896, 0, 'Ancestor Yor Waypoint'),
( 17393, 3, -4580.22,  -12906.0537,   11.97748, 0, 'Ancestor Yor Waypoint'),
( 17393, 4, -4568.75,  -12868.1787,   7.927529, 0, 'Ancestor Yor Waypoint'),
( 17393, 5, -4554.15,  -12831.7529,   12.02446, 0, 'Ancestor Yor Waypoint'),
( 17393, 6, -4546.50,  -12792.3477,   16.54275, 0, 'Ancestor Yor Waypoint'),
( 17393, 7, -4542.02,  -12741.7676,   9.442755, 0, 'Ancestor Yor Waypoint'),
( 17393, 8, -4531.60,  -12668.3301,   16.59256, 0, 'Ancestor Yor Waypoint'),
( 17393, 9, -4533.93,  -12614.7734,   12.47356, 0, 'Ancestor Yor Waypoint'),
( 17393, 10, -4538.40,  -12557.1943,  12.974200, 0, 'Ancestor Yor Waypoint'),
( 17393, 11, -4542.75,  -12491.9033,  3.171876, 0, 'Ancestor Yor Waypoint'),
( 17393, 12, -4548.39,  -12419.8945,   8.676768, 0, 'Ancestor Yor Waypoint'),
( 17393, 13, -4554.66,  -12380.1074,   19.042257, 0, 'Ancestor Yor Waypoint'),
( 17393, 14, -4569.86,  -12336.9443,   21.875879, 0, 'Ancestor Yor Waypoint'),
( 17393, 15, -4582.32,  -12297.8769,   15.123099, 0, 'Ancestor Yor Waypoint'),
( 17393, 16, -4605.11,  -12233.0928,   28.588888, 0, 'Ancestor Yor Waypoint'),
( 17393, 17, -4603.43,  -12153.1113,   39.701370, 0, 'Ancestor Yor Waypoint'),
( 17393, 18, -4599.52,  -12068.0009,   44.449554, 0, 'Ancestor Yor Waypoint'),
( 17393, 19, -4594.67,  -11936.1240,   36.185963, 0, 'Ancestor Yor Waypoint'),
( 17393, 20, -4574.30,  -11893.3506,   26.572578, 0, 'Ancestor Yor Waypoint'),
( 17393, 21, -4542.13,  -11847.5361,   21.584305, 0, 'Ancestor Yor Waypoint'),
( 17393, 22, -4514.82,  -11811.0195,   14.145091, 0, 'Ancestor Yor Waypoint'),
( 17393, 23, -4522.52,  -11743.0654,   17.374144, 0, 'Ancestor Yor Waypoint'),
( 17393, 24, -4488.64,  -11644.7168,   11.355472, 0, 'Ancestor Yor Waypoint');


REPLACE INTO script_texts
   (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
   (-1050017, 'Come, %s . Let us leave the water together, purified.', '', '', '', '', '', '', '', '', 0, 0, 0, 0, ''),
   (-1050018, '[Furbolg] We go now, together. We will seek Vark.', '', '', '', '', '', '', '', '', 0, 0, 0, 0, ''),
   (-1050019, '[Furbolg] Follow me to Vark.', '', '', '', '', '', '', '', '', 0, 0, 0, 0, '');