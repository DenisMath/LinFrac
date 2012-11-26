#include <windows.h>
#include <winuser.h>
#include <set>
#include "main.h"
#include "resource2.h"
#include <commctrl.h>       // must have
#pragma comment( lib, "comctl32.lib" )  // must have
//#include "resource.h"
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#pragma comment (lib, "d3d9.lib")
//#pragma comment (lib, "d3dx9.lib")
#include <strsafe.h>
#pragma warning( default : 4996 )
#include<vector>
#include "fractal.h"
#include <cmath>
//#include "bpoint.h"
//#define UNICODE
#define PI 3.14159265
#define ID_BUTTON 3001


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold Vertices

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw; // The transformed position for the vertex
	DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

std::vector<std::pair<double, double>> GraphicsPoints ;
std::vector<double> Tensions;
CUSTOMVERTEX* Vertices = new CUSTOMVERTEX[2];

HWND hMainDlg, TempChild, hWndDirectX;
HINSTANCE hInst;
LPRECT lpMainDialogRect = new RECT;
LPRECT lpMainDialogRectChild = new RECT;
LPRECT lpDesktopWindow = new RECT;
#define DELETE_MSG WM_USER + 1
int size = 0;
int nCmdSh = 0 ;
wchar_t buff[256];
std::set<HWND> basicPointsWindows;
Fractal f;

int toColor(double x, double max_temp)
{
	//return 0x111111 * pow(15,floor(max_temp/x));
	//return 0x111111 * ((int)floor(log(x)/log(max_temp))%16);
	return 0x111111 * ((int)floor(log(x)/log(max_temp))%16);
	//return 0x000001 * ((int)floor((max_temp/x)*0x0FFFFF)%0xFFFFFF);
}



void SetBufferPoints()
{
	int temp = GraphicsPoints.size();
	delete[] Vertices;
	Vertices = new CUSTOMVERTEX[temp];
	for(int i=0; i<temp; i++)
	{
		Vertices[i].x = GraphicsPoints[i].first ;
		Vertices[i].y = GraphicsPoints[i].second ;
		Vertices[i].z = 0.5f;
		Vertices[i].rhw = 1.0f ;
		Vertices[i].color = 0xFFD700 ;
	}
};

void SetBufferPointsW()
{
	int temp = GraphicsPoints.size();
	double temp_max = *max_element(Tensions.begin(),Tensions.end());
	delete[] Vertices;
	Vertices = new CUSTOMVERTEX[temp];
	for(int i=0; i<temp; i++)
	{
		Vertices[i].x = GraphicsPoints[i].first ;
		Vertices[i].y = GraphicsPoints[i].second ;
		Vertices[i].z = 0.5f;
		Vertices[i].rhw = 1.0f ;
		Vertices[i].color = toColor(Tensions[i], temp_max) ; ;
	}
};

void deleteBufferPoints()
{
	delete[] Vertices;
};



