#ifndef GPU_FLOAT_CLASS_H
#define GPU_FLOAT_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include "gpu_uniform.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>

using namespace godot;

class GPU_Float : public GPUUniform
{
    GDCLASS(GPU_Float, GPUUniform);

    protected:
        static void _bind_methods();

        Ref<RDUniform> create_uniform();
        RID create_rid(RenderingDevice *rd);

    public:

        GPU_Float();
        ~GPU_Float();

        double data = 0.0;
        UNIFORM_TYPES uniform_type;

        Ref<RDUniform> initialize(RenderingDevice *rd);
        Variant get_uniform_data(RenderingDevice *rd);
        void set_uniform_data(RenderingDevice *rd, Variant value);
        PackedByteArray float_to_byte_array(double value);
        float byte_array_to_float(PackedByteArray bytes);

        float get_data();
        void set_data(float value);
        String get_alias();
        void set_alias(String value);
        int get_binding();
        void set_binding(int value);
        RID get_buffer_rid();
        Ref<RDUniform> get_uniform();

        UNIFORM_TYPES get_uniform_type();
        void set_uniform_type(UNIFORM_TYPES type);

};



#endif // GPU_FLOAT_CLASS_H