#include "modelssingleton.h"

ModelsSingleton ModelsSingleton::_instance = ModelsSingleton();

ModelsSingleton::ModelsSingleton(void)
{
	_models.clear();
	
	_modelCube.InitModel( ".\\Resources\\cube.obj" , ".\\Resources\\diamond_ore.png" );
	_modelCube.Translate(0, 0, 5);
	
	Model* m1 = new Model(_modelCube);
	m1->SetTexture(".\\Resources\\stonebrick_mossy.png");
	_models.push_back(m1);

	Model* m2 = new Model();
	m2->InitModel( ".\\Resources\\cube.obj" , ".\\Resources\\diamond_ore.png" );
	m2->Translate(0, 3, 0);
	_models.push_back(m2);

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
