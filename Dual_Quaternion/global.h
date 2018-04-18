#pragma once
#include <gl/glut.h>
#include <windows.h>
#include "dual_quat.h"
#include "skeleton.h"
#include "mesh.h"
#include "Transformation.h"

/**
*https://free3d.com/3d-model/rigged-male-character-84850.html
*https://www.cgtrader.com/items/696175/download-page
*/
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1600
#define PI 3.1415926535898
#define DEG_TO_RAD (PI/180)
#define BONE_LENGTH 1.0f
//for mesh
#define CIRCULAR_DENSITY 6
#define LAYERS 30
#define RADIUS 0.2
#define FRACTION 0.85

//funcs
void display(void);
void reshape(int, int);
void keyboard(unsigned char key, int x, int y);
void animate();
void createSkeleton();
void createMesh();

struct Camera {
	float angle = 0;  // angle with y-axis
	float x = 0, y = BONE_LENGTH, z = 5;
	float lx = 0, ly = 0, lz = -1; // sight vector
	void orient() {
		lx = sin(angle);
		lz = -cos(angle);
		glLoadIdentity();
		gluLookAt(x, y, z,
			x + lx, y + ly, z + lz,
			0.0f, 1.0f, 0.0f);
	}
	void moveSight(int direction) {
		x = x + direction*(lx)*0.1;
		z = z + direction*(lz)*0.1;
		glLoadIdentity();
		gluLookAt(x, y, z,
			x + lx, y + ly, z + lz,
			0.0f, 1.0f, 0.0f);
	}
};
//global vars
struct Globals {
public:
	Globals() :s(), m() {}
	~Globals() {}
	skeleton s;
	mesh m;
	Camera cam;
	float angle; // in degree;
	int rot_axis = 1; // 1 for y, -1 for x;
};
