
// FinalProject01Dlg.h: 헤더 파일
//

#pragma once

#include "opencv2/opencv.hpp"
#include "SerialCom.h"


using namespace cv;
using namespace std;


// CFinalProject01Dlg 대화 상자
class CFinalProject01Dlg : public CDialogEx
{
// 생성입니다.
public:
	CFinalProject01Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CSerialComm* m_comm;
	LRESULT		OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT		OnReceive(WPARAM length, LPARAM lpara);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINALPROJECT01_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	VideoCapture* capture;
	Mat frame;
	Mat hsv_frame;
	CImage cimage_mfc;
	Scalar lowery = Scalar(20, 100, 100);																	// HSV color 노란색 범위 지정
	Scalar uppery = Scalar(30, 255, 255);
	Scalar lowerr = Scalar(0, 100, 100);																	// HSV color 빨간색 범위 지정
	Scalar upperr = Scalar(10, 255, 255);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	CEdit m_box1;
	CEdit m_box2;
	CEdit m_box3;
	int user = 0;
	int com = 0;
	int user_score = 0;
	int com_score = 0;
	CString str;
};

