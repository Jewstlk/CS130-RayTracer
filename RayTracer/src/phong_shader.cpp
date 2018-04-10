#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

//ssh jmira006@bolt.cs.ucr.edu


vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth) const
{
    vec3 color;
    vec3 light_sum;
    double N_L;
    double R_C;
    vec3 N = same_side_normal;
    vec3 d_light_color;
    vec3 s_light_color;
    // TODO: determine the color
    for (unsigned int i=0; i < world.lights.size(); i++)
    {
	vec3 light_position = world.lights.at(i)->position;
	//vec3 light_color = world.lights.at(i)->color;
	
	vec3 lvector = (light_position - intersection_point).normalized();
	double distance = (light_position - intersection_point).magnitude();
	vec3 C = (world.camera.position - intersection_point).normalized();
	
	if(world.enable_shadows){
	    Ray shadow(intersection_point + (0.001 * lvector), lvector);	
	    Hit tem = Hit();
	
	    Object* s = world.Closest_Intersection(shadow, tem);
	
	    vec3 hiter = shadow.Point(tem.t);
	
	    vec3 after_light = hiter - intersection_point;
	
	    double distance_point = after_light.magnitude();
	
	    if(s != 0 && distance_point < distance){
		continue;
	    }	
	}
	
	vec3 R = (-lvector + 2.0 * (dot(lvector,N) * N)).normalized();
	
	N_L = dot(N,lvector);
	R_C = dot(R,C);
	
	
	double d_correction = fmax(0.0,N_L);
	double r_correction;
	
	if (d_correction == 0) {
		r_correction = 0;
	}else {
		r_correction = fmax(0.0,R_C);
	}
	
	d_light_color = (double(1.0)/double(pow(distance,2))) * world.lights.at(i)->Emitted_Light(ray);
	s_light_color = (double(1.0)/double(pow(distance,2))) * world.lights.at(i)->Emitted_Light(ray);
	
	light_sum += d_correction * color_diffuse * d_light_color + color_specular * pow(r_correction,specular_power) * s_light_color;
	
	}
	color = ((color_ambient * world.ambient_color) * world.ambient_intensity) + light_sum;
    return color;
}
