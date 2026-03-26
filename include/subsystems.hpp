#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Motors 
inline pros::Motor intake(7);
inline pros::Motor lever(8);
inline pros::Motor discore(9);


// Pneumatics
inline ez::Piston matchLoad('A');
inline ez::Piston lift('B');
inline ez::Piston gate('C');