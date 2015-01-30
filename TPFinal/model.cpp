#include "Model.h"
#include <fstream>

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

Model::Model(void)
{
	SetLocation(0,0,0);
	SetRotation(0,0,0);
	SetScale(1);
}

Model::Model(const Model& model)
{
	this->nbFace = 0;
	std::map<int, Face*>::const_iterator it1 = model._faces.begin();
	for( it1; it1 != model._faces.end(); it1++ )
	{
		Face* newFace = new Face();
		for(int i = 0; i < (*it1).second->_nbVertex; i++)
		{
			newFace->AddVertex((*it1).second->_vertexTable[i]);
		}
		this->_faces[it1->first] = newFace;
		this->nbFace++;
	}
	
	this->nbVertex = 0;
	std::map<int, Point3>::const_iterator it2 = model._vertex.begin();
	for( it2; it2 != model._vertex.end(); it2++ )
	{
		this->_vertex[it2->first] = it2->second;
		this->nbVertex++;
	}
	
	this->nbTexture = 0;
	std::map<int, Point2>::const_iterator it3 = model._textures.begin();
	for( it3; it3 != model._textures.end(); it3++ )
	{
		this->_textures[it3->first] = it3->second;
		this->nbTexture++;
	}

	this->_texture = model._texture;
	this->_name = model._name;
	
	this->_location = model._location;
	this->_rotation = model._rotation;
	this->_scale = model._scale;
}

Model::~Model(void)
{
	std::map<int, Face*>::iterator it = _faces.begin();
	while (it != _faces.end())
	{
		delete (*it).second;
		it = _faces.erase(it);
	}
}

///////////
//  INIT //
///////////
bool Model::InitModel( string modelName, string textureName )
{

	// init the path the object
	_name = modelName;

	// init the model
	bool result;
	
	result = ReadFileCounts();
	if( !result )
	{
		MessageBox(NULL, "Error when trying to read the file !",  "Game", MB_OK);
		return false;
	}

	result = LoadData();
	if( !result )
	{
		MessageBox(NULL, "Error when trying to read the file !",  "Game", MB_OK);
		return false;
	}

	// init the texture
	_texture = textureName;

	return true;
}

////////////////
//  LOCATION  //
////////////////
void Model::SetLocation(Point3 newLoc)
{
	_location.x = newLoc.x;
	_location.y = newLoc.y;
	_location.z = newLoc.z;
}

void Model::SetLocation(float x, float y, float z)
{
	_location.x = x;
	_location.y = y;
	_location.z = z;
}

void Model::Translate(Point3 newLoc)
{
	_location.x += newLoc.x;
	_location.y += newLoc.y;
	_location.z += newLoc.z;
}

void Model::Translate(float x, float y, float z)
{
	_location.x += x;
	_location.y += y;
	_location.z += z;
}

////////////////
//  ROTATION  //
////////////////
void Model::SetRotation(Point3 axis, float angle)
{
	this->_rotation.x = axis.x * angle;
	this->_rotation.y = axis.y * angle;
	this->_rotation.z = axis.z * angle;
}

void Model::SetRotation(float xAngle, float yAngle, float zAngle)
{
	this->_rotation.x = xAngle;
	this->_rotation.y = yAngle;
	this->_rotation.z = zAngle;
}

void Model::Rotate(Point3 axis, float angle)
{
	this->_rotation.x += axis.x * angle;
	this->_rotation.y += axis.y * angle;
	this->_rotation.z += axis.z * angle;
}

void Model::Rotate(float xAngle, float yAngle, float zAngle)
{
	this->_rotation.x += xAngle;
	this->_rotation.y += yAngle;
	this->_rotation.z += zAngle;
}

/////////////
//  SCALE  //
/////////////
void Model::SetScale(float scale)
{
	this->_scale = scale;
}

void Model::Scale(float factor)
{
	this->_scale *= factor;
}

///////////////
//  TEXTURE  //
///////////////
void Model::SetTexture(std::string newTex)
{
	_texture = newTex;
}

