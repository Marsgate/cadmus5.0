#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_


bool isFired();

void shootAsync();
void ratchetAsync();
void shoot();
void ratchet();

void launcherTask(void* parameter);

void launcherOp();

#endif
