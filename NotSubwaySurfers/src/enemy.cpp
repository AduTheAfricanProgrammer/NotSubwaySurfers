#include "enemy.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <cmath>

using namespace godot;

void Enemy::_bind_methods() {

    // ClassDB::bind_method(D_METHOD("get_gravity"), &Enemy::get_gravity);
    // ClassDB::bind_method(D_METHOD("set_gravity", "p_gravity"), &Enemy::set_gravity);
    // ClassDB::add_property("Enemy", PropertyInfo(Variant::FLOAT, "gravity", PROPERTY_HINT_RANGE, "1,10,0.1"), "set_gravity", "get_gravity");

    ClassDB::bind_method(D_METHOD("spawn_enemy"), &Enemy::spawn_enemy);
    ClassDB::bind_method(D_METHOD("can_die"), &Enemy::can_die);

}


Enemy::Enemy() {
	// Initialize any variables here.
	positions = {-3, 0, 3};
    currHP = 1;
	canDie = false;
}


Enemy::~Enemy() {
	// Add your cleanup here.
}

void Enemy::_process(double delta) {
    return;
}

void Enemy::_physics_process(double delta) {
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }
}

void Enemy::spawn_enemy() const {
    return ;
}

void Enemy::can_die() const {
    return ;
}