#include "stdafx.h"
#include <time.h>
#include "GameStateMachine.h"
#include "FrameTimer.h"
#include "GameSettings.h"
#include "resource.h"
#include "Input.h"

#define MAX_LOADSTRING 100

// Global Variables:
GameStateMachine gameStateMachine;

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Srand
	srand((unsigned int)time(NULL));

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_BOMBDODGER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BOMBDODGER));

	MSG msg = { 0 };
	

	// Main message loop:
	while (gameStateMachine.get_is_playing())
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		gameStateMachine.Update();
		gameStateMachine.Draw();
	}

	PostQuitMessage(0);

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BOMBDODGER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_BOMBDODGER);
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
	auto dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle,
		400, 200, 806, 650, nullptr, nullptr, hInstance, nullptr);

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
	switch (message)
	{
	case WM_CREATE:
	{
		gameStateMachine.Init(hWnd, hInst);
	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 0x41: // A key down
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingLeft, Input::EInputState::kPress);
			break;

		case 0x44: // D key down
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingRight, Input::EInputState::kPress);
			break;

		case 0x53: // S key down
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingDown, Input::EInputState::kPress);
			break;

		case 0x57: // W key down
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingUp, Input::EInputState::kPress);
			break;

		case VK_RIGHT:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackRight, Input::EInputState::kPress);
			break;

		case VK_DOWN:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackDown, Input::EInputState::kPress);
			break;

		case VK_UP:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackUp, Input::EInputState::kPress);
			break;

		case VK_LEFT:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackLeft, Input::EInputState::kPress);
			break;

		case VK_ESCAPE:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kQuit, Input::EInputState::kPress);
			break;
		
		case VK_SPACE:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kSkip, Input::EInputState::kPress);
			break;
		}
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 0x41: // A key up
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingLeft, Input::EInputState::kJustRelease);
			break;

		case 0x44: // D key up
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingRight, Input::EInputState::kJustRelease);
			break;

		case 0x53: // S key up
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingDown, Input::EInputState::kJustRelease);
			break;

		case 0x57: // W key up
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kIsMovingUp, Input::EInputState::kJustRelease);
			break;

		case VK_RIGHT:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackRight, Input::EInputState::kJustRelease);
			break;

		case VK_DOWN:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackDown, Input::EInputState::kJustRelease);
			break;

		case VK_UP:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackUp, Input::EInputState::kJustRelease);
			break;

		case VK_LEFT:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kAttackLeft, Input::EInputState::kJustRelease);
			break;

		case VK_SPACE:
			gameStateMachine.get_input()->SetInputValue(Input::EInputValue::kSkip, Input::EInputState::kJustRelease);
			break;
		}
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
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		gameStateMachine.set_is_playing(false);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
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

