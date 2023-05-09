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

using namespace std;

void Rasterize_ST() {
	renderer.setCanvas(windowX, windowY);

	LevelObject m1;
	CubePrim c(3, 0, 0);
	DebugSp d(-3, 0, 0);
	PlayerObject Player(0.0f,5.0f,0.0f);


	m1.ObjectTransform->zPos = 5;
	while (1) {
		if (onTick) {
			m1.Update();
			c.Update();
			d.Update();
			Player.Update();
			onTick = false;
		}
		ConsoleUpdate();
	}
}

int main() {

	Rasterize_ST();

	return 0;
}