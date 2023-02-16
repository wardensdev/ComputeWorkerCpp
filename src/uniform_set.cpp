#include "uniform_set.h"
#include "gpu_uniform.h"
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/classes/rd_uniform.hpp>

using namespace godot;

UniformSet::UniformSet(){}
UniformSet::~UniformSet(){}

void UniformSet::initialize(RenderingDevice *rd, RID shader_rid)
{
    
    TypedArray<RDUniform> uniform_set;
    uniform_set.resize(uniforms.size());

    for(int i = 0; i < uniforms.size(); i++)
    {
        Ref<GPUUniform> uu = uniforms[i];
        Ref<RDUniform> rdu = uu->initialize(rd);
        
        uniform_set.push_back(rdu);
    }

    uniform_set_rid = rd->uniform_set_create(uniform_set, shader_rid, set_id);
    
}

void UniformSet::destroy(RenderingDevice *rd)
{
    rd->free_rid(uniform_set_rid);

    for(int i = 0; i < uniforms.size(); i++)
    {

        Ref<GPUUniform> uu = uniforms[i];

        rd->free_rid(uu->buffer_rid);
        uu->uniform->clear_ids();
    }
}

TypedArray<GPUUniform> UniformSet::get_uniforms()
{
    return uniforms;
}

void UniformSet::set_uniforms(TypedArray<GPUUniform> p_value)
{
    uniforms = p_value;
}

int UniformSet::get_set_id()
{
    return set_id;
}

void UniformSet::set_set_id(int new_id)
{
    set_id = new_id;
}

void UniformSet::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("initialize", "rd", "shader_rid"), &UniformSet::initialize);
    ClassDB::bind_method(D_METHOD("destroy", "rd"), &UniformSet::destroy);
    ClassDB::bind_method(D_METHOD("get_uniforms"), &UniformSet::get_uniforms);
    ClassDB::bind_method(D_METHOD("set_uniforms", "p_value"), &UniformSet::set_uniforms);

    ClassDB::bind_method(D_METHOD("get_set_id"), &UniformSet::get_set_id);
    ClassDB::bind_method(D_METHOD("set_set_id", "new_id"), &UniformSet::set_set_id);
    
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "uniforms", PROPERTY_HINT_ARRAY_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "GPUUniform")), "set_uniforms", "get_uniforms");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "set_id"), "set_set_id", "get_set_id");
}