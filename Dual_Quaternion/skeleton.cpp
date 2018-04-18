#include "skeleton.h"
#include <gl\glut.h>

void skeleton::setJoint(int ind, int par_ind, Vector3f rot, Vector3f trans) {
	Joint &j = getJoint(ind);
	if (par_ind != -1)
		j.setParent(&getJoint(par_ind));
	else
		j.setParent(nullptr);
	j.setLocalTrans(rot[0], rot[1], rot[2], trans[0], trans[1], trans[2]);
	j.setGlobalTrans();
}
void skeleton::calculateJointsBones(Joint* j) {
	Vector4f global_pos = j->getGlobalPos();
	joints_pos.push_back(global_pos);
	if (j->getParent() != nullptr)
	{
		vector<Vector4f> bone;
		Vector4f start = j->getParent()->getGlobalPos();
		Vector4f end = j->getGlobalPos();
		bone.push_back(start);
		bone.push_back(end);
		bones.push_back(bone);
	}
	int n = j->getChildrenNum();
	for (int i = 0; i < n; i++) {
		calculateJointsBones(j->getChild(i));
	}
}
void skeleton::draw() {
	joints_pos.clear();
	bones.clear();
	calculateJointsBones(root);
	glPointSize(8);
	glColor3f(0, 1, 0);
	// draw points
	glBegin(GL_POINTS);
	for(int i = 0; i < joint_num; i++)
	{
		Vector4f global_pos = joints_pos[i];
		glVertex3f(global_pos[0], global_pos[1], global_pos[2]);
	}
	glEnd();

	// draw bones
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(1.5f);
	glBegin(GL_LINES);
	for (size_t i = 0; i < bones.size(); i++)
	{
		glVertex3f(bones[i][0].x(), bones[i][0].y(), bones[i][0].z());
		glVertex3f(bones[i][1].x(), bones[i][1].y(), bones[i][1].z());
	}
	glEnd();
}

void skeleton::transformLocal(int ind, Matrix4f trans_mat)
{
	Joint &j = getJoint(ind);
	j.transformLocal(trans_mat);
}

void skeleton::passForward(int ind)
{
	Joint &j = getJoint(ind);
	j.passForward();
}
