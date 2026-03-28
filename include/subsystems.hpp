#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"


// Motors 
inline pros::Motor intake(7);
inline pros::Motor lever(8);
inline pros::Motor discore(9);


// Pneumatics
inline ez::Piston matchLoad('G');
inline ez::Piston lift('H');
inline ez::Piston gate('F');

enum LeverMode {LEVER_IDLE, LEVER_SLOW, LEVER_FAST};
extern Drive chassis;
extern LeverMode auto_lever_mode;
inline LeverMode auto_lever_mode = LEVER_IDLE; 
inline bool is_testing_auton = false;

// Lever Class
class LeverController {
public:
    void fast() {
        auto_lever_mode = LEVER_FAST;
        // Notice we are using your original 'lever' motor name here
        while (lever.get_position() < 85.0) {
            pros::delay(20);
        }
    }

    void slow() {
        auto_lever_mode = LEVER_SLOW;
        while (lever.get_position() < 85.0) {
            pros::delay(20);
        }
    }

    void down() {
        auto_lever_mode = LEVER_IDLE;
        while (lever.get_position() > 10.0) {
            pros::delay(20);
        }
    }
};
inline LeverController fireLever;