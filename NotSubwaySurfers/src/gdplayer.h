#ifndef GDPLAYER_H
#define GDPLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <vector>

namespace godot {

class GDPlayer : public CharacterBody3D {
	GDCLASS(GDPlayer, CharacterBody3D)

private:
    std::vector<double> positions;
    int curPos;
	double jump_vel;
	double gravity;
	bool pause;
	bool swipe_toggle;
	bool is_forward;
	double forward_max;
	double forward;

    int swipeDir;
	int swipeLen;
	Vector2 startSwipe;
	Vector2 curSwipe;
	bool swiping;
	int threshold;

	bool jumping;
    

protected:
	static void _bind_methods();

public:
	GDPlayer();
	~GDPlayer();

    // void _ready();
    void _physics_process(double delta);
	void _process(double delta);
	void shoot_projectile();
	void _on_button_pressed();
	void _on_area_3d_area_entered(Area3D* area);

	void set_jump_velocity(const double p_jump_velocity);
	double get_jump_velocity() const;
	void set_gravity(const double p_gravity);
	double get_gravity() const;
	void set_swipe(const bool p_swipe);
	bool get_swipe() const;
};

}

#endif