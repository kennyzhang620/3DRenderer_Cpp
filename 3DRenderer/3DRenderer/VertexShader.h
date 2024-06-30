#pragma once
#include "Camera.h"
#include <math.h>
#include "MatrixMxN.h"
#include "Global_Stack.h"

#define PROJECT_PERSPECTIVE 0
#define PROJECT_ORTHO 1

// Takes triangle strip and function pointer to FragShader and rasterize.
void Rasterizer(Renderer3D& renderer, int xCoords, int yCoords, priority_queue<Triangle, vector<Triangle>, std::greater<Triangle>>& tris) {
	//renderer.setCanvas(xCoords, yCoords);

	renderer.ClearPixels();
	// Sort by z-index and rasterize by distance.

	while (tris.size() > 0) {
		int maxS = tris.size() - 1;
	//	renderer.RenderTris(tris.front(), tris.front().FragShader, tris.front().fparms);
		tris.pop();
	}

	renderer.displayImage(xCoords, yCoords);
	//renderer.deleteImage();

}


void Rasterizer_MT(Renderer3D& renderer, priority_queue <Triangle, vector<Triangle>, std::greater<Triangle>>& tris) {
	renderer.setCanvas(854, 480);

	// Sort by z-index and rasterize by distance.
	while (tris.size() > 0) {
		int maxS = tris.size() - 1;
	//	renderer.MultiThreadedRenderTris(tris.front());
		tris.pop();
	}
}

void SetProjMatrix(float fov, float width, float height, float nearP, float farP, float params[]) {
	float aspect = ((float)(width/ (height + 0.0f)));
	float top = tan(radians(fov)*0.5f) * nearP;
	float bottom = -top;
	float left = -top * aspect;
	float right = top * aspect;
	
	params[0] = top; //t
	params[1] = aspect * top; //r
	params[2] = -params[1]; //l
	params[3] = -top; //b
	params[4] = nearP;
	params[5] = farP;
}

void SetOthoMatrix(float width, float height, VectorCoords maxV, VectorCoords minV, float nearP, float farP, float params[]) {
	float aspect = ((float)(width / (height + 0.0f)));
	float top = max(max(minV.x, maxV.x), max(minV.y, maxV.y));
	float bottom = -top;
	float left = -top * aspect;
	float right = top * aspect;

	params[0] = top; //t
	params[1] = aspect * top; //r
	params[2] = -params[1]; //l
	params[3] = -top; //b
	params[4] = nearP;
	params[5] = farP;
}


VectorCoords Vector_IntersectPlane(VectorCoords& plane_p, VectorCoords& plane_n, VectorCoords& lineStart, VectorCoords& lineEnd) {
	plane_n.normalize();
	float plane_d = -plane_n.dotProduct(plane_p);
	float ad = lineStart.dotProduct(plane_n);
	float bd = lineEnd.dotProduct(plane_n);
	float t = (-plane_d - ad) / (bd - ad);
	VectorCoords lineStartEnd = VectorCoords(lineEnd.x - lineStart.x, lineEnd.y - lineStart.y, lineEnd.z - lineStart.z);
	VectorCoords intersectLine = VectorCoords(t * lineStartEnd.x, t * lineStartEnd.y, t * lineStartEnd.z);
	return VectorCoords(lineStart.x + intersectLine.x, lineStart.y + intersectLine.y, lineStart.z + intersectLine.z);

}

