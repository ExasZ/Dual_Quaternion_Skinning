#pragma once
#include <Eigen\core>
#include <vector>
using namespace Eigen;
using namespace std;
class Joint
{
public:
	Joint():index(0) {}
	Joint(int index) :index(index) {}
	~Joint() {}
		
	//Setter
	void setParent(Joint *parent);
	void setLocalTrans(float rx, float ry, float rz, float tx, float ty, float tz);
	void setGlobalTrans();

	//Getter
	int getIndex() { return index; }
	Matrix4f getLocalTrans() { return local_trans; }
	Matrix4f getGlobalTrans() { return global_trans; }
	Joint* getParent() { return parent; }
	int getChildrenNum() { return children.size(); }
	Joint* getChild(int ind) { return children[ind]; }
	Vector4f getGlobalPos() { Vector4f O(0,0,0,1); return global_trans * O; }
	
	//Animator
	void transformLocal(Matrix4f trans_mat);
	void passForward();
private:
	int index;
	Matrix4f local_trans; // transformation from parent local frame
	Matrix4f global_trans; // transformation from global frame
	Joint *parent;
	vector<Joint *> children;
};

