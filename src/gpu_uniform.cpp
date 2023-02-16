#include "gpu_uniform.h"

using namespace godot;


GPUUniform::GPUUniform(){}
GPUUniform::~GPUUniform(){}

Ref<RDUniform> GPUUniform::create_uniform(){ return nullptr; }
RID GPUUniform::create_rid(RenderingDevice *rd){ RID r; return r; }
Ref<RDUniform> GPUUniform::initialize(RenderingDevice *rd){ return nullptr; }
Variant GPUUniform::get_uniform_data(RenderingDevice *rd){ int i = 0; return i; }
void GPUUniform::set_uniform_data(RenderingDevice *rd, Variant value){}


void GPUUniform::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_uniform"), &GPUUniform::create_uniform);
    ClassDB::bind_method(D_METHOD("create_rid", "rd"), &GPUUniform::create_rid);
    ClassDB::bind_method(D_METHOD("initialize", "rd"), &GPUUniform::initialize);
    ClassDB::bind_method(D_METHOD("get_uniform_data", "rd"), &GPUUniform::get_uniform_data);
    ClassDB::bind_method(D_METHOD("set_uniform_data", "rd", "value"), &GPUUniform::set_uniform_data);
    
}