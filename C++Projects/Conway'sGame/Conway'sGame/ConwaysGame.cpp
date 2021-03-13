// Conway'sGame.cpp : Defines the entry point for the application.

#include "stdafx.h"
#include "resource.h"
#include "Game.h"
#include "MyInput.h"
#include "MyLog.h"

#define MAX_LOADSTRING 100
#define IDT_TIMER_UPDATE 1

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Game g_game;									// global game instance

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Timer function signature
// In InitInstance we called SetTimer
// Implemented the function
void				TimerCallback(HWND, UINT, UINT_PTR, DWORD);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	LoadStringW(hInstance, IDC_CONWAYSGAME, szWindowClass, MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;	
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONWAYSGAME));

	MSG msg;

	// Init logger
	MyLog::get_instance().Init();

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CONWAYSGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CONWAYSGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	RECT windowRect {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};

	AdjustWindowRect(&windowRect, WS_POPUPWINDOW | WS_CAPTION, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		1100, 100, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WORD xLocation = LOWORD(lParam);

	WORD yLocation = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		// For dragging
		if (DragDetect(hWnd, { xLocation, yLocation }))
		{
			MyInput::get_instance().set_is_drag(true);
		}
		// For clicking
		MyInput::get_instance().set_is_click(true);

		InvalidateRgn(hWnd, nullptr, TRUE);
	}
	break;

	case WM_LBUTTONUP:
	{
		//up the Lbutton can end dragging.
		MyInput::get_instance().set_is_drag(false);

		MyInput::get_instance().set_is_click(false);

		InvalidateRgn(hWnd, nullptr, TRUE);
	}
	break;

	case WM_MOUSEHOVER: 
		break;

	case WM_MOUSEMOVE:
	{
		MyInput::get_instance().set_mouse_pos({ (float)xLocation, (float)yLocation });
	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 0x53:
			MyLog::get_instance().LogToConsole("S Pressed");

			g_game.SimulationForward();

			break;

		case 0x20:
			MyLog::get_instance().LogToConsole("SpaceBar Pressed");

			if (g_game.get_is_simulating())
			{
				g_game.set_is_simulating(false);

				KillTimer(hWnd, IDT_TIMER_UPDATE);
			}
			else
			{
				g_game.set_is_simulating(true);

				SetTimer(hWnd, IDT_TIMER_UPDATE, g_game.get_simulation_time(), (TIMERPROC)(&TimerCallback));
			}
			
			break;
		
		case 0x1B:
			// escape key: reset
			MyLog::get_instance().LogToConsole("Escape Pressed");

			g_game.Reset();

			KillTimer(hWnd, IDT_TIMER_UPDATE);

			break;
		
		case 0x41:
			// accelerate simulation 
			MyLog::get_instance().LogToConsole("A Pressed");

			if (g_game.get_is_simulating())
			{
				g_game.AccelerateSimulation();

				SetTimer(hWnd, IDT_TIMER_UPDATE, g_game.get_simulation_time(), (TIMERPROC)(&TimerCallback));
			}

			break;

		case 0x44:
			// decelerate simulation
			g_game.DecelerateSimulation();

			SetTimer(hWnd, IDT_TIMER_UPDATE, g_game.get_simulation_time(), (TIMERPROC)(&TimerCallback));

			MyLog::get_instance().LogToConsole("D Pressed");

			break;

		case 0x50:
			MyLog::get_instance().LogToConsole("P Pressed");

			g_game.set_is_drawing_grids(!g_game.get_is_drawing_grids());
		default:
			break;
		}

		InvalidateRgn(hWnd, nullptr, TRUE);
	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		
		case IDM_ABOUT:
		
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			
			break;
		
		case IDM_EXIT:
		
			DestroyWindow(hWnd);
			
			break;
		
		default:
		
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		g_game.Draw(hdc);

		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:

		PostQuitMessage(0);

		break;

	default:

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	g_game.Update();

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void TimerCallback(HWND hWnd, UINT no, UINT_PTR idea, DWORD what)
{
	g_game.SimulationForward();

	InvalidateRgn(hWnd, nullptr, TRUE);
}
