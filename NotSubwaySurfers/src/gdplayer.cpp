#include "gdplayer.h"
#include "projectile.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/audio_stream_player3d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <cmath>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/scene_tree.hpp>



using namespace godot;

void GDPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_jump_velocity"), &GDPlayer::get_jump_velocity);
    ClassDB::bind_method(D_METHOD("set_jump_velocity", "p_jump_velocity"), &GDPlayer::set_jump_velocity);
    ClassDB::add_property("GDPlayer", PropertyInfo(Variant::FLOAT, "jump_velocity", PROPERTY_HINT_RANGE, "1,10,0.1"), "set_jump_velocity", "get_jump_velocity");

    ClassDB::bind_method(D_METHOD("get_gravity"), &GDPlayer::get_gravity);
    ClassDB::bind_method(D_METHOD("set_gravity", "p_gravity"), &GDPlayer::set_gravity);
    ClassDB::add_property("GDPlayer", PropertyInfo(Variant::FLOAT, "gravity", PROPERTY_HINT_RANGE, "1,10,0.1"), "set_gravity", "get_gravity");

    ClassDB::bind_method(D_METHOD("get_swipe"), &GDPlayer::get_swipe);
    ClassDB::bind_method(D_METHOD("set_swipe", "p_swipe"), &GDPlayer::set_swipe);
    ClassDB::add_property("GDPlayer", PropertyInfo(Variant::BOOL, "Enable Swipe"), "set_swipe", "get_swipe");

    ClassDB::bind_method(D_METHOD("_on_area_3d_area_entered", "area"), &GDPlayer::_on_area_3d_area_entered);

    ADD_SIGNAL(MethodInfo("hurt"));
}

GDPlayer::GDPlayer() {
	// Initialize any variables here.
	positions = {-2.8, 0, 2.8};
    curPos = 1;
    swipeDir = 0;
    jump_vel = 7;
    gravity = 9.8;
    pause = false;
    is_forward = false;
    forward_max = 1;
    forward = 0;
    
    // True = allow swipe input
    swipe_toggle = true;

    // Swiping variables
    swipeLen = 100;
	startSwipe = Vector2(0, 0);
	curSwipe = Vector2(0, 0);
	swiping = false;
	threshold = 20;

    // states
    jumping = false;
}

GDPlayer::~GDPlayer() {
	// Add your cleanup here.
}

void GDPlayer::_process(double delta) {
    return;
}

