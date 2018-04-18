#include "Vertex.h"
void Vertex::setWeights(vector<float>& weights) {
	this->weights = weights;
}
void Vertex::setNormal(Vector4f& normal) {
	this->normal = normal;
}
// compute transformations for each vertex in joint spaces
void Vertex::setInitTransformations(Vector4f& global_pos) { // set transformations list on T-pose
	int n = skel->getJointNum();
	for (int i = 0; i < n; i++) {
		Joint &j = skel->getJoint(i);
		Matrix4f global_inv = j.getGlobalTrans().inverse();
		Vector4f local_trans = global_inv * global_pos;
		transformation_lists.push_back(local_trans);
	}
}

Vector4f Vertex::calculateGlobalPos(bool dq_flag) { // still no vn
	if (dq_flag) // dual quaternion blending
	{
		vector<dual_quat> dual_quats;
		for (int i = 0; i < weights.size(); i++) {
			Matrix4f joint_global_trans = skel->getJoint(i).getGlobalTrans();
			float tx = transformation_lists[i].x(), ty = transformation_lists[i].y(), tz = transformation_lists[i].z();
			Matrix4f vertex_local_trans;
			vertex_local_trans << 
				1, 0, 0, tx,
				0, 1, 0, ty,
				0, 0, 1, tz,
				0, 0, 0, 1;
			Matrix4f vertex_global_trans = joint_global_trans * vertex_local_trans;
			dual_quat dqi = Transformation::matToDual(vertex_global_trans);
			dual_quats.push_back(dqi);
		}
		Vector3f v(0, 0, 0);
		Vector3f vn(normal[0], normal[1], normal[2]);
		dual_quat::transform(v, vn, dual_quats, weights);
		return Vector4f(v[0], v[1], v[2], 1);
	}
	else { // linear blending
		Vector4f global_pos(0, 0, 0, 0);
		for (int i = 0; i < weights.size(); i++) {
			if (weights[i] == 0) // no influence from joint[i]
				continue;
			else {
				//get joint global transformation
				Matrix4f joint_global_trans = skel->getJoint(i).getGlobalTrans();
				Vector4f O(0, 0, 0, 1);
				Vector4f global_component = joint_global_trans * transformation_lists[i] * weights[i];
				global_pos += global_component;
			}
		}
		return global_pos;
	}
}
