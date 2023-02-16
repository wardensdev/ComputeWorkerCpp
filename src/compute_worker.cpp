#include "uniform_set.h"
#include "gpu_uniform.h"
#include "compute_worker.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/rd_shader_file.hpp>
#include <godot_cpp/classes/rd_shader_spirv.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/rendering_device.hpp>

using namespace godot;

ComputeWorker::ComputeWorker(){};
ComputeWorker::~ComputeWorker(){};

void ComputeWorker::initialize(){

    ERR_FAIL_COND_MSG(rd != nullptr, "Call `destroy()` before initializing ComputeWorker.");

    if(use_global_device){
        RenderingDevice *n_rd = RenderingServer::get_singleton()->get_rendering_device();
        rd = n_rd;
    }
    else{
        RenderingDevice *n_rd = RenderingServer::get_singleton()->create_local_rendering_device();
        rd = n_rd;
    }

    Ref<RDShaderSPIRV> shader_spirv = shader_file->get_spirv();
    shader_rid = rd->shader_create_from_spirv(shader_spirv);

    for(int i = 0; i < uniform_sets.size(); i++){
        Ref<UniformSet> uu = uniform_sets[i];
        uu->initialize(rd, shader_rid);
    }

    compute_pipeline_rid = rd->compute_pipeline_create(shader_rid);

    dispatch_compute_list();

    initialized = true;
}


RenderingDevice *ComputeWorker::get_rendering_device(){
    return rd;
}


bool ComputeWorker::is_device_processing(){
    return _is_device_processing;
}


Variant ComputeWorker::get_uniform_data(int binding, int set_id){
    ERR_FAIL_COND_V_MSG(!initialized, 0, "ComputeWorker must be initialized before accessing uniform data");
    
    Ref<GPUUniform> gp = get_uniform_by_binding(binding, set_id);

    return gp->get_uniform_data(rd);
}


Variant ComputeWorker::get_uniform_data_by_alias(String alias, int set_id){
    ERR_FAIL_COND_V_MSG(!initialized, 0, "ComputeWorker must be initialized before accessing uniform data");

    Ref<GPUUniform> gp = get_uniform_by_alias(alias, set_id);

    return gp->get_uniform_data(rd);
}


void ComputeWorker::set_uniform_data(int binding, int set_id, Variant data, bool dispatch){
    ERR_FAIL_COND_MSG(!initialized, "ComputeWorker must be initialized before accessing uniform data");

    Ref<GPUUniform> gp = get_uniform_by_binding(binding, set_id);
    gp->set_uniform_data(rd, data);

    if(dispatch){
        dispatch_compute_list();
        begin();
    }
}


void ComputeWorker::set_uniform_data_by_alias(String alias, int set_id, Variant data, bool dispatch){
    ERR_FAIL_COND_MSG(!initialized, "ComputeWorker must be initialized before accessing uniform data");

    Ref<GPUUniform> gp = get_uniform_by_alias(alias, set_id);
    gp->set_uniform_data(rd, data);

    if(dispatch){
        dispatch_compute_list();
        begin();
    }
}


void ComputeWorker::dispatch_compute_list(){
    int64_t compute_list_rid = rd->compute_list_begin();
    rd->compute_list_bind_compute_pipeline(compute_list_rid, compute_pipeline_rid);

    for(int i = 0; i < uniform_sets.size(); i++){
        Ref<UniformSet> us = uniform_sets[i];
        rd->compute_list_bind_uniform_set(compute_list_rid, us->uniform_set_rid, us->set_id);
    }

    rd->compute_list_dispatch(compute_list_rid, work_group_size.x, work_group_size.y, work_group_size.z);
    rd->compute_list_end();
}


void ComputeWorker::begin(){
    ERR_FAIL_COND_MSG(use_global_device, "Cannot use function `begin()` while  `use_global_device` is true.");

    _is_device_processing = true;
    rd->submit();
}


void ComputeWorker::end(){

    rd->sync();
    _is_device_processing = false;
}


Ref<UniformSet> ComputeWorker::get_uniform_set_by_id(int set_id){

    Ref<UniformSet> ret;

    for(int i = 0; i < uniform_sets.size(); i++){

        ret = uniform_sets[i];

        if(ret->set_id == set_id){
            return ret;
        }
    }
    
    ERR_FAIL_COND_V_MSG(*ret == nullptr, 0, "UniformSet not found for set_id " + String::num(set_id));
    return ret;
}


Ref<GPUUniform> ComputeWorker::get_uniform_by_binding(int binding, int set_id){

    Ref<UniformSet> us = get_uniform_set_by_id(set_id);
    Ref<GPUUniform> gp;

    for(int i = 0; i < us->uniforms.size(); i++){

        gp = us->uniforms[i];

        if(gp->binding == binding){
            return gp;
        }
    }
    ERR_FAIL_NULL_V_MSG(gp, 0, "GPUUniform not found for binding " + String::num(binding));
    return gp;
}


