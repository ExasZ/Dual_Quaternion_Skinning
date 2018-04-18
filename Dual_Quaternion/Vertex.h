#pragma once
#include <Eigen\core>
#include <Eigen\dense>
#include <vector>
#include <stack>
#include "skeleton.h"
#include "dual_quat.h"
#include "Transformation.h"
using namespace std;
using namespace Eigen;
class Vertex
{
public:
	Vertex(int index) : index(index) {}
	~Vertex() {}

	// Setters
	void setWeights(vector<float>& weights);
	void setNormal(Vector4f& normal);
	void setInitTransformations(Vector4f& global_pos); // set transformations list on T-pose
	void setBindingSkeleton(skeleton*s) { skel = s; }

	// Getters
	Vector4f& getNormal() { return normal; }
	// get weight for joints[index]
	float getWeight(int index) { return weights[index]; }
	// get transformation mat for joints[index]
	Vector4f& getTrans(int index) { return transformation_lists[index]; }

	// blending function
	Vector4f calculateGlobalPos(bool dq_flag);

private:
	int index;
	skeleton* skel;
	Vector4f normal;
	vector<float> weights; // joint weights, sorted by joint indices
	vector<Vector4f> transformation_lists; // transformations
	stack<Matrix4f> mat_stack;
};

