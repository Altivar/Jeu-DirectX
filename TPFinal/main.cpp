
////////////////
//	INCLUDES  //
////////////////
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9mesh.h>
#include <d3dx9math.h>
#include <memory.h>

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG 


///////////////////////////
//  DEFINE VERTEX STRUCT //
///////////////////////////
struct CUSTOM_VERTEX
{
	FLOAT x, y, z; // position
	DWORD COLOR; // color
	FLOAT u, v; // texture
};
#define D3DFVF_CUSTOM_VERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

/////////////////
//  VARIABLES  //
/////////////////
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
FLOAT texture_size = 1.0f;


//////////////////////
//  INIT DIRECT 3D  //
//////////////////////
HRESULT InitDirect3D(HWND hWnd)
{
	// creation of a Direct3d objet and test versions of headers
	if( NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) )
		return E_FAIL;
	// parameters of presentation
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // fill the memory with 0
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	// create the Direct3D device
	if( FAILED( g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pd3dDevice) ) )
	{
		return E_FAIL;
	}

	// disable the culling
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// disable lighting
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	return S_OK;
}


////////////////////
//  CLOSE WINDOW  //
////////////////////
void OnWindowClosed()
{
	if( g_pTexture != NULL )
		g_pTexture->Release();
	if( g_pVB != NULL )
		g_pVB->Release();
	if( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();
	if( g_pD3D != NULL )
		g_pD3D->Release();
}


/////////////////////////
//  INIT VERTEX BUFFER //
/////////////////////////
HRESULT InitVertexBuffer()
{
	int taille = 256;
	// init vertex
	CUSTOM_VERTEX sommets[] = 
	{
		{0.0f, 0.5f , 0.0f, 0xffff8000, texture_size/2, texture_size}, 
		{-0.5f, 0.0f , 0.5f, 0xffff8000, 0.0f, 0.0f},
		{0.5f, 0.0f , -0.5f, 0xffff8000, 0.0f, texture_size},
		
		{0.0f, 0.5f , 0.0f, 0xffff0080, texture_size/2, texture_size},
		{-0.5f, 0.0f , -0.5f, 0xffff0080, 0.0f, 0.0f},
		{0.5f, 0.0f , 0.5f, 0xffff0080, 0.0f, texture_size}
	};

	// create vertex buffer
	if( FAILED( g_pd3dDevice->CreateVertexBuffer(
		sizeof(sommets),
		0,
		D3DFVF_CUSTOM_VERTEX,
		D3DPOOL_DEFAULT,
		&g_pVB,
		NULL) ) )
	{
		return E_FAIL;
	}

	// fill vertex buffer with custom vertex
		// lock vertex buffer
	void* psommets;
	if( FAILED(g_pVB->Lock(0,
		sizeof(sommets),
		(void**)&psommets,
		0)))
	{
		return E_FAIL;
	}
		// fill with vertex
	memcpy(psommets, sommets, sizeof(sommets));
		// unlock
	g_pVB->Unlock();

	return S_OK;
}


////////////////////
//  INIT TEXTURE  //
////////////////////
HRESULT InitTexture()
{
	
	// load texture from file
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, ".\\Resources\\wheat_stage_7.png", &g_pTexture)))
	{
		MessageBox(NULL, "Fichier de texture non trouv� !!",  "MON APPLI DE TEXTURE", MB_OK);
		return E_FAIL;
	}

	g_pd3dDevice->SetTexture(0, g_pTexture);
	
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_BLENDDIFFUSEALPHA);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

}


