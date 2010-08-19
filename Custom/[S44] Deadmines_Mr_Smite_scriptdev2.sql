-- Some Locale Update + Inserts

UPDATE `script_texts` SET `content_loc3`='Ihr da! Untersucht dieses Geräusch!' WHERE (`entry`='-1036000') ; 
UPDATE `script_texts` SET `content_loc3`='Wir werden angegriffen! Kommt Ihr Hunde! Wehrt die Eindringlinge ab!' WHERE (`entry`='-1036001');  
REPLACE INTO `script_texts`
	(`entry`,`content_default`,`content_loc3`)
VALUES
	('1036002', 'You landlubbers are tougher than i thought. I`ll have to improvise!', 'Ihr Landratten seid zäher, als ich dachte! Ich muss wohl improvisieren!');
REPLACE INTO `script_texts`
	(`entry`,`content_default`,`content_loc3`)
VALUES
	('1036003', 'D`ah! Now you\'re making me angry!', 'D`ah! Jetzt macht Ihr mich aber wütend!');
