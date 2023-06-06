#pragma once
#include "OBJ-Loader/OBJ_Loader.h"
#include "Material.h"
#include "Mesh.h"

void LoadMesh(const char* obj, Mesh& mesh) {
	objl::Loader load;
	bool c = load.LoadFile(obj);

	if (c && load.LoadedVertices.size() % 3 == 0) {
		for (int i = 0; i < load.LoadedVertices.size(); i+=3) {
			VectorCoords x1(load.LoadedVertices[i].Position.X, load.LoadedVertices[i].Position.Y, load.LoadedVertices[i].Position.Z, 1, load.LoadedVertices[i].Normal.X, load.LoadedVertices[i].Normal.Y, load.LoadedVertices[i].Normal.Z, 1, load.LoadedVertices[i].TextureCoordinate.X, load.LoadedVertices[i].TextureCoordinate.Y);
			VectorCoords x2(load.LoadedVertices[i+1].Position.X, load.LoadedVertices[i+1].Position.Y, load.LoadedVertices[i+1].Position.Z, 1, load.LoadedVertices[i+1].Normal.X, load.LoadedVertices[i+1].Normal.Y, load.LoadedVertices[i+1].Normal.Z, 1, load.LoadedVertices[i+1].TextureCoordinate.X, load.LoadedVertices[i+1].TextureCoordinate.Y);
			VectorCoords x3(load.LoadedVertices[i+2].Position.X, load.LoadedVertices[i+2].Position.Y, load.LoadedVertices[i+2].Position.Z, 1, load.LoadedVertices[i+2].Normal.X, load.LoadedVertices[i+2].Normal.Y, load.LoadedVertices[i+2].Normal.Z, 1, load.LoadedVertices[i+2].TextureCoordinate.X, load.LoadedVertices[i+2].TextureCoordinate.Y);
			
			Triangle t1(x1, x2, x3);

			mesh.MeshCoords.push_back(t1);
		}
	}
}