varying vec3 v_world_position;   //Posició del vèrtex en l'espai del món
varying vec3 v_world_normal;     //Normal del vèrtex en l'espai del món
varying vec3 v_color;            
varying vec2 v_texCoord;         //Coordenades de textura

uniform float let_c; 

uniform sampler2D u_face_texture;

void main()
{
    vec3 diffuse; 
    //Normalitza els vectors interpolats--------------------------------------
    vec3 normal = normalize(v_world_normal);
    vec3 viewDirection = normalize(-v_world_position);
    //------------------------------------------------------------------------


    //Calcula la direcció de la llum i la seva distància----------------------
    vec3 lightDirection = normalize(vec3(0.0, 0.0, 1.0) - v_world_position);
    float dist = length(vec3(0.0, 0.0, 1.0) - v_world_position);
    float attenuation = 1.0 / (dist * dist);
    //------------------------------------------------------------------------


    //Lluminositat difusa amb textura-----------------------------------------
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);
    if (let_c < 0.5) {
        diffuse = texture(u_face_texture, v_texCoord).rgb * diffuseFactor;
    } else if (let_c > 0.5) {
        diffuse = vec3(1.0, 1.0, 1.0) * diffuseFactor;
    }
    //------------------------------------------------------------------------
    

    //Lluminositat especular--------------------------------------------------
    vec3 reflectedDirection = reflect(-lightDirection, normal);
    float specularFactor = max(dot(reflectedDirection, viewDirection), 0.0);
    specularFactor = pow(specularFactor, 10.0);
    vec3 specular = vec3(1.0, 1.0, 1.0) * specularFactor * attenuation;
    //------------------------------------------------------------------------


    //Color final amb textura-------------------------------------------------
    vec3 finalColor = (diffuse + specular) * v_color;
    //------------------------------------------------------------------------


    //Sortida del fragment----------------------------------------------------
    gl_FragColor = vec4(finalColor, 1.0);
    //------------------------------------------------------------------------

}
