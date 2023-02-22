#include "register_types.h"
#include "compute_worker.h"
#include "uniform_set.h"
#include "gpu_uniform.h"
#include "gpu_float.h"
#include "gpu_boolean.h"
#include "gpu_integer.h"
#include "gpu_vector3.h"
#include "dvector3.hpp"
#include "double_vector3.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void initialize_compute_types(ModuleInitializationLevel p_level)
{
    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
    {
        return;
    }

    ClassDB::register_class<ComputeWorker>();

    ClassDB::register_class<UniformSet>();

    ClassDB::register_class<dVector3>();
    //ClassDB::register_class<DoubleVector3>();

    ClassDB::register_class<GPUUniform>(true);
    ClassDB::register_class<GPU_Float>();
    ClassDB::register_class<GPU_Boolean>();
    ClassDB::register_class<GPU_Integer>();
    ClassDB::register_class<GPU_Vector3>();
}


void uninitialize_compute_types(ModuleInitializationLevel p_level){

    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }
}


extern "C"
{
    GDExtensionBool GDE_EXPORT compute_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);
        
        init_obj.register_initializer(initialize_compute_types);
        init_obj.register_terminator(uninitialize_compute_types);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}

