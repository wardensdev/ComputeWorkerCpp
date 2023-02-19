#include "register_types.h"
#include "summator.h"
#include "compute_worker.h"
#include "uniform_set.h"
#include "gpu_uniform.h"
#include "gpu_float.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_summator_types(ModuleInitializationLevel p_level){

    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }

    ClassDB::register_class<Summator>();
    ClassDB::register_class<ComputeWorker>();
    ClassDB::register_class<UniformSet>();
    ClassDB::register_class<GPUUniform>();

    ClassDB::register_class<GPU_Float>();
}


void uninitialize_summator_types(ModuleInitializationLevel p_level){

    if(p_level != MODULE_INITIALIZATION_LEVEL_SCENE){
        return;
    }
}


extern "C"
{
    GDExtensionBool GDE_EXPORT summator_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

        init_obj.register_initializer(initialize_summator_types);
        init_obj.register_terminator(uninitialize_summator_types);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}

