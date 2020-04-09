#include "main.h"

double kP = 0;

int minSpeed = 0;

PIDController::PIDController(double inkP, int inMinSpeed) {
  kP = inkP;
  minSpeed = inMinSpeed;
}
int PIDController::getSpeedToMotor(int target, int current) {

  error = target - current;

  int speed = error * kP;

  if (speed <= minSpeed && speed >= 0) {
    speed = minSpeed;
  }

  if (speed <= -minSpeed && speed > 0) {
    speed = -minSpeed;
  }

  return speed;

}

double PIDController::getError() {
  return error;
}

//drivePID.getOutput(target, current);
