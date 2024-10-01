#include "bossstagger.h"

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/navigation_agent3d.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/progress_bar.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/csg_sphere3d.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/csg_box3d.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/center_container.hpp>
#include <godot_cpp/classes/navigation_agent3d.hpp>
#include <godot_cpp/classes/navigation_region3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>
#include <godot_cpp/classes/label3d.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace godot;

void BossStagger::_bind_methods() {
}

BossStagger::BossStagger() {
    on = false;
    stagger_timer = 4;
    stagger_timer_max = 4;
}

BossStagger::~BossStagger() {
}

void BossStagger::_ready(){
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }
}

void BossStagger::_physics_process(double delta) {
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }
}

void BossStagger::_process(double delta){
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint() ){
        return;
    }

    if (!on) {
        return;
    }
    
    stagger_timer -= delta;

    auto boss = Object::cast_to<Boss>(get_parent()->get_parent());
    if (stagger_timer <= 0) {
        stagger_timer = stagger_timer_max;
        transition(StringName("BossPattern1"));
    }

    // OPTIONAL Stagger behaviors (animation?)
}


void BossStagger::enter() {
    UtilityFunctions::print("Entered staggered");
    Label3D* state_text = get_parent()->get_parent()->get_node<Label3D>("./MeshInstance3D/Label3D");
    state_text->set_text("Staggered");
    on = true;
}

void BossStagger::exit() {
    UtilityFunctions::print("Exited staggered");
    auto boss = Object::cast_to<Boss>(get_parent()->get_parent());
    boss->emit_signal("end_stagger");
    on = false;
}

void BossStagger::transition(StringName new_state) {
    emit_signal("transition", this, new_state);
}
