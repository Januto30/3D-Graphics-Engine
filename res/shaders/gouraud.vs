varying vec3 v_world_position;   // Posición del vértice en el espacio del mundo
varying vec3 v_world_normal;     // Normal del vértice en el espacio del mundo
varying vec3 v_color;            // Color calculado en el vértice

varying vec3 v_Ka;
varying vec3 v_Kd;
varying vec3 v_Ks;

varying vec3 Ia;
varying vec3 Id;
varying vec3 Is;

uniform mat4 u_model;            //Matriu model
uniform mat4 u_viewprojection;   //Matriu de vista i projecció
uniform vec3 u_lightPosition;    //Posición de la llum en l'espai mon
uniform vec3 u_lightColor;       //Color de la llum

void main()
{
    //Llum ambient------------------------------------------------------------------------
    vec3 ambient_light = v_Ka * Ia;
    //------------------------------------------------------------------------------------


    //------------------------------------------------------------------------------------
    //Transforma la posició del vèrtex i la seva normal al sistema de coordenades del món
    vec3 world_position = (u_model * vec4(gl_Vertex.xyz, 1.0)).xyz;
    vec3 world_normal = normalize(mat3(transpose(inverse(u_model))) * gl_Normal.xyz);
    //------------------------------------------------------------------------------------


    //Llum Difusa-------------------------------------------------------------------------
    //Calcula la direcció i la distància de la llum en el sistema de coordenades del món
    float dist = length(u_lightPosition - world_position);
    float attenuation = 1.0 / (dist * dist);
    vec3 diffuse = u_lightColor * attenuation * max(dot(world_normal, normalize(u_lightPosition - world_position)), 0.0) * 2;
    //------------------------------------------------------------------------------------


    // Llum Especular----------------------------------------------------------------------
    //Calcula la direcció de reflexió especular
    vec3 viewDirection = normalize(-world_position);                    //Vector de vista
    vec3 lightDirection = normalize(u_lightPosition - world_position);  //Direcció de la llum

    //Calcula la intensitat especular atenuada en el vèrtex
    float specularFactor = max(dot(reflect(-lightDirection, world_normal), viewDirection), 0.0);
    specularFactor = pow(specularFactor, 10.0);                         //Ajustable
    vec3 specular = u_lightColor * 2 * specularFactor * attenuation;
    //------------------------------------------------------------------------------------


    //Final-------------------------------------------------------------------------------
    //Suma les components difusa, ambiental i especular per deduir el color final.
    vec3 finalColor = ambient_light + diffuse + specular;

    finalColor = clamp(finalColor, 0.0, 1.0);

    //Enviem el color al fragment shader
    v_color = finalColor;

    //Transforma la posició del vèrtex a screenspace
    gl_Position = u_viewprojection * vec4(gl_Vertex.xyz, 1.0);

    v_world_position = world_position;
    v_world_normal = world_normal;
    //------------------------------------------------------------------------------------
}
