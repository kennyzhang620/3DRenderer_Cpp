#pragma once
#include "GameObject.h"
#include "Material.h"
#include "VertexShader.h"
class RendererObject :
    public GameObject
{
public:
    Mesh ObjectMesh;
    Material* BaseMat;

    void Start() {
        
    }

    RendererObject() {
        Start();
    }

    void Update() {
        MeshTransform(ObjectMesh, *ObjectTransform,BaseMat);
    }

};

