#ifndef GPU_VECTOR3_CLASS_H
#define GPU_VECTOR3_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include "gpu_uniform.h"
#include "dvector3.hpp"
#include "double_vector3.hpp"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>

using namespace godot;


class GPU_Vector3 : public GPUUniform
{
    GDCLASS(GPU_Vector3, GPUUniform);

    dVector3 _data;

    protected:
        static void _bind_methods();

        Ref<RDUniform> create_uniform();
        RID create_rid(RenderingDevice *rd);

    public:

        GPU_Vector3();
        ~GPU_Vector3();

        Vector3 data = Vector3();
        bool is_double = 0;
        UNIFORM_TYPES uniform_type = UNIFORM_TYPES::UNIFORM_BUFFER;

        Ref<RDUniform> initialize(RenderingDevice *rd);
        Variant get_uniform_data(RenderingDevice *rd);
        void set_uniform_data(RenderingDevice *rd, Variant value);
        PackedByteArray vec3_to_byte_array(Variant value);
        Variant byte_array_to_vec3(PackedByteArray bytes);

        Vector3 get_data();
        void set_data(Vector3 value);
        String get_alias();
        void set_alias(String value);
        int get_binding();
        void set_binding(int value);
        bool get_is_double();
        void set_is_double(bool value);
        RID get_buffer_rid();
        Ref<RDUniform> get_uniform();

        UNIFORM_TYPES get_uniform_type();
        void set_uniform_type(UNIFORM_TYPES type);
};


#endif // GPU_VECTOR3_CLASS_H