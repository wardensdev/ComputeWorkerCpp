#ifndef GPUUNIFORM_CLASS_H
#define GPUUNIFORM_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>

using namespace godot;

class GPUUniform : public Resource
{
    GDCLASS(GPUUniform, Resource);

    protected:

        static void _bind_methods() {}

        String alias;
        Variant data;
        int binding = 0;

        RID buffer_rid;
        Ref<RDUniform> uniform;

        virtual Ref<RDUniform> create_uniform() { Ref<RDUniform> r; return r; }
        virtual RID create_rid(RenderingDevice *rd) { RID r; return r; }

    public:

        virtual ~GPUUniform() {}

        enum UNIFORM_TYPES{
            UNIFORM_BUFFER,
            STORAGE_BUFFER
        };

        virtual Ref<RDUniform> initialize(RenderingDevice *rd) { Ref<RDUniform> r; return r; }
        virtual Variant get_uniform_data(RenderingDevice *rd) { int a = 0; return a; }
        virtual void set_uniform_data(RenderingDevice *rd, Variant value) {}
        
        virtual String get_alias() { String a; return a; }
        virtual void set_alias(String value) {}
        virtual int get_binding() { return 0; }
        virtual void set_binding(int value) {}
        virtual RID get_buffer_rid() { RID r; return r; }
        virtual Ref<RDUniform> get_uniform() { Ref<RDUniform> r; return r; }
};

VARIANT_ENUM_CAST(GPUUniform::UNIFORM_TYPES);

#endif // GPUUNIFORM_CLASS_H