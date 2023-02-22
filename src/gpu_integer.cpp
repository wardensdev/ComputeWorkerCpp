#include "gpu_integer.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

GPU_Integer::GPU_Integer()
{
    RDUniform *r = memnew(RDUniform);
    uniform = Ref<RDUniform>(r);
}


GPU_Integer::~GPU_Integer(){}


Ref<RDUniform> GPU_Integer::initialize(RenderingDevice *rd)
{
    buffer_rid = create_rid(rd);
    return create_uniform();
}


Ref<RDUniform> GPU_Integer::create_uniform()
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


RID GPU_Integer::create_rid(RenderingDevice *rd)
{
    PackedByteArray bytes = int_to_byte_array(data);
    UtilityFunctions::print(bytes.size());
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


Variant GPU_Integer::get_uniform_data(RenderingDevice *rd)
{
    PackedByteArray out = rd->buffer_get_data(buffer_rid);
    return byte_array_to_int(out);
}


void GPU_Integer::set_uniform_data(RenderingDevice *rd, Variant value)
{
    ERR_FAIL_COND_MSG(value.get_type() != Variant::INT, "`value` must be an int type.");

    PackedByteArray bytes = int_to_byte_array(value);
    rd->buffer_update(buffer_rid, 0, bytes.size(), bytes);
}


PackedByteArray GPU_Integer::int_to_byte_array(int value)
{
    if(is_signed){
        PackedByteArray a;
        a.resize(4);
        a.encode_s32(0, value);
        return a;
    }
    else{
        PackedByteArray a;
        a.resize(4);
        a.encode_u32(0, value);
        return a;
    }
}


int GPU_Integer::byte_array_to_int(PackedByteArray bytes)
{
    if(is_signed){
        return bytes.decode_s32(0);
    }
    else{
        return bytes.decode_u32(0);
    }
}


int GPU_Integer::get_data()
{
    return data;
}


void GPU_Integer::set_data(int value)
{
    data = value;
}


String GPU_Integer::get_alias()
{
    return alias;
}


void GPU_Integer::set_alias(String value)
{
    alias = value;
}


int GPU_Integer::get_binding()
{
    return binding;
}


void GPU_Integer::set_binding(int value)
{
    binding = value;
}


RID GPU_Integer::get_buffer_rid()
{
    return buffer_rid;
}


Ref<RDUniform> GPU_Integer::get_uniform()
{
    return uniform;
}


GPU_Integer::UNIFORM_TYPES GPU_Integer::get_uniform_type()
{
    return uniform_type;
}


void GPU_Integer::set_uniform_type(UNIFORM_TYPES type)
{
    uniform_type = type;
}


bool GPU_Integer::get_is_signed()
{
    return is_signed;
}


void GPU_Integer::set_is_signed(bool value)
{
    is_signed = value;
}


void GPU_Integer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_uniform"), &GPU_Integer::create_uniform);
    ClassDB::bind_method(D_METHOD("create_rid", "rd"), &GPU_Integer::create_rid);
    ClassDB::bind_method(D_METHOD("initialize", "rd"), &GPU_Integer::initialize);
    ClassDB::bind_method(D_METHOD("get_uniform_data", "rd"), &GPU_Integer::get_uniform_data);
    ClassDB::bind_method(D_METHOD("set_uniform_data", "rd", "value"), &GPU_Integer::set_uniform_data);

    ClassDB::bind_method(D_METHOD("int_to_byte_array", "value"), &GPU_Integer::int_to_byte_array);
    ClassDB::bind_method(D_METHOD("byte_array_to_int", "bytes"), &GPU_Integer::byte_array_to_int);

    ClassDB::bind_method(D_METHOD("set_data", "value"), &GPU_Integer::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &GPU_Integer::get_data);
    ClassDB::bind_method(D_METHOD("set_alias", "value"), &GPU_Integer::set_alias);
    ClassDB::bind_method(D_METHOD("get_alias"), &GPU_Integer::get_alias);
    ClassDB::bind_method(D_METHOD("set_binding", "value"), &GPU_Integer::set_binding);
    ClassDB::bind_method(D_METHOD("get_binding"), &GPU_Integer::get_binding);
    ClassDB::bind_method(D_METHOD("set_is_signed", "value"), &GPU_Integer::set_is_signed);
    ClassDB::bind_method(D_METHOD("get_is_signed"), &GPU_Integer::get_is_signed);
    ClassDB::bind_method(D_METHOD("get_buffer_rid"), &GPU_Integer::get_buffer_rid);
    ClassDB::bind_method(D_METHOD("get_uniform"), &GPU_Integer::get_uniform);
    ClassDB::bind_method(D_METHOD("get_uniform_type"), &GPU_Integer::get_uniform_type);
    ClassDB::bind_method(D_METHOD("set_uniform_type", "value"), &GPU_Integer::set_uniform_type);

    BIND_ENUM_CONSTANT(UNIFORM_BUFFER);
    BIND_ENUM_CONSTANT(STORAGE_BUFFER);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "data"), "set_data", "get_data");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_signed"), "set_is_signed", "get_is_signed");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "alias"), "set_alias", "get_alias");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "binding"), "set_binding", "get_binding");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "uniform_type", PROPERTY_HINT_ENUM, "Uniform Buffer,Storage Buffer"), "set_uniform_type", "get_uniform_type");
}