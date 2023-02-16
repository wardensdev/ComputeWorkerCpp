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
        static void _bind_methods();

        virtual Ref<RDUniform> create_uniform();
        virtual RID create_rid(RenderingDevice *rd);

    public:
        
        GPUUniform();
        ~GPUUniform();

        enum UNIFORM_TYPES{
            UNIFORM_BUFFER,
            STORAGE_BUFFER
        };
        
        String alias;
        Variant data;
        int binding;

        RID buffer_rid;
        Ref<RDUniform> uniform;

        virtual Ref<RDUniform> initialize(RenderingDevice *rd);
        virtual Variant get_uniform_data(RenderingDevice *rd);
        virtual void set_uniform_data(RenderingDevice *rd, Variant value);
        
};

#endif // GPUUNIFORM_CLASS_H