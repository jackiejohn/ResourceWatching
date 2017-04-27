#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <Pdh.h>
#include "NotifyIcon.h"
#include "Shobjidl.h"
#pragma comment(lib,"Pdh.lib")
#pragma warning(disable:4996)
bool isclosed = false;
HWND myhwnd = 0;
int DisplayMode = 0;//0为窗口显示 1为任务栏显示
typedef struct setting{
	int attribute;
	int left;
	int top;
};

void MemoryWatching()
{		

	MEMORYSTATUSEX mStatus = {0};
	mStatus.dwLength = sizeof(mStatus);
	GlobalMemoryStatusEx(&mStatus);
	float TotalMemory = mStatus.ullTotalPhys/1024/1024;//bits/1024/1024=MB
	PDH_STATUS Status;
	HQUERY Query = NULL;
	HCOUNTER Counter;
	PDH_FMT_COUNTERVALUE DisplayValue = {0};
	Status = PdhOpenQuery(NULL, NULL, &Query);
	WCHAR *Location = TEXT("\\Memory\\Available MBytes");
	Status = PdhAddCounter(Query, Location, 0, &Counter);
	//Status = PdhCollectQueryData(Query);
	//Status = PdhCollectQueryData(Query);		
	//Status = PdhGetFormattedCounterValue(Counter, PDH_FMT_DOUBLE, 0, &DisplayValue);
	
	float CurrentLeft = 0;
	float percent_c = 0;
	int percent = 0;
	char buf[] = "";
	while (isclosed == false)
	{		
		PdhCollectQueryData(Query);
		PdhGetFormattedCounterValue(Counter, PDH_FMT_DOUBLE, 0, &DisplayValue);
		CurrentLeft = DisplayValue.doubleValue;
		percent_c = (TotalMemory - CurrentLeft)/TotalMemory*100;
		percent = percent_c;
		sprintf(buf, "当前已用内存：%i %% ", percent);
		SetWindowTextA(myhwnd, buf);
		Sleep(2000);
	}
	return;
}

void UploadWatching()
{	
	PDH_STATUS Status;
	HQUERY Query = NULL;
	HCOUNTER Counter;
	PDH_FMT_COUNTERVALUE DisplayValue = { 0 };
	Status = PdhOpenQuery(NULL, NULL, &Query);
	WCHAR *Location = TEXT("\\Network Interface(Realtek PCIe FE Family Controller)\\Bytes Sent/sec");
	Status = PdhAddCounter(Query, Location, 0, &Counter);
	char buf[] = "";
	float up_Byte=0;
	while (isclosed == false)
	{
		PdhCollectQueryData(Query);
		PdhGetFormattedCounterValue(Counter, PDH_FMT_DOUBLE, 0, &DisplayValue);
		up_Byte = DisplayValue.doubleValue/1024;
		if (up_Byte >= 1024)
		{
			up_Byte = up_Byte / 1024;
			sprintf(buf, "Upload: %.2f %MB/s", up_Byte);
		}
		else sprintf(buf, "Upload: %.2f %kB/s", up_Byte);
		//SetWindowTextA(myhwnd, buf);
		SetDlgItemTextA(myhwnd, 1000,buf);
		Sleep(1000);
	}
	return;
}

void DownloadWatching()
{
	PDH_STATUS Status;
	HQUERY Query = NULL;
	HCOUNTER Counter;
	PDH_FMT_COUNTERVALUE DisplayValue = { 0 };
	Status = PdhOpenQuery(NULL, NULL, &Query);
	WCHAR *Location = TEXT("\\Network Interface(Realtek PCIe FE Family Controller)\\Bytes Received/sec");
	Status = PdhAddCounter(Query, Location, 0, &Counter);
	char buf[] = "";
	float Down_kByte = 0;
	while (isclosed == false)
	{
		PdhCollectQueryData(Query);
		PdhGetFormattedCounterValue(Counter, PDH_FMT_DOUBLE, 0, &DisplayValue);
		Down_kByte = DisplayValue.doubleValue / 1024;
		if (Down_kByte >= 1024)
		{
			Down_kByte = Down_kByte / 1024;
			sprintf(buf, "Download: %.2f %MB/s", Down_kByte);
		}
		else sprintf(buf, "Download: %.2f %kB/s", Down_kByte);
		//SetWindowTextA(myhwnd, buf);
		SetDlgItemTextA(myhwnd, 1001, buf);
		SetWindowPos(myhwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		Sleep(1000);
	}
	return;
}


void initialize(HWND hwnd,HICON icon)
{
	
	myhwnd = hwnd;
	BOOL iscreate=notifyicon_add(myhwnd,icon);
	if (DisplayMode == 0)
	{
		//设置位置和坐标
		RECT myrect = { 0 };
		GetClientRect(myhwnd, &myrect);

		SetWindowPos(myhwnd,
			HWND_TOPMOST,
			GetSystemMetrics(SM_CXFULLSCREEN) - (myrect.right - myrect.left) - 10,
			GetSystemMetrics(SM_CYFULLSCREEN) - (myrect.bottom - myrect.top) - 10,
			0, 0, SWP_NOSIZE);
		SetLayeredWindowAttributes(myhwnd, NULL, (255 * 70) / 100, LWA_ALPHA);//窗口属性必须是分层的(layered)
	}
	else if (DisplayMode == 1)
	{
		
	}
	
	HANDLE memorycheck = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MemoryWatching, 0, 0, 0);
	HANDLE uploadcheck = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UploadWatching, 0, 0, 0);
	HANDLE downloadcheck = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DownloadWatching, 0, 0, 0);
	
}

void WillClose()
{
	isclosed = true;
}