Ref<GPUUniform> ComputeWorker::get_uniform_by_alias(String alias, int set_id){

    Ref<UniformSet> us = get_uniform_set_by_id(set_id);
    Ref<GPUUniform> gp;

    for(int i = 0; i < us->uniforms.size(); i++){

        gp = us->uniforms[i];

        if(gp->alias == alias){
            return gp;
        }
    }
    
    ERR_FAIL_NULL_V_MSG(gp, gp, "GPUUniform not found for alias " + alias);
    return gp;
}


int ComputeWorker::get_uniform_binding_by_alias(String alias, int set_id){
    
    Ref<UniformSet> us = get_uniform_set_by_id(set_id);
    Ref<GPUUniform> gp;

    for(int i = 0; i < us->uniforms.size(); i++){

        gp = us->uniforms[i];

        if(gp->alias == alias){
            return gp->binding;
        }
    }
    
    ERR_FAIL_NULL_V_MSG(gp, 0, "GPUUniform binding not found for alias " + alias);
    return -1;
}


Ref<RDShaderFile> ComputeWorker::get_shader_file(){
    return shader_file;
};


void ComputeWorker::set_shader_file(Ref<RDShaderFile> file){
    shader_file = file;
};


TypedArray<UniformSet> ComputeWorker::get_uniform_sets(){
    return uniform_sets;
}


void ComputeWorker::set_uniform_sets(TypedArray<UniformSet> sets){
    uniform_sets = sets;
}


Vector3i ComputeWorker::get_work_group_size(){
    return work_group_size;
}


void ComputeWorker::set_work_group_size(Vector3i size){
    work_group_size = size;
}


bool ComputeWorker::get_use_global_device(){
    return use_global_device;
}


void ComputeWorker::set_use_global_device(bool value){
    use_global_device = value;
}


void ComputeWorker::_bind_methods(){

    ClassDB::bind_method(D_METHOD("initialize"), &ComputeWorker::initialize);
    ClassDB::bind_method(D_METHOD("get_rendering_device"), &ComputeWorker::get_rendering_device);
    ClassDB::bind_method(D_METHOD("is_processing"), &ComputeWorker::is_processing);
    ClassDB::bind_method(D_METHOD("get_uniform_data", "binding", "set_id"), &ComputeWorker::get_uniform_data);
    ClassDB::bind_method(D_METHOD("get_uniform_data_by_alias", "alias", "set_id"), &ComputeWorker::get_uniform_data_by_alias);
    ClassDB::bind_method(D_METHOD("set_uniform_data", "binding", "set_id", "data", "dispatch"), &ComputeWorker::set_uniform_data);
    ClassDB::bind_method(D_METHOD("set_uniform_data_by_alias", "alias", "set_id", "data", "dispatch"), &ComputeWorker::set_uniform_data_by_alias);
    ClassDB::bind_method(D_METHOD("dispatch_compute_list"), &ComputeWorker::dispatch_compute_list);
    ClassDB::bind_method(D_METHOD("begin"), &ComputeWorker::begin);
    ClassDB::bind_method(D_METHOD("end"), &ComputeWorker::end);
    
    ClassDB::bind_method(D_METHOD("get_uniform_set_by_id", "set_id"), &ComputeWorker::get_uniform_set_by_id);
    ClassDB::bind_method(D_METHOD("get_uniform_by_binding", "binding", "set_id"), &ComputeWorker::get_uniform_by_binding);
    ClassDB::bind_method(D_METHOD("get_uniform_by_alias", "alias", "set_id"), &ComputeWorker::get_uniform_by_alias);
    ClassDB::bind_method(D_METHOD("get_uniform_binding_by_alias", "alias", "set_id"), &ComputeWorker::get_uniform_binding_by_alias);

    ClassDB::bind_method(D_METHOD("set_shader_file", "file"), &ComputeWorker::set_shader_file);
    ClassDB::bind_method(D_METHOD("get_shader_file"), &ComputeWorker::get_shader_file);
    ClassDB::bind_method(D_METHOD("set_uniform_sets", "sets"), &ComputeWorker::set_uniform_sets);
    ClassDB::bind_method(D_METHOD("get_uniform_sets"), &ComputeWorker::get_uniform_sets);
    ClassDB::bind_method(D_METHOD("set_work_group_size", "size"), &ComputeWorker::set_work_group_size);
    ClassDB::bind_method(D_METHOD("get_work_group_size"), &ComputeWorker::get_work_group_size);
    ClassDB::bind_method(D_METHOD("get_use_global_device"), &ComputeWorker::get_use_global_device);
    ClassDB::bind_method(D_METHOD("set_use_global_device", "value"), &ComputeWorker::set_use_global_device);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "shader_file", PROPERTY_HINT_RESOURCE_TYPE, "RDShaderFile"), "set_shader_file", "get_shader_file");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "uniform_sets", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "UniformSet")), "set_uniform_sets", "get_uniform_sets");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "work_group_size"), "set_work_group_size", "get_work_group_size");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_global_device"), "set_use_global_device", "get_use_global_device");

}