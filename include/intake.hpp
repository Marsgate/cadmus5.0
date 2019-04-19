#ifndef _INTAKE_H_
#define _INTAKE_H_

void intake(int vel);

bool hasBall();
bool isLoaded();

void intakeBallAsync();
void loadBallAsync();
void loadAndClearAsync();
void indexBallAsync();
void unindexBallAsync();

void intakeBall();
void loadBall();
void loadAndClear();
void indexBall();
void unindexBall();

void intakeTask(void* parameter);

void intakeOp();

#endif
