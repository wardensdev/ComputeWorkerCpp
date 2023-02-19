#include "gpu_float.h"
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;

GPU_Float::GPU_Float(){
    UtilityFunctions::print("GPU_Float init");
    UtilityFunctions::print(String::num(binding));
};
GPU_Float::~GPU_Float(){};

Ref<RDUniform> GPU_Float::initialize(RenderingDevice *rd){
    buffer_rid = create_rid(rd);
    return create_uniform();
}

Ref<RDUniform> GPU_Float::create_uniform(){
    switch (uniform_type)
    {
        case UNIFORM_TYPES::UNIFORM_BUFFER:
            uniform->set_uniform_type(RenderingDevice::UNIFORM_TYPE_UNIFORM_BUFFER);
            break;
        
        case UNIFORM_TYPES::STORAGE_BUFFER:
            uniform->set_uniform_type(RenderingDevice::UNIFORM_TYPE_STORAGE_BUFFER);
            break;

        default:
            break;
    }

    uniform->set_binding(binding);
    uniform->add_id(buffer_rid);

    return uniform;
}

RID GPU_Float::create_rid(RenderingDevice *rd){

    PackedByteArray bytes = float_to_byte_array(data);

    RID buffer;

    switch (uniform_type)
    {
        case UNIFORM_TYPES::UNIFORM_BUFFER:
            buffer = rd->uniform_buffer_create(bytes.size(), bytes);
            break;
        
        case UNIFORM_TYPES::STORAGE_BUFFER:
            buffer = rd->storage_buffer_create(bytes.size(), bytes);
            break;
        
        default:
            break;
    }

    return buffer;
}

Variant GPU_Float::get_uniform_data(RenderingDevice *rd){
    PackedByteArray out = rd->buffer_get_data(buffer_rid);
    return out.decode_double(0);
}

void GPU_Float::set_uniform_data(RenderingDevice *rd, Variant value){
    ERR_FAIL_COND_MSG(value.get_type() != Variant::FLOAT, "`value` must be a float type.");

    PackedByteArray bytes = float_to_byte_array(value);
    rd->buffer_update(buffer_rid, 0, bytes.size(), bytes);
}

PackedByteArray GPU_Float::float_to_byte_array(float value){
    PackedFloat64Array f;
    f.append(value);
    f.append(0.0);
    PackedByteArray bytes = f.to_byte_array();

    return bytes;
}

float GPU_Float::byte_array_to_float(PackedByteArray bytes){
    return bytes.decode_double(0);
}

float GPU_Float::get_data(){
    return data;
}

void GPU_Float::set_data(float value){
    data = value;
}

String GPU_Float::get_alias(){
    return alias;
}

void GPU_Float::set_alias(String value){
    alias = value;
}

int GPU_Float::get_binding(){
    return binding;
}

void GPU_Float::set_binding(int value){
    binding = value;
}

RID GPU_Float::get_buffer_rid(){
    return buffer_rid;
}

Ref<RDUniform> GPU_Float::get_uniform(){
    return uniform;
}

GPU_Float::UNIFORM_TYPES GPU_Float::get_uniform_type(){
    return uniform_type;
}

void GPU_Float::set_uniform_type(UNIFORM_TYPES type){
    uniform_type = type;
}

void GPU_Float::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_uniform"), &GPU_Float::create_uniform);
    ClassDB::bind_method(D_METHOD("create_rid", "rd"), &GPU_Float::create_rid);
    ClassDB::bind_method(D_METHOD("initialize", "rd"), &GPU_Float::initialize);
    ClassDB::bind_method(D_METHOD("get_uniform_data", "rd"), &GPU_Float::get_uniform_data);
    ClassDB::bind_method(D_METHOD("set_uniform_data", "rd", "value"), &GPU_Float::set_uniform_data);

    ClassDB::bind_method(D_METHOD("float_to_byte_array", "value"), &GPU_Float::float_to_byte_array);
    ClassDB::bind_method(D_METHOD("byte_array_to_float"), &GPU_Float::byte_array_to_float);

    ClassDB::bind_method(D_METHOD("set_data", "value"), &GPU_Float::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &GPU_Float::get_data);
    ClassDB::bind_method(D_METHOD("set_alias", "value"), &GPU_Float::set_alias);
    ClassDB::bind_method(D_METHOD("get_alias"), &GPU_Float::get_alias);
    ClassDB::bind_method(D_METHOD("set_binding", "value"), &GPU_Float::set_binding);
    ClassDB::bind_method(D_METHOD("get_binding"), &GPU_Float::get_binding);
    ClassDB::bind_method(D_METHOD("get_buffer_rid"), &GPU_Float::get_buffer_rid);
    ClassDB::bind_method(D_METHOD("get_uniform"), &GPU_Float::get_uniform);
    ClassDB::bind_method(D_METHOD("get_uniform_type"), &GPU_Float::get_uniform_type);
    ClassDB::bind_method(D_METHOD("set_uniform_type", "value"), &GPU_Float::set_uniform_type);

    BIND_ENUM_CONSTANT(UNIFORM_BUFFER);
    BIND_ENUM_CONSTANT(STORAGE_BUFFER);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "data"), "set_data", "get_data");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "alias"), "set_alias", "get_alias");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "binding"), "set_binding", "get_binding");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "uniform_type"), "set_uniform_type", "get_uniform_type");
}