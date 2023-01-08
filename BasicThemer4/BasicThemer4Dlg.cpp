
// BasicThemer4Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BasicThemer4.h"
#include "BasicThemer4Dlg.h"
#include "afxdialogex.h"
#define	WM_USER_SHELLICON WM_USER + 1
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWMNCRENDERINGPOLICY policy = DWMNCRP_DISABLED;
NOTIFYICONDATA nidApp;
static UINT s_uTaskbarRestart;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	virtual BOOL OnInitDialog();
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
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	DwmSetWindowAttribute(GetSafeHwnd(), DWMWA_NCRENDERING_POLICY, &policy, sizeof policy);
	return TRUE;
}

// CBasicThemer4Dlg dialog



CBasicThemer4Dlg::CBasicThemer4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASICTHEMER4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBasicThemer4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBasicThemer4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

VOID CALLBACK WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	if (dwEvent == EVENT_OBJECT_CREATE)
	{
		if (IsWindow(hwnd))
		{
			DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof policy);
			//SetWindowTheme(hwnd, L"", L"");
		}
	}
}
BOOL CALLBACK hwndcallback(HWND hwnd, LPARAM lParam)
{
	if (IsWindow(hwnd))
	{
		DwmSetWindowAttribute(hwnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof policy);
	}
	return TRUE;
}
// CBasicThemer4Dlg message handlers
BOOL CBasicThemer4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	HICON hMainIcon = LoadIcon(AfxGetInstanceHandle(), (LPCTSTR)MAKEINTRESOURCE(IDR_MAINFRAME));
	nidApp.cbSize = sizeof(NOTIFYICONDATA);
	nidApp.hWnd = AfxGetMainWnd()->m_hWnd;
	nidApp.uID = IDR_MAINFRAME;
	nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nidApp.hIcon = hMainIcon;
	nidApp.uCallbackMessage = WM_USER + 1;
	nidApp.uVersion = NOTIFYICON_VERSION_4;
	LoadString(AfxGetInstanceHandle(), IDS_NAME, nidApp.szTip, 100);
	Shell_NotifyIcon(NIM_ADD, &nidApp);

	DwmSetWindowAttribute(AfxGetMainWnd()->m_hWnd, DWMWA_NCRENDERING_POLICY, &policy, sizeof policy);

	hEvent = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE, NULL,
		WinEventProcCallback, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNTHREAD);
	//s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"))
	EnumWindows(hwndcallback, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBasicThemer4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBasicThemer4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBasicThemer4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBasicThemer4Dlg::OnClose()
{
	Shell_NotifyIcon(NIM_DELETE, &nidApp);
	EndDialog(0);
}
