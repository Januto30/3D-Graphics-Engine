varying vec3 v_world_normal;
varying vec2 v_uv;
uniform sampler2D u_face_texture;


void main()
{
	vec4 texture_color = texture2D(u_face_texture, v_uv);
	gl_FragColor = texture_color;
}
