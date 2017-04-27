
// CResourceWatchingDlg.h : 头文件
//

#pragma once


// CCResourceWatchingDlg 对话框
class CCResourceWatchingDlg : public CDialogEx
{
// 构造
public:
	CCResourceWatchingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CRESOURCEWATCHING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT NotifyIconMessage(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
