#include "boss.h"
#include "projectile.h"

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
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>
#include <godot_cpp/classes/gpu_particles3d.hpp>

#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace godot;

void Boss::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_low_hp"), &Boss::get_low_hp);
    ClassDB::bind_method(D_METHOD("get_is_stagger"), &Boss::get_is_stagger);
    ClassDB::bind_method(D_METHOD("_on_hit", "area"), &Boss::_on_hit);
    ClassDB::bind_method(D_METHOD("_on_boss_weakness_hit"), &Boss::_on_boss_weakness_hit);
    ClassDB::bind_method(D_METHOD("_on_boss_end_stagger"), &Boss::_on_boss_end_stagger);
    ClassDB::bind_method(D_METHOD("boss_death"), &Boss::boss_death);


    ADD_SIGNAL(MethodInfo("weakness_hit"));
    ADD_SIGNAL(MethodInfo("end_stagger"));
}

Boss::Boss() {
    hp = 100;
    low_hp = false;

    is_staggered = false;
    weakness_hit = false;
    weakness_timer = 5;
    weakness_timer_max = 5;
    death = false;
    Node3D* current_weakness = nullptr;
    // Dummy boolean for nullptr reference fencepost case
    first = true;
}

Boss::~Boss() {
}

void Boss::_ready() {
    auto engine = Engine::get_singleton();
    if(engine->is_editor_hint()){
        return;
    }

    auto area = get_node<Area3D>("./Hitbox"); 
    if(area != nullptr){
        area->connect("area_entered", Callable(this, "_on_hit"));
    }

    this->connect("weakness_hit", Callable(this, "_on_boss_weakness_hit"));
    this->connect("end_stagger", Callable(this, "_on_boss_end_stagger"));
}

void Boss::_process(double delta) {
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }


    if (!is_staggered) {
        if (weakness_timer > 0) {
            weakness_timer -= delta;
        } else {
            weakness_timer = weakness_timer_max;
            
            // Pick another random weakness mesh to turn on
            // Generate a random number between 0 and 5
            if (!first) {
                if (current_weakness->has_signal("stop")) {
                    current_weakness->emit_signal("stop");
                }
            } else {
                first = false;
            }

            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int randomInt = std::rand() % 6;

            switch (randomInt) {
                case 0:
                    UtilityFunctions::print("Top Left Weakness on");
                    current_weakness = get_node<Node3D>("./Weaknesses/top_left");
                    break;
                case 1:
                    UtilityFunctions::print("Bottom Left Weakness on");
                    current_weakness = get_node<Node3D>("./Weaknesses/bottom_left");
                    break;
                case 2:
                    UtilityFunctions::print("Bottom center Weakness on");
                    current_weakness = get_node<Node3D>("./Weaknesses/bottom_center");
                    break;
                case 3:
                    UtilityFunctions::print("Bottom right Weakness on");
                    current_weakness = get_node<Node3D>("./Weaknesses/bottom_right");
                    break;
                case 4:
                    UtilityFunctions::print("Top Right Weakness on");
                    current_weakness = get_node<Node3D>("./Weaknesses/top_right");
                    break;
                case 5:
                    UtilityFunctions::print("Top Center Weakness on");
                    current_weakness = get_node<Node3D>("./Weaknesses/top_center");
                    break;
                default:
                    break;
            }

            if (current_weakness->has_signal("start")) {
                current_weakness->emit_signal("start");
            }
        }
    }
}

void Boss::_on_hit(Area3D* area) {
    // ProgressBar* healthbar = get_node<ProgressBar>("./healthbar/Sprite3D/SubViewport/ProgressBar");

    if (is_staggered) {
        ProgressBar* healthbar = get_node<ProgressBar>("./healthbar/Sprite3D/SubViewport/ProgressBar");
        hp -= 5;
        healthbar->set_value(hp);
        float hp_ratio = hp / 100.0;
        Color lerped_color = Color((1.0 - hp_ratio) * 2.0, hp_ratio * 2.0, 0.0, 1.0);  // Lerp from green to red
        if (lerped_color.r < 0) {
            lerped_color.r = 0;
        }
        if (lerped_color.r > 1) {
            lerped_color.r = 1;
        }

        if (lerped_color.g < 0) {
            lerped_color.g = 0;
        }
        if (lerped_color.g > 1) {
            lerped_color.g = 1;
        }
        Ref<StyleBoxFlat> custom_style = healthbar->get_theme_stylebox("fill");
        custom_style->set_bg_color(lerped_color);
        healthbar->add_theme_stylebox_override("fill", custom_style);

        // hp is low, go back to base
        if (hp <= 0) {
            // Emit death particles
            get_parent()->get_node<GPUParticles3D>("./explosion/spark")->restart();
            get_parent()->get_node<GPUParticles3D>("./explosion/flash")->restart();
            get_parent()->get_node<GPUParticles3D>("./explosion/fire")->restart();
            death = true;
            //this->queue_free();
        } else if (hp <= 50) {
            low_hp = true;
        }
    }
}

void Boss::_on_boss_weakness_hit() {
    UtilityFunctions::print("Boss - Weakness hit");
    weakness_hit = true;
    is_staggered = true;
    current_weakness->emit_signal("stop");
    weakness_timer = weakness_timer_max;
}

void Boss::_on_boss_end_stagger() {
    weakness_hit = false;
    is_staggered = false;
}

void Boss::_physics_process(double delta) {
    auto engine = Engine::get_singleton();
    if(engine->is_editor_hint()){
        return;
    }
}

int Boss::get_hp() {
    return hp;
}

bool Boss::get_low_hp() {
    return low_hp;
}

bool Boss::get_is_stagger() {
    return is_staggered;
}

bool Boss::is_weakness_hit() {
    return weakness_hit;
}

bool Boss::boss_death() {
    return death;
}

// _on_boss_end_stagger
// _on_boss_weakness_hit