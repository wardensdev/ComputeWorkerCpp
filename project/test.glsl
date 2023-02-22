#[compute]

#version 450

layout(local_size_x = 1, local_size_y = 2, local_size_z = 1) in;

layout(binding = 0, set = 0) buffer Test{
    double test_float;
};

layout(binding = 1, set = 0) buffer Boo{
    bool test_bool;
};

layout(binding = 2, set = 0) buffer Signed{
    int test_signed;
};

layout(binding = 3, set = 0) buffer Unsigned{
    uint test_unsigned;
};

void main(){
    test_float += 1.0;
    test_bool = !test_bool;
}