//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
	// Create the D3D object.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return E_FAIL;
	}

	// Device state would normally be set here

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitVB()
// Desc: Creates a vertex buffer and fills it with our Vertices. The vertex
//       buffer is basically just a chuck of memory that holds Vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT InitVB()
{
	//Initialize three Vertices for rendering a triangle
	//CUSTOMVERTEX Vertices[] =
	//{
	//    { 150.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
	//    { 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
	//    {  50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
	//};

	// Create the vertex buffer. Here we are allocating enough memory
	// (from the default pool) to hold all our 3 custom Vertices. We also
	// specify the FVF, so the vertex buffer knows what data it contains.

	if( FAILED( g_pd3dDevice->CreateVertexBuffer( GraphicsPoints.size()  * sizeof( CUSTOMVERTEX ),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
	{
		return E_FAIL;
	}

	// Now we fill the vertex buffer. To do this, we need to Lock() the VB to
	// gain access to the Vertices. This mechanism is required becuase vertex
	// buffers may be in device memory.
	VOID* pVertices;
	if( FAILED( g_pVB->Lock( 0, GraphicsPoints.size()* sizeof( CUSTOMVERTEX ), ( void** )&pVertices, 0 ) ) )
		return E_FAIL;
	memcpy( pVertices, Vertices, GraphicsPoints.size()* sizeof( CUSTOMVERTEX ) );
	int temp = sizeof( Vertices );
	g_pVB->Unlock();

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if( g_pVB != NULL )
		g_pVB->Release();

	if( g_pd3dDevice != NULL )
		g_pd3dDevice->Release();

	if( g_pD3D != NULL )
		g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------


VOID Render()
{
	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 25, 25, 112 ), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
	{
		// Draw the triangles in the vertex buffer. This is broken into a few
		// steps. We are passing the Vertices down a "stream", so first we need
		// to specify the source of that stream, which is our vertex buffer. Then
		// we need to let D3D know what vertex shader to use. Full, custom vertex
		// shaders are an advanced topic, but in most cases the vertex shader is
		// just the FVF, so that D3D knows what type of Vertices we are dealing
		// with. Finally, we call DrawPrimitive() which does the actual rendering
		// of our geometry (in this case, just one triangle).
		g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
		g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
		g_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST, 0, GraphicsPoints.size()  );

		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

void convertDoubleToWchar(double input, wchar_t* output)
{
	//memset(buff,0,sizeof(wchar_t)*256);
	char cbuff[256];
	_gcvt(input, 7, cbuff);
	MultiByteToWideChar(
		CP_UTF8,
		0,
		cbuff,
		256,
		output,
		256
		);
	//memset(buff,0,sizeof(wchar_t)*256);
}

void SetBasicPoint(HWND &hWnd, double a11,double a12,double a21,double a22,double xCoord,double yCoord )
{
	wchar_t buff[256];
	//char cbuff[256];
	//memset(buff,0,sizeof(wchar_t)*256);
	//sprintf(a11,buff,256);
	//sprintf( buff, "%e", a11 );
	//wcstof( const wchar_t* str, wchar_t** str_end )

	//FormatFloat
	//memset(buff,0,sizeof(wchar_t)*256);
	convertDoubleToWchar(a11, buff);
	SetDlgItemText(hWnd,IDC_A11, buff);
	//memset(buff,0,sizeof(wchar_t)*256);
	convertDoubleToWchar(a12, buff);
	SetDlgItemText(hWnd,IDC_A12,buff);
	convertDoubleToWchar(a21, buff);
	SetDlgItemText(hWnd,IDC_A21,buff);
	convertDoubleToWchar(a22, buff);
	SetDlgItemText(hWnd,IDC_A22,buff);
	convertDoubleToWchar(xCoord, buff);
	SetDlgItemText(hWnd,IDC_X,buff);
	convertDoubleToWchar(yCoord, buff);
	SetDlgItemText(hWnd,IDC_Y,buff);
}

void GetBasicPoint(const HWND &hWnd, BasicPoint &bpoint )
{
	wchar_t buff[256];
	double a11, a12, a21, a22, xCoord, yCoord;
	Extpair extpair;
	GetDlgItemText(hWnd,
		IDC_A11,
		buff,
		256);
	a11 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_A12,
		buff,
		256);
	a12 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_A21,
		buff,
		256);
	a21 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_A22,
		buff,
		256);
	a22 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_X,
		buff,
		256);
	xCoord = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_Y,
		buff,
		256);
	yCoord = _wtof(buff);

	extpair.xKoord = xCoord;
	extpair.yKoord = yCoord;
	bpoint.point = extpair;
	bpoint.transform.oo = a11;
	bpoint.transform.ot = a12;
	bpoint.transform.to = a21;
	bpoint.transform.tt = a22;			
}


void AddBasicPoint(const HWND &hWnd, Fractal &fractal )
{
	wchar_t buff[256];
	double a11, a12, a21, a22, xCoord, yCoord;
	Extpair extpair;
	GetDlgItemText(hWnd,
		IDC_A11,
		buff,
		256);
	a11 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_A12,
		buff,
		256);
	a12 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_A21,
		buff,
		256);
	a21 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_A22,
		buff,
		256);
	a22 = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_X,
		buff,
		256);
	xCoord = _wtof(buff);
	GetDlgItemText(hWnd,
		IDC_Y,
		buff,
		256);
	yCoord = _wtof(buff);

	extpair.xKoord = xCoord;
	extpair.yKoord = yCoord;
	fractal.addpoint(xCoord, yCoord, a11, a12, a21, a22);
	fractal.fracset.push_back(extpair);

}




