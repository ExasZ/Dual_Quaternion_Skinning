#pragma once
#include <Eigen\core>
#include "dual_quat.h"
using namespace Eigen;
class Transformation
{
public:
	static Matrix4f toRotationMat(float rx, float ry, float rz);
	static Matrix4f toTranslationMat(float tx, float ty, float tz);
	static dual_quat matToDual(Matrix4f m);
};

