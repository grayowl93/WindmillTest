#pragma once


#include <Eigen/Core>
#include <Eigen/Dense>

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>


#include <mutex>
#include <thread>
#include <assert.h>

#include <windows.h>
#include <atlstr.h>

#define TC_PI 3.141592653589798323846

typedef struct tcPoint {
	double posX;
	double posY;
}tcPoint, * tcPointPtr, ** tcPointHandle;

using namespace std;

// OpenCVは、デバックモードで使用したくない.
// デバックモードライブラリがメモリーリークを起こしているため.
//#define CV_IGNORE_DEBUG_BUILD_GUARD
//上記を定義すれば、リリースモードライブラリをリンクできるが、例外エラーが出る.
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/videoio.hpp>

using namespace cv;

// 交点検出----------------------------.
#ifndef DETECT_INTER_SECTION
#define DETECT_INTER_SECTION
#define INF 1e60
typedef struct Point_Coordinates {
    double x, y;
    friend Point_Coordinates operator-(const Point_Coordinates& l, const Point_Coordinates& r) {
        return { l.x - r.x, l.y - r.y };
    }
} point;

#ifdef  __cplusplus
extern "C" {
#endif
point Extension(const point& a, const point& b);
double Cross(const point& a, const point& b);
point Intersection(const point& a, const point& b, const point& c, const point& d);
#ifdef  __cplusplus
}
#endif
// 交点検出----------------------------.
#endif
