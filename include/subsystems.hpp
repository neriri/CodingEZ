#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');

inline pros::Motor intake(1);
inline ez::Piston matchLoad('A');
inline ez::Piston lift('B');
inline ez::Piston gate('C');
