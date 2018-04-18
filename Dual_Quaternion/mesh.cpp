#include "mesh.h"
#include <gl/glut.h>

void mesh::setVertex(int ind, Vector4f& normal, vector<float> weights, Vector4f& global_pos) {
	Vertex& v = getVertex(ind);
	v.setNormal(normal);
	v.setWeights(weights);
	v.setInitTransformations(global_pos);
}

void mesh::draw() {
	vertices_pos.clear();
	polygons_pos.clear();
	calculateVertPolys();

	// draw polygons
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 1, 1);
	for (int i = 0; i < polygons_pos.size(); i++) {
		Vector4f v0 = polygons_pos[i][0];
		Vector4f v1 = polygons_pos[i][1];
		Vector4f v2 = polygons_pos[i][2];
		glBegin(GL_TRIANGLES);
		glVertex3f(v0.x(), v0.y(), v0.z());
		glVertex3f(v1.x(), v1.y(), v1.z());
		glVertex3f(v2.x(), v2.y(), v2.z());
		glEnd();
	}
	
}

void mesh::calculateVertPolys() {
	for (int i = 0; i < vertex_list.size(); i++) {
		Vector4f global_pos = vertex_list[i].calculateGlobalPos(dq_flag);
		vertices_pos.push_back(global_pos);
	}
	for (int i = 0; i < polygon_list.size(); i++) {
		Vector3i vertices_index = polygon_list[i];
		int v0 = vertices_index[0], v1 = vertices_index[1], v2 = vertices_index[2];
		vector<Vector4f> polygon;
		polygon.push_back(vertices_pos[v0]);
		polygon.push_back(vertices_pos[v1]);
		polygon.push_back(vertices_pos[v2]);
		polygons_pos.push_back(polygon);
	}
}
