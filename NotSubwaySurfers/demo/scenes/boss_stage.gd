extends Node3D

var timer = 0
var low_hp = false
var stagger = false
var win_scene = preload("res://scenes/win_screen.tscn")

# Called when the node enters the scene tree for the first time.
func _ready():
	$Timer.start()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if ($Boss):

		if ($Boss.boss_death()):
			self.queue_free()
			load_win_screen()
		if ($Boss and $Boss.get_low_hp() and not low_hp):
			low_hp = true
			timer = 0
		
		stagger = $Boss.get_is_stagger()
		if (stagger):
			$Floor_Attacks/back_left._on_reset()
			$Floor_Attacks/back_right._on_reset()
			$Floor_Attacks/back_center._on_reset()
			$Floor_Attacks/front_left._on_reset()
			$Floor_Attacks/front_right._on_reset()
			$Floor_Attacks/front_center._on_reset()
			
		if (not stagger):
			if (not low_hp):
				attack1()
			else:
				attack2()


func attack1():
	if (timer == 1):
		$Floor_Attacks/back_left._on_start()
		$Floor_Attacks/front_left._on_start()
		
	if (timer == 6):
		$Floor_Attacks/back_center._on_start()
		$Floor_Attacks/front_center._on_start()
	
	if (timer == 12):
		$Floor_Attacks/back_right._on_start()
		$Floor_Attacks/front_right._on_start()
		
	if (timer >= 18):
		timer = 0
	
func attack2():
	# 1 3 5 11 13 19 21 24
	# 1 4 9 15 19 25 28 32
	if (timer == 1): 
		$Floor_Attacks/back_left._on_start()
		$Floor_Attacks/front_left._on_start()
	# 1 or .5 seconds
	if (timer == 4):
		$Floor_Attacks/back_center._on_start()
		$Floor_Attacks/front_center._on_start()
	# 1 or .5 seconds
	if (timer == 9):
		$Floor_Attacks/back_right._on_start()
		$Floor_Attacks/front_right._on_start()
		
	if (timer == 15):
		$Floor_Attacks/back_center._on_start()
		$Floor_Attacks/front_center._on_start()
	
	if (timer == 19):
		$Floor_Attacks/back_left._on_start()
		$Floor_Attacks/back_right._on_start()
		$Floor_Attacks/front_left._on_start()
		$Floor_Attacks/front_right._on_start()
		
	if (timer == 25):
		$Floor_Attacks/back_left._on_start()
		$Floor_Attacks/front_center._on_start()
		$Floor_Attacks/back_right._on_start()
	
	if (timer == 28):
		$Floor_Attacks/front_left._on_start()
		$Floor_Attacks/back_center._on_start()
		$Floor_Attacks/front_right._on_start()
	
	if (timer >= 32):
		timer = 0
	pass


func _on_timer_timeout():
	timer += 1
	pass # Replace with function body.
	
func load_win_screen():
	var win_scene_instance = win_scene.instantiate()
	get_tree().root.add_child(win_scene_instance)  # Add the win scene to the scene tree
	print(get_tree().current_scene)
	get_tree().current_scene.queue_free()  # Optionally, free the current scene if you want to replace it entirely

