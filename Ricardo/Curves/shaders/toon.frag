//
// toon.frag -- from lighthouse3d.com
//

varying vec3 normal;
varying vec3 lightDir;

void main (void)
{
  float intensity;
  vec3 color;
  vec3 n = normalize (normal);

  intensity = dot (lightDir, n);

  vec3 Kd = gl_FrontMaterial.diffuse.xyz;

  if (intensity > 0.95)
    color = Kd*vec3 (0.9, 0.9, 0.9);
  else if (intensity > 0.5)
    color = Kd*vec3 (0.7, 0.7, 0.7);
  else if( intensity > 0.25 )
    color = Kd*vec3 (0.4, 0.4, 0.4);
  else
    color = Kd*vec3 (0.2, 0.2, 0.2);

  gl_FragColor = vec4(color, 1.0);
}