int Triangle_ClipAgainstPlane(VectorCoords plane_p, VectorCoords plane_n, Triangle& in_tri, Triangle& out_tri1, Triangle& out_tri2) {

	plane_n.normalize();

	auto dist = [&](VectorCoords& p)
	{
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - plane_n.dotProduct(plane_p));
	};

	VectorCoords* inside_points[3];  int nInsidePointCount = 0;
	VectorCoords* outside_points[3]; int nOutsidePointCount = 0;

	// Get signed distance of each point in triangle to plane
	float d0 = dist(in_tri.v1);
	float d1 = dist(in_tri.v2);
	float d2 = dist(in_tri.v3);

	if (d0 >= 0) { inside_points[nInsidePointCount++] = &in_tri.v1; }
	else { outside_points[nOutsidePointCount++] = &in_tri.v1; }
	if (d1 >= 0) { inside_points[nInsidePointCount++] = &in_tri.v2; }
	else { outside_points[nOutsidePointCount++] = &in_tri.v2; }
	if (d2 >= 0) { inside_points[nInsidePointCount++] = &in_tri.v3; }
	else { outside_points[nOutsidePointCount++] = &in_tri.v3; }

	if (nInsidePointCount == 0)
	{
		// All points lie on the outside of plane, so clip whole triangle
		// It ceases to exist

		return 0; // No returned triangles are valid
	}

	if (nInsidePointCount == 3)
	{
		// All points lie on the inside of plane, so do nothing
		// and allow the triangle to simply pass through
		out_tri1 = in_tri;

		return 1; // Just the one returned original triangle is valid
	}

	if (nInsidePointCount == 1 && nOutsidePointCount == 2)
	{
		// Triangle should be clipped. As two points lie outside
		// the plane, the triangle simply becomes a smaller triangle

		// Copy appearance info to new triangle
		out_tri1.FragMaterial = in_tri.FragMaterial; //in_tri.FragShader;
		out_tri1.z_index = in_tri.z_index;


		// The inside point is valid, so keep that...
		out_tri1.v1 = *inside_points[0];

		// but the two new points are at the locations where the 
		// original sides of the triangle (lines) intersect with the plane
		out_tri1.v2 = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
		out_tri1.v3 = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

		return 1; // Return the newly formed single triangle
	}

	if (nInsidePointCount == 2 && nOutsidePointCount == 1)
	{
		// Triangle should be clipped. As two points lie inside the plane,
		// the clipped triangle becomes a "quad". Fortunately, we can
		// represent a quad with two new triangles

		// Copy appearance info to new triangles
		out_tri1.FragMaterial = in_tri.FragMaterial;
		out_tri1.z_index = in_tri.z_index;

		out_tri2.FragMaterial = in_tri.FragMaterial;//in_tri.FragShader;
		out_tri2.z_index = in_tri.z_index;

		// The first triangle consists of the two inside points and a new
		// point determined by the location where one side of the triangle
		// intersects with the plane
		out_tri1.v1 = *inside_points[0];
		out_tri1.v2 = *inside_points[1];
		out_tri1.v3 = Vector_IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]); 

		// The second triangle is composed of one of he inside points, a
		// new point determined by the intersection of the other side of the 
		// triangle and the plane, and the newly created point above
		out_tri2.v1 = *inside_points[1];
		out_tri2.v2 = out_tri1.v3;
		out_tri2.v3 = Vector_IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

		return 2; // Return two newly formed triangles which form a quad
	}
}

void ClearTrisBuffer() {
	while (!tris.empty()) {
		tris.pop();
	}
}

