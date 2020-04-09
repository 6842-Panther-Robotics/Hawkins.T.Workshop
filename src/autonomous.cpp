#include "main.h"

void redFront() {
  moveForward(24);
}
void blueFront() {
  moveForward(28);
}
void autonomous() {

  switch (autonIndex) {
    case 0:
      redFront();
      break;
    case 1:
      blueFront();
      break;
    

  }
}

//error = target - current position

//gain = multiplication factor(The value you tune)
//kP gain
//kl gain
//kD gian

//PID = proportional integral derivative

//output -> proportional + integral + derivative
//output is power

//proportional -> error * kP
