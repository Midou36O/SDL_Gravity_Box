#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; // Inverse transforms are very expensive. Find a way to avoid them.
                                                        // To avoid them, we should be calculating the normal matrix in the
                                                        // CPU and passing it to the shader.

    //Normal = aNormal;  
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