BOOL CALLBACK ChildDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM) {
	double pos;
	static double  temp_pos = 100; 
	int randSize = 7;
	double temp;
	double a11, a12, a21, a22, xCoord, yCoord;
	BasicPoint bpoint;

	switch(uMsg) {
	case WM_ACTIVATE:
		TempChild = hWnd;
		break;
	case WM_VSCROLL:

		switch(LOWORD(wParam))
		{

			//При любом изменении положения движка, меняем громкость
		case TB_LINEUP:
		case TB_LINEDOWN:
		case TB_PAGEUP:
		case TB_PAGEDOWN:
		case TB_TOP:
		case TB_BOTTOM:
		case TB_THUMBPOSITION:

			pos= 100 - SendDlgItemMessage(hWnd, IDC_TENSION, TBM_GETPOS, 0,0);
			GetBasicPoint(hWnd , bpoint);
			SetBasicPoint(hWnd, bpoint.transform.oo*pos/temp_pos ,bpoint.transform.ot*pos/temp_pos, bpoint.transform.to*pos/temp_pos, bpoint.transform.tt*pos/temp_pos, bpoint.point.xKoord, bpoint.point.yKoord );
			temp_pos = pos;
			GetBasicPoint(hWnd , bpoint);
			convertDoubleToWchar(bpoint.transform.GetTension(), buff);
			SetDlgItemText(hWnd,IDC_TENSIONEDIT, buff);

			//SetDlgItemInt(hWnd, IDC_EDIT1, 100 - (int)pos*10,0);
			break;
		}


		break;
	case WM_COMMAND:

		switch(LOWORD(wParam)) {
	case IDC_CALIBRATE:
		GetBasicPoint(hWnd, bpoint);
		temp = sqrt(bpoint.transform.oo*bpoint.transform.oo + bpoint.transform.ot*bpoint.transform.ot + bpoint.transform.to*bpoint.transform.to + bpoint.transform.tt*bpoint.transform.tt );
		SetBasicPoint(hWnd, bpoint.transform.oo/temp, bpoint.transform.ot/temp, bpoint.transform.to/temp, bpoint.transform.tt/temp, bpoint.point.xKoord, bpoint.point.yKoord);
		GetBasicPoint(hWnd , bpoint);
		convertDoubleToWchar(bpoint.transform.GetTension(), buff);
		SetDlgItemText(hWnd,IDC_TENSIONEDIT, buff);
		//pos = bpoint.transform.oo/temp;
		//pos = 1;
		break;
	case IDC_RANDOM:
		GetBasicPoint(hWnd, bpoint);
		SetBasicPoint(hWnd, (rand() % randSize) - 2, (rand() % randSize) - 2, (rand() % randSize) - 2, (rand() % randSize) - 2, bpoint.point.xKoord, bpoint.point.yKoord);
		GetBasicPoint(hWnd , bpoint);
		convertDoubleToWchar(bpoint.transform.GetTension(), buff);
		SetDlgItemText(hWnd,IDC_TENSIONEDIT, buff);
		break;
	case IDOK:
	case IDCANCEL:
		EndDialog(hWnd, 0);
		basicPointsWindows.erase(hWnd);
		SendMessage(hMainDlg,DELETE_MSG,NULL,NULL);
		break;

		}
		break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		basicPointsWindows.erase(hWnd);
		SendMessage(hMainDlg,DELETE_MSG,NULL,NULL);
		break;
	}

	return false;
}


