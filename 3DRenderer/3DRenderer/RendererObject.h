#pragma once
#include "GameObject.h"
#include "Material.h"
#include "VertexShader.h"
class RendererObject :
    public GameObject
{
public:
    Mesh* ObjectMesh = nullptr;
    Material* BaseMat = nullptr;

    void Start() {
        
    }

    RendererObject() {
        Start();
    }

    void Update() {
        MeshTransform(*ObjectMesh, *ObjectTransform,BaseMat);
    }

};

