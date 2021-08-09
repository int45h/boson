# boson

# The Boson 3D Library

Basic all-in-one portable library you can use for 2D or 3D game development. Written entirely in C. (C11 standard)
![alt text](https://github.com/josuke-higashikata/boson/blob/master/test/raytracer/out.png?raw=true)

### Includes:
- Math library for vector, matrix, and quaternion operations
- Basic IO functions for file reading
- Wrappers around SDL and OpenGL functions for rendering
- Data structures for 3D objects, cameras, transforms, and models

### TO-DO
- Remove dependency for stb-image
- Make more advanced rendering functions
- Add architecture specific optimizations (For the math library, e.g. ARM NEON or x86 SIMD instructions to make vector operations faster)
- Add support for fixed point math functions and data types
- Add some kind of documentation 
- Add support for Vulkan or other rendering APIs
- Make it complient with the C99 standard
