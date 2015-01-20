
#pragma

////////////////
//	INCLUDES  //
////////////////
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9mesh.h>
#include <d3dx9math.h>
#include <memory.h>

/////////////////
//  VARIABLES  //
/////////////////
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
FLOAT texture_size = 1.0f;