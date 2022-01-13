#include <windows.h>
#include "BW.h" 
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) 
{
	WNDCLASS BWordClass = NewWindowClass
	(
		(HBRUSH)COLOR_HIGHLIGHTTEXT,
		LoadCursor(NULL, IDC_ARROW),
		hInst,
		LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)),
		L"BWordClass",
		BWordProcedure
	);
	if (!RegisterClassW(&BWordClass)) { return -1; } 
	MSG BWordMessage = { 0 };
	CreateWindow
	(
		L"BWordClass", 
		L"B.WORD",
		WS_MAXIMIZE | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		0,
		0,
		1366,
		768,
		NULL,
		NULL,
		NULL,
		NULL
	);
	while (GetMessage(&BWordMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&BWordMessage);
		DispatchMessage(&BWordMessage);
	}
	return 0;
}
WNDCLASS NewWindowClass
(
	HBRUSH BGColor,
	HCURSOR Cursor,
	HINSTANCE hInst,
	HICON Icon,
	LPCWSTR Name,
	WNDPROC Procedure
)
{
	WNDCLASS NWC = { 0 };
	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;
	return NWC;
}
LRESULT CALLBACK BWordProcedure
(
	HWND hWnd,
	UINT msg,
	WPARAM wp,
	LPARAM lp
)
{
	switch (msg) {
	case WM_SIZE:
		sx = LOWORD(lp);
		sy = HIWORD(lp);
		break;
	case WM_COMMAND:
		switch (wp)
		{
		case OnMenuClicked1:
			MessageBoxA(hWnd, "ПРОГРАММА:\n'B.WORD'\n\nРАЗРАБОТЧИК: \nСтудент группы: ЭИСБ-24\nБолонин Михаил Александрович\n\n\nВерсия: 1.0.301121", "О программе B.Word", MB_OK);
			break;
		case OnMenuClicked2:
			PostQuitMessage(0);
			break;
		case OnButtonClicked1:
			PostQuitMessage(0);
			break;
		case OnFileSave:
			//if (GetSaveFileNameA(&ofn)) { SaveData(filename); }
			//SaveData("C:/Users/bolon/OneDrive/Рабочий стол/BOLOBOL.txt");
			SaveData(filename);
			break;
		case OnFileLoad:
			if (GetOpenFileNameA(&ofn)) { LoadData(filename); }
			//LoadData("C:/Users/bolon/OneDrive/Рабочий стол/BOLOBOL.txt");
			break;
		case OnFileSaveAs:
			if (GetSaveFileNameA(&ofn)) { SaveData(filename); }
			//GetSaveFileNameA(&ofn);
			break;
		default:break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParams(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd,msg,wp,lp);
	}
}
void MainWndAddMenus(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU SubMenu1 = CreateMenu();
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"B.Word");
	AppendMenu(SubMenu, MF_STRING, OnMenuClicked1, L"О программе B.Word");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnMenuClicked2, L"Bыход");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu1, L"Фаил");
	AppendMenu(SubMenu1, MF_STRING, OnFileLoad, L"Открыть");
	AppendMenu(SubMenu1, MF_STRING, OnFileSave, L"Сохранить");
	AppendMenu(SubMenu1, MF_STRING, OnFileSaveAs, L"Сохранить как");
	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("static", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 70, 4000, 2000, hWnd, NULL, NULL, NULL);
	hEditControl = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL, sx/2-(800/2), 100, 800, 580, hWnd, NULL, NULL, NULL);
	//CreateWindowA("button", "ВЫХОД", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 100, 63, hWnd, (HMENU)OnButtonClicked1, NULL, NULL);
}

void SaveData(LPCSTR path)
{
	HANDLE FileToSave = CreateFileA
	(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	int SaveSize = GetWindowTextLength(hEditControl) + 1;
	char* data = new char[SaveSize];
	SaveSize = GetWindowTextA(hEditControl, data, SaveSize);
	DWORD bytesIterated;
	WriteFile(FileToSave, data, SaveSize, &bytesIterated, NULL);
	CloseHandle(FileToSave);
	delete[]data;
}
void LoadData(LPCSTR path)
{
	HANDLE FileToLoad = CreateFileA
	(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);
	SetWindowTextA(hEditControl, Buffer);
	CloseHandle(FileToLoad);
}

void SetOpenFileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = "*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}