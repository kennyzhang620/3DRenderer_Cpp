# 3DRenderer_Cpp
Software+Hardware 3D Renderer/Rasterizer in C++!

This is a small personal project I am working on. I am implementing software 2D/3D rendering from scratch using C++ to complement
my desire for 3D graphics and games.

Aside from the bitmap library, all of the code is vanilla C++ with only the Windows library required to plot pixels directly to the framebuffer.

# Rasterization

2D graphics mainly focuses on pulling a texture from a file and drawing directly on screen and using matrix operations to apply transformations such
as rotation, scaling and translation. It can also draw triangles, lines and vectors given a set of vertices (which is vital for 3D).

# Rendering 
In 3D rendering, the main goal is to transform a 3D model, a set of vertices in 3D space and project it onto a 2D plane. First we break up the mesh into triangles. Then for each triangle we assign three vertices that make up the polygon. A z-index is calculated which ensures that the furthest object is rendered first. Finally, they are paired up with a fragment shader and its parameters (fragShader and addparms). For each triangle, we first need to apply the transformations in "model space" (this is the space that the 3D model is originally set in. its usually between (-1,1) for x,y,z). This allows us to scale, and rotate the mesh to be moved around in the 3D space. We then translate the mesh to move it away from the origin and anywhere we want in the 3D space we are working with. 

As of right now, there is no camera system set up. All the meshes are transformed with scaling/rotation applied and translated near the camera view. Also there is no perspective. Everything is rendered orthographically.

Once the transformations are completed, we feed these transformed triangles into a triangle rasterization routine.