// Set up a camera and project into view space from cam point. Either write the new changes directly to Tbuffer or into image texture
void CameraSetup(int xCoords, int yCoords, Camera camera, float nearPlane, float farPlane, int ProjectMode) {
	MatrixMxN<float> cam(4, 4);
	MatrixMxN<float> rot(4, 4);
	cam.ViewMatrix(VectorCoords(camera.xPos, camera.yPos, camera.zPos), camera.yRot, camera.xRot);
	cam.res_to_matrix();

	// [Tv][Ryv][Sv]
	// [Vm][Mm]

	// [Proj][Vm][Mm]

	float projectparams[] = { 0,0,0,0,0,0 };

	if (ProjectMode == PROJECT_PERSPECTIVE) {
		SetProjMatrix(90, xCoords, yCoords, nearPlane, farPlane, projectparams);
		rot.ProjectPerspective(projectparams[2], projectparams[1], projectparams[0], projectparams[3], projectparams[5], projectparams[4]);
	}
	if (ProjectMode == PROJECT_ORTHO) {
		SetOthoMatrix(xCoords, yCoords, VectorCoords(farPlane, farPlane, farPlane), VectorCoords(nearPlane, nearPlane, nearPlane), nearPlane, farPlane, projectparams);
		rot.ProjectOrtho(projectparams[2], projectparams[1], projectparams[0], projectparams[3], projectparams[5], projectparams[4]);
	}
	rot.res_to_matrix();

	renderer.setCounter();
	PolyCount = 0;
	int sizeQ = tris.size();

	for (sizeQ = tris.size(); sizeQ >= 0; sizeQ--) {
		VectorCoords v1n = cam.matmul_vtr(tris.front().v1);
		VectorCoords v2n = cam.matmul_vtr(tris.front().v2);
		VectorCoords v3n = cam.matmul_vtr(tris.front().v3);

		Material* mat = tris.front().FragMaterial;

		int clippedTris = 0;
		Triangle clipped[2];

		Triangle viewT(v1n, v2n, v3n);
		clippedTris = Triangle_ClipAgainstPlane(VectorCoords(0, 0, nearPlane, 1), VectorCoords(0, 0, farPlane, 1), viewT, clipped[0], clipped[1]);
		
		if (clippedTris > 0) {
			int i = 0;

			for (i = 0; i < clippedTris; i++) {
				v1n = rot.matmul_vtr(clipped[i].v1);
				v2n = rot.matmul_vtr(clipped[i].v2);
				v3n = rot.matmul_vtr(clipped[i].v3);

				PolyCount++;
				if (v1n.w != 1 && v1n.w != 0) {
					v1n.x /= v1n.w;
					v1n.y /= v1n.w;
					v1n.z /= v1n.w;
				}

				if (v2n.w != 1 && v2n.w != 0) {
					v2n.x /= v2n.w;
					v2n.y /= v2n.w;
					v2n.z /= v2n.w;


				}

				if (v3n.w != 1 && v3n.w != 0) {
					v3n.x /= v3n.w;
					v3n.y /= v3n.w;
					v3n.z /= v3n.w;


				}

				v1n.x = ((v1n.x + 1) / 2.0f) * xCoords;
				v1n.y = ((v1n.y + 1) / 2.0f) * yCoords;
				v2n.x = ((v2n.x + 1) / 2.0f) * xCoords;
				v2n.y = ((v2n.y + 1) / 2.0f) * yCoords;
				v3n.x = ((v3n.x + 1) / 2.0f) * xCoords;
				v3n.y = ((v3n.y + 1) / 2.0f) * yCoords;


				// convert to raster space and mark the position of the vertex in the image with a simple dot

				Triangle worldTris(v1n, v2n, v3n, mat);
				renderer.RenderTris(worldTris, mat);

			}
		}
		tris.push(tris.front());
		tris.pop();
	}
	renderer.ClearPixels(renderer.Interlace != Interlace);
	renderer.Interlace = Interlace;
	renderer.displayImage(xCoords, yCoords, scaleFactor, NEAREST_NEIGHBOR);
}

void MeshTransform(Mesh mesh, Transform trans, Material* mat) {
	// Converts model space to world space coordinates (applys model transforms and projects to world)
	// Assign each triangle its associated fragment (pixel) shader.
	queue<Triangle>& triangleCollection = tris;
	MatrixMxN<float> scale(4, 4);
	MatrixMxN<float> rot(4, 4);
	scale.Scale3D(trans.xScale, trans.yScale, trans.zScale);
	scale.res_to_matrix();
	rot.RotateZ(trans.zRot);
	rot.res_to_matrix();
	rot.matmul(scale);
	rot.res_to_matrix();
	scale.RotateY(trans.yRot);
	scale.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();
	rot.RotateX(trans.xRot);
	rot.res_to_matrix();
	rot.matmul(scale);
	rot.res_to_matrix();

	scale.Translate3D(trans.xPos, trans.yPos, trans.zPos);
	scale.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();

	// NOTE! scale is the model -> world space matrix
	int i = 0;
	std::mutex tc;
#pragma omp parallel for private(i)
	for (i = 0; i < mesh.MeshCoords.size(); i++) {
		VectorCoords v1n = scale.matmul_vtr(mesh.MeshCoords[i].v1);
		VectorCoords v2n = scale.matmul_vtr(mesh.MeshCoords[i].v2);
		VectorCoords v3n = scale.matmul_vtr(mesh.MeshCoords[i].v3);

		Triangle worldTris(v1n, v2n, v3n, mat);
		std::lock_guard<std::mutex> guard(tc);
		triangleCollection.push(worldTris);
	}

}