void GDPlayer::_physics_process(double delta) {
    auto engine = Engine::get_singleton();
    if (engine->is_editor_hint()) {
        return;
    }

    auto input = Input::get_singleton();

    // Pause and don't allow any other inputs
    if (input->is_action_just_pressed("menu")) {
        pause = !pause;
    }

    if (pause) {
        return;
    }

    AnimationPlayer *anim = get_node<AnimationPlayer>("AnimationPlayer");

    AudioStreamPlayer3D *run_sfx = get_node<AudioStreamPlayer3D>("RunningSFX");
    AudioStreamPlayer3D *sprint_sfx = get_node<AudioStreamPlayer3D>("SprintingSFX");

    anim->set_speed_scale(1);
    if(is_on_floor()) {
        anim->play("Run");
        if (!run_sfx->is_playing() && !is_forward) {
            if (sprint_sfx->is_playing()) {
                sprint_sfx->stop();
            }
            run_sfx->play();
        } else if (!sprint_sfx->is_playing() && is_forward) {
            if (run_sfx->is_playing()) {
                run_sfx->stop();
            }
            sprint_sfx->play();
        }
    } else {
        if (run_sfx->is_playing()) {
            run_sfx->stop();
        }
        if (sprint_sfx->is_playing()) {
            sprint_sfx->stop();
        }
    }

    if (input->is_action_just_pressed("shoot_projectile")) {
        shoot_projectile();
    }

    if (input->is_action_just_pressed("right_press")) {
        // UtilityFunctions::print("moving forward");
        is_forward = true;
    }

    if (input->is_action_just_released("right_press")) {
        // UtilityFunctions::print("moving backwards");
        is_forward = false;
    }

    if (input->is_action_just_pressed("move_left")) {
        // UtilityFunctions::print("left pressed");
        swipeDir = 1;
        get_node<AudioStreamPlayer3D>("SwipingSFX")->play();
    }

    if (input->is_action_just_pressed("move_right")) {
        // UtilityFunctions::print("right pressed");
        swipeDir = -1;
        get_node<AudioStreamPlayer3D>("SwipingSFX")->play();
    }

    Vector3 cur_vel = get_velocity();
    if (input->is_action_just_pressed("jump") && is_on_floor()) {
        // UtilityFunctions::print("jump pressed");
        jumping = true;
        cur_vel.y = jump_vel;
        get_node<AudioStreamPlayer3D>("JumpingSFX")->play();
    }

    if (jumping) {
        anim->play("Jump");
        if (is_on_floor()) {
            jumping = false;
        }
    }

    if (swipe_toggle) {
        // Get initial position
        if (input->is_action_just_pressed("press")) {
            if (!swiping) {
                swiping = true;
                startSwipe = get_viewport()->get_mouse_position();
            }
        }
        
        // Grab final position to decide swipe direction
        if (input->is_action_pressed("press")) {
            if (swiping) {
                curSwipe = get_viewport()->get_mouse_position();
                
                if (startSwipe.distance_to(curSwipe) >= swipeLen) {
                    if (abs(startSwipe.y - curSwipe.y) < threshold) {
                        // Move right
                        if ((startSwipe.x - curSwipe.x) < 0) {
                            UtilityFunctions::print("left swipe");
                            swipeDir = -1;
                        // Move left
                        } else {
                            UtilityFunctions::print("right swipe");
                            swipeDir = 1;
                        }
                    }
                    // Jump
                    if (abs(startSwipe.x - curSwipe.x) < threshold) {
                        if ((startSwipe.y - curSwipe.y) > 0 && is_on_floor()) {
                            UtilityFunctions::print("jump swipe");
                            cur_vel.y = jump_vel;
                        }
                    }

                    swiping = false;
                }
            }
        } else {
            swiping = false;
        }
    }

    if (swipeDir == 1) {
		if (curPos < 2) {
			curPos += 1;
			swipeDir = 0;
        }
    } else if (swipeDir == -1) {
		if (curPos > 0) {
			curPos -= 1;
			swipeDir = 0;
        }
    }
			

    Vector3 cur_pos = get_position();
    cur_pos.z = Math::lerp((double)cur_pos.z, positions[curPos], delta*10);

    Camera3D* camera = get_node<Camera3D>("./Camera3D");
    double deltaSpeed = 2 * delta;
    if (is_forward) {
        if (forward < forward_max) {
            forward += deltaSpeed;
            camera->set_position(camera->get_position() - Vector3(deltaSpeed, 0, 0));
            cur_pos.x -= deltaSpeed;
        }
    } else {
        if (forward > 0) {
            forward -= deltaSpeed;
            camera->set_position(camera->get_position() + Vector3(deltaSpeed, 0, 0));
            cur_pos.x += deltaSpeed;
        }
    }

    cur_vel.y = cur_vel.y - gravity * delta;

    set_velocity(cur_vel);
    set_position(cur_pos);
    move_and_slide();
}

void GDPlayer::shoot_projectile() {
    Ref<PackedScene> projectileScene = ResourceLoader::get_singleton()->load("res://scenes/projectile.tscn");
    // Node3D* model = get_node<Node3D>("Model");

    if(projectileScene.is_valid()){
        Projectile* node = Object::cast_to<Projectile>(projectileScene->instantiate());

        get_parent()->add_child(node);
        Vector3 shoot_origin = get_node<Node3D>("./projectileOrigin")->get_global_position();

        node->set_global_position(shoot_origin);
    }
}

// Unpause game when menu is closed
void GDPlayer::_on_button_pressed() {
    pause = false;
    return;
}

void GDPlayer::_on_area_3d_area_entered(Area3D* area) {
    if (area->has_meta("is_hurt") && area->get_meta("is_hurt")) {
        UtilityFunctions::print("Got hit!");
        emit_signal("hurt");
        get_tree()->reload_current_scene();
        get_parent()->queue_free();
    }
}


void GDPlayer::set_jump_velocity(const double p_jump_velocity) {
    jump_vel = p_jump_velocity;
}

double GDPlayer::get_jump_velocity() const {
    return jump_vel;
}

void GDPlayer::set_gravity(const double p_gravity){
    gravity = p_gravity;
}
double GDPlayer::get_gravity() const{
    return gravity;
}

void GDPlayer::set_swipe(const bool p_swipe) {
    swipe_toggle = p_swipe;
}

bool GDPlayer::get_swipe() const {
    return swipe_toggle;
}