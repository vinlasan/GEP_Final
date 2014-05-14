#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager ResourceManager::m_ResourceManager;

ResourceManager* ResourceManager::GetResourceManager()
{
	return &m_ResourceManager;
}

bool ResourceManager::loadFromXMLFile(std::string FileName)
{
	tinyxml2::XMLDocument doc(FileName.c_str());

	if (doc.LoadFile(FileName.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLNode* ResourceTree = doc.FirstChild();

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
								//Render manager code here
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