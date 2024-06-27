samples rays --> anti aliasing
rays reflect (randomly) until no collision --> diffuse materials!
rays reflect like a mirror -> metal!
mirror + fuzzed direction -> fuzzy / brushy metal!

refraction (water, glass) -> snells law
n * sin(theta) = n' * sin(theta')

n, n' are refractive indices
theta, theta' are refractive indices

refracted ray R'
 - split into parts of the ray that are perpendicular and parallel
   to n' (the normal) 

 - formula to calculate R' in terms of R, n and n'


Bounding Volume Hierarchies:

optimize ray-objection intersection, currently runs in linear time with
respect to # of objects in the world. can turn this into a kind of binary
search, since the objects have some sort of ordering in the 3D world (we
can say that sphere A is further left than sphere B, in all directions)


Axis-Aligned Bounding Boxes - Bounding Box - BBox - "rectangular parallelepipeds"
