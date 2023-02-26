# ComputeWorkerCpp

This is a C++ port of the ComputeWorker plugin that is available on the Godot Asset Library. It's currently a work in progress. The core of the plugin is finished,
meaning the ComputeWorker node itself is fully implemented, along with UniformSets and the GPUUniform class, and a few of the GPUUniform-derived basic types. The example project is also functional, and demostrates the currently implemented data types.

The main advantage of re-writing the plugin in C++ is the ability to more carefully handle encoding and decoding of the shader data. GDScript makes some assumptions about what data types are used behind the scenes. For example, in GDScript `float`s are always 64-bit (unless inside of a Vector) and `ints` are always 32-bit, signed integers. So to be able to have full control over your data, and to avoid precision loss, the plugin needs to be re-written to serve as a bridge between Godot's encoding rules and GLSL's encoding rules.
