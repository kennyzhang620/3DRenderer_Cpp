#pragma once
#include "Scene.h"
#include "PlayerObject.h"
#include "CubePrim.h"
#include "TestObj.h"
#include "Cube_PrTest.h"

class Scene1_A {
public:
	TestObj o = TestObj(0, 0, 3);
	CubePrim o2 = CubePrim(0, 0, 3);
	CubePrim c = CubePrim(3, 0, 0);
	Cube_PrTest c1 = Cube_PrTest(0, 0, 0);
	PlayerObject Player = PlayerObject(-0.6f, 2.3f, -1.8f);

	SceneNode snode = SceneNode(nullptr);
	SceneNode snode2 = SceneNode(&o);
	Scene scene = Scene(&snode);
	Scene1_A() {
		snode.AddGameObject(&c);
		snode.AddGameObject(&Player);
		snode.AddSceneNode(&snode2);
		//	snode2.AddGameObject(&c1);
	}

	void Run() {
		scene.Traverse();
	}
};

