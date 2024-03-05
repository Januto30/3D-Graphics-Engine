varying vec3 v_world_position;   //Posició del vèrtex en l'espai del món
varying vec3 v_world_normal;     //Normal del vèrtex en l'espai del món
varying vec3 v_color;            
varying vec2 v_texCoord;         //Coordenades de textura

varying vec3 v_Ka;
varying vec3 v_Kd;
varying vec3 v_Ks;

varying vec3 Ia;
varying vec3 Id;
varying vec3 Is;

uniform mat4 u_model;           //Matriu de model
uniform mat4 u_viewprojection;  //Matriu de vista i projecció
uniform vec3 u_lightPosition;   //Posició de la llum en l'espai del món
uniform vec3 u_lightColor;      //Color de la llum

void main()
{
    //Lluminositat ambiental--------------------------------------------------
    vec3 ambient_light = v_Ka * Ia;
    //------------------------------------------------------------------------


    //Transforma la posició del vèrtex i la seva normal al sistema de coordenades del món
    vec4 world_position = u_model * gl_Vertex;
    vec3 world_normal = normalize(mat3(transpose(inverse(u_model))) * gl_Normal.xyz);
    //------------------------------------------------------------------------


    //Lluminositat difusa-----------------------------------------------------
    vec3 lightDirection = normalize(u_lightPosition - world_position.xyz);
    float diffuseFactor = max(dot(world_normal, lightDirection), 0.0);
    vec3 diffuse = v_Kd * Id * diffuseFactor;
    //------------------------------------------------------------------------
    
    
    //Lluminositat especular
    vec3 viewDirection = normalize(-world_position.xyz);
    vec3 reflectedDirection = reflect(-lightDirection, world_normal);
    float specularFactor = max(dot(reflectedDirection, viewDirection), 0.0);
    specularFactor = pow(specularFactor, 10.0);
    vec3 specular = v_Ks * Is * specularFactor;
    //------------------------------------------------------------------------


    //Color final-------------------------------------------------------------
    vec3 finalColor = ambient_light + diffuse + specular + 0.5;

    //Envia el color calculat al fragment shader per a processament posterior
    v_color = finalColor;

    //Transforma la posició del vèrtex a coordenades de pantalla
    gl_Position = u_viewprojection * world_position;

    //Interpola els valors al llarg del triangle per a l'ombreament de Phong
    v_world_position = world_position.xyz;
    v_world_normal = world_normal;

    //Pasa les coordenades de textura al fragment shader
    v_texCoord = gl_MultiTexCoord0.st;
    //------------------------------------------------------------------------

}
