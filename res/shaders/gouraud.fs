varying vec3 v_color;      // Color calculado en el v�rtice

void main()
{
    gl_FragColor = vec4(v_color, 1.0);
}
