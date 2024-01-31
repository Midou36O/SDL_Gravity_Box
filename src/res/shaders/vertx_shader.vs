#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection; 

void main()
{
    //gl_Position = vec4(aPos, 1.0);
    // Projection * View * Model * Position is the necessary transformation.
    // RTL.
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y); 
    FragColor = vec4(1.0);
}
