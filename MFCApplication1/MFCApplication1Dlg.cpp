
// MFCApplication1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include "kvaser/canlib.h"
#include "ControlCAN.h"
#include "afxwin.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT32 CAN_ID;
VCI_CAN_OBJ test_data;
//int i;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO1, m_ComboBox_Baudrate);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplication1Dlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication1Dlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始化代码
	//m_ComboBox_Baudrate.InsertString(0, _T("1000K"));
	m_ComboBox_Baudrate.InsertString(0, _T("500K"));
	m_ComboBox_Baudrate.InsertString(1, _T("250K"));
	m_ComboBox_Baudrate.InsertString(2, _T("125K"));
	m_ComboBox_Baudrate.InsertString(3, _T("100K"));//这个顺序别动
	m_ComboBox_Baudrate.SetCurSel(0);//选取列表框中的一个选项

	//List_control初始化
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小
	m_list1.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_list1.SetExtendedStyle(m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 为列表视图控件添加四列   
	m_list1.InsertColumn(0, _T("时间"), LVCFMT_CENTER, (rect.Width() / 6), 0);
	m_list1.InsertColumn(1, _T("方向"), LVCFMT_CENTER, (rect.Width() / 6), 1);
	m_list1.InsertColumn(2, _T("ID"), LVCFMT_CENTER, (rect.Width() / 6), 2);
	m_list1.InsertColumn(3, _T("DATA"), LVCFMT_CENTER, (rect.Width()  / 2), 3);
	
	//i = rect.Width();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}
//以下为新增
// @ Kvaser 设备打开 **********************************************
void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_ComboBox_Baudrate.GetCurSel()返回值为列表框的索引
	//int i;
	//canBITRATE_500K为-2;
	int Bitrate = canBITRATE_500K - m_ComboBox_Baudrate.GetCurSel();
	//int i = m_ComboBox_Baudrate.GetCurSel();
	//int j = canBITRATE_100K;
	//int k = BAUD_100K;
	canInitializeLibrary();//初始化库文件

	kvaser_hnd = canOpenChannel(0, canOPEN_REQUIRE_EXTENDED);//打开通道
	if (kvaser_hnd < 0) {
		MessageBox(_T("Kvaser open fail."));
		return;
	}
	
	kvaser_stat = canSetBusParams(kvaser_hnd, Bitrate, 0, 0, 0, 0, 0);
	if (kvaser_stat != canOK) {
		MessageBox(_T("Kvaser set bitrate fail."));
		return;
	}

	kvaser_stat = canBusOn(kvaser_hnd);
    if (kvaser_stat != canOK) {
		MessageBox(_T("Kvaser bus on fail."));
		return;
	}

	(*GetDlgItem(IDC_BUTTON1)).EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);

	MessageBox(_T("Kvaser open success."));
}

// @ Kvaser 设备关闭 **********************************************
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	kvaser_stat = canBusOff(kvaser_hnd);
	if (kvaser_stat != canOK) {
		MessageBox(_T("Kvaser bus off fail."));
		return;
	}
	kvaser_stat = canClose(kvaser_hnd);
	if (kvaser_stat != canOK) {
		MessageBox(_T("Kvaser close fail."));
		return;
	}

	(*GetDlgItem(IDC_BUTTON1)).EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);

	MessageBox(_T("Kvaser close success."));
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CAN_ID = 0x001;
	
	test_data.Data[0] = 0x01;
	test_data.Data[1] = 0x00;
	test_data.Data[2] = 0x00;
	test_data.Data[3] = 0x00;
	test_data.Data[4] = 0x00;
	test_data.Data[5] = 0x00;
	test_data.Data[6] = 0x00;
	test_data.Data[7] = 0x00;

	canWrite(kvaser_hnd, CAN_ID, test_data.Data, 8, 0);
	dislay();
}


void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	CAN_ID = 0x001;

	test_data.Data[0] = 0x00;
	test_data.Data[1] = 0x00;
	test_data.Data[2] = 0x00;
	test_data.Data[3] = 0x00;
	test_data.Data[4] = 0x00;
	test_data.Data[5] = 0x00;
	test_data.Data[6] = 0x00;
	test_data.Data[7] = 0x00;

	canWrite(kvaser_hnd, CAN_ID, test_data.Data, 8, 0);
	dislay();
}


void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	CAN_ID = 0x002;
	
	test_data.Data[0] = 0x01;
	test_data.Data[1] = 0x00;
	test_data.Data[2] = 0x00;
	test_data.Data[3] = 0x00;
	test_data.Data[4] = 0x00;
	test_data.Data[5] = 0x00;
	test_data.Data[6] = 0x00;
	test_data.Data[7] = 0x00;

	canWrite(kvaser_hnd, CAN_ID, test_data.Data, 8, 0);
	dislay();
}


void CMFCApplication1Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	CAN_ID = 0x002;
	
	test_data.Data[0] = 0x00;
	test_data.Data[1] = 0x00;
	test_data.Data[2] = 0x00;
	test_data.Data[3] = 0x00;
	test_data.Data[4] = 0x00;
	test_data.Data[5] = 0x00;
	test_data.Data[6] = 0x00;
	test_data.Data[7] = 0x00;

	canWrite(kvaser_hnd, CAN_ID, test_data.Data, 8, 0);
	dislay();
}

void CMFCApplication1Dlg::dislay()
{
	SYSTEMTIME st;
	CString strTime;
	CString tx_data;

	int i;

	//显示当前时间
	GetLocalTime(&st);
	strTime.Format(_T("%02d:%02d:%02d:%03d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	m_list1.InsertItem(m_list1_num, strTime);

	//显示当前方向
	m_list1.SetItemText(m_list1_num, 1, _T("发送->"));

	//显示当前ID
	//m_list1.SetItemText(0, 2, _T("0x001"));
	tx_data.Format(_T("0x%03d"), CAN_ID);
	m_list1.SetItemText(m_list1_num, 2, tx_data);//转化为CString类型

	//显示当前DATA
	//m_list1.SetItemText(0,3,_T("0x01 0x00 0x00 0x00 0x00 0x00 0x00 0x00 "));
	tx_data.Format(_T("%02d %02d %02d %02d %02d %02d %02d %02d"), test_data.Data[0]\
		, test_data.Data[1], test_data.Data[2], test_data.Data[3], test_data.Data[4]\
		, test_data.Data[5], test_data.Data[6], test_data.Data[7]);
	m_list1.SetItemText(m_list1_num, 3, tx_data);

	m_list1_num++;

	i = m_list1.GetItemCount();
	if (i > 20)
	{
		m_list1.DeleteAllItems();//清除行
		m_list1_num = 0;
	}
}

void CMFCApplication1Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
