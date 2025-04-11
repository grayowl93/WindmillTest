
// WindmillTestDlg.h : ヘッダー ファイル
//

#pragma once
#include "UserCommon.h"

// CWindmillTestDlg ダイアログ
class CWindmillTestDlg : public CDialogEx
{
// コンストラクション
public:
	CWindmillTestDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

												// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDMILLTEST_DIALOG };
#endif
	CWinApp* pSaveParent = NULL;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// iniファイルパス
//	std::wstring strInfilePath = L".¥¥CWindmillTest.ini";
	CString strInfilePath = _T(".¥¥CWindmillTest.ini");

	CString MovieInputFullPathName;
	CString MovieFullPathName;

	CImage cimg[3];
//	CImage cGray[3];
//	CImage c2Bit[3];
//	CImage cDraft;
	cv::Mat	DraftImage;
	cv::Mat	NewImage;
	//	cv::Mat gray[3];
	cv::Point2d blade_center[5];
	cv::Point2d blade_top[5];
	int	blade_current = 0;
	int	blade_new = 0;

#if 0
	cv::Mat *binary[3] = { NULL };
#endif
	cv::Mat	binary[3];
	cv::Mat	diff1;
	cv::Mat	diff2;
	cv::Mat	diff;
	int		current_img_pos;
	int		iWidth, iHeight;
	CImage	DispMain;
	CImage	DispGray;
	CImage	DispDraft;
	CImage	Disp1Bit;
	CImage	Disp1BitDiff1;
	CImage	Disp1BitDiff2;
	CImage	Disp1BitDiff;
	bool	reDraw = false;
	bool	readMP4 = false;

	CString	current_img_dir;
	CString	current_file_name;
	CString	current_file_ext;
	CString	current_file;
	CString	current_format;
	int		current_img_digits;
	int		current_img_counter;
	int		current_fram_counter;
	void LoadImageFile(CString file_name);
	void Gray2BitImage(int pos,CImage &dstImg,CImage &dstImg2);
	void CImageToMat(CImage &img,Mat &mat);
	void MatToCImage(Mat& mat, CImage& img);
	void drawAxis(cv::Mat& img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale = 0.2,int thickness = 1);
	void DiffImage(int pos);
	void GetMaxLabelPositon(POINT &center,POINT &left,POINT &right);
	void GetTurnCenter(POINT& center);
	void UpdateDraff();
public:
	afx_msg void OnBnClickedButtonImgDir();
	afx_msg void OnBnClickedButtonBefore();
	afx_msg void OnBnClickedButtonForword();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckMovieOutput();
	afx_msg void OnBnClickedButtonMovieFile();
};
