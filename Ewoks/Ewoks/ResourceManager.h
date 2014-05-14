#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "EngineObject.h"
#include <iostream>
#include <list>
#include <map>
#include <string>

#include <tinyxml2.h>

class Resource : public EngineObject
{
public:
	unsigned int m_ResourceID;
	unsigned int m_Scope;
	std::string m_FileName;
	bool m_bLoaded;

	virtual ~Resource(){};
	virtual void load(){};
	virtual void unload(){};

	inline Resource()
	{
		m_ResourceID = m_Scope = 0;
		m_bLoaded = false;
	}


protected:

private:

};

class ResourceManager
{
public:
	static ResourceManager* GetResourceManager();

	std::map<unsigned int, std::list<Resource*>> m_Resources;

	void clear();

	bool loadFromXMLFile(std::string FileName);

	const unsigned int getResourceCount() { return m_ResourceCount; }

protected:
	static ResourceManager m_ResourceManager;
	unsigned int m_ResourceCount;

private:

};


#endif