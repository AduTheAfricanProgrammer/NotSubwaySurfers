extends Node3D

var timer = 0
var low_hp = false
var stagger = false


# Called when the node enters the scene tree for the first time.
func _ready():
	$Timer.start()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if (not stagger):
		if (not low_hp):
			attack1()
		else:
			attack2()
	
func attack1():
	if (timer == 1):
		$back_left._on_start()
		$front_left._on_start()
		
	if (timer == 5):
		$back_center._on_start()
		$front_center._on_start()
	
	if (timer == 9):
		$back_right._on_start()
		$front_right._on_start()
		
	if (timer == 13):
		timer = 0
	
func attack2():
	if (timer == 1): 
		$back_left._on_start()
		$front_left._on_start()
	# 1 or .5 seconds
	if (timer == 3):
		$back_center._on_start()
		$front_center._on_start()
	# 1 or .5 seconds
	if (timer == 5):
		$back_right._on_start()
		$front_right._on_start()
		
	if (timer == 11):
		$back_center._on_start()
		$front_center._on_start()
	
	if (timer == 13):
		$back_left._on_start()
		$back_right._on_start()
		$front_left._on_start()
		$front_right._on_start()
		
	if (timer == 19):
		$back_left._on_start()
		$front_center._on_start()
		$back_right._on_start()
	
	if (timer == 21):
		$front_left._on_start()
		$back_center._on_start()
		$front_right._on_start()
	
	if (timer == 24):
		timer = 0
	pass


func _on_timer_timeout():
	timer += 1
	pass # Replace with function body.
