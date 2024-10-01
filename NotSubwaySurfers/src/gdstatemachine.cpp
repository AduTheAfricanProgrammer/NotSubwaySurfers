#include "gdstatemachine.h"
#include "gdstate.h"

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace godot;

void GDStateMachine::_bind_methods() {;
    ClassDB::bind_method(D_METHOD("_on_child_transition"), &GDStateMachine::_on_child_transition);
}

GDStateMachine::GDStateMachine() {
    current_state = nullptr;
    initial_state = nullptr;
    std::map<godot::StringName, GDState*> states;
}

GDStateMachine::~GDStateMachine() {
}

void GDStateMachine::_ready(){
    auto engine = Engine::get_singleton();
    if(engine->is_editor_hint()){
        return;
    }
    
    for (int i = 0; i < get_child_count(); i++) {
        Node* curr_child = get_child(i);
        if (curr_child->has_meta("is_state") && curr_child->get_meta("is_state")) {
            GDState* curr_state = Object::cast_to<GDState>(curr_child);
            
            // Add this state to our states dictionary
            states[curr_child->get_name()] = curr_state;

            UtilityFunctions::print(curr_child->get_name());

            // States will emit "transition" when you want to exit
            curr_child->connect("transition", Callable(this, "_on_child_transition"));
        }
    }

    if (initial_state) {
        UtilityFunctions::print("Initial state = true", initial_state);
        initial_state->enter();
        UtilityFunctions::print("Initial state ENTERED");
        current_state = initial_state;
    } else {
        UtilityFunctions::print("Defaulted, setting wander as current state");
        current_state = states[StringName("BossPattern1")];
        current_state->enter();
    }
}

void GDStateMachine::_physics_process(double delta) {
    if (current_state) {
        // current_state->_physics_process(delta);
    }
}

void GDStateMachine::_process(double delta){
    if (current_state) {
        // current_state->_process(delta);
    }
}

void GDStateMachine::_on_child_transition(GDState* state, StringName new_state_name) {
    if (state != current_state) {
        return;
    }

    GDState* new_state = states[new_state_name];
    if (!new_state) {
        return;
    }

    if (current_state) {
        current_state->exit();
    }

    new_state->enter();
    current_state = new_state;
}