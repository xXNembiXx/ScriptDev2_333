/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Instance_Gnomeregan
SD%Complete: 
SDAuthor: Nembi
SDComment: Inferna Christmas PreEvent
SDCategory: Gnomeregan
EndScriptData */


#include "precompiled.h"
#include "gnomeregan.h"


enum
{
	NPC_PUCKY		= 400041,

	GO_PUCKY_RIGHT	= 146086,
	GP_PUCKY_LEFT	= 146085
};

struct MANGOS_DLL_DECL instance_gnomeregan : public ScriptedInstance
{
	instance_gnomeregan(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

	uint32 m_auiEncounter[MAX_ENCOUNTER];
	std::string strInstData;

	uint64 m_uiPuckyGUID;

	uint64 m_uiGoLeftGUID;
	uint64 m_uiGoRightGUID;


	void Initialize()
	{
		memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

		m_uiPuckyGUID = 0;

		m_uiGoLeftGUID = 0;
		m_uiGoRightGUID = 0;
	}

	void OnCreatureCreate(Creature* pCreature)
	{
		switch(pCreature->GetEntry())
		{
			case NPC_PUCKY: m_uiPuckyGUID = pCreature->GetGUID(); break;
		}
	}


	void OnObjectCreate(GameObject* pGo)
	{
		switch(pGo->GetEntry())
		{
			case GP_PUCKY_LEFT: m_uiGoLeftGUID = pGo->GetGUID(); break;
			case GO_PUCKY_RIGHT: m_uiGoRightGUID = pGo->GetGUID(); break;
		}
	}


	void SetData(uint32 uiType, uint32 uiData)
	{
		switch(uiType)
		{
			case TYPE_PUCKY:
				m_auiEncounter[0] = uiData;
				break;
		}

		if (uiData == DONE)
		{
			OUT_SAVE_INST_DATA;

			std::ostringstream saveStream;
			saveStream << m_auiEncounter[0];

			strInstData = saveStream.str();

			SaveToDB();
			OUT_SAVE_INST_DATA_COMPLETE;
		}
	}


	uint32 GetData(uint32 uiType)
	{
		switch(uiType)
		{
			case TYPE_PUCKY:
				return m_auiEncounter[0];
		}
		return 0;
	}

	uint64 GetData64(uint32 uiData)
	{
		switch(uiData)
		{
			case DATA_PUCKY:
				return m_uiPuckyGUID;
			case DATA_GO_PUCKY_RIGHT:
				return m_uiGoLeftGUID;
			case DATA_GO_PUCKY_LEFT:
				return m_uiGoRightGUID;
		}
		return 0;
	}


	const char* Save()
	{
		return strInstData.c_str();
	}

	void Load(const char* in)
	{
		if (!in)
		{
			OUT_LOAD_INST_DATA_FAIL;
			return;
		}

		OUT_LOAD_INST_DATA(in);

		std::istringstream loadStream(in);
		loadStream >> m_auiEncounter[0];

		for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
			if (m_auiEncounter[i] == IN_PROGRESS)
				m_auiEncounter[i] = NOT_STARTED;

		OUT_LOAD_INST_DATA_COMPLETE;
	}
};


InstanceData* GetInstanceData_instance_gnomeregan(Map* pMap)
{
	return new instance_gnomeregan(pMap);
}

void AddSC_instance_gnomeregan()
{
	Script *newscript;
	newscript = new Script;
	newscript->Name = "instance_gnomeregan";
	newscript->GetInstanceData = &GetInstanceData_instance_gnomeregan;
	newscript->RegisterSelf();
}