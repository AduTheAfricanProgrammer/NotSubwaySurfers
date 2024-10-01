extends Node3D

signal start
signal reset

var countdown_max = 3
var countdown = 3
# If spike is currently attacking
var active = false
# Spike's up speed
var speed = 15
# When spike is out, let it linger for a time
var linger = false
var linger_countdown = .6
var linger_countdown_max = .6
# Transparency var
var transparency = 255

# Called when the node enters the scene tree for the first time.
func _ready():
	_on_start()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if active and not linger:
		if $model.position.y >= $end.position.y:
			# Attack over, sit for a few seconds
			linger = true
			return
		else:
			$model.position.y += speed * delta
	
	if linger:
		# Spike attack is over, reset
		if linger_countdown <= 0:
			_on_reset()
		else:
			linger_countdown -= delta
			transparency -= 5
			$model.get_active_material(0).albedo_color = Color8(255, 255, 255, transparency)

# Called to reset the attack
func _on_reset():
	linger = false
	linger_countdown = linger_countdown_max
	transparency = 255
	active = false
	countdown = countdown_max
	$Label3D.hide()
	$Label3D.text = str(countdown)
	$model.position.y = $reset.position.y
	$model.hide()

# Called to start the attack
func _on_start():
	_on_reset()
	$model.show()
	$Label3D.show()
	$Timer.start()
	active = false

func _on_timer_timeout():
	countdown -= 1
	$Label3D.text = str(countdown)
	
	if countdown == 0:
		active = true
		$model.show()
		$Label3D.hide()
		$Timer.stop()
		return
	pass # Replace with function body.
