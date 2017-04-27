
// CResourceWatchingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CResourceWatching.h"
#include "CResourceWatchingDlg.h"
#include "afxdialogex.h"
#include "ResourceWatching.h"
#include "NotifyIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCResourceWatchingDlg 对话框


CCResourceWatchingDlg::CCResourceWatchingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCResourceWatchingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CCResourceWatchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCResourceWatchingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_NOTIFYICONMESSAGE, NotifyIconMessage)
END_MESSAGE_MAP()


// CCResourceWatchingDlg 消息处理程序

BOOL CCResourceWatchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	initialize(CWnd::m_hWnd, m_hIcon);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCResourceWatchingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCResourceWatchingDlg::OnQueryDragIcon()
{
	
	return static_cast<HCURSOR>(m_hIcon);
}


//托盘图标消息处理函数
LRESULT CCResourceWatchingDlg::NotifyIconMessage(WPARAM w, LPARAM l)
{

	if (l==WM_CONTEXTMENU )
	{
		POINT const pt = { LOWORD(w), HIWORD(w) };
		ShowContextMenu(CWnd::m_hWnd, pt);
	}

	return 0;
}


void CCResourceWatchingDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	WillClose();
	CDialogEx::OnClose();
}
