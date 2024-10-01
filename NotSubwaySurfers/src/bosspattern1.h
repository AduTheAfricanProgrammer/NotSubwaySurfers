#ifndef BOSSPATTERN1_H
#define BOSSPATTERN1_H

#include "gdstate.h"
#include "boss.h"

#include <map>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class BossPattern1 : public GDState  {
    GDCLASS(BossPattern1, GDState)

private:
    bool on;
    double cooldown;
    double cooldown_max;

protected:
    static void _bind_methods();

public:
    BossPattern1();
    ~BossPattern1();
    
    void _ready();
    void _physics_process(double delta);
    void _process(double delta);
    void enter() override;
    void exit() override;
    void transition(StringName new_state);
};

}

#endif