#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

// Optical
extern pros::Optical color_sensor;

// Motors 
inline pros::Motor intake(7);
inline pros::Motor lever(8);
inline pros::Motor discore(9);


// Pneumatics
inline ez::Piston matchLoad('H');
inline ez::Piston lift('G');
inline ez::Piston gate('F');

enum LeverMode {LEVER_IDLE, LEVER_SLOW, LEVER_FAST};
extern Drive chassis;
extern LeverMode auto_lever_mode;
inline LeverMode auto_lever_mode = LEVER_IDLE; 
inline bool is_testing_auton = false;

// Lever Class
class LeverController {
public:
    
    // We add a "timeout" variable. By default, it gives the arm time  to finish.
    void fast(int timeout = 1000) {
        auto_lever_mode = LEVER_FAST; 
        int time_spent = 0;
        
        // Loop runs AS LONG AS it's under 85 degrees AND we haven't run out of time
        while (lever.get_position() < 90.0 && time_spent < timeout) {
            pros::delay(20);
            time_spent += 20; // Add 20ms to our stopwatch every loop
        }
    }

    void slow(int timeout = 2000) {
        auto_lever_mode = LEVER_SLOW; 
        int time_spent = 0;
        
        while (lever.get_position() < 85.0 && time_spent < timeout) {
            pros::delay(20);
            time_spent += 20;
        }
    }

    void down(int timeout = 2000) {
        auto_lever_mode = LEVER_IDLE; 
        int time_spent = 0;
        
        while (lever.get_position() > 10.0 && time_spent < timeout) {
            pros::delay(20);
            time_spent += 20;
        }
    }
};

inline LeverController fireLever;


























/// Testing WIll delete later

// class LeverController {
// public:
//     void fast(int timeout) {
//         auto_lever_mode = LEVER_FAST;
//         // Notice we are using your original 'lever' motor name here
//         while (lever.get_position() < 85.0) {
//             pros::delay(20);
//         }
//     }

//     void slow() {
//         auto_lever_mode = LEVER_SLOW;
//         while (lever.get_position() < 85.0) {
//             pros::delay(20);
//         }
//     }

//     void down() {
//         auto_lever_mode = LEVER_IDLE;
//         while (lever.get_position() > 10.0) {
//             pros::delay(20);
//         }
//     }
// };