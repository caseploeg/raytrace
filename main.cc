#include "rtweekend.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "vec3.h"
#include "material.h"
#include "camera.h"
#include "sphere.h"

#include <iostream>
void bounce() {
    hittable_list world;

    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
      for (int b = -11; b < 11; b++) {
        auto choose_mat = random_double();
        point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

        if ((center - point3(4, 0.2, 0)).length() > 0.9) {
          shared_ptr<material> sphere_material;
          if (choose_mat < 0.8) {
            auto albedo = color::random() * color::random();
            sphere_material = make_shared<lambertian>(albedo);
            auto center2 = center + vec3(0, random_double(0,.5), 0);
            world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
          }
        }
      }
    }



    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);
}

void checkered_spheres() {
    hittable_list world;
    auto checker = make_shared<image_texture>("checkerboard.png");

    world.add(make_shared<sphere>(point3(0,-12, -50), 10, make_shared<lambertian>(checker)));
    world.add(make_shared<sphere>(point3(0, 12, -50), 10, make_shared<lambertian>(checker)));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 50;
    cam.lookfrom = point3(0,0,0);
    cam.lookat   = point3(0,0,-10);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}



void earth() {
  auto earth_texture = make_shared<image_texture>("checkerboard.png");
  auto earth_surface = make_shared<lambertian>(earth_texture);
  auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth         = 50;

  cam.vfov     = 20;
  cam.lookfrom = point3(0,0,12);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0;

  cam.render(hittable_list(globe));
}

void perlin_spheres() {
  hittable_list world;

  auto pertext = make_shared<noise_texture>();
  world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
  world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

  camera cam;
  cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);

}



int main() {
  switch(4) {
    case 1: bounce(); break;
    case 2: earth();  break;
    case 3: checkered_spheres(); break;
    case 4: perlin_spheres(); break;
  }
}
