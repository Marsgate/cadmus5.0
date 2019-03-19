#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES

#define PROS_USE_LITERALS

#include "api.h"
#include "drive.hpp"
#include "intake.hpp"
#include "launcher.hpp"
#include "adjuster.hpp"
#include "lift.hpp"
#include "macros.hpp"
#include "skills.hpp"

//ports
#define LEFTFRONT 17
#define LEFTREAR 16
#define RIGHTFRONT 15
#define RIGHTREAR 14
#define LAUNCHER 13
#define ADJUSTER 18
#define LIFT 19
#define INTAKE 20

//definition of a tile in encoder ticks
#define TL *545

using namespace pros;
using namespace pros::literals;

extern Controller master;
extern bool mirror;
extern int auton;

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
//#include <iostream>
#endif

#endif  // _PROS_MAIN_H_
