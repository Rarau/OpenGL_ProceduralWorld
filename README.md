# OpenGL_ProceduralWorld

[![IMAGE ALT TEXT HERE](http://img.youtube.com/vi/TuvSt2uzPX4/0.jpg)](http://www.youtube.com/watch?v=TuvSt2uzPX4)

We developed our own basic 3D engine as a framework to build the project. The only external library used is GLFW to help with OpenGL 4.3 context and window management.

The rendering for the terrain is done in two different passes inspired by http://http.developer.nvidia.com/GPUGems3/gpugems3_ch01.htm:

Rendering a quad mesh 33 times via instanced drawing and setting the viewport to 33x33 pixels resolution. At the fragment shader of this pass we use the fragment position and the instance ID of the object as coordinates to sample a Simplex 3D noise function. The noise value is then written to the red channel of the output texture, thus generating an array of 33 noise textures each 33x33 pixels in size.
With these textures we render a 32x32x32 vertices mesh. At the geometry shader of this stage we consider each vertex to be the center of a small cube (voxel), so we sample the noise textures eight times for each vertex (at the voxel's corners). Depending on the fetched values the geometry shader will output the appropriate number of primitives (triangles) with the help of a lookup table and it will calculate the normals for each of them. Finally at the fragment shader we add directional lighting as well as Fresnel reflections.