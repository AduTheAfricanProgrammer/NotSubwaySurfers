#include "projectile.h"

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/core/math.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace godot;

void Projectile::_bind_methods() {
    ADD_SIGNAL(MethodInfo("hit_weakness"));
    ClassDB::bind_method(D_METHOD("_on_projectile_area_entered", "area"), &Projectile::_on_projectile_area_entered);
}

Projectile::Projectile() {
    speed = 20;
    pause = false;
    time_passed = 0;
}

Projectile::~Projectile() {
}

void Projectile::_ready(){
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }

    auto area = get_node<Area3D>("./Area3D");
    if(area != nullptr){
        area->connect("area_entered", Callable(this, "_on_projectile_area_entered"));
    }
}

void Projectile::_on_projectile_area_entered(Area3D* area){
    if (area->has_meta("is_weakness") && area->get_meta("is_weakness")) {
        UtilityFunctions::print("Boss weakness hit");
        emit_signal("hit_weakness");
    }

    this->queue_free();
}

void Projectile::_physics_process(double delta) {
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    } 
    
    auto input = Input::get_singleton();

    // Pause and don't allow any other inputs
    if (input->is_action_just_pressed("menu")) {
        pause = !pause;
    }

    if (pause) {
        return;
    }

    time_passed += delta;
    if (time_passed > 3) {
        this->queue_free();
    }

    Vector3 position = get_position();

    Vector3 direction = Vector3(-1, 0, 0);
    position += direction * speed * delta;

    set_position(position);
}

void Projectile::_process(double delta){
    return;
}