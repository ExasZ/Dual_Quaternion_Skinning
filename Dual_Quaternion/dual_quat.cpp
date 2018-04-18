#include "dual_quat.h"

//Algorithm 1 of the paper
void dual_quat::transform(Vector3f& v, Vector3f&vn, vector<dual_quat>& dquats, vector<float>& weights) {
	dual_quat b = dual_quat();
	for (int i = 0; i < dquats.size(); i++) {
		b += dquats[i] * weights[i];
	}
	quaternion c0 = b.getReal();
	quaternion ce = b.getDual();
	float b0 = c0.norm();
	c0 *= 1 / b0;
	ce *= 1 / b0;
	Vector3f d0 = c0.getComp(), de = ce.getComp();
	float a0 = c0.getReal(), ae = ce.getReal();
	v += 2 * d0.cross(d0.cross(v) + a0 * v) + 2 * (a0*de - ae * d0 + d0.cross(de));
	vn += 2 * d0.cross(d0.cross(vn) + a0 * vn);
}