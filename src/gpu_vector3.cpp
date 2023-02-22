#include "gpu_vector3.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

GPU_Vector3::GPU_Vector3()
{
    RDUniform *r = memnew(RDUniform);
    uniform = Ref<RDUniform>(r);
}


GPU_Vector3::~GPU_Vector3(){}


Ref<RDUniform> GPU_Vector3::initialize(RenderingDevice *rd)
{
    buffer_rid = create_rid(rd);
    return create_uniform();
}


Ref<RDUniform> GPU_Vector3::create_uniform()
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


RID GPU_Vector3::create_rid(RenderingDevice *rd)
{
    PackedByteArray bytes = vec3_to_byte_array(data);
    
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


Variant GPU_Vector3::get_uniform_data(RenderingDevice *rd)
{
    PackedByteArray out = rd->buffer_get_data(buffer_rid);
    return byte_array_to_vec3(out);
}


void GPU_Vector3::set_uniform_data(RenderingDevice *rd, Variant value)
{
    bool cond = (value.get_type() == Variant::VECTOR3 || \
                 value.get_type() == Variant::PACKED_FLOAT64_ARRAY || \
                 value.get_type() == Variant::PACKED_FLOAT32_ARRAY);

    ERR_FAIL_COND_MSG(!cond, "`value` must be a Vector3 or PackedFloat**Array type.");

    PackedByteArray bytes = vec3_to_byte_array(value);
    rd->buffer_update(buffer_rid, 0, bytes.size(), bytes);
}


PackedByteArray GPU_Vector3::vec3_to_byte_array(Variant value)
{
    dVector3 a = dVector3(value);
    return a.to_byte_array();
}


Variant GPU_Vector3::byte_array_to_vec3(PackedByteArray bytes)
{
    if(is_double){
        DoubleVector3 vec;
        vec.x = bytes.decode_double(0);
        vec.y = bytes.decode_double(8);
        vec.z = bytes.decode_double(16);
        return dVector3(vec).to_variant();
    }
    else{
        Vector3 vec;
        vec.x = bytes.decode_float(0);
        vec.y = bytes.decode_float(4);
        vec.z = bytes.decode_float(8);
        return dVector3(vec).to_variant();
    }
}


Vector3 GPU_Vector3::get_data()
{
    switch (_data.precision)
    {
        case dVector3::Precision::DOUBLE:
            return _data.dvec.to_vector3();

        case dVector3::Precision::FLOAT:
            return _data.fvec;

        default:
            return data;
    }
}


void GPU_Vector3::set_data(Vector3 value)
{
    data = value;

    if(is_double){
        DoubleVector3 d = DoubleVector3(data);
        _data.dvec = d;
    }
    else{
        _data.fvec = data;
    }
}


String GPU_Vector3::get_alias()
{
    return alias;
}


void GPU_Vector3::set_alias(String value)
{
    alias = value;
}


int GPU_Vector3::get_binding()
{
    return binding;
}


void GPU_Vector3::set_binding(int value)
{
    binding = value;
}


RID GPU_Vector3::get_buffer_rid()
{
    return buffer_rid;
}


Ref<RDUniform> GPU_Vector3::get_uniform()
{
    return uniform;
}


GPU_Vector3::UNIFORM_TYPES GPU_Vector3::get_uniform_type()
{
    return uniform_type;
}


void GPU_Vector3::set_uniform_type(UNIFORM_TYPES type)
{
    uniform_type = type;
}


bool GPU_Vector3::get_is_double()
{
    return is_double;
}


void GPU_Vector3::set_is_double(bool value)
{
    is_double = value;
}


void GPU_Vector3::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("create_uniform"), &GPU_Vector3::create_uniform);
    ClassDB::bind_method(D_METHOD("create_rid", "rd"), &GPU_Vector3::create_rid);
    ClassDB::bind_method(D_METHOD("initialize", "rd"), &GPU_Vector3::initialize);
    ClassDB::bind_method(D_METHOD("get_uniform_data", "rd"), &GPU_Vector3::get_uniform_data);
    ClassDB::bind_method(D_METHOD("set_uniform_data", "rd", "value"), &GPU_Vector3::set_uniform_data);

    ClassDB::bind_method(D_METHOD("vec3_to_byte_array", "value"), &GPU_Vector3::vec3_to_byte_array);
    ClassDB::bind_method(D_METHOD("byte_array_to_vec3", "bytes"), &GPU_Vector3::byte_array_to_vec3);

    ClassDB::bind_method(D_METHOD("set_data", "value"), &GPU_Vector3::set_data);
    ClassDB::bind_method(D_METHOD("get_data"), &GPU_Vector3::get_data);
    ClassDB::bind_method(D_METHOD("set_alias", "value"), &GPU_Vector3::set_alias);
    ClassDB::bind_method(D_METHOD("get_alias"), &GPU_Vector3::get_alias);
    ClassDB::bind_method(D_METHOD("set_binding", "value"), &GPU_Vector3::set_binding);
    ClassDB::bind_method(D_METHOD("get_binding"), &GPU_Vector3::get_binding);
    ClassDB::bind_method(D_METHOD("set_is_double", "value"), &GPU_Vector3::set_is_double);
    ClassDB::bind_method(D_METHOD("get_is_double"), &GPU_Vector3::get_is_double);
    ClassDB::bind_method(D_METHOD("get_buffer_rid"), &GPU_Vector3::get_buffer_rid);
    ClassDB::bind_method(D_METHOD("get_uniform"), &GPU_Vector3::get_uniform);
    ClassDB::bind_method(D_METHOD("get_uniform_type"), &GPU_Vector3::get_uniform_type);
    ClassDB::bind_method(D_METHOD("set_uniform_type", "value"), &GPU_Vector3::set_uniform_type);

    BIND_ENUM_CONSTANT(UNIFORM_BUFFER);
    BIND_ENUM_CONSTANT(STORAGE_BUFFER);

    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "data"), "set_data", "get_data");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_double"), "set_is_double", "get_is_double");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "alias"), "set_alias", "get_alias");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "binding"), "set_binding", "get_binding");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "uniform_type", PROPERTY_HINT_ENUM, "Uniform Buffer,Storage Buffer"), "set_uniform_type", "get_uniform_type");
}