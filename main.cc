#include "rtweekend.h"

#include "bvh.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "vec3.h"
#include "material.h"
#include "camera.h"
#include "sphere.h"
#include "quad.h"

#include <iostream>
#include <string>

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

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 20;
    cam.lookfrom = point3(7,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world);
}

void checkered_spheres() {
    hittable_list world;
    auto checker = make_shared<image_texture>("perlintexture.png");

    world.add(make_shared<sphere>(point3(0,-12, -50), 10, make_shared<metal>(checker, 1.0)));
    world.add(make_shared<sphere>(point3(0, 12, -50), 10, make_shared<metal>(checker, 1.5)));

    auto checker2 = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker2)));

    world = hittable_list(make_shared<bvh_node>(world));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 50;
    cam.lookfrom = point3(0,0,0);
    cam.lookat   = point3(0,0,-10);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}



void earth() {
  auto earth_texture = make_shared<image_texture>("earthmap.jpg");
  auto earth_surface = make_shared<lambertian>(earth_texture);
  auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth         = 50;
  cam.background = color(0.7, 0.8, 1.0);

  cam.vfov     = 20;
  cam.lookfrom = point3(0,0,12);
  cam.lookat   = point3(0,0,0);
  cam.vup      = vec3(0,1,0);

  cam.defocus_angle = 0;

  cam.render(hittable_list(globe));
}

void perlin_spheres(int arg1) {
  hittable_list world;

  auto pertext = make_shared<noise_texture>(arg1);
    //world.add(make_shared<sphere>(point3(0,0,-1000), 1000, make_shared<dielectric>(1.5)));
    //world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,3,0), 2, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,-3,0), 2, make_shared<lambertian>(pertext)));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth         = 50;
    cam.background = color(0.7, 0.8, 1.0);

    cam.vfov     = 50;
    cam.lookfrom = point3(0,4,10);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void quads() {
  hittable_list world;




  // Materials
    auto left_red     = make_shared<lambertian>(color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<lambertian>(color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<lambertian>(color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<lambertian>(color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<lambertian>(color(0.2, 0.8, 0.8));

    // Quads
    world.add(make_shared<quad>(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(make_shared<quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(make_shared<quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(make_shared<quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(make_shared<quad>(point3(-2, -3, 5), vec3(4, 0, 0), vec3(0, 0, -4), lower_teal));


  camera cam;

  cam.aspect_ratio      = 1.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth         = 50;
  cam.background = color(0.7, 0.8, 1.0);

  cam.vfov = 80;
  cam.lookfrom = point3(0,0,9);
  cam.lookat = point3(0,0,0);
  cam.vup = vec3(0,1,0);

  cam.defocus_angle = 0;

  cam.render(world);
}

void simple_light() {
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    auto checker = make_shared<checker_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    world.add(make_shared<sphere>(point3(0,-999,0), 1000, make_shared<lambertian>(checker)));
    //world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
  //auto earth_texture = make_shared<image_texture>("moon.jpeg");
  //auto earth_surface = make_shared<lambertian>(earth_texture);
    //world.add(make_shared<sphere>(point3(0,2,0), 2, earth_surface));

    auto difflight = make_shared<diffuse_light>(color(1,1,1));
    auto redlight = make_shared<diffuse_light>(color(1,0,0));
   world.add(make_shared<quad>(point3(3,1,-2), vec3(2,0,0), vec3(0,2,0), difflight));
    world.add(make_shared<sphere>(point3(0,2,2), 2, redlight));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 800;
    cam.samples_per_pixel = 200;
    cam.max_depth         = 50;
    cam.background        = color(0,0,0);

    cam.vfov     = 20;
    cam.lookfrom = point3(26,4,6);
    cam.lookat   = point3(0,4,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}


int main(int argc, char **argv) {
  int arg1 = 0;
  if (argc > 1)
    arg1 = std::stoi(argv[1]);
  switch(4) {
    case 1: bounce(); break;
    case 2: earth();  break;
    case 3: checkered_spheres(); break;
    case 4: perlin_spheres(arg1); break;
    case 5: quads(); break;
    case 6: simple_light(); break;
  }
}
