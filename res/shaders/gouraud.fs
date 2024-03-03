varying vec3 v_color;      // Color calculado en el vértice

void main()
{
    // Output del fragmento usando el color calculado en el vértice
    gl_FragColor = vec4(v_color, 1.0);
}
