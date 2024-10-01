#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class Projectile : public Node3D {
    GDCLASS(Projectile, Node3D)

private:
    float speed;
    Vector3 spawn_position;
    double time_passed;
    bool pause;
    
protected:
    static void _bind_methods();

public:
    Projectile();
    ~Projectile();
    
    void _ready();
    void _physics_process(double delta);
    void _process(double delta);

    void _on_projectile_area_entered(Area3D* area);
};

}

#endif