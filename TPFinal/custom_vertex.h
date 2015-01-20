
////////////////
//	INCLUDES  //
////////////////
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9mesh.h>
#include <d3dx9math.h>
#include <memory.h>

///////////////////////////
//  DEFINE VERTEX STRUCT //
///////////////////////////
#pragma
struct CUSTOM_VERTEX
{
	FLOAT x, y, z; // position
	DWORD COLOR; // color
	FLOAT u, v; // texture
};
#define D3DFVF_CUSTOM_VERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

