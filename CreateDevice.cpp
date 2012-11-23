//-----------------------------------------------------------------------------
// File: CreateDevice.cpp
//
// Desc: This is the first tutorial for using Direct3D. In this tutorial, all
//       we are doing is creating a Direct3D device and using it to clear the
//       window.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device

// Global Variables:
HINSTANCE hInst;								// current instance
LRESULT CALLBACK	DlgProc(HWND, UINT, WPARAM, LPARAM);




//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
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
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
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
	
    if( NULL == g_pd3dDevice )
        return;

    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 255, 255, 255), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Rendering of scene objects can happen here
struct MYVERTEX
{
    FLOAT x, y, z, rhw;
	DWORD color;
}data[100];

#define MY_FVF (D3DFVF_XYZRHW|D3DFVF_DIFFUSE);

// заполнение массива data "случайными" точками Е
for(int i=0;i<100;i++)
{data[i].x = i;
data[i].y = i;
data[i].z = 0;
data[i].rhw = 0;
data[i].color = D3DCOLOR_XRGB(0,255,0);
}

// процедура вывода сцены
g_pd3dDevice->SetFVF MY_FVF;
LPDIRECT3DVERTEXBUFFER9     VBuffer     = NULL;
VOID* pBuff;
g_pd3dDevice->CreateVertexBuffer(sizeof(MYVERTEX)*100, 0, D3DFVF_XYZRHW|D3DFVF_DIFFUSE , D3DPOOL_DEFAULT, &VBuffer, NULL );
VBuffer->Lock( 0, sizeof(MYVERTEX)*100, (void**)&pBuff, 0 );
memcpy( pBuff, data, sizeof(MYVERTEX)*100 );
VBuffer-> Unlock();

g_pd3dDevice->SetStreamSource( 0, VBuffer, 0, sizeof(MYVERTEX) );
g_pd3dDevice->SetFVF MY_FVF ;
g_pd3dDevice->DrawPrimitive( D3DPT_POINTLIST , 0, 100 );
//g_pd3dDevice->DrawPrimitiveUP( D3DPT_POINTLIST, 100, data, 
 //sizeof(MYVERTEX) );
        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
            Render();
            ValidateRect( hWnd, NULL );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Tutorial", L"D3D Tutorial 01: CreateDevice",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Enter the message loop
        MSG msg;
        while( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );

	DialogBox((hInst = hInstance), (LPCTSTR)IDD_DIALOG, NULL, (DLGPROC)DlgProc);
    return 0;


}

LRESULT CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = FALSE;
	BOOL bCmd = FALSE;
	char sText[256];
	switch (message) 
	{
		case WM_INITDIALOG:
			bRet = TRUE;
			break;
		case WM_COMMAND:
			bRet = TRUE;
			bCmd = TRUE;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			EndDialog(hWnd, TRUE); 
			break;
	}
	if(bCmd)
	switch(LOWORD(wParam))
	{
		case IDOK:
			if(GetDlgItemText(hWnd,IDC_EDIT1,sText,255))
			   SetDlgItemText(hWnd,IDC_EDIT2,sText);
			break;
		case IDM_EXIT:
		case IDCANCEL: 
			SendMessage(hWnd,WM_DESTROY,0,0);
			break;
	}
	return bRet;
}