// Vertex shader
void ProjectMesh(int xCoords, int yCoords, float nearPlane, float farPlane, int ProjectMode, Mesh mesh, Transform trans, Camera camera, priority_queue<Triangle, vector<Triangle>, std::greater<Triangle>>& triangleCollection, VectorCoords(*FragShader)(const float[], const float[]), float* parms = nullptr) {
	// Converts model space to world space coordinates (applys model transforms and projects to world)
	// Assign each triangle its associated fragment (pixel) shader.
	MatrixMxN<float> scale(4, 4);
	MatrixMxN<float> rot(4, 4);
	scale.Scale3D(trans.xScale, trans.yScale, trans.zScale);
	scale.res_to_matrix();
	rot.RotateZ(trans.zRot);
	rot.res_to_matrix();
	rot.matmul(scale);
	rot.res_to_matrix();
	scale.RotateY(trans.yRot);
	scale.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();
	rot.RotateX(trans.xRot);
	rot.res_to_matrix();
	rot.matmul(scale);
	rot.res_to_matrix();

	scale.Translate3D(trans.xPos, trans.yPos, trans.zPos);
	scale.res_to_matrix();
	scale.matmul(rot);
	scale.res_to_matrix();

	// NOTE! scale is the model -> world space matrix

	MatrixMxN<float> cam(4, 4);
	cam.ViewMatrix(VectorCoords(camera.xPos, camera.yPos, camera.zPos), camera.yRot, camera.xRot);
	cam.res_to_matrix();

	// [Tv][Ryv][Sv]
	// [Vm][Mm]

	// [Proj][Vm][Mm]

	cam.matmul(scale);
	cam.res_to_matrix();

	float projectparams[] = {0,0,0,0,0,0};

	if (ProjectMode == PROJECT_PERSPECTIVE) {
		SetProjMatrix(90, xCoords, yCoords, nearPlane, farPlane, projectparams);
		rot.ProjectPerspective(projectparams[2], projectparams[1], projectparams[0], projectparams[3], projectparams[5], projectparams[4]);
	}
	if (ProjectMode == PROJECT_ORTHO) {
		SetOthoMatrix(xCoords, yCoords, VectorCoords(8,8,8), VectorCoords(0, 0, 0), nearPlane, farPlane, projectparams);
		rot.ProjectOrtho(projectparams[2], projectparams[1], projectparams[0], projectparams[3], projectparams[5], projectparams[4]);
	}
	rot.res_to_matrix();
	/*
	MatrixMxN<float> cam2(4, 4);
	cam2.ViewMatrix(VectorCoords(camera.xPos, camera.yPos, camera.zPos), camera.yRot, camera.xRot);
	cam2.res_to_matrix();
	SetOthoMatrix(xCoords, yCoords, cam2.matmul_vtr(VectorCoords(1,1,1)), cam2.matmul_vtr(VectorCoords(-1, -1, -1)), 0.01f, 1000, projectparams);
	rot.ProjectOrtho(projectparams[2], projectparams[1], projectparams[0], projectparams[3], projectparams[5], projectparams[4]);
	rot.res_to_matrix();
	*/

	for (int i = 0; i < mesh.MeshCoords.size(); i++) {
		VectorCoords v1n = cam.matmul_vtr(mesh.MeshCoords[i].v1);
		VectorCoords v2n = cam.matmul_vtr(mesh.MeshCoords[i].v2);
		VectorCoords v3n = cam.matmul_vtr(mesh.MeshCoords[i].v3);

		int clippedTris = 0;
		Triangle clipped[2];

		Triangle viewT = Triangle(v1n, v2n, v3n);
		clippedTris = Triangle_ClipAgainstPlane(VectorCoords(0, 0,nearPlane, 0), VectorCoords(0, 0, farPlane, 0), viewT, clipped[0], clipped[1]);

		for (int i = 0; i < clippedTris; i++) {
			v1n = rot.matmul_vtr(clipped[i].v1);
			v2n = rot.matmul_vtr(clipped[i].v2);
			v3n = rot.matmul_vtr(clipped[i].v3);

			if (v1n.w != 1 && v1n.w != 0) {
				v1n.x /= v1n.w;
				v1n.y /= v1n.w;
				v1n.z /= v1n.w;
			}

			if (v2n.w != 1 && v2n.w != 0) {
				v2n.x /= v2n.w;
				v2n.y /= v2n.w;
				v2n.z /= v2n.w;


			}

			if (v3n.w != 1 && v3n.w != 0) {
				v3n.x /= v3n.w;
				v3n.y /= v3n.w;
				v3n.z /= v3n.w;


			}

			v1n.x = ((v1n.x + 1) / 2.0f) * xCoords;
			v1n.y = ((v1n.y + 1) / 2.0f) * yCoords;
			v2n.x = ((v2n.x + 1) / 2.0f) * xCoords;
			v2n.y = ((v2n.y + 1) / 2.0f) * yCoords;
			v3n.x = ((v3n.x + 1) / 2.0f) * xCoords;
			v3n.y = ((v3n.y + 1) / 2.0f) * yCoords;


			// convert to raster space and mark the position of the vertex in the image with a simple dot

		//		Triangle worldTris(v1n, v2n, v3n, FragShader, parms);
			//	triangleCollection.push(worldTris);

		//	

			

		}
		
	}

}