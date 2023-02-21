#include "gpu_boolean.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

GPU_Boolean::GPU_Boolean()
{
    RDUniform *r = memnew(RDUniform);
    uniform = Ref<RDUniform>(r);
}


GPU_Boolean::~GPU_Boolean(){}


Ref<RDUniform> GPU_Boolean::initialize(RenderingDevice *rd)
{
    buffer_rid = create_rid(rd);
    return create_uniform();
}


Ref<RDUniform> GPU_Boolean::create_uniform()
{
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


RID GPU_Boolean::create_rid(RenderingDevice *rd)
{
    PackedByteArray bytes = bool_to_byte_array(data);

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


Variant GPU_Boolean::get_uniform_data(RenderingDevice *rd)
{
    PackedByteArray out = rd->buffer_get_data(buffer_rid);
    return byte_array_to_bool(out);
}


void GPU_Boolean::set_uniform_data(RenderingDevice *rd, Variant value)
{
    ERR_FAIL_COND_MSG(value.get_type() != Variant::BOOL, "`value` must be a float type.");

    PackedByteArray bytes = bool_to_byte_array(value);
    rd->buffer_update(buffer_rid, 0, bytes.size(), bytes);
}


PackedByteArray GPU_Boolean::bool_to_byte_array(bool value)
{
    PackedByteArray bytes;
    bytes.resize(4);

    if(value){
        bytes.encode_u32(0, 1);
    }
    else{
        bytes.encode_u32(0, 0);
    }

    return bytes;
}


bool GPU_Boolean::byte_array_to_bool(PackedByteArray bytes)
{
    int num = bytes.decode_u32(0);

    if(num == 0){
        return false;
    }
    else{
        return true;
    }
}


bool GPU_Boolean::get_data()
{
    return data;
}


void GPU_Boolean::set_data(bool value)
{
    data = value;
}


String GPU_Boolean::get_alias()
{
    return alias;
}


void GPU_Boolean::set_alias(String value)
{
    alias = value;
}


int GPU_Boolean::get_binding()
{
    return binding;
}


void GPU_Boolean::set_binding(int value)
{
    binding = value;
}


RID GPU_Boolean::get_buffer_rid()
{
    return buffer_rid;
}


Ref<RDUniform> GPU_Boolean::get_uniform()
{
    return uniform;
}


GPU_Boolean::UNIFORM_TYPES GPU_Boolean::get_uniform_type()
{
    return uniform_type;
}


void GPU_Boolean::set_uniform_type(UNIFORM_TYPES type)
{
    uniform_type = type;
}


void GPU_Boolean::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_uniform"), &GPU_Boolean::create_uniform);
    ClassDB::bind_method(D_METHOD("create_rid", "rd"), &GPU_Boolean::create_rid);
    ClassDB::bind_method(D_METHOD("initialize", "rd"), &GPU_Boolean::initialize);
    ClassDB::bind_method(D_METHOD("get_uniform_data", "rd"), &GPU_Boolean::get_uniform_data);
    ClassDB::bind_method(D_METHOD("set_uniform_data", "rd", "value"), &GPU_Boolean::set_uniform_data);

    ClassDB::bind_method(D_METHOD("bool_to_byte_array", "value"), &GPU_Boolean::bool_to_byte_array);
    ClassDB::bind_method(D_METHOD("byte_array_to_bool", "bytes"), &GPU_Boolean::byte_array_to_bool);

    ClassDB::bind_method(D_METHOD("set_data", "value"), &GPU_Boolean::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &GPU_Boolean::get_data);
    ClassDB::bind_method(D_METHOD("set_alias", "value"), &GPU_Boolean::set_alias);
    ClassDB::bind_method(D_METHOD("get_alias"), &GPU_Boolean::get_alias);
    ClassDB::bind_method(D_METHOD("set_binding", "value"), &GPU_Boolean::set_binding);
    ClassDB::bind_method(D_METHOD("get_binding"), &GPU_Boolean::get_binding);
    ClassDB::bind_method(D_METHOD("get_buffer_rid"), &GPU_Boolean::get_buffer_rid);
    ClassDB::bind_method(D_METHOD("get_uniform"), &GPU_Boolean::get_uniform);
    ClassDB::bind_method(D_METHOD("get_uniform_type"), &GPU_Boolean::get_uniform_type);
    ClassDB::bind_method(D_METHOD("set_uniform_type", "value"), &GPU_Boolean::set_uniform_type);

    BIND_ENUM_CONSTANT(UNIFORM_BUFFER);
    BIND_ENUM_CONSTANT(STORAGE_BUFFER);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "data"), "set_data", "get_data");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "alias"), "set_alias", "get_alias");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "binding"), "set_binding", "get_binding");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "uniform_type", PROPERTY_HINT_ENUM, "Uniform Buffer,Storage Buffer"), "set_uniform_type", "get_uniform_type");
}