#version 330 core
in lowp vec4 frag_Color;
out lowp vec4 FragColr; 
void main() {
  FragColr = frag_Color;
}