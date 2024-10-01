#ifndef BOSSSTAGGER_H
#define BOSSSTAGGER_H

#include "gdstate.h"
#include "boss.h"

#include <map>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class BossStagger : public GDState  {
    GDCLASS(BossStagger, GDState)

private:
    bool on;
    double stagger_timer;
    double stagger_timer_max;


protected:
    static void _bind_methods();

public:
    BossStagger();
    ~BossStagger();
    
    void _ready();
    void _physics_process(double delta);
    void _process(double delta);
    void enter() override;
    void exit() override;
    void transition(StringName new_state);
};

}

#endif