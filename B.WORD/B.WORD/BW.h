#pragma once
#define OnMenuClicked1   1
#define OnMenuClicked2   2
#define OnMenuClicked3   3
#define OnMenuClicked4   4
#define OnMenuClicked5   5
#define OnButtonClicked1 31
#define OnFileSave       6
#define OnFileLoad       7
#define OnFileSaveAs     8
#define TextBufferSize   256
//===================================================================================================================================================
char Buffer[TextBufferSize];
static int sx, sy;
HWND hEditControl;


char filename[256];
OPENFILENAMEA ofn;
LRESULT CALLBACK BWordProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
void SetOpenFileParams(HWND hWnd);
//===================================================================================================================================================