BOOL CALLBACK MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM) {
	InitCommonControls();
	int xSizeChild = 100;
	int ySizeChild = 100;
	int xSizeCounter = 0;
	int ySizeCounter = 0;
	static int counter = 0;
	std::set<HWND>::iterator at;
	double a11, a12, a21, a22;
	double xCoord, yCoord;
	BasicPoint bpoint;
	Extpair extpair;
	Matrix matrix;
	int iteration;
	switch(uMsg) {
		case WM_CREATE:
		SetDlgItemText(hWnd,IDC_ITERATIONNUMBER,L"1");
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
	case IDC_PRINTEPS:
		CheckDlgButton(
			hMainDlg,
			IDC_CHECKEPS,
			BST_UNCHECKED
			);
		f.writetoEps();
		CheckDlgButton(
			hMainDlg,
			IDC_CHECKEPS,
			BST_CHECKED
			);
		break;
	case IDC_ADD:
		basicPointsWindows.insert(TempChild = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHILDDLG), (HWND)hMainDlg, ChildDlgProc));
		SendDlgItemMessage(TempChild, IDC_TENSION, TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0,100));
		//SendDlgItemMessage(TempChild, IDC_TENSION, TBM_SETPOS, (WPARAM)1, (LPARAM)5);
		GetWindowRect( TempChild, lpMainDialogRectChild );
		xSizeChild = lpMainDialogRectChild->right - lpMainDialogRectChild->left;
		ySizeChild = lpMainDialogRectChild->bottom - lpMainDialogRectChild->top;


		/*xSizeCounter = (lpDesktopWindow->right - lpMainDialogRect->right) / xSizeChild;
		ySizeCounter = lpDesktopWindow->bottom / ySizeChild;*/
		xSizeCounter = (lpMainDialogRect->right - lpMainDialogRect->left) / xSizeChild + 1;
		ySizeCounter = (lpDesktopWindow->bottom - lpMainDialogRect->bottom) / ySizeChild ;

		SetWindowPos( 
			TempChild, 
			HWND_BOTTOM,
			xSizeChild * ((counter / ySizeCounter ) % xSizeCounter), 
			ySizeChild *(counter % ySizeCounter )+lpMainDialogRect->bottom -  lpMainDialogRect->top, 
			xSizeChild  , 
			ySizeChild  , 
			SWP_SHOWWINDOW
			); 

		size = basicPointsWindows.size();
		SetDlgItemText(hWnd,IDC_POINTSNUMBER,_itow(size,buff,256));

		//ShowWindow(TempChild,nCmdSh);
		++counter;

		SetDlgItemText(TempChild,IDC_A11,L"0.5");
		SetDlgItemText(TempChild,IDC_A12,L"0");
		SetDlgItemText(TempChild,IDC_A21,L"0");
		SetDlgItemText(TempChild,IDC_A22,L"0.5");
		SetDlgItemText(TempChild,IDC_X,L"100.0");
		SetDlgItemText(TempChild,IDC_Y,L"100.0");
		//DialogBox(hInst, MAKEINTRESOURCE(IDD_CHILDDLG), hMainDlg, ChildDlgProc);
		break;
	case IDOK:

		break;
	case IDC_DRAW:
		CheckDlgButton(
			hMainDlg,
			IDC_CHECKEPS,
			BST_UNCHECKED
			);


		iteration = GetDlgItemInt(hMainDlg, IDC_ITERATIONNUMBER, NULL, FALSE );
		f.fracsetW.clear();
		f.basicpoints.clear();
		//at = basicPointsWindows.begin();
		for(at = basicPointsWindows.begin(); at != basicPointsWindows.end(); at++)
		{
			AddBasicPoint( *at , f );
		}

		f.buildW(iteration);
		//buildFractalPolygone(f);
		wConvertFractalToPairVector(f, GraphicsPoints, Tensions);
		SetBufferPointsW();
		// Initialize Direct3D
		if( SUCCEEDED( InitD3D( hWndDirectX ) ) )
		{
			// Create the vertex buffer
			if( SUCCEEDED( InitVB() ) )
			{
				// Show the window
				Render();
				UpdateWindow( hWndDirectX );	
			}
		}
		CheckDlgButton(
			hMainDlg,
			IDC_CHECKEPS,
			BST_CHECKED
			);
		break;
	case IDC_BUILDING:
		/*SendMessage(GetDlgItem(hMainDlg,IDC_COMPLETE),BM_SETCHECK,1,0); 
		SendMessage(GetDlgItem(hMainDlg,IDC_BUILDING),BM_SETCHECK,0,0); */
		CheckRadioButton(
			hMainDlg,
			IDC_COMPLETE,
			IDC_BUILDING,
			IDC_BUILDING);

		iteration = GetDlgItemInt(hMainDlg, IDC_ITERATIONNUMBER, NULL, FALSE );
		f.fracset.clear();
		f.basicpoints.clear();
		//at = basicPointsWindows.begin();
		for(at = basicPointsWindows.begin(); at != basicPointsWindows.end(); at++)
		{
			AddBasicPoint( *at , f );
		}

		f.build(iteration);
		//buildFractalPolygone(f);
		convertFractalToPairVector(f, GraphicsPoints);
		SetBufferPoints();
		// Initialize Direct3D
		if( SUCCEEDED( InitD3D( hWndDirectX ) ) )
		{
			// Create the vertex buffer
			if( SUCCEEDED( InitVB() ) )
			{
				// Show the window
				Render();
				UpdateWindow( hWndDirectX );	
			}
		}
		//SendMessage(hWnd, WM_PAINT, NULL, NULL);
		CheckRadioButton(
			hMainDlg,
			IDC_COMPLETE,
			IDC_BUILDING,
			IDC_COMPLETE);
		break;
	case IDC_COMPLETE:
		CheckRadioButton(
			hMainDlg,
			IDC_COMPLETE,
			IDC_BUILDING,
			IDC_COMPLETE);
		/*CheckRadioButton(
		hMainDlg,
		IDC_COMPLETE,
		IDC_BUILDING,
		IDC_COMPLETE);*/
		break;

		}	// switch(LOWORD(wParam))
		break;
	case DELETE_MSG:
		size = basicPointsWindows.size();
		SetDlgItemText(hWnd,IDC_POINTSNUMBER,_itow(size,buff,256));
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	}

	return false;
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
HWND hConnectButton;
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	//HWND hw;
	switch( msg )
	{
	case WM_CREATE:
		hMainDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAINDLG), (HWND)hWnd, MainDlgProc);
		SetDlgItemText(hMainDlg,IDC_ITERATIONNUMBER,L"1");
		GetWindowRect( hMainDlg, lpMainDialogRect );
		SetWindowPos( 
			hMainDlg, 
			HWND_BOTTOM,
			0, 
			0, 
			lpMainDialogRect->right - lpMainDialogRect->left, 
			lpMainDialogRect->bottom - lpMainDialogRect->top  , 
			SWP_SHOWWINDOW
			); 
		ShowWindow(hMainDlg, nCmdSh);
		break;
		//hConnectButton=CreateWindow(L"BUTTON",L"Connect to ",WS_CHILD|WS_VISIBLE| BS_DEFPUSHBUTTON,0,0,90,20,hWnd,(HMENU)ID_BUTTON,hInst,NULL);
		//ShowWindow(hConnectButton, nCmdSh);
		/*	break;
		case WM_PAINT:

		break;*/
	case WM_LBUTTONDOWN:
		SetDlgItemInt(TempChild,IDC_X, LOWORD(lParam) , FALSE);
		SetDlgItemInt(TempChild,IDC_Y, HIWORD(lParam) , FALSE);
		break;
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

