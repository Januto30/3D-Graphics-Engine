varying vec3 v_color;      // Color calculado en el v�rtice

void main()
{
    // Output del fragmento usando el color calculado en el v�rtice
    gl_FragColor = vec4(v_color, 1.0);
}
