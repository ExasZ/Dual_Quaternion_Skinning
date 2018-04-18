#pragma once
#include <Eigen\core>
#include <vector>
#include "Joint.h"
using namespace std;
using namespace Eigen;
class skeleton
{
public:
	skeleton() : joint_num(0){}
	skeleton(Joint *root) :root(root), joint_num(0) {}
	~skeleton() {}

	//Setter
	void setRoot() { this->root = &joint_list[0]; }
	void setJointNum(int n) { joint_list.reserve(n*sizeof(Joint)); }
	void addJoint(Joint& j) { joint_list.push_back(j); joint_num++; }
	void setJoint(int ind, int par_ind, Vector3f rot, Vector3f trans);
	
	//Getter
	Joint& getJoint(int index) { return joint_list[index]; }
	int getJointNum() { return joint_num; }

	//Drawer
	void calculateJointsBones(Joint* j);
	void draw();

	//Animator
	void transformLocal(int ind, Matrix4f trans_mat);
	void passForward(int ind);
private:
	Joint * root;
	vector<Joint> joint_list;
	unsigned joint_num;
	// display buffers
	vector<Vector4f> joints_pos;
	vector<vector<Vector4f>> bones;
};
