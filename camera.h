#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"

class camera {
  public:
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 10;
    int max_depth = 10;
    color background; // scene background color

    double vfov = 90;
    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0); // camera-relative "up" direction

    double defocus_angle = 0;
    double focus_dist = 10;

    int reflect = 1;

  void render(const hittable& world) {
    initialize();
    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++) {
          std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
          for (int i = 0; i < image_width; i++) {
            color pixel_color(0,0,0);
            // whats happening
            for (int sample = 0; sample < samples_per_pixel; sample++) {
              ray r = get_ray(i, j);
              pixel_color += ray_color(r, max_depth, world);
            }

            write_color(std::cout, pixel_sample_scale * pixel_color);
          }
      }
    std::clog << "\rDone.         \n";
  }

  private:
    int image_height;
    point3 center; 
    point3 pixel00_loc; // location of pixel 0,0k
    vec3 pixel_delta_u; // ofset of pixel to the right
    vec3 pixel_delta_v; // ofset of pixel blelow 
    double pixel_sample_scale;
    vec3 u, v, w; // camera frame basis vectors
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;


    void initialize() {
      image_height = int(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;
      center = lookfrom;
      auto theta = degrees_to_radians(vfov);
      auto h = tan(theta/2);
      auto viewport_height = 2 * h * focus_dist;
      auto viewport_width = viewport_height * (double(image_width)/image_height);
      
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      auto viewport_u = viewport_width * u; 
      auto viewport_v = viewport_height * -v; 

      pixel_delta_u = viewport_u / image_width;
      pixel_delta_v = viewport_v / image_height;

      auto viewport_upper_left = center - (focus_dist * w)
        - viewport_u/2 - viewport_v/2;
                               
      pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

      pixel_sample_scale = 1.0 / samples_per_pixel;

      auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle /2));
      defocus_disk_u = u * defocus_radius;
      defocus_disk_v = v * defocus_radius; 
    }
    
    color ray_color(const ray& r, int depth, const hittable& world) {
      // recursive base case - end infinite reflection
      if (depth <= 0)
        return color(0,0,0);

      hit_record rec;
      
      // if ray hits nothing, return background color
      if (!world.hit(r, interval(0.001, infinity), rec))
        return background;

      // keep bouncing rays, recursive
      // ignore very close hits to prevent acne
      
      ray scattered;
      color attenuation;
      color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);
      
      if (!rec.mat->scatter(r, rec, attenuation, scattered))
        return color_from_emission;

      color color_from_scatter = attenuation * ray_color(scattered, depth-1, world);
      return color_from_emission + color_from_scatter;
    }

  ray get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
                      + ((i + offset.x()) * pixel_delta_u)
                      + ((j + offset.y()) * pixel_delta_v);
    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    auto ray_time = random_double();

    return ray(ray_origin, ray_direction, ray_time);
  }

  vec3 sample_square() const {
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  point3 defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
  }
};

#endif
