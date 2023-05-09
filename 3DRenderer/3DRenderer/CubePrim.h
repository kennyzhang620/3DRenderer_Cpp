#pragma once
#include "GameObject.h"
#include "RendererObject.h"
class CubePrim: public GameObject
{
	public:

		CubePrim() :objectMesh(am) {
			Start();
		}

		CubePrim(float x, float y, float z) :objectMesh(am) {
			Start();
			ObjectTransform->xPos = x;
			ObjectTransform->yPos = y;
			ObjectTransform->zPos = z;
		}

		Mesh& objectMesh;
		RendererObject Renderer;

		void Start() {
			Renderer.ObjectMesh = objectMesh;
			Renderer.ObjectTransform = ObjectTransform;
		}
		void Update() {
			Renderer.Update();
		}

	private:
		vector<float> positions = { 1, 1, -1, -1, 1, -1, -1, 1, 1, 1, 1, -1, -1, 1, 1, 1, 1, 1, 1, -1, 1, 1, 1, 1, -1, 1, 1, 1, -1, 1, -1, 1, 1, -1, -1, 1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 1, 1, 1, -1, 1, -1, -1, -1, -1, 1, -1, 1, 1, -1, -1, -1, -1, 1, 1, -1, 1, -1, -1 }; //[-1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, 1, 1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1, 1, -1, -1, 1, 1, -1, -1, -1, 1, -1, -1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, -1, 1, -1, 1, 1, -1]//[-1,-1,-1, -1,-1, 1, -1, 1, 1,   1, 1,-1, -1,-1,-1, -1, 1,-1,   1,-1, 1, -1,-1,-1, 1,-1,-1,   1, 1,-1, 1,-1,-1, -1,-1,-1, -1,-1,-1, -1, 1, 1, -1, 1,-1, 1,-1, 1, -1,-1, 1, -1,-1,-1, -1, 1, 1, -1,-1, 1, 1,-1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1,-1, 1, 1, 1, 1,-1, 1, 1, 1, 1, 1, 1,-1, -1, 1,-1, 1, 1, 1, -1, 1,-1, -1, 1, 1, 1, 1, 1, -1, 1, 1, 1,-1, 1};
		vector<float> test_pos = { 0.338895, 0.188425, 0.338895, 0.338895, 0.188425, -0.338895, 0.338895, 2.777286, -0.338895, 0.338895, 0.188425, 0.338895, 0.338895, 2.777286, -0.338895, 0.338895, 2.777286, 0.338895, 1, -1, 1, 0.338895, 0.188425, 0.338895, -0.338895, 0.188425, 0.338895, 1, -1, 1, -0.338895, 0.188425, 0.338895, -1, -1, 1, -1, -1, 1, -0.338895, 0.188425, 0.338895, -0.338895, 0.188425, -0.338895, -1, -1, 1, -0.338895, 0.188425, -0.338895, -1, -1, -1, -1, -1, -1, 1, -1, -1, 0.549299, -1.583461, -0.549299, -1, -1, -1, 0.549299, -1.583461, -0.549299, -0.549299, -1.583461, -0.549299, 1, -1, -1, 0.338895, 0.188425, -0.338895, 0.338895, 0.188425, 0.338895, 1, -1, -1, 0.338895, 0.188425, 0.338895, 1, -1, 1, -1, -1, -1, -0.338895, 0.188425, -0.338895, 0.338895, 0.188425, -0.338895, -1, -1, -1, 0.338895, 0.188425, -0.338895, 1, -1, -1, -0.338895, 2.777286, -0.338895, -0.338895, 2.777286, 0.338895, -0.169716, 2.777286, 0.169716, -0.338895, 2.777286, -0.338895, -0.169716, 2.777286, 0.169716, -0.169716, 2.777286, -0.169716, 0.338895, 0.188425, -0.338895, -0.338895, 0.188425, -0.338895, -0.338895, 2.777286, -0.338895, 0.338895, 0.188425, -0.338895, -0.338895, 2.777286, -0.338895, 0.338895, 2.777286, -0.338895, -0.338895, 0.188425, 0.338895, 0.338895, 0.188425, 0.338895, 0.338895, 2.777286, 0.338895, -0.338895, 0.188425, 0.338895, 0.338895, 2.777286, 0.338895, -0.338895, 2.777286, 0.338895, -0.338895, 0.188425, -0.338895, -0.338895, 0.188425, 0.338895, -0.338895, 2.777286, 0.338895, -0.338895, 0.188425, -0.338895, -0.338895, 2.777286, 0.338895, -0.338895, 2.777286, -0.338895, 0.169716, 3.288299, -0.169716, -0.169716, 3.288299, -0.169716, -0.169716, 3.799312, -0.169716, 0.169716, 3.288299, -0.169716, -0.169716, 3.799312, -0.169716, 0.169716, 3.799312, -0.169716, -0.338895, 2.777286, 0.338895, 0.338895, 2.777286, 0.338895, 0.169716, 2.777286, 0.169716, -0.338895, 2.777286, 0.338895, 0.169716, 2.777286, 0.169716, -0.169716, 2.777286, 0.169716, 0.338895, 2.777286, -0.338895, -0.338895, 2.777286, -0.338895, -0.169716, 2.777286, -0.169716, 0.338895, 2.777286, -0.338895, -0.169716, 2.777286, -0.169716, 0.169716, 2.777286, -0.169716, 0.338895, 2.777286, 0.338895, 0.338895, 2.777286, -0.338895, 0.169716, 2.777286, -0.169716, 0.338895, 2.777286, 0.338895, 0.169716, 2.777286, -0.169716, 0.169716, 2.777286, 0.169716, 0.169716, 3.799312, 0.169716, 0.169716, 3.799312, -0.169716, 0.169716, 6.133103, -0.169716, 0.169716, 3.799312, 0.169716, 0.169716, 6.133103, -0.169716, 0.169716, 6.133103, 0.169716, 0.169716, 3.799312, -0.169716, 0.169716, 3.799312, 0.169716, 2.855141, 3.799312, 0.169716, 0.169716, 3.799312, -0.169716, 2.855141, 3.799312, 0.169716, 2.855141, 3.799312, -0.169716, -0.169716, 3.288299, -0.169716, -0.169716, 3.288299, 0.169716, -0.169716, 3.799312, 0.169716, -0.169716, 3.288299, -0.169716, -0.169716, 3.799312, 0.169716, -0.169716, 3.799312, -0.169716, -0.169716, 3.288299, 0.169716, 0.169716, 3.288299, 0.169716, 0.169716, 3.288299, 3.672321, -0.169716, 3.288299, 0.169716, 0.169716, 3.288299, 3.672321, -0.169716, 3.288299, 3.672321, -0.169716, 2.777286, 0.169716, 0.169716, 2.777286, 0.169716, 0.169716, 3.288299, 0.169716, -0.169716, 2.777286, 0.169716, 0.169716, 3.288299, 0.169716, -0.169716, 3.288299, 0.169716, -0.169716, 2.777286, -0.169716, -0.169716, 2.777286, 0.169716, -0.169716, 3.288299, 0.169716, -0.169716, 2.777286, -0.169716, -0.169716, 3.288299, 0.169716, -0.169716, 3.288299, -0.169716, 0.169716, 2.777286, 0.169716, 0.169716, 2.777286, -0.169716, 0.169716, 3.288299, -0.169716, 0.169716, 2.777286, 0.169716, 0.169716, 3.288299, -0.169716, 0.169716, 3.288299, 0.169716, 0.169716, 2.777286, -0.169716, -0.169716, 2.777286, -0.169716, -0.169716, 3.288299, -0.169716, 0.169716, 2.777286, -0.169716, -0.169716, 3.288299, -0.169716, 0.169716, 3.288299, -0.169716, 2.855141, 3.288299, 0.169716, 2.855141, 3.288299, -0.169716, 3.302497, 3.121528, -0.28049, 2.855141, 3.288299, 0.169716, 3.302497, 3.121528, -0.28049, 3.302497, 3.121528, 0.28049, 0.169716, 3.799312, 0.169716, 0.169716, 3.288299, 0.169716, 2.855141, 3.288299, 0.169716, 0.169716, 3.799312, 0.169716, 2.855141, 3.288299, 0.169716, 2.855141, 3.799312, 0.169716, 0.169716, 3.288299, -0.169716, 0.169716, 3.799312, -0.169716, 2.855141, 3.799312, -0.169716, 0.169716, 3.288299, -0.169716, 2.855141, 3.799312, -0.169716, 2.855141, 3.288299, -0.169716, 0.169716, 3.288299, 0.169716, 0.169716, 3.288299, -0.169716, 2.855141, 3.288299, -0.169716, 0.169716, 3.288299, 0.169716, 2.855141, 3.288299, -0.169716, 2.855141, 3.288299, 0.169716, 0.169716, 3.288299, 3.672321, 0.169716, 3.799312, 3.672321, 0.246526, 3.914951, 3.873332, 0.169716, 3.288299, 3.672321, 0.246526, 3.914951, 3.873332, 0.246526, 3.17266, 3.873332, 0.169716, 3.288299, 0.169716, 0.169716, 3.799312, 0.169716, 0.169716, 3.799312, 3.672321, 0.169716, 3.288299, 0.169716, 0.169716, 3.799312, 3.672321, 0.169716, 3.288299, 3.672321, 0.169716, 3.799312, 0.169716, -0.169716, 3.799312, 0.169716, -0.169716, 3.799312, 3.672321, 0.169716, 3.799312, 0.169716, -0.169716, 3.799312, 3.672321, 0.169716, 3.799312, 3.672321, -0.169716, 3.799312, 0.169716, -0.169716, 3.288299, 0.169716, -0.169716, 3.288299, 3.672321, -0.169716, 3.799312, 0.169716, -0.169716, 3.288299, 3.672321, -0.169716, 3.799312, 3.672321, -0.169716, 6.133103, -0.169716, -0.169716, 6.133103, 0.169716, -0.37321, 6.376593, 0.37321, -0.169716, 6.133103, -0.169716, -0.37321, 6.376593, 0.37321, -0.37321, 6.376593, -0.37321, -0.169716, 3.799312, -0.169716, -0.169716, 3.799312, 0.169716, -0.169716, 6.133103, 0.169716, -0.169716, 3.799312, -0.169716, -0.169716, 6.133103, 0.169716, -0.169716, 6.133103, -0.169716, -0.169716, 3.799312, 0.169716, 0.169716, 3.799312, 0.169716, 0.169716, 6.133103, 0.169716, -0.169716, 3.799312, 0.169716, 0.169716, 6.133103, 0.169716, -0.169716, 6.133103, 0.169716, 0.169716, 3.799312, -0.169716, -0.169716, 3.799312, -0.169716, -0.169716, 6.133103, -0.169716, 0.169716, 3.799312, -0.169716, -0.169716, 6.133103, -0.169716, 0.169716, 6.133103, -0.169716, 0.37321, 6.376593, -0.37321, -0.37321, 6.376593, -0.37321, -0.103801, 6.938471, -0.103801, 0.37321, 6.376593, -0.37321, -0.103801, 6.938471, -0.103801, 0.103801, 6.938471, -0.103801, -0.169716, 6.133103, 0.169716, 0.169716, 6.133103, 0.169716, 0.37321, 6.376593, 0.37321, -0.169716, 6.133103, 0.169716, 0.37321, 6.376593, 0.37321, -0.37321, 6.376593, 0.37321, 0.169716, 6.133103, -0.169716, -0.169716, 6.133103, -0.169716, -0.37321, 6.376593, -0.37321, 0.169716, 6.133103, -0.169716, -0.37321, 6.376593, -0.37321, 0.37321, 6.376593, -0.37321, 0.169716, 6.133103, 0.169716, 0.169716, 6.133103, -0.169716, 0.37321, 6.376593, -0.37321, 0.169716, 6.133103, 0.169716, 0.37321, 6.376593, -0.37321, 0.37321, 6.376593, 0.37321, 0.103801, 6.938471, -0.103801, -0.103801, 6.938471, -0.103801, -0.103801, 6.938471, 0.103801, 0.103801, 6.938471, -0.103801, -0.103801, 6.938471, 0.103801, 0.103801, 6.938471, 0.103801, 0.37321, 6.376593, 0.37321, 0.37321, 6.376593, -0.37321, 0.103801, 6.938471, -0.103801, 0.37321, 6.376593, 0.37321, 0.103801, 6.938471, -0.103801, 0.103801, 6.938471, 0.103801, -0.37321, 6.376593, -0.37321, -0.37321, 6.376593, 0.37321, -0.103801, 6.938471, 0.103801, -0.37321, 6.376593, -0.37321, -0.103801, 6.938471, 0.103801, -0.103801, 6.938471, -0.103801, -0.37321, 6.376593, 0.37321, 0.37321, 6.376593, 0.37321, 0.103801, 6.938471, 0.103801, -0.37321, 6.376593, 0.37321, 0.103801, 6.938471, 0.103801, -0.103801, 6.938471, 0.103801, 0.246526, 3.914951, 3.873332, -0.246526, 3.914951, 3.873332, -0.042408, 3.607651, 4.63741, 0.246526, 3.914951, 3.873332, -0.042408, 3.607651, 4.63741, 0.042408, 3.607651, 4.63741, 0.169716, 3.799312, 3.672321, -0.169716, 3.799312, 3.672321, -0.246526, 3.914951, 3.873332, 0.169716, 3.799312, 3.672321, -0.246526, 3.914951, 3.873332, 0.246526, 3.914951, 3.873332, -0.169716, 3.288299, 3.672321, 0.169716, 3.288299, 3.672321, 0.246526, 3.17266, 3.873332, -0.169716, 3.288299, 3.672321, 0.246526, 3.17266, 3.873332, -0.246526, 3.17266, 3.873332, -0.169716, 3.799312, 3.672321, -0.169716, 3.288299, 3.672321, -0.246526, 3.17266, 3.873332, -0.169716, 3.799312, 3.672321, -0.246526, 3.17266, 3.873332, -0.246526, 3.914951, 3.873332, -0.042408, 3.47996, 4.63741, 0.042408, 3.47996, 4.63741, 0.042408, 3.607651, 4.63741, -0.042408, 3.47996, 4.63741, 0.042408, 3.607651, 4.63741, -0.042408, 3.607651, 4.63741, -0.246526, 3.17266, 3.873332, 0.246526, 3.17266, 3.873332, 0.042408, 3.47996, 4.63741, -0.246526, 3.17266, 3.873332, 0.042408, 3.47996, 4.63741, -0.042408, 3.47996, 4.63741, -0.246526, 3.914951, 3.873332, -0.246526, 3.17266, 3.873332, -0.042408, 3.47996, 4.63741, -0.246526, 3.914951, 3.873332, -0.042408, 3.47996, 4.63741, -0.042408, 3.607651, 4.63741, 0.246526, 3.17266, 3.873332, 0.246526, 3.914951, 3.873332, 0.042408, 3.607651, 4.63741, 0.246526, 3.17266, 3.873332, 0.042408, 3.607651, 4.63741, 0.042408, 3.47996, 4.63741, 3.302497, 3.966084, 0.28049, 3.302497, 3.121528, 0.28049, 5.085871, 3.401694, 0.094395, 3.302497, 3.966084, 0.28049, 5.085871, 3.401694, 0.094395, 5.085871, 3.685917, 0.094395, 2.855141, 3.288299, -0.169716, 2.855141, 3.799312, -0.169716, 3.302497, 3.966084, -0.28049, 2.855141, 3.288299, -0.169716, 3.302497, 3.966084, -0.28049, 3.302497, 3.121528, -0.28049, 2.855141, 3.799312, 0.169716, 2.855141, 3.288299, 0.169716, 3.302497, 3.121528, 0.28049, 2.855141, 3.799312, 0.169716, 3.302497, 3.121528, 0.28049, 3.302497, 3.966084, 0.28049, 2.855141, 3.799312, -0.169716, 2.855141, 3.799312, 0.169716, 3.302497, 3.966084, 0.28049, 2.855141, 3.799312, -0.169716, 3.302497, 3.966084, 0.28049, 3.302497, 3.966084, -0.28049, 5.085871, 3.401694, 0.094395, 5.085871, 3.401694, -0.094395, 5.085871, 3.685917, -0.094395, 5.085871, 3.401694, 0.094395, 5.085871, 3.685917, -0.094395, 5.085871, 3.685917, 0.094395, 3.302497, 3.966084, -0.28049, 3.302497, 3.966084, 0.28049, 5.085871, 3.685917, 0.094395, 3.302497, 3.966084, -0.28049, 5.085871, 3.685917, 0.094395, 5.085871, 3.685917, -0.094395, 3.302497, 3.121528, 0.28049, 3.302497, 3.121528, -0.28049, 5.085871, 3.401694, -0.094395, 3.302497, 3.121528, 0.28049, 5.085871, 3.401694, -0.094395, 5.085871, 3.401694, 0.094395, 3.302497, 3.121528, -0.28049, 3.302497, 3.966084, -0.28049, 5.085871, 3.685917, -0.094395, 3.302497, 3.121528, -0.28049, 5.085871, 3.685917, -0.094395, 5.085871, 3.401694, -0.094395, -0.549299, -1.583461, -0.549299, 0.549299, -1.583461, -0.549299, 0.549299, -1.583461, 0.549299, -0.549299, -1.583461, -0.549299, 0.549299, -1.583461, 0.549299, -0.549299, -1.583461, 0.549299, 1, -1, 1, -1, -1, 1, -0.549299, -1.583461, 0.549299, 1, -1, 1, -0.549299, -1.583461, 0.549299, 0.549299, -1.583461, 0.549299, -1, -1, 1, -1, -1, -1, -0.549299, -1.583461, -0.549299, -1, -1, 1, -0.549299, -1.583461, -0.549299, -0.549299, -1.583461, 0.549299, 1, -1, -1, 1, -1, 1, 0.549299, -1.583461, 0.549299, 1, -1, -1, 0.549299, -1.583461, 0.549299, 0.549299, -1.583461, -0.549299 };
		vector<float> normals = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1 };
		vector<float> test_norms = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0.4861, 0.8739, 0, 0.4861, 0.8739, 0, 0.4861, 0.8739, 0, 0.4861, 0.8739, 0, 0.4861, 0.8739, 0, 0.4861, 0.8739, -0.8739, 0.4861, 0, -0.8739, 0.4861, 0, -0.8739, 0.4861, 0, -0.8739, 0.4861, 0, -0.8739, 0.4861, 0, -0.8739, 0.4861, 0, 0, -0.6113, -0.7914, 0, -0.6113, -0.7914, 0, -0.6113, -0.7914, 0, -0.6113, -0.7914, 0, -0.6113, -0.7914, 0, -0.6113, -0.7914, 0.8739, 0.4861, 0, 0.8739, 0.4861, 0, 0.8739, 0.4861, 0, 0.8739, 0.4861, 0, 0.8739, 0.4861, 0, 0.8739, 0.4861, 0, 0, 0.4861, -0.8739, 0, 0.4861, -0.8739, 0, 0.4861, -0.8739, 0, 0.4861, -0.8739, 0, 0.4861, -0.8739, 0, 0.4861, -0.8739, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, -0.3493, -0.937, 0, -0.3493, -0.937, 0, -0.3493, -0.937, 0, -0.3493, -0.937, 0, -0.3493, -0.937, 0, -0.3493, -0.937, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0.9341, 0, -0.3569, 0.9341, 0, -0.3569, 0.9341, 0, -0.3569, 0.9341, 0, -0.3569, 0.9341, 0, -0.3569, 0.9341, 0, -0.3569, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -0.7673, -0.6413, 0, -0.7673, -0.6413, 0, -0.7673, -0.6413, 0, -0.7673, -0.6413, 0, -0.7673, -0.6413, 0, -0.7673, -0.6413, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0.4323, -0.9017, 0, 0.4323, -0.9017, 0, 0.4323, -0.9017, 0, 0.4323, -0.9017, 0, 0.4323, -0.9017, 0, 0.4323, -0.9017, 0, -0.6413, 0.7673, 0, -0.6413, 0.7673, 0, -0.6413, 0.7673, 0, -0.6413, 0.7673, 0, -0.6413, 0.7673, 0, -0.6413, 0.7673, 0, -0.6413, -0.7673, 0, -0.6413, -0.7673, 0, -0.6413, -0.7673, 0, -0.6413, -0.7673, 0, -0.6413, -0.7673, 0, -0.6413, -0.7673, 0.7673, -0.6413, 0, 0.7673, -0.6413, 0, 0.7673, -0.6413, 0, 0.7673, -0.6413, 0, 0.7673, -0.6413, 0, 0.7673, -0.6413, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0.9017, 0.4323, 0, 0.9017, 0.4323, 0, 0.9017, 0.4323, 0, 0.9017, 0.4323, 0, 0.9017, 0.4323, 0, 0.9017, 0.4323, 0, -0.9017, 0.4323, 0, -0.9017, 0.4323, 0, -0.9017, 0.4323, 0, -0.9017, 0.4323, 0, -0.9017, 0.4323, 0, -0.9017, 0.4323, 0, 0, 0.4323, 0.9017, 0, 0.4323, 0.9017, 0, 0.4323, 0.9017, 0, 0.4323, 0.9017, 0, 0.4323, 0.9017, 0, 0.4323, 0.9017, 0, 0.9278, 0.3731, 0, 0.9278, 0.3731, 0, 0.9278, 0.3731, 0, 0.9278, 0.3731, 0, 0.9278, 0.3731, 0, 0.9278, 0.3731, 0, 0.8668, -0.4987, 0, 0.8668, -0.4987, 0, 0.8668, -0.4987, 0, 0.8668, -0.4987, 0, 0.8668, -0.4987, 0, 0.8668, -0.4987, 0, -0.8668, -0.4987, 0, -0.8668, -0.4987, 0, -0.8668, -0.4987, 0, -0.8668, -0.4987, 0, -0.8668, -0.4987, 0, -0.8668, -0.4987, -0.9341, 0, -0.3569, -0.9341, 0, -0.3569, -0.9341, 0, -0.3569, -0.9341, 0, -0.3569, -0.9341, 0, -0.3569, -0.9341, 0, -0.3569, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, -0.9278, 0.3731, 0, -0.9278, 0.3731, 0, -0.9278, 0.3731, 0, -0.9278, 0.3731, 0, -0.9278, 0.3731, 0, -0.9278, 0.3731, -0.9661, 0, 0.2581, -0.9661, 0, 0.2581, -0.9661, 0, 0.2581, -0.9661, 0, 0.2581, -0.9661, 0, 0.2581, -0.9661, 0, 0.2581, 0.9661, 0, 0.2581, 0.9661, 0, 0.2581, 0.9661, 0, 0.2581, 0.9661, 0, 0.2581, 0.9661, 0, 0.2581, 0.9661, 0, 0.2581, 0.1038, 0, 0.9946, 0.1038, 0, 0.9946, 0.1038, 0, 0.9946, 0.1038, 0, 0.9946, 0.1038, 0, 0.9946, 0.1038, 0, 0.9946, -0.2404, 0, -0.9707, -0.2404, 0, -0.9707, -0.2404, 0, -0.9707, -0.2404, 0, -0.9707, -0.2404, 0, -0.9707, -0.2404, 0, -0.9707, -0.2404, 0, 0.9707, -0.2404, 0, 0.9707, -0.2404, 0, 0.9707, -0.2404, 0, 0.9707, -0.2404, 0, 0.9707, -0.2404, 0, 0.9707, -0.3493, 0.937, 0, -0.3493, 0.937, 0, -0.3493, 0.937, 0, -0.3493, 0.937, 0, -0.3493, 0.937, 0, -0.3493, 0.937, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0.1552, 0.9879, 0, 0.1552, 0.9879, 0, 0.1552, 0.9879, 0, 0.1552, 0.9879, 0, 0.1552, 0.9879, 0, 0.1552, 0.9879, 0, 0.1552, -0.9879, 0, 0.1552, -0.9879, 0, 0.1552, -0.9879, 0, 0.1552, -0.9879, 0, 0.1552, -0.9879, 0, 0.1552, -0.9879, 0, 0.1038, 0, -0.9946, 0.1038, 0, -0.9946, 0.1038, 0, -0.9946, 0.1038, 0, -0.9946, 0.1038, 0, -0.9946, 0.1038, 0, -0.9946, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -0.6113, 0.7914, 0, -0.6113, 0.7914, 0, -0.6113, 0.7914, 0, -0.6113, 0.7914, 0, -0.6113, 0.7914, 0, -0.6113, 0.7914, -0.7914, -0.6113, 0, -0.7914, -0.6113, 0, -0.7914, -0.6113, 0, -0.7914, -0.6113, 0, -0.7914, -0.6113, 0, -0.7914, -0.6113, 0, 0.7914, -0.6113, 0, 0.7914, -0.6113, 0, 0.7914, -0.6113, 0, 0.7914, -0.6113, 0, 0.7914, -0.6113, 0, 0.7914, -0.6113, 0 };
		vector<float> uvCoords = {};
		vector<float> uv_test = {};

		Mesh am = Mesh(positions, test_norms, uvCoords);

};

