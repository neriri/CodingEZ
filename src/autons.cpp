#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110; // 80%
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(0.0, 0.0, 0.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void calibrateArms() {
    // 1. Apply a gentle downward voltage. 
    lever.move_voltage(-3000);
    discore.move_voltage(-3000); 
    // 2. Wait a tiny bit to give the motor time to actually start moving
    pros::delay(250); 
    // 3. Create tracking flags to know when each one is finished
    bool lever_done = false;
    bool discore_done = false;
        
    // 4. We hit the bottom! Stop the motor.

    while (!lever_done || !discore_done) {
        
        // Check the lever (if it isn't done already)
        if (!lever_done && std::abs(lever.get_actual_velocity()) <= 2) {
            lever.move_voltage(0); // Stop the lever
            lever_done = true;     // Mark it as finished
        }

        // Check the discore (if it isn't done already)
        if (!discore_done && std::abs(discore.get_actual_velocity()) <= 2) {
            discore.move_voltage(0); // Stop the discore
            discore_done = true;     // Mark it as finished
        }

        pros::delay(20); // Standard PROS delay
    }

    // 5. THE CRITICAL STEP: Reset the encoder to exactly 0 at this physical position
    lever.tare_position();
    discore.tare_position(); 
}





// . . .
// Make your own autonomous functions here!
// . . .

void FourRushWing() {
 // Matchload
  chassis.pid_drive_set(37_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED*50, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(120_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED*50, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(60_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
 // Long Score 4 Block,
 // Wing
}

void NineBlockRush()  {
  // Matchload All Rush
  // Offset, Reverse Intake slow
  // Score 4 Blocks
  // Matchload 5 Blocks
  // Score 5 Blocks

}

void MiddleLast() {
  // Matchload All Rush
  // Offset, Reverse Intake 
  // Score 
  // Matchload 
  // Middle Score
  // Swing to Wing
}

void SideBlockGrab() {
  // Mid Side Block Grab
  // Middle Score 3 blocks
  // Matchload 3 blocks
  // Score 
  // Wing
}

void skills() {

}



void leverState() {
    bool launching = false;
    // Hardstop Angles
    const double maxUpAngle = 550.0; 
    const double minDownAngle = 1.0;
    double halfAngle = maxUpAngle / (4.0);

    while (true) {
        double current_angle = lever.get_position();

        // 1. Fast Lever (R2)
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            if (current_angle < maxUpAngle) {
                lever.move_voltage(12000);
            } else {
                lever.move_voltage(1000); // Fixed colon to semicolon
            }
            launching = true;
        }

        // 2. Slow Lever (R1) with Dynamic Start
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            // First, make sure we haven't reached the absolute top
            if (current_angle < maxUpAngle) {
                
                // Are we in the first 50% of the lift?
                if (current_angle < halfAngle) {
                    double progress = current_angle / halfAngle;
                    double dynamicVoltage = 12000 - (progress * 7000);
                    lever.move_voltage(dynamicVoltage);
                } 
                // We passed 50%, hold steady at 6000mV
                else {
                    lever.move_voltage(6000);
                }
                
            } 
            // We reached the absolute top, hold safely at 1V
            else { 
                lever.move_voltage(1000);
            } 
            launching = true;
        }
        
        // 3. AUTOMATIC DOWN
        else {
            if (launching) {
                // Pull down UNTIL we hit the target angle
                if (current_angle > minDownAngle) {
                    lever.move_voltage(-12000); 
                } else {
                    // We reached the bottom safely! 
                    launching = false; // This triggers the 1V hold below
                }
            } else {
                // Hold gently at 1V so it stays down.
                lever.move_voltage(-1000);  
            }
        } 
        
        // Proper PROS delay syntax at the end of the while loop
        pros::delay(20);
    }
}
// Define our three possible target states
  enum DiscoreState { DOWN, MID, UP };
void discoreState() {
    // Start in the DOWN position
    DiscoreState targetState = DOWN; 

    // Define your angles (You will need to tune these!)
    const double downAngle = 5.0;
    const double midAngle = 45.0;
    const double upAngle = 90.0;
    
    // A small buffer so the motor doesn't aggressively jitter 
    // trying to hit an exact decimal like 45.0001
    const double margin = 3.0; 

    while (true) {
        // =======================================================
        // 1. INPUT HANDLING (Change the Target State)
        // =======================================================
        
        // Digital UP Button (The Toggle)
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
            if (targetState == UP) {
                targetState = MID; // If we are UP (or going UP), switch to MID
            } else {
                targetState = UP;  // Otherwise, go UP
            }
        }
        
        // Digital Y Button (The Reset)
        else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
            targetState = DOWN; // Immediately target DOWN
        }


        // =======================================================
        // 2. MOTOR EXECUTION (Move and Anti-Overheat)
        // =======================================================
        
        double current_angle = discore.get_position();
        double target_angle = downAngle; // Default fallback

        // Determine which angle number we are aiming for based on the state
        if (targetState == UP) target_angle = upAngle;
        else if (targetState == MID) target_angle = midAngle;
        else if (targetState == DOWN) target_angle = downAngle;

        // Calculate how far we are from our goal
        double error = target_angle - current_angle;

        // Are we below the target? Move UP.
        if (error > margin) {
            discore.move_voltage(12000);
        } 
        // Are we above the target? Move DOWN.
        else if (error < -margin) {
            discore.move_voltage(-12000);
        } 
        // We are within the margin! We arrived at the target.
        else {
            if (targetState == DOWN) {
                // If we are at the bottom, gently push down into the hardstop
                discore.move_voltage(-1000); 
            } else {
                // If we are MID or UP, apply the anti-gravity hold
                discore.move_voltage(1000);
            }
        }

        pros::delay(20);
    }
}





















///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(48_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}


/// Odom Drive PID 
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}


/// Odom Boomerang

void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}


/// Odom Boomerang Injected Pure Pursuit

void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}


/// Calculate the offsets of your tracking wheels

void measure_offsets() {
  // Number of times to test
  int iterations = 10;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}





