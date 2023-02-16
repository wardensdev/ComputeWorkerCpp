#ifndef SUMMATOR_CLASS_H
#define SUMMATOR_CLASS_H

#ifdef WIN32
#include <Windows.h>
#endif

#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Summator : public Node
{
    GDCLASS(Summator, Node);

    int count;
    Array test_arr;

protected:
    static void _bind_methods();

public:
    Summator();
    ~Summator();

    void _ready();

    void add(int p_value);
    void reset();
    int get_total() const;
    Variant get_array_element(int index);
};

#endif // SUMMATOR_CLASS_H