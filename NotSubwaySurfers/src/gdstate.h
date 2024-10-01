#ifndef GDSTATE_H
#define GDSTATE_H


#include <map>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class GDState : public Node3D {
    GDCLASS(GDState, Node3D)

private:

protected:
    static void _bind_methods();

public:
    GDState();
    virtual ~GDState();
    
    virtual void _ready();
    virtual void _physics_process(double delta);
    virtual void _process(double delta);

    virtual void transition();
    virtual void enter();
    virtual void exit();
};

}

#endif