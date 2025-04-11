#include "pch.h"
#include "UserCommon.h"

// 直線を左方向へ延長
point Extension(const point& a, const point& b)
{
    point left;
    left.x = 0;
    left.y = 0;

    double dxy;
    if (a.x == b.x)
    {   // 縦線
        left.x = a.x;
        return left;
    }
    dxy = (a.y - b.y) / (a.x - b.x);
    if (a.x < b.x)
    {
        left.y = (left.x - a.x) * dxy + a.y;
    }
    else
    {
        if (dxy == 0.0)
        {
            left.y = a.y;
        }
        else
        {
            left.x = (left.y - a.y) / dxy + a.x;
        }
    }

    return left;
}

// 交点検出----------------------------.
double Cross(const point& a, const point& b)
{
	return a.x * b.y - a.y * b.x;
}

point Intersection(const point& a, const point& b, const point& c, const point& d)
{
    double s, t, deno = Cross(b - a, d - c);
    point error = { INF, INF },aa,cc;
    if (deno == 0.0) {
        // 線分が平行
        return error;
    }
    // a、cの座標を領域左上まで延長する
    aa = Extension(a, b);
    cc = Extension(c, d);

    // done再計算.
    deno = Cross(b - aa, d - cc);
    s = Cross(c - aa, d - cc) / deno;
    t = Cross(b - aa, a - cc) / deno;
    if (s < 0.0 || 1.0 < s || t < 0.0 || 1.0 < t) {
        // 線分が交差していない
        return error;
    }
    return { aa.x + s * (b - aa).x, aa.y + s * (b - aa).y };
}
// 交点検出----------------------------.
