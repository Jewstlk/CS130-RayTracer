#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    vec3 v = ray.endpoint - center;
    double delta = pow(dot(ray.direction,v),2) - (dot(ray.direction,ray.direction))*(dot(v,v)-pow(radius,2));
    
    if ( delta > 0)
		{
		double t1 = -(dot(ray.direction,v)) + sqrt(delta);
		double t2 = -(dot(ray.direction,v)) - sqrt(delta);
		
		Hit h1 = {this,t1,true};
		Hit h2 = {this,t2,true};
		
		if (t1 >= 0)
			hits.push_back(h1);
		if (t2 >= 0)
			hits.push_back(h2);
		return true;	
		}
    return false;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    // TODO: set the normal
    normal = ((point - center)/radius).normalized();
    return normal;
}
