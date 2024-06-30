#pragma once
#include <queue>
#include <vector>
#include "Renderer_3D.h"
#include "Renderer_2D.h"

#define PI 3.14159

float radians(float deg) {
	return (deg * (PI) / (180.f));
}

static queue<Triangle> tris;

// Defines render resolution
static int scaleFactor = 4;
static int windowX = 1024 / scaleFactor; int windowY = 896 / scaleFactor;
// Maximum quality
static int QualityLevel = 100;
static bool Interlace = !true;
static Renderer3D renderer;

static int frames = 0;
static int tframe = 0;
static int dTtime = 0;
static int cfps = 0;
static int PolyCount = 0;
static bool onTick = true; // Allow game operation if this is active.
static time_t t = time(NULL);

bool Tri_Comp(Triangle t, vector<Triangle> ts) {
	for (int i = 0; i < ts.size(); i++) {
		if (ts[i].v1.x == t.v1.x && ts[i].v1.y == t.v1.y
			&& ts[i].v2.x == t.v2.x && ts[i].v2.y == t.v2.y
			&& ts[i].v3.x == t.v3.x && ts[i].v3.y == t.v3.y) {
			return true;
		}
	}

	return false;
}

void CaptureFrames() {

	time_t c = time(NULL) - t;
	if (c >= 1) {
		t = time(NULL);
		float fps = tframe;
		fps /= c;
		cfps = fps;
		tframe = 0;
	}
}

string IsInterlaced() {
	if (Interlace) return "Interlaced";
	return "Progressive";
}

void ConsoleUpdate() {
	string s = " " + std::to_string(cfps) + " FPS" + " Frames rendered: " + std::to_string(frames++) + " Tick rate: " + std::to_string(cfps * (0.05f)) + " Polys: " + std::to_string(PolyCount) + " Resolution: (" + std::to_string(windowX) + "x" + std::to_string(windowY) + ") " + IsInterlaced() + "\n";
	tframe++;
	wstring r = std::wstring(s.begin(), s.end());
	LPCWSTR wideString = r.c_str();
	SetConsoleTitle(wideString);

	CaptureFrames();
	dTtime++;

	if (dTtime > cfps * 0.05f) {
		onTick = true;
		dTtime = false;
	}

	while (!tris.empty()) {
		tris.pop();
	}
}



