#include "Transformation.h" 
#include <cmath> 

Matrix4f Transformation::toRotationMat(float rx, float ry, float rz) {
	Matrix4f Rx, Ry, Rz;
	Rx << 1, 0, 0, 0,
		0, cos(rx), -sin(rx), 0,
		0, sin(rx), cos(rx), 0,
		0, 0, 0, 1;
	Ry << cos(ry), 0, sin(ry), 0,
		0, 1, 0, 0,
		-sin(ry), 0, cos(ry), 0,
		0, 0, 0, 1;
	Rz << cos(rz), -sin(rz), 0, 0,
		sin(rz), cos(rz), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
	return Rx * Ry * Rz;
}
Matrix4f Transformation::toTranslationMat(float tx, float ty, float tz) {
	Matrix4f T;
	T << 1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;
	return T;
}
dual_quat Transformation::matToDual(Matrix4f m)
{
	float w = sqrt(1 + m(0, 0) + m(1, 1) + m(2, 2)) / 2,
		x = (m(2, 1) - m(1, 2)) / 4 / w,
		y = (m(0, 2) - m(2, 0)) / 4 / w,
		z = (m(1, 0) - m(0, 1)) / 4 / w;
	quaternion q0(w, x, y, z);
	float tx = m(0, 3), ty = m(1, 3), tz = m(2, 3);
	quaternion qe(0, tx / 2, ty / 2, tz / 2);
	qe *= q0;
	return dual_quat(q0, qe);
}
