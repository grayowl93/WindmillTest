﻿
// WindmillTest.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CWindmillTestApp:
// このクラスの実装については、WindmillTest.cpp を参照してください
//

class CWindmillTestApp : public CWinApp
{
public:
	CWindmillTestApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CWindmillTestApp theApp;
