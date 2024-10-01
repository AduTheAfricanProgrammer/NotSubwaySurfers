extends Node3D
class_name Boss_Generator

## This builds and operates the terrain "conveyor belt"
##
## A set of randomly choosen terrain blocks is rendered to the viewport.
## As the game played the terrian is moved in the positive X direction.

## Holds the catalog of loaded terrian block scenes
var TerrainBlocks: Array = []
var terrain_belt: Array[MeshInstance3D] = []
var pause = false
@export var terrain_velocity: float = 5.0
@export var num_terrain_blocks = 10
@export_dir var terrian_blocks_path = "res://Boss_Stages"


func _ready() -> void:
	_load_terrain_scenes(terrian_blocks_path)
	_init_blocks(num_terrain_blocks)


func _physics_process(delta: float) -> void:
	if Input.is_action_just_pressed("menu"):
		pause = not pause
	
	if not pause:
		_progress_terrain(delta)


func _init_blocks(number_of_blocks: int) -> void:
	var x_position = 0.0
	for block_index in number_of_blocks:
		var block = TerrainBlocks.pick_random().instantiate()
		var mesh = block.mesh
		if mesh:
			var mesh_size = mesh.get_aabb().size
			block.position.x = x_position
			x_position -= mesh_size.y / 3 # Update the x_position for the next block
			add_child(block)
			terrain_belt.append(block)
			# print("loaded")
			# print(x_position)
		else:
			print("Mesh not found in the instantiated block")


func _progress_terrain(delta: float) -> void:
	for block in terrain_belt:
		block.position.x += terrain_velocity * delta

	if terrain_belt[0].position.x >= terrain_belt[0].get_aabb().size.y/2:
		var last_terrain = terrain_belt[-1]
		var first_terrain = terrain_belt.pop_front()

		var block = TerrainBlocks.pick_random().instantiate()
		_append_to_far_edge(last_terrain, block)
		add_child(block)
		terrain_belt.append(block)
		first_terrain.queue_free()


func _append_to_far_edge(target_block: MeshInstance3D, appending_block: MeshInstance3D) -> void:
	var target_mesh_size = target_block.mesh.get_aabb().size
	var appending_mesh_size = appending_block.mesh.get_aabb().size
	appending_block.position.x = target_block.position.x - target_mesh_size.y / 3 #- appending_mesh_size.x/1
	# print(appending_block.position.x)


func _load_terrain_scenes(target_path: String) -> void:
	var dir = DirAccess.open(target_path)
	for scene_path in dir.get_files():
		# print("Loading terrian block scene: " + target_path + "/" + scene_path)
		TerrainBlocks.append(load(target_path + "/" + scene_path))


func _on_button_pressed():
	pause = false
	pass # Replace with function body.
