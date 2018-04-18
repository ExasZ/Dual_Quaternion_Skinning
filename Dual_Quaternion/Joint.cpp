#include "Joint.h"
#include "Transformation.h"

void Joint::setParent(Joint *parent) {
	this->parent = parent;
	if(parent != nullptr)
		parent->children.push_back(this);
}

void Joint::setLocalTrans(float rx, float ry, float rz, float tx, float ty, float tz) {
	Matrix4f R = Transformation::toRotationMat(rx, ry, rz);
	Matrix4f T = Transformation::toTranslationMat(tx, ty, tz);
	this->local_trans = T * R;
}

void Joint::setGlobalTrans() {
	if (this->parent == nullptr) {
		this->global_trans = this->local_trans;
		return;
	}
	this->global_trans = parent->global_trans*this->local_trans;
}

void Joint::transformLocal(Matrix4f trans_mat)
{
	local_trans = local_trans * trans_mat;
}

void Joint::passForward()
{
	setGlobalTrans();
	for (int i = 0; i < getChildrenNum(); i++)
		children[i]->passForward();
}
