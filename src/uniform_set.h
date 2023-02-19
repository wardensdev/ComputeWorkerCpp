#ifndef UNIFORM_SET_CLASS_H
#define UNIFORM_SET_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/resource.hpp>
#include "gpu_uniform.h"

using namespace godot;


class UniformSet : public Resource
{
    GDCLASS(UniformSet, Resource);

    protected:
        static void _bind_methods();
    
    public:

        UniformSet();
        ~UniformSet();

        TypedArray<GPUUniform> uniforms;
        int set_id = 0;
        RID uniform_set_rid;

        void initialize(RenderingDevice *rd, RID shader_rid);
        void destroy(RenderingDevice *rd);

        TypedArray<GPUUniform> get_uniforms();
        void set_uniforms(TypedArray<GPUUniform> p_value);

        int get_set_id();
        void set_set_id(int new_id);
};


#endif // UNIFORM_SET_CLASS_H