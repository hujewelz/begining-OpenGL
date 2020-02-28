#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out lowp vec4 frag_Color;
out lowp vec2 tex_Coord;

void main() {
  gl_Position = vec4(aPosition, 1.0);
  frag_Color = vec4(aColor, 1.0);
  tex_Coord = aTexCoord;
}