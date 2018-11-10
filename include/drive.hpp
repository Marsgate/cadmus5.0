#ifndef _DRIVE_H_
#define _DRIVE_H_

int drivePos();

bool isDriving();

void driveTask(void* parameter);
void turnTask(void* parameter);

void startDrive(int sp);
void startTurn(int sp);
void autoDrive(int sp);
void autoTurn(int sp);

void setSpeed(int speed);
void setSlant(int s);

void driveOp();

#endif
