-- insert text for cut scene "judgement"
REPLACE INTO `script_texts`
	(entry,content_default,content_loc1,content_loc2,content_loc3,content_loc4,content_loc5,content_loc6,content_loc7,content_loc8,sound, type,language,emote,comment)
VALUES 
	(-1055005,'Bring forth the blood elf.','','','','','','','','',0,0,0,0,'VELEN_IMAGE_1'),
	(-1055006,'Matis, blood elf lieutenant of the Sunhawks, you have been found guilty of genocide against the draenei people.','','','','','','','','',0,0,0,0,'VELEN_IMAGE_2'),
	(-1055007,'You are to be executed at light\'s dawning. Have you anything to say for yourself?','','','','','','','','',0,0,0,0,'VELEN_IMAGE_3'),
	(-1055008,'May the Light have mercy on your soul. Take him back to his cell.','','','','','','','','',0,0,0,0,'VELEN_IMAGE_4'),
	(-1055009,'The Light?','','','','','','','','',0,0,0,0,'MATIS_JUDGED_1'),
	(-1055010,'I am Blood Knight, mongrel. I do not serve the Light, the Light serves me. If mercy is to be granted, it will be by me.','','','','','','','','',0,0,0,0,'MATIS_JUDGED_2'),
	(-1055011,'You seek to martyr me before my order - so be it. Strike me down, another will rise in my place and the suffering of the Light - of the conquered - will continue uninterrupted.','','','','','','','','',0,0,0,0,'MATIS_JUDGED_3'),
	(-1055012,'You blaspheme! The Light would never allow such an aberration!','','','','','','','','',0,0,0,0,'VINDICATOR_KUROS_1'),
	(-1055013,'The Light has no choice. It does as it is commanded. Just as the naaru you hold at the core of your vessel will do when we capture and enslave it... Do my words surprise you, blue blood? Yes, we know... We know everything.','','','','','','','','',0,0,0,0,'MATIS_JUDGED_4'),
	(-1055014,'Take him away.','','','','','','','','',0,0,0,0,'VELEN_IMAGE_5'),
	(-1055015,'Move!','','','','','','','','',0,0,0,0,'BLADE_OF_ARGUS'),
	(-1055016,'Draenei dog! Did you know that the one called Saruan wept like a babe as I beat him? A feeling of euphoria coursed through me, knowing that I had a member of high rank in my grasp. Were it not for Sironas\' plans for him, I would have tortured him to death... As I do to all draenei that I capture. Alas, I am certain that you will see him soon...','','','','','','','','',0,0,0,0,'MATIS_JUDGED_5'),
	(-1055017,'Breathe your last breath, heathen.','','','','','','','','',0,0,0,0,'VINDICATOR_KUROS_2'),
	(-1055018,'Find their source of power and tear it down. Tear it all down.','','','','','','','','',0,0,0,0,'VELEN_IMAGE_6');

-- insert text for capturing
REPLACE INTO `script_texts`
	(entry,content_default,content_loc1,content_loc2,content_loc3,content_loc4,content_loc5,content_loc6,content_loc7,content_loc8,sound, type,language,emote,comment)
VALUES 
	(-1055000,'We\'ve got you now, Matis the Cruel!','','','','','','','','',0,0,0,0,'TRACKER_OF_THE_HAND_1'),
	(-1055001,'You will never take me alive!','','','','','','','','',0,0,0,0,'MATIS_THE_CRUEL'),
	(-1055002,'Return to Kuros. I will bring him to Blood Watch.','','','','','','','','',0,0,0,0,'TRACKER_OF_THE_HAND_2');
