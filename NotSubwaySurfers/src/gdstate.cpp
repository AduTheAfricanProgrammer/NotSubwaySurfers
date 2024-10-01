#include "gdstate.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void GDState::_bind_methods() {
    ADD_SIGNAL(MethodInfo("transition"));
}

GDState::GDState() {
}

GDState::~GDState() {
}

void GDState::_ready(){
    auto engine = Engine::get_singleton();
    if(engine->is_editor_hint()){
        return;
    }
}

void GDState::_physics_process(double delta) {
}

void GDState::_process(double delta){
}

void GDState::enter() {
    UtilityFunctions::print("THIS IS STATES DEFAULT ENTER");
}

void GDState::exit() {
    UtilityFunctions::print("THIS IS STATES DEFAULT EXIT");
}

void GDState::transition() {

}