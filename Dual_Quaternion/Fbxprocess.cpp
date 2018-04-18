#include "Fbxprocess.h"
void Fbxprocess::fbxInitial(const char* filename, skeleton* s, mesh *m) {
	skel = s;
	msh = m;
	FbxManager* fbxMnger = FbxManager::Create();
	// Create the IO settings object.
	FbxIOSettings *ios = FbxIOSettings::Create(fbxMnger, IOSROOT);
	fbxMnger->SetIOSettings(ios);

	// Create an importer using the SDK manager.
	FbxImporter* fbxImporter = FbxImporter::Create(fbxMnger, "");

	// Use the first argument as the filename for the importer.
	if (!fbxImporter->Initialize(filename, -1, fbxMnger->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", fbxImporter->GetStatus().GetErrorString());
		exit(-1);
	}
	// Create a new scene so that it can be populated by the imported file.
	scene = FbxScene::Create(fbxMnger, "myScene");

	// Import the contents of the file into the scene.
	fbxImporter->Import(scene);

	// The file is imported, so get rid of the importer.
	fbxImporter->Destroy();
}

void Fbxprocess::ProcessNode(FbxNode* pNode)
{

	if (pNode->GetNodeAttribute())
	{
		switch (pNode->GetNodeAttribute()->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh: 
			ProcessMesh(pNode);
			break;
		case FbxNodeAttribute::eSkeleton:
			ProcessSkeleton(pNode);
			break;
		case FbxNodeAttribute::eLight:
			ProcessLight(pNode);
			break;
		case FbxNodeAttribute::eCamera:
			ProcessCamera(pNode);
			break;
		}
	}

	for (int i = 0; i < pNode->GetChildCount(); ++i)
	{
		ProcessNode(pNode->GetChild(i));
	}
}

void Fbxprocess::ProcessMesh(FbxNode* pNode) {
	FbxMesh *m = pNode->GetMesh();
}

void Fbxprocess::ProcessSkeleton(FbxNode * pNode)
{
	if (pNode->GetName()[0] == 'L')
		return;
	Joint j(joint_num);
	jointToIndex[pNode] = joint_num;
	FbxSkeleton *joint = pNode->GetSkeleton();
	FbxVector4 local_pos = pNode->LclTranslation.Get();
	FbxVector4 local_rot = pNode->LclRotation.Get();
	FbxNode* p = pNode->GetParent();
	unsigned par_ind = -1;
	if (p && p->GetNodeAttribute() &&
		p->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton) {// has a parent joint
		par_ind = jointToIndex[p];
	}
	skel->addJoint(j);
	skel->setJoint(joint_num, par_ind, { (float)local_rot[0],(float)local_rot[1],(float)local_rot[2] }, { (float)local_pos[0],(float)local_pos[1],(float)local_pos[2] });
	joint_num++;
}

void Fbxprocess::ProcessLight(FbxNode * pNode)
{
}

void Fbxprocess::ProcessCamera(FbxNode * pNode)
{
}
