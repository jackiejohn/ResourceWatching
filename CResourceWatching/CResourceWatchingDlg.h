
// CResourceWatchingDlg.h : ͷ�ļ�
//

#pragma once


// CCResourceWatchingDlg �Ի���
class CCResourceWatchingDlg : public CDialogEx
{
// ����
public:
	CCResourceWatchingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CRESOURCEWATCHING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT NotifyIconMessage(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
