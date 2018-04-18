#pragma once
#include <vector>
#include "Vertex.h"
using namespace std;
class mesh
{
public:
	mesh(): dq_flag(false), skel(nullptr){}
	~mesh() {}
	
	void setBindingSkeleton(skeleton* s) { skel = s; }
	void setBlendingOption(bool dq_flag) { this->dq_flag = dq_flag; }
	void changeBlendingOption() { dq_flag = !dq_flag; }
	void addVertex(Vertex& vertex) { vertex.setBindingSkeleton(skel); vertex_list.push_back(vertex); }
	void setVertex(int ind, Vector4f& normal, vector<float> weights, Vector4f& global_pos);
	void setPolygon(int v1, int v2, int v3) { polygon_list.push_back(Vector3i(v1, v2, v3)); }

	Vector3i getPolygon(int index) { return polygon_list[index]; }
	Vertex& getVertex(int index) { return vertex_list[index]; }

	void calculateVertPolys();
	void draw();
	
private:
	skeleton * skel; // binding skeleton
	bool dq_flag; // blending control. true: dual quaternion; false: linear.
	vector<Vertex> vertex_list;
	vector<Vector4f> vertices_pos; // vertex position buffer
	vector<Vector3i> polygon_list;
	vector<vector<Vector4f>> polygons_pos; // polygon position buffer
};

