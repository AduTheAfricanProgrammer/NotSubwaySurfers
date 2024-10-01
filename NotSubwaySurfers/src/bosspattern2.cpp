#include "bosspattern2.h"

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
#include <godot_cpp/classes/label3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace godot;

void BossPattern2::_bind_methods() {
}

BossPattern2::BossPattern2() {
    on = false;
    cooldown = 0;
    cooldown_max = 5;
}

BossPattern2::~BossPattern2() {
}

void BossPattern2::_ready(){
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }
}

void BossPattern2::_physics_process(double delta) {
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }
}

void BossPattern2::_process(double delta){
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }

    if (!on) {
        return;
    }

    auto boss = Object::cast_to<Boss>(get_parent()->get_parent());
    if (boss->is_weakness_hit()) {
        transition(StringName("BossStagger"));
        return;
    }

    // Reference ./Weakness/... for ground attacks
    // Implement random attack patterns

    // Dummy pattern
    // if (cooldown > 0) {
    //     cooldown -= delta;
    // } else {
    //     get_parent()->get_parent()->get_parent()->get_node<Node3D>("./Floor_Attacks/front_center")->emit_signal("start");
    //     cooldown = cooldown_max;
    // }
}


void BossPattern2::enter() {
    UtilityFunctions::print("Entered Pattern 2");
    Label3D* state_text = get_parent()->get_parent()->get_node<Label3D>("./MeshInstance3D/Label3D");
    state_text->set_text("Angry");
    on = true;
    // temp_test_timer = 0;
}

void BossPattern2::exit() {
    UtilityFunctions::print("Exited Pattern 2");
    on = false;
}

void BossPattern2::transition(StringName new_state) {
    emit_signal("transition", this, new_state);
}
