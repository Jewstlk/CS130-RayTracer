#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
#include "light.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    // TODO: determine the color
	vec3 reflected_color;
    vec3 N = same_side_normal;
    

    for(unsigned int i = 0; i < world.lights.size(); i++){
//	vec3 light_position = world.lights[i]->position;

	vec3 V = (ray.endpoint - intersection_point).normalized();
	vec3 R = (-V + 2.0 * (dot(V, N)) * N).normalized();
	Ray rayT(intersection_point + .001 * R, R);
	reflected_color = world.Cast_Ray(rayT,recursion_depth+1);
	color = reflectivity * reflected_color + (1 - reflectivity) * shader->Shade_Surface(rayT, intersection_point, N, recursion_depth+1);

    }
	
	
    
    return color;
}
