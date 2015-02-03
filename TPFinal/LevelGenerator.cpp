#include "LevelGenerator.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

LevelGenerator* LevelGenerator::_instance = NULL;

LevelGenerator::LevelGenerator(void)
{
	//_instance = LevelGenerator();
}

void LevelGenerator::Start()
{
	nextUpdate = 5.0f;
}

void LevelGenerator::Update()
{
	if(nextUpdate < GameManager::Instance().player->_location.z)
	{
		nextUpdate += 5.0f;
		Model* newMdl = new Model(*_plateformList[0]);
		newMdl->_location = Point3(0.0f, 0.0f, nextUpdate+10.0f);
		_plateformUse.push_back(*newMdl);
		GameManager::Instance()._models.push_back(newMdl);
	}
}

void LevelGenerator::AddPlateformToList(Model* mdl)
{
	_plateformList.push_back(mdl);
}


LevelGenerator::~LevelGenerator(void)
{
	std::vector<Model*>::iterator it = _plateformList.begin();
	while (it != _plateformList.end())
	{
		delete (*it);
		it = _plateformList.erase(it);
	}
}

LevelGenerator*& LevelGenerator::Instance()
{
	if(_instance == NULL)
		_instance = new LevelGenerator();
	return _instance;
}
