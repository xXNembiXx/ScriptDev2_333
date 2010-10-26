/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_OCULUS_H
#define DEF_OCULUS_H

enum
{
	MAX_ENCOUNTER                   = 4,

	TYPE_ORAMUS						= 1,
	TYPE_EDWIN						= 2,
	TYPE_OSSIRIAN					= 3,
	TYPE_TRIAL						= 4,


	DATA_ORAMUS						= 10,
	DATA_EDWIN						= 11,
	DATA_OSSIRIAN					= 12,
	DATA_RAGNAROS					= 13,
	
	//Room1
	GO_DATA_COLLISION				= 20,
	GO_DATA_CANNON					= 21,
	GO_DATA_GATE1					= 22,

	//Room2
	GO_DATA_GATE2_ROOTS				= 23,
	GO_DATA_GATE2					= 24,
	GO_DATA_STATUE1					= 25,
	GO_DATA_STATUE2					= 26,
	GO_DATA_STATUE3					= 27,
	GO_DATA_STATUE4					= 28,
	GO_DATA_STATUE5					= 29,

	//---
	//Entrys
	//---
	NPC_ORAMUS			= 400059,
	NPC_EDWIN			= 400054,
	NPC_OSSIRIAN		= 400058,
	NPC_RAGNAROS		= 400060,

	//Room1
	GO_OCULUS_CANNON	= 400005,
	GO_OCULUS_GATE1		= 400004,
	GO_OCULUS_COLLISION	= 192633,
	GO_RANCID_MEAT		= 177664,

	//Room2
	GO_OCULUS_STATUE1	= 400006,
	GO_OCULUS_STATUE2	= 400007,
	GO_OCULUS_STATUE3	= 400008,
	GO_OCULUS_STATUE4	= 400009,
	GO_OCULUS_STATUE5	= 400010,
	GO_GATE2			= 400013,
	GO_GATE2_ROOTS		= 400011,
	GO_LIGHT1			= 106528,
	GO_LIGHT2			= 183948
};

#endif