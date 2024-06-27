#ifndef HITTABLE_H
#define HITTABLE_H

// tell c++ compiler this class will be compiled later
class material;

class hit_record {
 public:
  point3 p;
  vec3 normal;
  shared_ptr<material> mat;
  double t;
  // u,v are texture(surface) coordinates
  double u;
  double v;
  bool front_face;

  void set_face_normal(const ray& r, const vec3& outward_normal) {
    // Sets the hit record normal vector
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif
