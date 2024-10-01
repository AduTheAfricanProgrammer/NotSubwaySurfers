extends Node3D

signal start
signal stop

# Called when the node enters the scene tree for the first time.
func _ready():
	$model/Area3D/CollisionShape3D.set_deferred("disabled", true)
	$model/Area3D.set_deferred("monitorable", false)
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

func _on_start():
	print(str(self.name) + " is now active")
	self.show()
	$model/Area3D/CollisionShape3D.set_deferred("disabled", false)
	$model/Area3D.set_deferred("monitorable", true)
	pass # Replace with function body.

func _on_stop():
	print(str(self.name) + " is now unactive")
	self.hide()
	$model/Area3D/CollisionShape3D.set_deferred("disabled", true)
	$model/Area3D.set_deferred("monitorable", false)
	pass

func _on_area_3d_area_entered(area):
	_on_stop()
#	self.get_parent().get_parent().emit_signal("weakness_hit")
	self.get_parent().get_parent()._on_boss_weakness_hit()
	pass
