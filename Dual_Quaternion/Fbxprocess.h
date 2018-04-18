#pragma once
#include <fbxsdk.h>
#include <map>
#include "skeleton.h"
#include "mesh.h"
using namespace std;
class Fbxprocess
{
public:
	Fbxprocess() :joint_num(0) {}
	void fbxInitial(const char* filename, skeleton* s, mesh *m);
	void ProcessNode(FbxNode* pNode);
	void ProcessMesh(FbxNode* pNode);
	void ProcessSkeleton(FbxNode* pNode);
	void ProcessLight(FbxNode* pNode);
	void ProcessCamera(FbxNode* pNode);

	void read() { ProcessNode(scene->GetRootNode()); }
private:
	unsigned joint_num;
	FbxScene *scene;
	skeleton *skel;
	mesh *msh;
	map<FbxNode*, unsigned> jointToIndex;
};
