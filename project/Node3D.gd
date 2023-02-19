extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
	var sum = Summator.new()
	print(sum.get_array_element(4))
	
	$ComputeWorker.initialize()
	
#	var sf = RDShaderFile.new()
#
#
#	var cw = ComputeWorker.new()
#	var us = UniformSet.new()
#	var gp = GPU_Float.new()
#
#	gp.alias = "test_float"
#	gp.data = 3.5
#
#	us.uniforms.push_back(gp)
#
#	cw.shader_file = sf
#	cw.uniform_sets.push_back(us)
#
#	cw.initialize()
	
	
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	print($ComputeWorker.get_uniform_data_by_alias("test_float", 0))


func _on_summator_custom_signal(p_name, value):
	print("custom signal! " + p_name + str(value)) # Replace with function body.
