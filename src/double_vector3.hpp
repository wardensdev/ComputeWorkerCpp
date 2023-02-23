#ifndef DOUBLE_VECTOR3_CLASS_H
#define DOUBLE_VECTOR3_CLASS_H

#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

struct DoubleVector3{

    double x;
    double y;
    double z;

    _FORCE_INLINE_ DoubleVector3(){}
    _FORCE_INLINE_ ~DoubleVector3(){}

    _FORCE_INLINE_ DoubleVector3(PackedFloat64Array a){
        x = a[0];
        y = a[1];
        z = a[2];
    }
    _FORCE_INLINE_ DoubleVector3(PackedFloat32Array a){
        x = (double)a[0];
        y = (double)a[1];
        z = (double)a[2];
    }
    _FORCE_INLINE_ DoubleVector3(Vector3 a){
        x = (double)a.x;
        y = (double)a.y;
        z = (double)a.z;
    }

    Vector3 to_vector3() const{
        Vector3 gd;
        gd.x = (float)x;
        gd.y = (float)y;
        gd.z = (float)z;
        return gd;
    }
    PackedFloat64Array to_float_array() const{
        PackedFloat64Array a;
        a.append(x);
        a.append(y);
        a.append(z);
        return a;
    }
};

#endif // DOUBLE_VECTOR3_CLASS_H