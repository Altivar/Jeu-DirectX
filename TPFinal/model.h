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
	
	// Location
	void SetLocation(Point3 newLoc);
	void SetLocation(float x, float y, float z);
	void Translate(Point3 newLoc);
	void Translate(float x, float y, float z);
	Point3 _location;

	// Rotation
	void SetRotation(Point3 axis, float angle);
	void SetRotation(float xAngle, float yAngle, float zAngle);
	void Rotate(Point3 axis, float angle);
	void Rotate(float xAngle, float yAngle, float zAngle);
	Point3 _rotation;

	// Scale
	void SetScale(float scale);
	void Scale(float factor);
	float _scale;

private :
	bool ReadFileCounts();
	bool LoadData();

};

