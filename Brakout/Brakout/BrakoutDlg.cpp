
// BrakoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Brakout.h"
#include "BrakoutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrakoutDlg dialog



CBrakoutDlg::CBrakoutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BRAKOUT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBrakoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBrakoutDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CBrakoutDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CBrakoutDlg message handlers

BOOL CBrakoutDlg::OnInitDialog()
{
	GetClientRect(&mySize);
	CDialogEx::OnInitDialog();
	//GetBitmapDimension()
	
	//Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBrakoutDlg::OnPaint()
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
HCURSOR CBrakoutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBrakoutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnTimer(1);
}

void CBrakoutDlg::MoveBall()
{
	if (PosX >= mySize.right - BallWidth)
	{
		PosX = mySize.right - BallWidth;
		ModifyWidth = -ModifyWidth;
	}
	else if (PosX < 0)
	{
		PosX = 0;
		DirX = -DirX;
	}
	if (PosY >= mySize.bottom - BallHeight)
	{
		PosY = mySize.bottom - BallHeight;
		ModifyHeight = -ModifyHeight;
	}
	else if (PosY < 0)
	{
		PosY = 0;
		DirY = -DirY;
	}
	if (PosY + BallHeight / 2 >= (mySize.bottom-BarHeight)-Space)
	{
		if (PosX > MouseX && PosX + BallWidth < MouseX + BarWidth)
		{
			DirY = -DirY;
		}
	}
	if (PosY + BallHeight >= mySize.bottom)
	{
		PosX = 0;
		PosY = 0;
	}
	PosX += DirX*ModifyWidth;
	PosY += DirY*ModifyHeight;
}

void CBrakoutDlg::PaintBall(int& BallHeight, int& BallWidth)
{
	HANDLE hBitmapBall = LoadImage(0, TEXT("Pelotita.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CBitmap bmp;
	bmp.Attach(reinterpret_cast<HBITMAP>(hBitmapBall));
	CDC*pDC = this->GetDC();
	CDC bmDC;
	bmDC.CreateCompatibleDC(pDC);
	CBitmap* oldBMP = bmDC.SelectObject(&bmp);
	bmp.GetBitmap(&BallSizes);
	BallHeight = BallSizes.bmHeight;
	BallWidth = BallSizes.bmWidth;
	pDC->BitBlt(PosX, PosY, BallWidth, BallHeight, &bmDC, 0, 0, SRCCOPY);
}

void CBrakoutDlg::PaintBar(int& BarHeight, int& BarWidth)
{
	HANDLE hBitmapBar = (HBITMAP)LoadImage(0, TEXT("Barra.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	CBitmap bmp;
	bmp.Attach(reinterpret_cast<HBITMAP>(hBitmapBar));
	CDC*pDC = this->GetDC();
	CDC bmDC;
	bmDC.CreateCompatibleDC(pDC);
	CBitmap* oldBMP = bmDC.SelectObject(&bmp);
	bmp.GetBitmap(&BarSizes);
	BarHeight = BarSizes.bmHeight;
	BarWidth = BarSizes.bmWidth;
	pDC->BitBlt(MouseX, mySize.bottom-Space, BarWidth, BarHeight, &bmDC, 0, 0, SRCCOPY); //Conocer tamanio del bitmap
}

void CBrakoutDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	SetTimer(1, 50, NULL);
	CDialogEx::OnTimer(nIDEvent);
	CDC*pDC = this->GetDC();
	pDC->Rectangle(0, 0, mySize.right, mySize.bottom);
	PaintBar(BarHeight,BarWidth);
	PaintBall(BallHeight,BallWidth);
	MoveBall();
}

void CBrakoutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnMouseMove(nFlags, point);
	MouseX = point.x;
}
