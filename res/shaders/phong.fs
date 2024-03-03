varying vec3 v_world_position;   // Posición del vértice en el espacio del mundo
varying vec3 v_world_normal;     // Normal del vértice en el espacio del mundo
varying vec3 v_color;            // Color calculado en el vértice
varying vec2 v_texCoord;         // Coordenadas de textura

uniform sampler2D u_face_texture;

void main()
{
    // Normaliza los vectores interpolados
    vec3 normal = normalize(v_world_normal);
    vec3 viewDirection = normalize(-v_world_position);

    // Calcula la dirección de la luz y su distancia
    vec3 lightDirection = normalize(vec3(0.0, 0.0, 1.0) - v_world_position);
    float dist = length(vec3(0.0, 0.0, 1.0) - v_world_position);
    float attenuation = 1.0 / (dist * dist);

    // Luminosidad difusa con textura
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = texture2D(u_face_texture, v_texCoord).rgb * diffuseFactor;

    // Luminosidad especular
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float specularFactor = max(dot(reflectedDirection, viewDirection), 0.0);
    specularFactor = pow(specularFactor, 10.0);
    vec3 specular = vec3(1.0, 1.0, 1.0) * specularFactor * attenuation;

    // Color final con textura
    vec3 finalColor = (diffuse + specular) * v_color;

    // Salida del fragmento
    gl_FragColor = vec4(finalColor, 1.0);
}
