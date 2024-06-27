#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>



using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

// random numbers
inline double random_double() {
  return rand() / (RAND_MAX + 1.0);
}

// random numbers
inline double random_double(double min, double max) {
  return min + (max-min)*random_double();
}

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
