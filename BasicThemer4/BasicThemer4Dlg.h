
// BasicThemer4Dlg.h : header file
//

#pragma once

extern NOTIFYICONDATA nidApp;

// CBasicThemer4Dlg dialog
class CBasicThemer4Dlg : public CDialogEx
{
// Construction
public:
	CBasicThemer4Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASICTHEMER4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HWINEVENTHOOK hEvent;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};
