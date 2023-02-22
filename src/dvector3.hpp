#ifndef DVECTOR3_CLASS_H
#define DVECTOR3_CLASS_H

#include "double_vector3.hpp"
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

struct dVector3 : Object{
    
    GDCLASS(dVector3, Object);

    enum Precision{
        DOUBLE,
        FLOAT,
        EMPTY
    };

    Precision precision = Precision::EMPTY;

    union{
        Vector3 fvec;
        DoubleVector3 dvec;
    };

    dVector3(){}
    ~dVector3(){}

    _FORCE_INLINE_ dVector3(Precision p){

        switch (p)
        {
            case Precision::DOUBLE:
                dvec = DoubleVector3();
                precision = p;
                break;
            case Precision::FLOAT:
                fvec = Vector3();
                precision = p;
                break;
            default:
                break;
        }
    }

    _FORCE_INLINE_ dVector3(Vector3 a){
        fvec = a;
        precision = Precision::FLOAT;
    }

    _FORCE_INLINE_ dVector3(DoubleVector3 a){
        dvec = a;
        precision = Precision::DOUBLE;
    }

    _FORCE_INLINE_ dVector3(PackedFloat32Array a){
        fvec = Vector3(a[0], a[1], a[2]);
        precision = Precision::FLOAT;
    }

    _FORCE_INLINE_ dVector3(PackedFloat64Array a){
        dvec = DoubleVector3(a);
        precision = Precision::DOUBLE;
    }

    _FORCE_INLINE_ dVector3(Variant a){
        int a_type = a.get_type();

        if(a_type == Variant::VECTOR3){
            fvec = a;
            precision = Precision::FLOAT;
        }
        else if(a_type == Variant::PACKED_FLOAT32_ARRAY){
            PackedFloat32Array b = a;
            fvec = Vector3(b[0], b[1], b[2]);
            precision = Precision::FLOAT;
        }
        else if(a_type == Variant::PACKED_FLOAT64_ARRAY){
            PackedFloat64Array b = a;
            dvec = DoubleVector3(b);
            precision = Precision::DOUBLE;
        }
        else{
            ERR_FAIL_MSG("Variant must be Vector3 or PackedFloat**Array for constructor `dVector3(Variant a)`");
        }
    }

    _FORCE_INLINE_ PackedFloat32Array to_float32_array() const;
    _FORCE_INLINE_ PackedFloat64Array to_float64_array() const;
    _FORCE_INLINE_ PackedByteArray to_byte_array() const;
    _FORCE_INLINE_ Variant to_variant() const;
    _FORCE_INLINE_ static void _bind_methods();
};

PackedFloat32Array dVector3::to_float32_array() const{
    PackedFloat32Array a;
    switch(precision){
    
        case Precision::DOUBLE:
            a.append(dvec.x);
            a.append(dvec.y);
            a.append(dvec.z);
            return a;

        case Precision::FLOAT:
            a.append(fvec.x);
            a.append(fvec.y);
            a.append(fvec.z);
            return a;

        default:
            return a;
    }
}

PackedFloat64Array dVector3::to_float64_array() const{
    PackedFloat64Array a;
    switch(precision){

        case Precision::DOUBLE:
            a.append(dvec.x);
            a.append(dvec.y);
            a.append(dvec.z);
            return a;

        case Precision::FLOAT:
            a.append((double)fvec.x);
            a.append((double)fvec.y);
            a.append((double)fvec.z);
            return a;

        default:
            return a;
    }
}

PackedByteArray dVector3::to_byte_array() const{
    if(precision == Precision::DOUBLE){
        PackedFloat64Array d = to_float64_array();
        return d.to_byte_array();
    }
    else if(precision == Precision::FLOAT){
        PackedFloat32Array f = to_float32_array();
        return f.to_byte_array();
    }
    else{
        return PackedByteArray();
    }
}

Variant dVector3::to_variant() const{
    if(precision == Precision::DOUBLE){
        PackedFloat64Array d = to_float64_array();
        return Variant(d);
    }
    else if(precision == Precision::FLOAT){
        return Variant(fvec);
    }
    else{
        return Variant();
    }
}

void dVector3::_bind_methods(){
    ClassDB::bind_method(D_METHOD("to_float32_array"), &dVector3::to_float32_array);
    ClassDB::bind_method(D_METHOD("to_float64_array"), &dVector3::to_float64_array);
    ClassDB::bind_method(D_METHOD("to_byte_array"), &dVector3::to_byte_array);
    ClassDB::bind_method(D_METHOD("to_variant"), &dVector3::to_variant);
}

#endif // DVECTOR3_CLASS_H