
//const vec3 wi1 = vec3(-0.892, 0.3, 0.9);
//const vec3 Id1 = vec3(0.8, 0.8, 0.8);
//const vec3 Is1 = vec3( 0.5, 0.5, 0.5);

//const vec3 wi2 = vec3(0.588, 0.46, 0.248);
//const vec3 Id2 = vec3( 0.498, 0.5, 0.6);
//const vec3 Is2 = vec3(0.2, 0.2, 0.2);

//const vec3 wi3 = vec3(0.216, -0.392, -0.216);
//const vec3 Id3 = vec3(0.798, 0.838, 1.0);
//const vec3 Is3 = vec3(0.06, 0.0, 0.0);

varying vec3 normal;
varying vec4 position;

uniform sampler2D color_texture;

void main(void)
{
    vec3 wi1 = gl_LightSource[0].position.rgb;
    vec3 Id1 = gl_LightSource[0].diffuse.rgb;
    vec3 Is1 = gl_LightSource[0].specular.rgb;

    vec3 wi2 = gl_LightSource[1].position.rgb;
    vec3 Id2 = gl_LightSource[1].diffuse.rgb;
    vec3 Is2 = gl_LightSource[1].specular.rgb;

    vec3 wi3 = gl_LightSource[2].position.rgb;
    vec3 Id3 = gl_LightSource[2].diffuse.rgb;
    vec3 Is3 = gl_LightSource[2].specular.rgb;

    vec3 normal = normalize(normal);
    vec3 wo = normalize(-position.xyz);
//    vec3 wo = normalize(vec3(0, 0, 1));
    float alpha = gl_FrontMaterial.diffuse.a;
    vec3 Kd = gl_FrontMaterial.diffuse.rgb;
    vec3 Ks = gl_FrontMaterial.specular.rgb;
    vec3 Ke = gl_FrontMaterial.emission.rgb;
    float shininess = gl_FrontMaterial.shininess;

//    vec4 texVal = texture2D();

    if(dot(wo, normal) < 0.0)
        normal = -normal;

    vec3 wr1 = normalize(reflect(-wi1, normal));
    vec3 wr2 = normalize(reflect(-wi2, normal));
    vec3 wr3 = normalize(reflect(-wi3, normal));

    vec3 I = Ke;
    I += Kd * Id1 * max(0.0, dot(wi1, normal)) + Ks *Is1 * pow(max(0.0, dot(wr1, wo)), shininess);
    I += Kd * Id2 * max(0.0, dot(wi2, normal)) + Ks *Is2 * pow(max(0.0, dot(wr2, wo)), shininess);
    I += Kd * Id3 * max(0.0, dot(wi3, normal)) + Ks *Is3 * pow(max(0.0, dot(wr3, wo)), shininess);

    //added by Ricardo
//    float intensity = dot(I,I);
//    if(intensity < 0.5) {I = Kd*vec3(0.5,0.5,0.5);}
//    else if(intensity < 0.7) {I = Kd*vec3(0.7,0.7,0.7);}
//    else if(intensity < 0.9) {I = Kd*vec3(0.9,0.9,0.9);}
//    else I = Kd;
    //end

    gl_FragColor = (vec4(I, alpha) * texture2D(color_texture, gl_TexCoord[0].st));
}

