#pragma once
#include "quaternion.h"
#include "Eigen\Dense"
using namespace std;
class dual_quat
{
public:
	dual_quat() : q0(), qe() {}
	dual_quat(quaternion q0, quaternion qe) : q0(q0), qe(qe) {}

	~dual_quat() {}

	//Getters
	inline quaternion	getReal() {
		return q0;
	}
	inline quaternion	getDual() {
		return qe;
	}

	//util funcs
	inline dual_quat	conjugate() {
		return dual_quat(q0.conjugate(), qe.conjugate());
	}
	inline dual_quat	operator+(dual_quat& rhs) const {
		return dual_quat(q0 + rhs.q0, qe + rhs.qe);
	}
	inline dual_quat	operator-(const dual_quat& rhs) const {
		return dual_quat(q0 - rhs.q0, qe - rhs.qe);
	}
	inline dual_quat	operator*(const dual_quat& rhs) const {
		return dual_quat(q0*rhs.q0, qe*rhs.q0 + q0 * rhs.qe);
	}
	inline dual_quat	operator*(const float scale) const {
		return dual_quat(q0*scale, qe*scale);
	}
	inline dual_quat	operator+=(const dual_quat& rhs) {
		q0 += rhs.q0, qe += rhs.qe;
		return *this;
	}
	inline dual_quat	operator-=(const dual_quat& rhs) {
		q0 -= rhs.q0, qe -= rhs.qe;
		return *this;
	}
	inline dual_quat	operator*=(const dual_quat& rhs) {
		dual_quat dq = *this * rhs;
		q0 = dq.q0, qe = dq.qe;
		return *this;
	}
	inline dual_quat	operator*=(const float scale) {
		q0 *= scale, qe *= scale;
		return *this;
	}

	void static transform(Vector3f& v, Vector3f& vn, vector<dual_quat>& dqs, vector<float>& weights);
private:
	quaternion q0, qe;
};

