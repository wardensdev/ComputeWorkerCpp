extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready():
	
	print("pre")
#	var f = $ComputeWorker.get_uniform_by_alias("test_float", 0)
#	var g = $ComputeWorker.get_rendering_device()
#	var h = $ComputeWorker.get_uniform_set_by_id(0)
#	var j = $ComputeWorker.is_device_processing()
#	var k = $ComputeWorker.uniform_sets
#	var l = $ComputeWorker.get_class()
	$ComputeWorker.initialize()
	print("post")
#	print($ComputeWorker.get_rendering_device())
	
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
	pass
	
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	if !$ComputeWorker.is_device_processing():
		$ComputeWorker.dispatch_compute_list()
		$ComputeWorker.begin()
		$ComputeWorker.end()
	
	var f = $ComputeWorker.get_uniform_data_by_alias("test_float", 0)
#	print(f)
	
	var a = $ComputeWorker.get_uniform_data_by_alias("test_bool", 0)
#	print(a)
	
	var s = $ComputeWorker.get_uniform_data_by_alias("test_signed", 0)
#	print(s)
	
	var d = $ComputeWorker.get_uniform_data_by_alias("test_unsigned", 0)
#	print(d)
	
	var e = $ComputeWorker.get_uniform_data_by_alias("test_fvec", 0)
	print(e)
	
	var r = $ComputeWorker.get_uniform_data_by_alias("test_dvec", 0)
	print(r)
