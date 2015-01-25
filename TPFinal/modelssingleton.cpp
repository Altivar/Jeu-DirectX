#include "modelssingleton.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

ModelsSingleton ModelsSingleton::_instance = ModelsSingleton();

ModelsSingleton::ModelsSingleton(void)
{
	_models.clear();
	
	_modelCube.InitModel( ".\\Resources\\cube.obj" , ".\\Resources\\diamond_ore.png" );

	_modelTorus.InitModel( ".\\Resources\\torus.obj" , ".\\Resources\\stonebrick_mossy.png" );

	_modelThing.InitModel( ".\\Resources\\untitled.obj" , ".\\Resources\\redstone_block.png" );

	
	

	Model* m1 = new Model(_modelCube);
	m1->SetTexture(".\\Resources\\stonebrick_mossy.png");
	m1->Translate(0, 0, 5);
	_models.push_back(m1);

	Model* m2 = new Model(_modelCube);
	m2->SetTexture(".\\Resources\\diamond_ore.png");
	m2->Translate(0, 3, 0);
	_models.push_back(m2);

	Model* m3 = new Model(_modelTorus);
	m3->SetTexture(".\\Resources\\stonebrick_mossy.png");
	m3->Translate(0, 0, 1);
	_models.push_back(m3);

	Model* m4 = new Model(_modelThing);
	m4->SetTexture(".\\Resources\\redstone_block.png");
	m4->Translate(-1, -1, 0);
	_models.push_back(m4);

}


ModelsSingleton::~ModelsSingleton(void)
{
	std::list<Model*>::iterator it = _models.begin();
	while (it != _models.end())
	{
		delete (*it);
		it = _models.erase(it);
	}
}

ModelsSingleton& ModelsSingleton::Instance()
{
	return _instance;
}
