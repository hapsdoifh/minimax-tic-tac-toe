
// minimaxGUIDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "minimaxGUI.h"
#include "minimaxGUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CminimaxGUIDlg dialog



CminimaxGUIDlg::CminimaxGUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINIMAXGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CminimaxGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CminimaxGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_NCLBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_WM_SIZE()
END_MESSAGE_MAP()


// CminimaxGUIDlg message handlers

BOOL CminimaxGUIDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CminimaxGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

POINT mousePoint;
#define BORDER 30


void CminimaxGUIDlg::OnPaint()
{
	CPen drawPen(PS_SOLID,5,RGB(100,100,100));
	CPaintDC painter(this);
	painter.SelectObject(&drawPen);
	CRect ClientRect;
	GetClientRect(ClientRect);
	painter.MoveTo(ClientRect.left+BORDER, ClientRect.bottom / 3);
	painter.LineTo(ClientRect.right - BORDER, ClientRect.bottom / 3);
	painter.MoveTo(ClientRect.left+BORDER, ClientRect.bottom / 3*2);
	painter.LineTo(ClientRect.right - BORDER, ClientRect.bottom / 3*2);
	painter.MoveTo(ClientRect.right/3, ClientRect.top + BORDER);
	painter.LineTo(ClientRect.right/3, ClientRect.bottom - BORDER);
	painter.MoveTo(ClientRect.right / 3 * 2, ClientRect.top + BORDER);
	painter.LineTo(ClientRect.right / 3 * 2, ClientRect.bottom - BORDER);
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
HCURSOR CminimaxGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CminimaxGUIDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	GetCursorPos(&mousePoint);
//	this->Invalidate();
//	CDialogEx::OnNcLButtonDown(nHitTest, point);
//}


void CminimaxGUIDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetCursorPos(&mousePoint);
	this->Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CminimaxGUIDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	this->Invalidate();
	// TODO: Add your message handler code here
}
