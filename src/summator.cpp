#include "summator.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/tcp_server.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Summator::Summator()
{
    count = 0;

    test_arr.resize(10);
    test_arr[4] = Variant(1.515);    
}

Summator::~Summator()
{
}

void Summator::_ready()
{
    UtilityFunctions::print(test_arr[4]);
    emit_signal("custom_signal", "name", 13);
}

void Summator::add(int p_value)
{
    count += p_value;
}

void Summator::reset()
{
    count = 0;
}

int Summator::get_total() const
{
    return count;
}

Variant Summator::get_array_element(int index)
{
    return test_arr[index];
}

void Summator::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("add", "value"), &Summator::add, DEFVAL(1));
    ClassDB::bind_method(D_METHOD("reset"), &Summator::reset);
    ClassDB::bind_method(D_METHOD("get_total"), &Summator::get_total);
    ClassDB::bind_method(D_METHOD("get_array_element", "index"), &Summator::get_array_element);

    ADD_SIGNAL(MethodInfo("custom_signal", PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "value")));

}