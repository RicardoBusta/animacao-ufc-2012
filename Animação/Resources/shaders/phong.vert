varying vec4 position;
varying vec3 normal;

void main(void)
{
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;

    position = gl_ModelViewMatrix * gl_Vertex;
    normal = gl_NormalMatrix * gl_Normal;
}

