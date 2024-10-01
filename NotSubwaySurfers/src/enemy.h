#ifndef ENEMY_H
#define ENEMY_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <vector>

namespace godot {

class Enemy : public CharacterBody3D {
	GDCLASS(Enemy, CharacterBody3D)

private:
    std::vector<int> positions;
    int currHP;
	bool canDie;
    

protected:
	static void _bind_methods();

public:
	Enemy();
	~Enemy();

    // void _ready();
    void _physics_process(double delta);
	void _process(double delta);

	void can_die() const;
	// void set_gravity(const double p_gravity);
	// double get_gravity() const;
    void spawn_enemy() const;
};

}

#endif