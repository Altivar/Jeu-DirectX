#pragma

#include "custom_vertex.h"
#include "point2.h"
#include "point3.h"

struct Face
{
	Face()
	{
		_nbVertex = 0;
		_vertexTable = NULL;
	}
	~Face()
	{
		if( _vertexTable != NULL )
			delete[] _vertexTable;
	}
	
	void AddVertex(const CUSTOM_VERTEX& vert)
	{

		CUSTOM_VERTEX* tempTable = new CUSTOM_VERTEX[_nbVertex+1];
		for(int i = 0; i < _nbVertex; i++)
		{
			tempTable[i] = _vertexTable[i];
		}
		tempTable[_nbVertex] = vert;

		if( _vertexTable != NULL )
			delete[] _vertexTable;
		_vertexTable = tempTable;

		_nbVertex++;
	}

	int _nbVertex;
	CUSTOM_VERTEX* _vertexTable;

};