//////////////////
//  LOAD MODEL  //
//////////////////
bool Model::ReadFileCounts()
{
	
	ifstream fin;
    char input;

    // Initialise les compteurs.
    nbVertex = 0;
    nbTexture = 0;
    nbFace = 0;

    // Ouvre le fichier.
    fin.open(_name);

    // Vérifie si le fichier a bien été ouvert.
    if(fin.fail())
    {
		fin.close();
        return false;
    }

    // Effectue la lecture du fichier jusqu'à atteindre la fin.
    fin.get(input);
    while(!fin.eof())
    {
        // Si la ligne commence par 'v', compte soit les sommets, 
    // soit les coordonnées de texture, soit les normales.
        if(input == 'v')
        {
            fin.get(input);
            if(input == ' ') { nbVertex++; }
            if(input == 't') { nbTexture++; }
        }

        // Si la ligne commence par 'f', incrémente le nombre de faces.
        if(input == 'f')
        {
            fin.get(input);
            if(input == ' ') { nbFace++; }
        }
        
        // Sinon, lit le reste de la ligne.
        while(input != '\n')
        {
            fin.get(input);
        }

        // Commence à lire le début de la ligne suivante.
        fin.get(input);
    }

    // Close the file.
    fin.close();

	return true;
}

bool Model::LoadData()
{
	ifstream fin;
    char input;

    // Ouvre le fichier.
    fin.open(_name);

    // Vérifie si le fichier a bien été ouvert.
    if(fin.fail())
    {
		fin.close();
        return false;
    }

	int indexVertex = 1;
	int indexTexture = 1;
	int indexFace = 1;

	fin.get(input);
    while(!fin.eof())
    {
        if(input == 'v')
        {
            fin.get(input);

            // Lit les sommets.
            if(input == ' ') 
            { 
                float x, y, z;
				fin >> x >> y >> z;

				Point3 pt3;
				pt3.x = x;
				pt3.y = y;
				pt3.z = z;


				_vertex[indexVertex] = pt3;
				indexVertex++;
            }

            // Lit les coordonnées UV de texture.
            if(input == 't') 
            { 
				float x, y;
				fin >> x >> y;

				Point2 pt2;
				pt2.x = x;
				pt2.y = y;

				_textures[indexTexture] = pt2;
				indexTexture++;
            }

        }

        // Lit les faces.
        if(input == 'f') 
        {
            fin.get(input);
            if(input == ' ')
            {
				
				int gh = 45;
				// create the face
				Face* face = new Face();
				// check and create all the vertex of the face
				while(true)
				{
					int v, t;
					fin >> v >> input >> t;

					CUSTOM_VERTEX vertex;
					vertex.x = _vertex[v].x;
					vertex.y = _vertex[v].y;
					vertex.z = -_vertex[v].z;
					vertex.COLOR = 0xffff00ff;
					vertex.u = _textures[t].x;
					vertex.v = _textures[t].y;
					face->AddVertex(vertex);

					while(input != ' ' && input != '\n')
						fin.get(input);
					if(input == '\n')
						break;
				}

				if(face->_nbVertex == 0)
				{
					delete face;
				}
				else
				{
					gh = 2;
				}
				
				
				
				/*int v1, t1;
				int v2, t2;
				int v3, t3;
				
				// Lit les données des faces à partir de la fin pour passer en système indirect.
                fin >> v1 >> input >> t1;
				while(input != ' ')
					fin.get(input);
                fin >> v2 >> input >> t2;
				while(input != ' ')
					fin.get(input);
                fin >> v3 >> input >> t3;

				// create the face
				Face* face = new Face();
				// vertex 1
				CUSTOM_VERTEX vert1;
				vert1.x = _vertex[v1].x;
				vert1.y = _vertex[v1].y;
				vert1.z = _vertex[v1].z;
				vert1.COLOR = 0xffff0000;
				vert1.u = _textures[t1].x;
				vert1.v = _textures[t1].y;

				// vertex 2
				CUSTOM_VERTEX vert2;
				vert2.x = _vertex[v2].x;
				vert2.y = _vertex[v2].y;
				vert2.z = _vertex[v2].z;
				vert2.COLOR = 0xff00ff00;
				vert2.u = _textures[t2].x;
				vert2.v = _textures[t2].y;

				// vertex 3
				CUSTOM_VERTEX vert3;
				vert3.x = _vertex[v3].x;
				vert3.y = _vertex[v3].y;
				vert3.z = _vertex[v3].z;
				vert3.COLOR = 0xff0000ff;
				vert3.u = _textures[t3].x;
				vert3.v = _textures[t3].y;
				// set the custom vertex to the faces
				face->v1 = vert1;
				face->v2 = vert2;
				face->v3 = vert3;
				face->_nbVertex = 3;*/

				_faces[indexFace] = face;
				indexFace++;
            }
        }

        // Lit le reste de la ligne.
        while(input != '\n')
        {
            fin.get(input);
        }

        // Commence à lire la ligne suivante.
        fin.get(input);
    }

	fin.close();

	return true;

}
