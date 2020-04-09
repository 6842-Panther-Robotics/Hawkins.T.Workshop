#include "main.h"

pros::Imu inertial(8);

//8 is port #

pros::Motor rightFront (5, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront (7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (8, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


int TICS_PER_REVOLUTION = 360;
double WHEEL_DIAMATER = 4;
double pi = 3.14159;

double CORRECTION_FACTOR = 0.8;
int THRESHHOLD = -5;

PIDController movePID(0.5, 30); //tune PID here!    kP, minSpeed
PIDController turnPID(2.5, 30);

void wait(int time) {
    //milliseconds
    pros::delay(time);
}

void left(int speed) {
    leftFront.move(speed);
    leftBack.move(speed);
}

void right(int speed) {
    rightFront.move(speed);
    rightBack.move(speed);
}

void brake() {

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}

void coast() {
    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

}

void timedDrive(int time, int speed) {

    right(speed);
    left(speed);
    wait(time);
    right(0);
    left(0);
}

void moveForward(int inches) {

  rightFront.tare_position();
  leftFront.tare_position();

  int time = 0;

  double target = TICS_PER_REVOLUTION * (inches  / (WHEEL_DIAMATER * pi));

  while(time < 50) {

    int rightFrontPosition = rightFront.tare_position();
    int leftFrontPosition = leftFront.tare_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFrontPosition - leftFrontPosition <= THRESHHOLD) {    // can always cahnge "-5" to check
      right(PIDSpeed);
      left(PIDSpeed * 0.8);
    }
    else if (leftFrontPosition - rightFrontPosition <= -THRESHHOLD) {
      right(PIDSpeed * 0.8);
      left(PIDSpeed);
    }

    right(PIDSpeed);
    left(PIDSpeed);

    if(fabs(movePID.getError()) < 1) {
    time++;
    wait(2);

    }
  }
  right(0);
  left(0);
}

void moveBackwards(int inches) {
  rightFront.tare_position();

  int time = 0;

  double target = TICS_PER_REVOLUTION * (inches  / (WHEEL_DIAMATER * pi));

  while(time < 50) {

    int rightFrontPosition = rightFront.tare_position();
    int leftFrontPosition = leftFront.tare_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFrontPosition - leftFrontPosition >= THRESHHOLD) {    // can always cahnge "-5" to check
      right(-PIDSpeed * 0.8);
      left(-PIDSpeed);
    }
    else if (leftFrontPosition - rightFrontPosition >= -THRESHHOLD) {
      right(-PIDSpeed);
      left(-PIDSpeed * 0.8);
    }

    right(-PIDSpeed);
    left(-PIDSpeed);

    if(fabs(movePID.getError()) < 1) {
    time++;
    wait(2);

    }
  }
  right(0);
  left(0);
}

void driveOP() {
  rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
  leftFront.move(master.get_analog(ANALOG_LEFT_Y));
  rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
  leftBack.move(master.get_analog(ANALOG_LEFT_Y));

}

void turn(int degrees) {

int time = 0;

    while (time < 50) {

      left(turnPID.getSpeedToMotor(degrees, inertial.get_rotation()));
      right(-(turnPID.getSpeedToMotor(degrees, inertial.get_rotation())));

//inertial for degrees, rotation of degrees turned

      if(fabs(turnPID.getError()) < 1)
      time++;
      wait(2);
    }
    right(0);
    left(0);
}
