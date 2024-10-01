#ifndef BOSS_H
#define BOSS_H


#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class Boss : public Node3D {
    GDCLASS(Boss, Node3D)

private:
    int hp;
    bool low_hp;

    bool is_staggered;
    bool weakness_hit;
    double weakness_timer;
    double weakness_timer_max;

    Node3D* current_weakness;
    bool first;

    bool death;
    
protected:
    static void _bind_methods();

public:
    Boss();
    ~Boss();
    
    void _ready();
    void _physics_process(double delta);
    void _process(double delta);

    void _on_hit(Area3D* area);
    void _on_boss_weakness_hit();
    void _on_boss_end_stagger();

    int get_hp();
    bool get_is_stagger();
    bool get_low_hp();

    bool is_weakness_hit();

    bool boss_death();
};

}

#endif