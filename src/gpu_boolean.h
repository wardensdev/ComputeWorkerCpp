#ifndef GPU_BOOLEAN_CLASS_H
#define GPU_BOOLEAN_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include "gpu_uniform.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>

using namespace godot;

class GPU_Boolean : public GPUUniform
{
    GDCLASS(GPU_Boolean, GPUUniform);

    protected:
        static void _bind_methods();

        Ref<RDUniform> create_uniform();
        RID create_rid(RenderingDevice *rd);
    
    public:
        GPU_Boolean();
        ~GPU_Boolean();

        bool data = 0;
        UNIFORM_TYPES uniform_type;

        Ref<RDUniform> initialize(RenderingDevice *rd);
        Variant get_uniform_data(RenderingDevice *rd);
        void set_uniform_data(RenderingDevice *rd, Variant value);
        PackedByteArray bool_to_byte_array(bool value);
        bool byte_array_to_bool(PackedByteArray bytes);

        bool get_data();
        void set_data(bool value);
        String get_alias();
        void set_alias(String value);
        int get_binding();
        void set_binding(int value);
        RID get_buffer_rid();
        Ref<RDUniform> get_uniform();

        UNIFORM_TYPES get_uniform_type();
        void set_uniform_type(UNIFORM_TYPES type);
};

#endif // GPU_BOOLEAN_CLASS_H