BOOL WINAPI MainDlgProc1( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	//HWND hw;
	switch( msg )
	{
		/*case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDC_BUTTON1:
		break;
		}
		break;*/
	case WM_CREATE:
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;

	}

	return false;
}



int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR     lpCmdLine,
				   int       nCmdShow)
{
	hInst = hInstance;
	nCmdSh = nCmdShow;
	HWND hMainDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAINDLG), (HWND)NULL, MainDlgProc1);
	GetWindowRect( hMainDlg, lpMainDialogRect );
	GetClientRect(GetDesktopWindow(), lpDesktopWindow);

	if(!hMainDlg) return false;
	//ShowWindow(hMainDlg,nCmdShow);

	//	std::pair<double, double> temp;
	//	for(int i = 0; i < 100; i++)
	//{ 
	//	temp.first = i;
	//	temp.second = i;
	//	GraphicsPoints.push_back(temp);
	//
	//}	

	buildFractalPolygone(f, 9, 0.4, 2 );

	convertFractalToPairVector(f, GraphicsPoints);
	SetBufferPoints();
	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
		L"D3D Tutorial", NULL
	};
	RegisterClassEx( &wc );

	// Create the application's window
	/*HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 02: Vertices",
	WS_OVERLAPPEDWINDOW, lpMainDialogRect->right, 0, lpDesktopWindow->right - lpMainDialogRect->right , lpDesktopWindow->bottom,
	NULL, NULL, wc.hInstance, NULL );*/

	hWndDirectX = CreateWindow( L"D3D Tutorial", L"Self-Affine Plite",
		WS_OVERLAPPEDWINDOW, lpMainDialogRect->right, 0, lpDesktopWindow->right - lpMainDialogRect->right , lpDesktopWindow->bottom,
		NULL, NULL, wc.hInstance, NULL );

	// Initialize Direct3D
	if( SUCCEEDED( InitD3D( hWndDirectX ) ) )
	{
		// Create the vertex buffer
		if( SUCCEEDED( InitVB() ) )
		{
			// Show the window
			ShowWindow( hWndDirectX, SW_SHOWDEFAULT );
			UpdateWindow( hWndDirectX );

			// Enter the message loop
			MSG msg;
			ZeroMemory( &msg, sizeof( msg ) );
			while( msg.message != WM_QUIT )
			{
				if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
				{
					//UpdateWindow( hWndDirectX );
					TranslateMessage( &msg );
					DispatchMessage( &msg );
				}
				else
					Render();
			}
		}
	}


	//return 0;
	//	MSG msg;
	//	while (GetMessage(&msg, NULL, NULL, NULL)) {
	//		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	//			{
	//		if (!IsWindow(hMainDlg) || !IsDialogMessage(hMainDlg, &msg)) {
	//			TranslateMessage(&msg);
	//			DispatchMessage(&msg);
	//		}	// if (!IsWindow(hMainDlg) || !IsDialogMessage(hMainDlg, &msg))
	//		}
	//		else
	//		{Render();}
	//	}	// while (GetMessage(&msg, NULL, NULL, NULL))

	deleteBufferPoints();
	UnregisterClass( L"D3D Tutorial", wc.hInstance );

	return true;
}

