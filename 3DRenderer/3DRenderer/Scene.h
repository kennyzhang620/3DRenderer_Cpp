#pragma once
#include "GameObject.h"

class SceneNode {
public:

	SceneNode() {}

	SceneNode(GameObject* obj) {
		MainObj.push_back(obj);

		if (obj != nullptr) {
			NodeTrans.xPos = obj->ObjectTransform->xPos;
			NodeTrans.yPos = obj->ObjectTransform->yPos;
			NodeTrans.zPos = obj->ObjectTransform->zPos;
			NodeTrans.xRot = obj->ObjectTransform->xRot;
			NodeTrans.yRot = obj->ObjectTransform->yRot;
			NodeTrans.zRot = obj->ObjectTransform->zRot;
			NodeTrans.xScale = obj->ObjectTransform->xScale;
			NodeTrans.yScale = obj->ObjectTransform->yScale;
			NodeTrans.zScale = obj->ObjectTransform->zScale;
		}
	}

	SceneNode(GameObject** obj, int count) {
		
		for (int i = 0; i < count; i++) {
			MainObj.push_back(obj[i]);
		}

		if (obj[0] != nullptr) {
			NodeTrans.xPos = obj[0]->ObjectTransform->xPos;
			NodeTrans.yPos = obj[0]->ObjectTransform->yPos;
			NodeTrans.zPos = obj[0]->ObjectTransform->zPos;
			NodeTrans.xRot = obj[0]->ObjectTransform->xRot;
			NodeTrans.yRot = obj[0]->ObjectTransform->yRot;
			NodeTrans.zRot = obj[0]->ObjectTransform->zRot;
			NodeTrans.xScale = obj[0]->ObjectTransform->xScale;
			NodeTrans.yScale = obj[0]->ObjectTransform->yScale;
			NodeTrans.zScale = obj[0]->ObjectTransform->zScale;
		}
	}

	void AddGameObject(GameObject* go) {
		MainObj.push_back(go);
	}

	void AddGameObjects(GameObject** sn, int count) {
		for (int i = 0; i < count; i++) {
			MainObj.push_back(sn[i]);
		}
	}

	void AddSceneNode(SceneNode sn) {
		nextNodes.push_back(&sn);
	}

	void AddSceneNode(SceneNode* sn) {
		nextNodes.push_back(sn);
	}

	void AddSceneNodes(SceneNode** sn, int count) {
		for (int i = 0; i < count; i++) {
			nextNodes.push_back(sn[i]);
		}
	}

	void SetActive(bool a) {
		ActiveSelf = a;
	}

	Transform NodeTrans;
	bool ActiveSelf = true;
	std::list<GameObject*> MainObj;
	std::list<SceneNode*> nextNodes;
};
class Scene
{
public:
	Scene() {}
	Scene(SceneNode* root) {
		SceneRoot = root;
	}

	Scene(SceneNode root) {
		SceneRoot = &root;
	}

	void Traverse() {
		_traverse(SceneRoot);
	}

private:
	/*	*/

	VectorCoords transformPivot(Transform a, Transform b) {
		
		VectorCoords diff(a.xPos - b.xPos, a.yPos - b.yPos, a.zPos - b.zPos);
		scale.Scale3D(b.xScale, b.yScale, b.zScale);
		scale.res_to_matrix();
		rot.RotateZ(b.zRot);
		rot.res_to_matrix();
		rot.matmul(scale);
		rot.res_to_matrix();
		scale.RotateY(b.yRot);
		scale.res_to_matrix();
		scale.matmul(rot);
		scale.res_to_matrix();
		rot.RotateX(b.xRot);
		rot.res_to_matrix();
		rot.matmul(scale);
		rot.res_to_matrix();
		rot(0, 0) -= 3; rot(1, 1) -= 3; rot(2, 2) -= 3; rot(3, 3) -= 3;

		return rot.matmul_vtr(diff);
	}
	

	void _traverse(SceneNode* s) {
		if (s == nullptr) {

		}
		else {
			if (s->MainObj.begin() != s->MainObj.end()) {
				GameObject* curr = *(s->MainObj.begin());
				Transform* ct = &(s->NodeTrans);
				Transform ts;
				if (curr != nullptr) {
					ts = Transform(curr->ObjectTransform->xPos - ct->xPos, curr->ObjectTransform->yPos - ct->yPos, curr->ObjectTransform->zPos - ct->zPos, curr->ObjectTransform->xRot - ct->xRot, curr->ObjectTransform->yRot - ct->yRot, curr->ObjectTransform->zRot - ct->zRot, curr->ObjectTransform->xScale - ct->xScale, curr->ObjectTransform->yScale - ct->yScale, curr->ObjectTransform->zScale - ct->zScale);
					s->NodeTrans.set_all(*(curr->ObjectTransform));
				}

				/*
				X0 = Root_Transform (V1,V2,V3)
				X1,X2,....Xn = Child_Transforms

				A = X1 - X0
				B = (Rzyx(T))(A)
				C = B + X0
				*/

				for (std::list<SceneNode*>::iterator it = s->nextNodes.begin(); it != s->nextNodes.end(); it++) {
					(*it)->NodeTrans.xPos + ts.xPos; (*it)->NodeTrans.yPos + ts.yPos;  (*it)->NodeTrans.zPos + ts.zPos;
					_traverse((*it));
				}
				
				for (std::list<GameObject*>::iterator it = s->MainObj.begin(); it != s->MainObj.end(); ++it) {
					GameObject* currM = (*it);
					if (currM != nullptr) {
						currM->ObjectTransform->xPos += ts.xPos;
						currM->ObjectTransform->yPos += ts.yPos;
						currM->ObjectTransform->zPos += ts.zPos;

						Transform a = *(currM->ObjectTransform);
						Transform b = (s->NodeTrans);

						VectorCoords transformed = transformPivot(a, b);

						currM->ObjectTransform->xPos = transformed.x + b.xPos; currM->ObjectTransform->yPos = transformed.y + b.yPos; currM->ObjectTransform->zPos = transformed.z + b.zPos;
						currM->Update();
					}
				}

			}
		}
	}


	SceneNode* SceneRoot = nullptr;

	MatrixMxN<float> scale = MatrixMxN<float>(4, 4);
	MatrixMxN<float> rot = MatrixMxN<float>(4, 4);

};

