#pragma once

#include <iostream>
using namespace std;

#include "face.h"
#include <map>

struct Model
{

	Model(void);
	Model(const Model& model);
	~Model(void);
	bool InitModel( string modelName, string textureName );

	std::map<int, Face*> _faces;
	int nbFace;

	std::map<int, Point3> _vertex;
	int nbVertex;

	std::map<int, Point2> _textures;
	int nbTexture;

	string _name;
	
	void SetTexture(std::string newTex);
	string _texture;
	

	void SetLocation(Point3 newLoc);
	void SetLocation(float x, float y, float z);
	void Translate(Point3 newLoc);
	void Translate(float x, float y, float z);
	Point3 _location;

private :
	bool ReadFileCounts();
	bool LoadData();

};

