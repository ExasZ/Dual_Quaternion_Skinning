#include "global.h"

void openglInit() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Skinning Model");
	glutDisplayFunc(&display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);
	glEnable(GL_DEPTH_TEST);
}

Globals thisApp;

int main(int argc, char *argv[]) {
	//Initialze
	glutInit(&argc, argv);
	openglInit();
	thisApp.angle = 3;

	//Test 1: a self-defined rough mesh
	createSkeleton();
	createMesh();

	////Test 2: arms in fbx format
	//Fbxprocess fbx;
	//const char* filename1 = "C:\\Users\\zpx23\\OneDrive\\Courseworks\\888\\Dual_Quaternion\\Arms.fbx";
	//fbx.fbxInitial(filename1, &thisApp.s, &thisApp.m);
	//thisApp.s.setJointNum(50);
	//fbx.read();
	//thisApp.s.setRoot();
	
	glutMainLoop();

	return 0;
}

void createSkeleton() {
	//create skeleton
	thisApp.s.setJointNum(3);
	Joint root(0);
	thisApp.s.addJoint(root);
	thisApp.s.setJoint(0, -1, { 0, 0, 0 }, { 0, 0, 0 });
	Joint elbow(1);
	thisApp.s.addJoint(elbow);
	thisApp.s.setJoint(1, 0, { 0, 0, 0 }, { 0, BONE_LENGTH, 0 });
	Joint wrist(2);
	thisApp.s.addJoint(wrist);
	thisApp.s.setJoint(2, 1, { 0, 0, 0 }, { 0, BONE_LENGTH, 0 });

	thisApp.s.setRoot();
}

void createMesh() { // a rough mesh around a rough arm
	thisApp.m.setBindingSkeleton(&thisApp.s);
	thisApp.m.setBlendingOption(false);
	float ang = 2 * PI / CIRCULAR_DENSITY;
	// create Vertices
	int n = thisApp.s.getJointNum(); // n=4
	for (int i = 0; i < LAYERS; i++) {
		for (int j = 0; j < CIRCULAR_DENSITY; j++) {
			int ind = i * CIRCULAR_DENSITY + j;
			float w1(0), w2(0), w3(0);
			float y = i * 2 * BONE_LENGTH / (LAYERS - 1);
			Vertex v(ind);
			Vector4f normal(sin(j*ang), 0, cos(j*ang), 1);
			Vector4f global_pos(RADIUS*sin(j*ang), y, RADIUS*cos(j*ang), 1);
			//decide weights
			w1 = 1.0*(LAYERS - i - 1) / (LAYERS - 1);
			float blend_down = FRACTION*BONE_LENGTH, blend_up = (2 - FRACTION)*BONE_LENGTH;
			if (y < FRACTION*BONE_LENGTH)
				w1 = 1;
			else if (y > (2 - FRACTION)*BONE_LENGTH)
				w1 = 0;
			else
				w1 = (blend_up - y) / (blend_up - blend_down);
			w2 = 1 - w1;
			thisApp.m.addVertex(v);
			thisApp.m.setVertex(ind, normal, { w1,w2,w3 }, global_pos);
		}
	}
	// create polygons
	for (int i = 0; i < LAYERS-1; i++) {
		for (int j = 0; j < CIRCULAR_DENSITY; j++) {
			int v1 = i * CIRCULAR_DENSITY + j; // current index
			int v2 = j == (CIRCULAR_DENSITY-1) ? v1-j : v1 + 1;
			int v3 = v1 + CIRCULAR_DENSITY;
			int v4 = v2 + CIRCULAR_DENSITY;
			thisApp.m.setPolygon(v1, v2, v3);
			thisApp.m.setPolygon(v2, v4, v3);
		}
	}
}

void animate() {
	Matrix4f ani_mat;
	if(thisApp.rot_axis == 1)
		ani_mat = Transformation::toRotationMat(0, thisApp.angle*DEG_TO_RAD, 0);
	else
		ani_mat = Transformation::toRotationMat(0,0,thisApp.angle*DEG_TO_RAD);
	thisApp.s.transformLocal(1, ani_mat);
	thisApp.s.passForward(1);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	thisApp.s.draw();
	thisApp.m.draw();
	glutSwapBuffers();
	Sleep(25);
	animate();
}

void reshape(int w, int h) {
	float x = thisApp.cam.x, y = thisApp.cam.y, z = thisApp.cam.z,
		lx = thisApp.cam.lx, ly = thisApp.cam.ly, lz = thisApp.cam.lz;
	if (h == 0) {
		h = 1;
	}
	float ratio = 1.0*w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// viewport
	glViewport(0, 0, w, h);
	// correct perspective matrix
	gluPerspective(45, ratio, 1, 1000);
	// viewpoint
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'c': thisApp.m.changeBlendingOption(); break;
	case 'a': thisApp.cam.angle -= 0.01f; thisApp.cam.orient(); break;
	case 'd': thisApp.cam.angle += 0.01f; thisApp.cam.orient(); break;
	case 'w': thisApp.cam.moveSight(1); break;
	case 's': thisApp.cam.moveSight(-1); break;
	case 'r': thisApp.rot_axis *= -1; break;
	}
}

