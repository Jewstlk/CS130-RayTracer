#include "plane.h"
#include "ray.h"
#include <cfloat>


// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
	double num = double(dot((ray.endpoint - x1), normal));
    double denom = double(dot(ray.direction, normal));
  
    bool c1 = true;

    if(num <= 0){
	c1 = true;
    }else{
	c1 = false;
    }

    if(c1 == false && denom > 0){
	return false;	
    }else if(c1 == false && denom == 0){
	return false;
    }else if(c1 == true && (denom < 0 || denom == 0)){

	Hit h = {this,0.0,false};
	hits.push_back(h);
	
	return true;
    }else if(c1 == true && denom > 0){

	double t = -double(double(num) / double(denom));

	Hit h = {this,0.0,false};
	hits.push_back(h);

	Hit h2 = {this,t,true};
	hits.push_back(h2);

	return true;
    }else if(c1 == false && denom < 0){

	double t = -double(double(num) / double(denom));

	Hit h = {this,t,false};
	hits.push_back(h);
	
	return true;
    }

return false;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
