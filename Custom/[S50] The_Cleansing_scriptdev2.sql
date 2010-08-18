-- script texts for quest "The Cleansing"

DELETE FROM `custom_texts` WHERE `entry` IN(-2500001,-2500002,-2500003,-2500004);
INSERT INTO `custom_texts`
	(`entry`, `content_default`, `content_loc3`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-2500001, 'Do you think that you get rid of me by meditation?', 'Glaubt ihr, dass ihr mich durch Meditation loswerdet?', 0, 0, 0, 0, 'npc_your_inner_turmoil Spawn 01'),
	(-2500002, 'Fool! I will defeat you and will finally be, what has grown in you for all the years!', 'Narr! Ich werde Euch vernichten und letztendlich zu dem werden, was all die Jahre in Euch herangewachsen ist!', 0, 0, 0, 0, 'npc_your_inner_turmoil Spawn 02'),
	(-2500003, 'You can not beat me. I am an indelible part of you!', 'Ihr könnt mich nicht besiegen. Ich bin ein unauslöschlicher Teil von euch!', 0, 0, 0, 0, 'npc_your_inner_turmoil 50%'),
	(-2500004, 'NOOOOOOO!', 'NEEEEIIIiiiinnnnnn!', 0, 0, 0, 0, 'npc_your_inner_turmoil DEATH');
