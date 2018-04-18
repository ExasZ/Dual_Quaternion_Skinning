#pragma once

#include <Eigen\Core>
#include <Eigen\Dense>
#include <vector>
using namespace Eigen;
class quaternion
{
public:
	quaternion() : x(0), y(0), z(0), w(0) {}
	quaternion(float w, float x, float y, float z) : x(x), y(y), z(z), w(w){}
	quaternion(const quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {} // copy
	~quaternion() {}

	//Getter
	inline float		getReal() {
		return w;
	}
	inline Vector3f		getComp() {
		return Vector3f(x, y, z);
	}
	
	//util funcs
	inline float		dot(const quaternion& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}
	inline float		norm() {
		return sqrt(x * x + y * y + z * z + w * w);
	}
	inline void			normalize() {
		float norm = this->norm();
		x /= norm, y /= norm, z /= norm, w /= norm;
	}
	inline quaternion	conjugate() {
		return quaternion(w, -x, -y, -z);
	}

	//operators
	inline quaternion	operator+(const quaternion& rhs) const {
		return quaternion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z);
	}
	inline quaternion	operator-(const quaternion& rhs) const {
		return quaternion(w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z);
	}
	inline quaternion	operator*(const quaternion& rhs) const {
		Vector3f u, v, c;
		u << x, y, z;
		v << rhs.x, rhs.y, rhs.z;
		c = w*v + rhs.w*u + u.cross(v);
		float r = w * rhs.w - u.dot(v);
		return quaternion(r, c[0], c[1], c[2]);
	}
	inline quaternion	operator*(const float scale) const {
		return quaternion(w*scale, x*scale, y*scale, z*scale);
	}
	inline quaternion	operator+=(const quaternion& rhs) {
		x += rhs.x, y += rhs.y, z += rhs.z, w += rhs.w;
		return *this;
	}
	inline quaternion	operator-=(const quaternion& rhs) {
		x -= rhs.x, y -= rhs.y, z -= rhs.z, w -= rhs.w;
		return *this;
	}
	inline quaternion	operator*=(const quaternion& rhs) {
		quaternion q = *this * rhs;
		x = q.x, y = q.y, z = q.z, w = q.w;
		return *this;
	}
	inline quaternion	operator*=(const float scale) {
		x *= scale, y *= scale, z *= scale, w *= scale;
		return *this;
	}

private:
	float w, x, y, z;
};

