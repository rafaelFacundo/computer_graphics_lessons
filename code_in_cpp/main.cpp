#include <iostream>
#include "Objects.h"
using namespace std;

int main() {
  double c[3] = {0.0,10.0,0.0};
  double ke[3] = {0.0,10.0,0.0};
  double kd[3] = {0.0,10.0,0.0};
  Object newObject = Object(c, ke, kd, 10);
  cout << newObject.get_center() << endl;
  return 0;
} 