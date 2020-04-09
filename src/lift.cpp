#include "main.h"

PIDController liftPID(0.6, 5);    //tune PID here: kP, minSpeed

pros::Motor liftMotor (1, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer pot('B');

pros::ADILineSensor lineSensor('A');

void lift(int speed) {
  liftMotor.move_velocity(speed);
}

void timedLift(int time, int speed) {

    lift(speed);
    wait(time);
    lift(0);
}

void breakLift() {
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

// Auton

void moveLift(int position) {   // position = potentiometer value

  int time = 0;

  pot.calibrate();
  int currentLiftPosition = pot.get_value();
  int calibratedLiftValue = pot.get_value_calibrated();   //8,190 total positions

while(time < 50) {

  lift(liftPID.getSpeedToMotor(position, currentLiftPosition));

    if(fabs(liftPID.getError()) < 1) {
    time++;
    wait(2);
    }
  }
  lift(0);
}
// give this a shot, everything inside this function

// OPControl
void liftOP() {

  breakLift();

  if (master.get_digital(DIGITAL_L1)) {
    liftMotor.move_velocity(100);;
  }

  else if (master.get_digital(DIGITAL_L2)) {
    liftMotor.move_velocity(-100);
  }

  else {
    breakLift();
  }

}

void test() {
  if(lineSensor.get_value() < 2000 && lineSensor.get_value() > 100) {
  }
  else {

  }
}

//red = 100 rpm
//blue = 600 rpm
