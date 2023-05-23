#include <cstring>
#include <iostream>
#include <stack>
#include <time.h>
#include "Global_Stack.h"

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#endif

#include "LevelObject.h"
#include "PlayerObject.h"
#include "CubePrim.h"
#include "DebugSp.h"
#include "DiffuseMaterial.h"

using namespace std;

void Rasterize_ST() {
	renderer.setCanvas(windowX, windowY);

	LevelObject m1(0,0,5);
	CubePrim c(3, 0, 0);
	DebugSp d(-3, 0, 0);
	PlayerObject Player(0.0f,1.0f,0.0f);
	PlayerObject p2(0, 9, 4);
	
	p2.ObjectTransform->yRot = radians(90);
	p2.MainCamera.ProjectMode = Project_Ortho;
	p2.MainCamera.nearPlane = 0; p2.MainCamera.farPlane = 6;
//	c.ObjectTransform->SetRotation(radians(45),0,0);
	while (1) {
		if (onTick) {
			m1.Update();
			c.Update();
		//	d.Update();
			Player.Update();
		//	p2.Update();
			onTick = false;
		}
		ConsoleUpdate();
	}
}

int main() {

	Rasterize_ST();

	return 0;
}