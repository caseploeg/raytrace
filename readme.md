RAYTRACER: 

world + camera

world -> list of hittable objects

viewport
ray
hittable -> material + location + geometry -> did it hit? 
screen

notes:
   - blurring / antialiasing / focus effect achieved through sampling
   - more sampling -> more precise image 
   - materials are defined by the way they scatter a ray (reflect/refract)

MAIN(): 
  world setup 
  configure camera
  camera.render()

CAMERA::


CONFIG:
 - aspect ratio 
 - width 
 - samples per pixel
 - max depth (ray scatter recursion)
 - vfov
 - lookfrom
 - lookat
 - vup
 - defocus angle
 - focus dist

RENDER():
  - per pixel, color is the average of the sampled rays 
   - ray(i,j): vector (origin: camera , direction : camera -> pixel [i][j]) 

ray_color():
  rec.mat->scatter()
   -> material determines attenuation(color %), and further scatter
    -> random, always scatter --> matte (lambertian) 
    -> random reflection, always scatter -> metal mirror
      -> add fuzzing on reflection & ensure rays are inside normal hemisphere 
  attenuation is how much the color of the material affects the color of light

shadows:
 - if light does a lot of bouncing, color is summed up (absorbed by material) to something close to black


RAYTRACER IS DOING THE REVERSE OF IRL
 - IRL: light source -> bounce off objects -> hits eye / camera lens
    - objects absorb light?
 - RAY TRACE : camera -> bounce off objects -> light
    - rendered pixels calculated based on how objects interact with light 
    - reverse the path!
