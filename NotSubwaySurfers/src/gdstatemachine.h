#ifndef GDSTATEMACHINE_H
#define GDSTATEMACHINE_H

#include "gdstate.h"
#include <map>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class GDStateMachine : public Node {
    GDCLASS(GDStateMachine, Node)

private:
    GDState* initial_state;
    GDState* current_state;
    std::map<godot::StringName, GDState*> states;

protected:
    static void _bind_methods();

public:
    GDStateMachine();
    ~GDStateMachine();
    
    void _ready();
    void _physics_process(double delta);
    void _process(double delta);

    void _on_child_transition(GDState* state, StringName new_state_name);
};

}

#endif