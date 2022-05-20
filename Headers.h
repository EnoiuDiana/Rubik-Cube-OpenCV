#pragma once

#include "stdafx.h"
#include "common.h"
enum Color { red, orange, blue, green, white, yellow };

struct HsvMat {
	Mat hue;
	Mat value;
	Mat saturation;
};

struct YuvMat {
	Mat Y;
	Mat Up;
	Mat Vp;
};

struct MyPoint {
	int x;
	int y;
};