
// MFCApplication1Dlg.h: 头文件
//

#pragma once

#include "kvaser/canlib.h"
#include "kvaser/canstat.h"

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
//以下为新增
	CComboBox m_ComboBox_Baudrate;
	afx_msg void OnBnClickedButton1();
	canHandle kvaser_hnd;
	canStatus kvaser_stat;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	UINT8 Button3_lock;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	CListCtrl m_list1;
	UINT16 m_list1_num;
	void dislay();
};
