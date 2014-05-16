#include "stdafx.h"
#include "ResourceManager.h"
#include "RenderManager.h"

ResourceManager ResourceManager::m_ResourceManager;

ResourceManager* ResourceManager::GetResourceManager()
{
	return &m_ResourceManager;
}

Resource* ResourceManager::findResourcebyID(unsigned int UID)
{

	//Search through scopes
	for (auto &it : m_Resources)
	{
		if (!it.second.empty())
		{
			//Search through resources of scope
			for (auto &list_it : it.second)
			{
				//If matches ID
				if (list_it->m_ResourceID == UID)
					return list_it;
			}
		}
	}

	return NULL;
}

bool ResourceManager::loadFromXMLFile(std::string FileName)
{
	tinyxml2::XMLDocument doc(FileName.c_str());

	if (doc.LoadFile(FileName.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLNode* ResourceTree = doc.RootElement();

		if (ResourceTree)
		{
			for (tinyxml2::XMLNode* child = ResourceTree->FirstChild(); child; child = child->NextSibling())
			{
				tinyxml2::XMLElement* Element = child->ToElement();
				
				if (Element)
				{
					Resource *Resource = NULL;

					for (tinyxml2::XMLAttribute* ElementAttrib = const_cast<tinyxml2::XMLAttribute*>(Element->FirstAttribute()); ElementAttrib;
						ElementAttrib = const_cast<tinyxml2::XMLAttribute*>(ElementAttrib->Next()))
					{
						std::string AttribName = ElementAttrib->Name();
						std::string AttribValue = ElementAttrib->Value();

						if (AttribName == "type")
						{
							if (AttribValue == "graphic")
							{
								Resource = RenderManager::GetRenderManager()->loadFromXML(Element);
							}
						}
					}

					if (Resource)
					{
						m_Resources[Resource->m_Scope].push_back(Resource);
						m_ResourceCount++;
					}
				}
			}

			return true;
		}
	}

	return false;
}

void ResourceManager::setCurrentScope(unsigned int Scope)
{
	if (m_CurrentScope != 0)
	{
		std::list<Resource*>::iterator list_it;

		for (list_it = m_Resources[m_CurrentScope].begin(); list_it != m_Resources[m_CurrentScope].end(); list_it++)
			(*list_it)->unload();
	}

	m_CurrentScope = Scope;

	//Load new scope.
	std::list<Resource*>::iterator list_it;

	for (list_it = m_Resources[m_CurrentScope].begin(); list_it != m_Resources[m_CurrentScope].end(); list_it++)
	{
		(*list_it)->load();
	}
}