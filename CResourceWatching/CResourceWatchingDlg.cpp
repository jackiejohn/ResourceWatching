
// CResourceWatchingDlg.cpp : ʵ���ļ�
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


// CCResourceWatchingDlg �Ի���


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


// CCResourceWatchingDlg ��Ϣ�������

BOOL CCResourceWatchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	initialize(CWnd::m_hWnd, m_hIcon);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCResourceWatchingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}



//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCResourceWatchingDlg::OnQueryDragIcon()
{
	
	return static_cast<HCURSOR>(m_hIcon);
}


//����ͼ����Ϣ������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	WillClose();
	CDialogEx::OnClose();
}
