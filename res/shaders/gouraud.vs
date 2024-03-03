varying vec3 v_world_position;   // Posición del vértice en el espacio del mundo
varying vec3 v_world_normal;     // Normal del vértice en el espacio del mundo
varying vec3 v_color;            // Color calculado en el vértice

varying vec3 v_Ka;
varying vec3 v_Kd;
varying vec3 v_Ks;

varying vec3 Ia;
varying vec3 Id;
varying vec3 Is;

uniform mat4 u_model;            // Matriz de modelo
uniform mat4 u_viewprojection;   // Matriz de vista y proyección
uniform vec3 u_lightPosition;    // Posición de la luz en el espacio del mundo
uniform vec3 u_lightColor;       // Color de la luz

// Nueva uniform para la textura difusa
uniform sampler2D u_face_texture;

void main()
{
    // Llum ambient------------------------------------------------------------------------
    vec3 ambient_light = v_Ka * Ia;
    //------------------------------------------------------------------------------------

    //------------------------------------------------------------------------------------
    // Transforma la posició del vèrtex i la seva normal al sistema de coordenades del món
    vec3 world_position = (u_model * vec4(gl_Vertex.xyz, 1.0)).xyz;
    vec3 world_normal = normalize(mat3(transpose(inverse(u_model))) * gl_Normal.xyz);
    //------------------------------------------------------------------------------------

    // Llum Difusa-------------------------------------------------------------------------
    // Calcula la direcció i la distància de la llum en el sistema de coordenades del món
    float dist = length(u_lightPosition - world_position);
    float attenuation = 1.0 / (dist * dist);

    // Calcula las coordenadas de textura en el fragment shader
    vec2 texCoord = world_position.xy;

    // Obtén el color difuso de la textura
    vec3 textureColor = texture2D(u_face_texture, texCoord).rgb;

    // Reemplaza Kd con el color RGB de la textura
    vec3 diffuse = textureColor * u_lightColor * attenuation * max(dot(world_normal, normalize(u_lightPosition - world_position)), 0.0) * 2;
    //------------------------------------------------------------------------------------

    // Llum Especular----------------------------------------------------------------------
    //Calcula la direcció de reflexió especular
    vec3 viewDirection = normalize(-world_position);                    //Vector de vista
    vec3 lightDirection = normalize(u_lightPosition - world_position);  //Dirección de la luz

    //Calcula la intensitat especular atenuada en el vértice
    float specularFactor = max(dot(reflect(-lightDirection, world_normal), viewDirection), 0.0);
    specularFactor = pow(specularFactor, 10.0);                         // Exponente especular (ajustable)
    vec3 specular = u_lightColor * 2 * specularFactor * attenuation;
    //------------------------------------------------------------------------------------

    // Final-------------------------------------------------------------------------------
    // Suma las componentes difusa, ambiental y especular para obtener el color final
    vec3 finalColor = ambient_light + diffuse + specular;

    // Envía el color calculado al fragment shader para un procesamiento posterior
    v_color = finalColor;

    // Transforma la posición del vértice a coordenadas de pantalla usando la matriz de vista y proyección
    gl_Position = u_viewprojection * vec4(gl_Vertex.xyz, 1.0);

    // Interpola los valores a lo largo del triángulo para el Gouraud shading
    v_world_position = world_position;
    v_world_normal = world_normal;
    //------------------------------------------------------------------------------------
}
