extends Node3D

var pause = false

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if Input.is_action_just_pressed("menu"):
		pause = !pause

	if pause:
		get_node("pause_menu").show()
	else:
		get_node("pause_menu").hide()
	pass


func _on_button_pressed():
	get_tree().root.get_node("menu").show()
	self.queue_free()
	pass # Replace with function body.
