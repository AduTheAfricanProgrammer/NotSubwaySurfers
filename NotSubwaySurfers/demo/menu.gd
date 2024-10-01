extends Control

var scene

# Called when the node enters the scene tree for the first time.
func _ready():
	get_node("directions").hide()
	get_node("directions/exit_button").disabled = true
	get_node("main/join_button").disabled = false
	get_node("main/directions_button").disabled = false
	get_node("main").show()
	
	# Remove all other scenes
	for i in get_tree().root.get_child_count():
		if get_tree().root.get_child(i).name != "menu":
			get_tree().root.get_child(i).queue_free()
			
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_exit_button_pressed():
	get_node("directions").hide()
	get_node("directions/exit_button").disabled = true
	get_node("main/join_button").disabled = false
	get_node("main/directions_button").disabled = false
	get_node("main").show()
	pass # Replace with function body.


func _on_directions_button_pressed():
	get_node("main/join_button").disabled = true
	get_node("main/directions_button").disabled = true
	get_node("main").hide()
	get_node("directions").show()
	get_node("directions/exit_button").disabled = false
	pass # Replace with function body.


func _on_join_button_pressed():
	if get_tree().root.has_node("GameScene"):
		return;
	# players should get the scene, spawn players
	scene = load("res://scenes/main.tscn").instantiate()
	#scene = load("res://scenes/boss_stage.tscn").instantiate()

	scene.name = "GameScene"
	get_tree().root.add_child(scene)
	scene.show()
	self.hide()	
	pass # Replace with function body.
	
func _on_death():
	self.show()
