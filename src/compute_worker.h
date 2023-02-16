#ifndef COMPUTE_WORKER_CLASS_H
#define COMPUTE_WORKER_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include "gpu_uniform.h"
#include "uniform_set.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/rd_shader_file.hpp>
#include <godot_cpp/classes/rd_shader_spirv.hpp>

using namespace godot;

class ComputeWorker : public Node
{
    GDCLASS(ComputeWorker, Node);

    protected:
        static void _bind_methods();

    private:
        RenderingDevice *rd = nullptr;
        RID compute_pipeline_rid;
        RID shader_rid;

        bool initialized;
        bool _is_device_processing;
    
    public:

        ComputeWorker();
        ~ComputeWorker();

        Ref<RDShaderFile> shader_file;
        TypedArray<UniformSet> uniform_sets;
        Vector3i work_group_size;
        bool use_global_device;

        Ref<RDShaderFile> get_shader_file();
        void set_shader_file(Ref<RDShaderFile> file);
        TypedArray<UniformSet> get_uniform_sets();
        void set_uniform_sets(TypedArray<UniformSet> sets);
        Vector3i get_work_group_size();
        void set_work_group_size(Vector3i size);
        bool get_use_global_device();
        void set_use_global_device(bool value);

        void initialize();
        RenderingDevice *get_rendering_device();
        bool is_device_processing();
        Variant get_uniform_data(int binding, int set_id);
        Variant get_uniform_data_by_alias(String alias, int set_id);
        void set_uniform_data(int binding, int set_id, Variant data, bool dispatch);
        void set_uniform_data_by_alias(String alias, int set_id, Variant data, bool dispatch);
        void dispatch_compute_list();
        void begin();
        void end();
        
        Ref<UniformSet> get_uniform_set_by_id(int set_id);
        Ref<GPUUniform> get_uniform_by_binding(int binding, int set_id);
        Ref<GPUUniform> get_uniform_by_alias(String alias, int set_id);
        int get_uniform_binding_by_alias(String alias, int set_id);

};


#endif // COMPUTE_WORKER_CLASS_H