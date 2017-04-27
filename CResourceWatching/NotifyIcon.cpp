#include "stdafx.h"
#include "Shellapi.h"
#include "Strsafe.h"
#include "Resource.h"

bool isInTaskBar=false;
char buf[256] = "";

void ShowContextMenu(HWND hwnd, POINT pt)
{
	HMENU hMenu = LoadMenu(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDR_MENU1));
	if (hMenu)
	{
		HMENU hSubMenu = GetSubMenu(hMenu, 0);
		if (hSubMenu)
		{
			// our window must be foreground before calling TrackPopupMenu or the menu will not disappear when the user clicks away
			SetForegroundWindow(hwnd);

			// respect menu drop alignment
			UINT uFlags = TPM_RIGHTBUTTON;
			if (GetSystemMetrics(SM_MENUDROPALIGNMENT) != 0)
			{
				uFlags |= TPM_RIGHTALIGN;
			}
			else
			{
				uFlags |= TPM_LEFTALIGN;
			}

			TrackPopupMenuEx(hSubMenu, uFlags, pt.x, pt.y, hwnd, NULL);
		}
		DestroyMenu(hMenu);
	}
}

BOOL notifyicon_add(HWND hwnd,HICON icon)
{
	NOTIFYICONDATA nid = { sizeof(nid) };
	nid.hWnd = hwnd;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;
	nid.guidItem = { 0x0cf4e800, 0xcc8e, 0x4b32, { 0x95, 0x75, 0xac, 0x96, 0x7a, 0xff, 0xaf, 0x4e } };
	nid.uCallbackMessage = WM_NOTIFYICONMESSAGE;
	LoadIconMetric(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_NOTIFYICON), LIM_SMALL, &nid.hIcon);
	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"resource watching");
	Shell_NotifyIcon(NIM_ADD, &nid);

	nid.uVersion = NOTIFYICON_VERSION_4;//need the message
	return Shell_NotifyIcon(NIM_SETVERSION, &nid);
}


