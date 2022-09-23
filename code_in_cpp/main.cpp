#include <SDL2/SDL.h>
#include "Objects.h"
#include "Sphere.h"
#include <iostream>
using namespace std;

int main() {
  double c[3] = {0.0,10.0,0.0};
  double ke[3] = {0.0,10.0,0.0};
  
  Sphere *theSphere = new Sphere(c,ke,ke,10.0,10.0);
  
  return 0;
} 