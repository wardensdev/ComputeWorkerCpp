#[compute]

#version 450

layout(local_size_x = 1, local_size_y = 2, local_size_z = 1) in;

layout(binding = 0, set = 0) buffer Test{
    float test_float;
};

void main(){
    test_float += 1.0;
}