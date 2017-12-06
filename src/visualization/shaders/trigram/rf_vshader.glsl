#version 330
in vec3 vert;
in vec3 color;
out vec3 int_color;
uniform mat4 mvp;
uniform float c_cyl, c_sph;
const float TAU = 3.1415926535897932384626433832795 * 2;
void main() {
  vec3 xpos = vert * vec3(2, 2, 2) - vec3(1, 1, 1);
  xpos *= (1.0 - c_cyl - c_sph);
  vec2 a1pos = vec2(cos(vert.x * TAU), sin(vert.x * TAU));
  vec2 a2pos = vec2(sin(vert.y * TAU / 2.0), cos(vert.y * TAU / 2.0));
  vec3 cpos = vec3(a1pos * vert.y, vert.z * 2.0 - 1.0);
  xpos += cpos * c_cyl;
  vec3 spos = vec3(a1pos * a2pos.x, a2pos.y) * vert.z;
  xpos += spos * c_sph;
  gl_Position = mvp * vec4(xpos, 1.0);
  int_color = color;
}