//////////////
//  MATRIX  //
//////////////
void MatrixSettings()
{	
	D3DXMATRIX worldMatrix;

	// get the time 
	UINT time = timeGetTime() % 1000;

	FLOAT angle_radians = time * (2.0f*D3DX_PI)/1000.0f;
	D3DXMatrixRotationY(&worldMatrix, angle_radians);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &worldMatrix);

	D3DXMATRIX viewMatrix;
	
	D3DXVECTOR3 eyeVector(1.25f, 1.25f, -1.25f);
	D3DXVECTOR3 targetVector(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 upVector(-0.25f, 0.25f, 0.25f);
	
	/*D3DXVECTOR3 eyeVector(0.0f, 0.0f, -2.0f);
	D3DXVECTOR3 targetVector(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 upVector(0.0f, 1.0f, 0.0f);*/
	
	D3DXMatrixLookAtLH(&viewMatrix, &eyeVector, &targetVector, &upVector);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	D3DXMATRIX projectionMatrix;
	int fov_degree = 135;
	float fovy_radian = fov_degree/180.0*D3DX_PI;
	float aspect = 1.0f;
	float zn = 0.1f;
	float zf = 100.0f;
	D3DXMatrixPerspectiveFovLH( &projectionMatrix, fovy_radian, aspect, zn, zf );
	g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &projectionMatrix );
}


//////////////
//  RENDER  //
//////////////
void Render()
{


	////
	//  Init Vertex Buffer and Textures for rendering
	InitVertexBuffer();
	InitTexture();

	//// clear the back buffer
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 255), 1.0f, 0);
	
	//// set back buffer to front buffer
	// begin render
	g_pd3dDevice->BeginScene();

	// matrix settings
	MatrixSettings();

	// fix the source of stream
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOM_VERTEX));
		// inform the device of vertex type used
	g_pd3dDevice->SetFVF( D3DFVF_CUSTOM_VERTEX );
		// draw vertex of vertexbuffer
	g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);


	// end render
	g_pd3dDevice->EndScene();
	
	//// show the front buffer at screen
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


///////////////////////
///   WINDOW PROC   ///
///////////////////////
LRESULT WINAPI WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		OnWindowClosed();
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		Render();
		ValidateRect(hWnd, NULL);
		return 0;
	default:
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
		break;
	}
}


////////////////
///   MAIN   ///
////////////////
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{

	// memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	////
	//	Define the window
	///
		// create a variable of type WNDCLASSX
	WNDCLASSEX ma_WndClass;

		// set values at each of its members
	ma_WndClass.cbSize = sizeof(WNDCLASSEX);
	ma_WndClass.style = CS_HREDRAW|CS_VREDRAW; // redessine la fenetre suite a un changement de taille ou un mouvement
	ma_WndClass.lpfnWndProc = WindowProc; // pointeur vers la procedure de la fenetre de traitement de messages
	ma_WndClass.cbClsExtra = 0; // pas de memeoire supplementaire au dela de cette classe
	ma_WndClass.cbWndExtra = 0; // pas de memoire supplementaire au dela de cette instance
	ma_WndClass.hInstance = hInstance; // handle d'instance de l'application
	ma_WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // icone de la fenetre
	ma_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // curseur souris affich�e dans la fenetre 
	ma_WndClass.hbrBackground = NULL; // GetStockObject(GRAY_BRUSH); // definition du fond de la zone client
	ma_WndClass.lpszMenuName = NULL; //nom de la resource menu ( ici pas de menu )
	ma_WndClass.lpszClassName = "MON APPLI"; // nom de la classification
	ma_WndClass.hIconSm = NULL; // icone associee a la fenetre

		// register the class
	RegisterClassEx(&ma_WndClass);

	////
	//	creation and initialisation of the main window
	///
		// creation ( function CreateWindow() )
	HWND hWnd = CreateWindow(
		"MON APPLI", // nom de la classification de fenetre
		"MA JOLIE BARRE DE TITRE",// texte barre de titre
		WS_OVERLAPPEDWINDOW, // style de la fenetre
		300, // position initiale horizontale
		100, // position initiale verticale
		500, // largeur en unit� de device
		500, // hauteur en unit� de device
		NULL, // handle sur le parent
		NULL, // handle sur le menu
		NULL, // ignor� sous xp
		NULL // valeur a passer lors de la creation
	);
	
	////
	//  Init Direct 3D
	InitDirect3D(hWnd);

	// show
	ShowWindow(hWnd, nCmdShow);

	// init client zone
	UpdateWindow(hWnd);

	////
	//	message treatment
	///
	
	// message loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Render();
	}

	return msg.wParam;

}