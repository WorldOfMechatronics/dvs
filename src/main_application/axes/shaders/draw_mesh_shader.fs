#version 330

out vec4 color;
in vec3 fragment_color;
in vec4 coord_out;
uniform int use_color;

uniform vec4 clip_plane0;
uniform vec4 clip_plane1;
uniform vec4 clip_plane2;
uniform vec4 clip_plane3;
uniform vec4 clip_plane4;
uniform vec4 clip_plane5;

void main()
{
   if(dot(clip_plane0, coord_out) < 0.0)
   {
      discard;
   }
   else if(dot(clip_plane1, coord_out) < 0.0)
   {
      discard;
   }
   else if(dot(clip_plane2, coord_out) < 0.0)
   {
      discard;
   }
   else if(dot(clip_plane3, coord_out) < 0.0)
   {
      discard;
   }
   else if(dot(clip_plane4, coord_out) < 0.0)
   {
      discard;
   }
   else if(dot(clip_plane5, coord_out) < 0.0)
   {
      discard;
   }
   color = vec4(fragment_color, 0.5);
   color.a = 0.5;

		
}
