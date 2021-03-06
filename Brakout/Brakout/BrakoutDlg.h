
// BrakoutDlg.h : header file
//

#pragma once


// CBrakoutDlg dialog
class CBrakoutDlg : public CDialogEx
{
// Construction
public:
	CBrakoutDlg(CWnd* pParent = nullptr);	// standard constructor

public: //Variables
	RECT mySize;
	int DirX = 5; //Velocidad pelota
	int DirY = 5; //Velocidad pelota
	int PosX = mySize.top; //Posicion donde inicia la bola
	int PosY = mySize.left;
	int MouseX;
	int ModifyWidth = 1;
	int ModifyHeight = 1;
	//int BallSize;
	int BallHeight;
	int BallWidth;
	//int BarSize;
	int BarHeight;
	int BarWidth;
	int Space = 40;
	BITMAP BallSizes;
	BITMAP BarSizes;
	//CSize BarSize;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BRAKOUT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void MoveBall();
	void PaintBall(int& BallHeight, int& BallWidth);
	void PaintBar(int& BarHeight, int& BarWidth);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
