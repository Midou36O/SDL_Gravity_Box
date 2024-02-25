#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos; // Normally we should be transfomring everything to the carema space,
                      // but for now we will just pass the view position to the fragment shader
                      // since it's more intuitive.
float specularStrength = 0.5;

void main()
{

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Strength of the specular light
    vec3 viewDir = normalize(viewPos - FragPos);  // Direction from the fragment to the camera (view position)

    vec3 reflectDir = reflect(-lightDir, Normal); // Direction of the reflected light, the lightDir is inverted
                                                  // because the reflect function expects the light to be coming
                                                  // from the opposite direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // max(viewdir . reflectdir)³²
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 
