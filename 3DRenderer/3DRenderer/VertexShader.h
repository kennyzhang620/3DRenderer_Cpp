#pragma once
#include "Mesh.h"
// Takes triangle strip and function pointer to FragShader and rasterize.
void Rasterizer(priority_queue<Triangle>& tris, char i = 0) {

	Renderer3D renderer;
	renderer.setCanvas(854, 480);

	// Sort by z-index and rasterize by distance.

	while (tris.size() > 0) {
		int maxS = tris.size() - 1;
		renderer.RenderTris(tris.top(), tris.top().FragShader, tris.top().fparms, i);
		tris.pop();
	}

	renderer.displayImage(854, 480);
	renderer.deleteImage();

}

void Rasterizer_MT(Renderer3D& renderer, priority_queue<Triangle>& tris) {
	renderer.setCanvas(854, 480);

	// Sort by z-index and rasterize by distance.
	while (tris.size() > 0) {
		int maxS = tris.size() - 1;
		renderer.MultiThreadedRenderTris(tris.top());
		tris.pop();
	}
}

// Vertex shader
void ProjectMesh(Mesh mesh, Transform trans, priority_queue<Triangle>& triangleCollection, VectorCoords(*FragShader)(const float[], const float[]), float* parms = nullptr) {
	// Converts model space to world space coordinates (applys model transforms and projects to world)
	// Assign each triangle its associated fragment (pixel) shader.
	MatrixMxN<float> scale(4, 4);
	MatrixMxN<float> rot(4, 4);
	scale.Scale3D(trans.xScale, trans.yScale, trans.zScale);
	scale.res_to_matrix();
	rot.RotateZ(trans.zRot);
	rot.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();
	rot.RotateY(trans.yRot);
	rot.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();
	rot.RotateX(trans.xRot);
	rot.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();


	rot.Translate3D(trans.xPos, trans.yPos, trans.zPos);
	rot.res_to_matrix();
	rot.matmul(scale);
	rot.res_to_matrix();

	for (int i = 0; i < mesh.MeshCoords.size(); i++) {
		VectorCoords v1n = rot.matmul_vtr(mesh.MeshCoords[i].v1);
		VectorCoords v2n = rot.matmul_vtr(mesh.MeshCoords[i].v2);
		VectorCoords v3n = rot.matmul_vtr(mesh.MeshCoords[i].v3);

		Triangle worldTris(v1n, v2n, v3n, FragShader, parms);

		triangleCollection.push(worldTris);

	}

}