varying vec3 v_world_position;   // Posición del vértice en el espacio del mundo
varying vec3 v_world_normal;     // Normal del vértice en el espacio del mundo
varying vec3 v_color;            // Color calculado en el vértice
varying vec2 v_texCoord;         // Coordenadas de textura

varying vec3 v_Ka;
varying vec3 v_Kd;
varying vec3 v_Ks;

varying vec3 Ia;
varying vec3 Id;
varying vec3 Is;

uniform mat4 u_model;           // Matriz de modelo
uniform mat4 u_viewprojection;  // Matriz de vista y proyección
uniform vec3 u_lightPosition;   // Posición de la luz en el espacio del mundo
uniform vec3 u_lightColor;      // Color de la luz

void main()
{
    // Luminosidad ambiental
    vec3 ambient_light = v_Ka * Ia;

    // Transforma la posición del vértice y su normal al sistema de coordenadas del mundo
    vec4 world_position = u_model * gl_Vertex;
    vec3 world_normal = normalize(mat3(transpose(inverse(u_model))) * gl_Normal.xyz);

    // Luminosidad difusa
    vec3 lightDirection = normalize(u_lightPosition - world_position.xyz);
    float diffuseFactor = max(dot(world_normal, lightDirection), 0.0);
    vec3 diffuse = v_Kd * Id * diffuseFactor;

    // Luminosidad especular
    vec3 viewDirection = normalize(-world_position.xyz);
    vec3 reflectedDirection = reflect(-lightDirection, world_normal);
    float specularFactor = max(dot(reflectedDirection, viewDirection), 0.0);
    specularFactor = pow(specularFactor, 10.0);
    vec3 specular = v_Ks * Is * specularFactor;

    // Color final
    vec3 finalColor = ambient_light + diffuse + specular + 0.5;

    // Envía el color calculado al fragment shader para procesamiento posterior
    v_color = finalColor;

    // Transforma la posición del vértice a coordenadas de pantalla
    gl_Position = u_viewprojection * world_position;

    // Interpola los valores a lo largo del triángulo para Phong shading
    v_world_position = world_position.xyz;
    v_world_normal = world_normal;

    // Pasa las coordenadas de textura al fragment shader
    v_texCoord = gl_MultiTexCoord0.st;
}
