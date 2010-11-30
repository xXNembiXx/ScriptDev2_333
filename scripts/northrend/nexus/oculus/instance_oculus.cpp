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
SDName: Instance_Oculus
SD%Complete: 
SDAuthor: Nembi & Sys
SDComment: Inferna Christmas PreEvent
SDCategory: Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

struct MANGOS_DLL_DECL instance_oculus : public ScriptedInstance
{
    instance_oculus(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint32 m_auiEncounter[MAX_ENCOUNTER];
    std::string strInstData;

    uint64 m_uiOramusGUID;
    uint64 m_uiEdwinGUID;
    uint64 m_uiOssirianGUID;
    uint64 m_uiRagnarosGUID;
    uint64 m_uiTheradrasGUID;
    uint64 m_uiHakkarGUID;
    uint64 m_uiTriggerGUID;
    uint64 m_uiTrigger2GUID;

    uint64 m_uiSantaGUID;

    uint64 m_ui1GUID;

    uint64 m_uiCollisionGUID;
    uint64 m_uiCannonGUID;
    uint64 m_uiGate1GUID;
    uint64 m_uiMeatGUID;

    uint64 m_uiGate2GUID;
    uint64 m_uiGate2RootsGUID;
    uint64 m_uiStatue1GUID;
    uint64 m_uiStatue2GUID;
    uint64 m_uiStatue3GUID;
    uint64 m_uiStatue4GUID;
    uint64 m_uiStatue5GUID;
    uint64 m_uiLight1GUID;
    uint64 m_uiLight2GUID;

	uint64 m_uiGate4GUID;



    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        m_uiOramusGUID = 0;
        m_uiEdwinGUID = 0;
        m_uiRagnarosGUID = 0;
        m_uiTheradrasGUID = 0;
        m_uiHakkarGUID = 0;
        m_uiTriggerGUID = 0;
        m_uiTrigger2GUID = 0;

        m_uiSantaGUID = 0;

        m_ui1GUID = 0;

        m_uiCannonGUID = 0;
        m_uiGate1GUID = 0;
        m_uiCollisionGUID = 0;
        m_uiMeatGUID = 0;

        m_uiGate2GUID = 0;
        m_uiGate2RootsGUID = 0;
        m_uiStatue1GUID = 0;
        m_uiStatue2GUID = 0;
        m_uiStatue3GUID = 0;
        m_uiStatue4GUID = 0;
        m_uiStatue5GUID = 0;
        m_uiLight1GUID = 0;
        m_uiLight2GUID = 0;

		m_uiGate4GUID = 0;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case NPC_ORAMUS: m_uiOramusGUID = pCreature->GetGUID(); break;
            case NPC_EDWIN: m_uiEdwinGUID = pCreature->GetGUID(); break;
            case NPC_OSSIRIAN: m_uiOssirianGUID = pCreature->GetGUID(); break;
            case NPC_RAGNAROS: m_uiRagnarosGUID = pCreature->GetGUID(); break;
            case NPC_THERADRAS: m_uiTheradrasGUID = pCreature->GetGUID(); break;
            case NPC_HAKKAR: m_uiHakkarGUID = pCreature->GetGUID(); break;
            case NPC_TRIGGER: m_uiTriggerGUID = pCreature->GetGUID(); break;
            case NPC_TRIGGER2: m_uiTrigger2GUID = pCreature->GetGUID(); break;
            case NPC_1:	m_ui1GUID = pCreature->GetGUID(); break;
            case NPC_SANTA:	m_uiSantaGUID = pCreature->GetGUID(); break;
        }
    }


    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
			case GO_GATE4: m_uiGate4GUID = pGo->GetGUID(); break;
            case GO_OCULUS_CANNON: m_uiCannonGUID = pGo->GetGUID(); break;
            case GO_RANCID_MEAT: m_uiMeatGUID = pGo->GetGUID(); break;
            case GO_OCULUS_GATE1: 
                m_uiGate1GUID = pGo->GetGUID();
                if(m_auiEncounter[1] == DONE)
                    pGo->SetPhaseMask(128, true);
                break;
            case GO_OCULUS_COLLISION: 
                m_uiCollisionGUID = pGo->GetGUID(); 
                if(m_auiEncounter[1] == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case GO_GATE2_ROOTS: 
                m_uiGate2RootsGUID = pGo->GetGUID(); 
                if(m_auiEncounter[2] == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case GO_GATE2: 
                m_uiGate2GUID = pGo->GetGUID(); 
                if(m_auiEncounter[2] == DONE)
                    pGo->SetGoState(GO_STATE_ACTIVE);
                break;
            case GO_OCULUS_STATUE1: 
                m_uiStatue1GUID = pGo->GetGUID(); 
                if(m_auiEncounter[2] == DONE)
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            case GO_OCULUS_STATUE2: 
                m_uiStatue2GUID = pGo->GetGUID();
                if(m_auiEncounter[2] == DONE)
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            case GO_OCULUS_STATUE3: 
                m_uiStatue3GUID = pGo->GetGUID();
                if(m_auiEncounter[2] == DONE)
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            case GO_OCULUS_STATUE4: 
                m_uiStatue4GUID = pGo->GetGUID();
                if(m_auiEncounter[2] == DONE)
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            case GO_OCULUS_STATUE5: 
                m_uiStatue5GUID = pGo->GetGUID();
                if(m_auiEncounter[2] == DONE)
                    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                break;
            case GO_LIGHT1: m_uiLight1GUID = pGo->GetGUID(); break;
            case GO_LIGHT2: m_uiLight2GUID = pGo->GetGUID(); break;
        }
    }


    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_ORAMUS:
                m_auiEncounter[0] = uiData;
                break;
            case TYPE_EDWIN:
                m_auiEncounter[1] = uiData;
                break;
            case TYPE_OSSIRIAN:
                m_auiEncounter[2] = uiData;
                break;
			case TYPE_TRIAL:
                m_auiEncounter[3] = uiData;
                break;
		}

        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3];

            strInstData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }


    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_ORAMUS:
                return m_auiEncounter[0];
            case TYPE_EDWIN:
                return m_auiEncounter[1];
            case TYPE_OSSIRIAN:
                return m_auiEncounter[2];
            case TYPE_TRIAL:
                return m_auiEncounter[3];
        }
        return 0;
    }

    uint64 GetData64(uint32 uiData)
    {
        switch(uiData)
        {
            case DATA_ORAMUS:
                return m_uiOramusGUID;
            case DATA_EDWIN:
                return m_uiEdwinGUID;
            case DATA_OSSIRIAN:
                return m_uiOssirianGUID;
            case DATA_RAGNAROS:
                return m_uiRagnarosGUID;
            case DATA_THERADRAS:
                return m_uiTheradrasGUID;
            case DATA_HAKKAR:
                return m_uiHakkarGUID;
            case DATA_TRIGGER:
                return m_uiTriggerGUID;
            case DATA_TRIGGER2:
                return m_uiTrigger2GUID;
            case DATA_SANTA:
                return m_uiSantaGUID;
            case DATA_1:
                return m_ui1GUID;
            case GO_OCULUS_COLLISION:
                return m_uiCollisionGUID;
            case GO_OCULUS_GATE1:
                return m_uiGate1GUID;
            case GO_OCULUS_CANNON:
                return m_uiCannonGUID;
            case GO_RANCID_MEAT:
                return m_uiMeatGUID;
            case GO_GATE2:
                return m_uiGate2GUID;
            case GO_GATE2_ROOTS:
                return m_uiGate2RootsGUID;
            case GO_OCULUS_STATUE1:
                return m_uiStatue1GUID;
            case GO_OCULUS_STATUE2:
                return m_uiStatue2GUID;
            case GO_OCULUS_STATUE3:
                return m_uiStatue3GUID;
            case GO_OCULUS_STATUE4:
                return m_uiStatue4GUID;
            case GO_OCULUS_STATUE5:
                return m_uiStatue5GUID;
            case GO_LIGHT1:
                return m_uiLight1GUID;
            case GO_LIGHT2:
                return m_uiLight2GUID;
			case GO_GATE4:
				return m_uiGate4GUID;
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
        loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3];

        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};


InstanceData* GetInstanceData_instance_oculus(Map* pMap)
{
    return new instance_oculus(pMap);
}

void AddSC_instance_oculus()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "instance_oculus";
    newscript->GetInstanceData = &GetInstanceData_instance_oculus;
    newscript->RegisterSelf();
}