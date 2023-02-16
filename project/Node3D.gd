extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
	var sum = Summator.new()
	print(sum.get_array_element(4))
	
	$ComputeWorker.initialize()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass


func _on_summator_custom_signal(p_name, value):
	print("custom signal! " + p_name + str(value)) # Replace with function body.
