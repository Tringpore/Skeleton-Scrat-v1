#include "main.h"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "globals.hpp"
#include "mech_lib.hpp"

void on_center_button() {

}

void initialize() {
	//base
    Motor onel(onel_port, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor twol(twol_port, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor threel(threel_port, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor fourl(fourl_port, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
	Motor oner(oner_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
	Motor twor(twor_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
    Motor threer(threer_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
    Motor fourr(fourr_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
    
    //catapult
    Motor catal(catal_port, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
    Motor catar(catar_port, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
    Rotation catarot(catarot_port);

    //intake
    Motor rollers(rollers_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
    Motor flipper(flipper_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); //change to gearset_36 if using flipper
    Rotation flipperrot(flipperrot_port);
}

void disabled() {

}


void competition_initialize() {

}


void autonomous() {

}


void opcontrol() {
    Controller master(pros::E_CONTROLLER_MASTER);
    
    //base
    Motor onel(onel_port);
	Motor twol(twol_port);
	Motor threel(threel_port);
	Motor fourl(fourl_port);
	Motor oner(oner_port);
	Motor twor(twor_port);
    Motor threer(threer_port);
    Motor fourr(fourr_port);

    //drive mode control
    bool tankdrive = true;

    //catapult
    Motor catal(catal_port);
    Motor catar(catar_port);
    Rotation catarot(catarot_port);
    bool shoot = false;

    //intake
    Motor rollers(rollers_port);
    Motor flipper(flipper_port);
    bool flipper_lifted = true;

    //clear controller screen
    master.clear();

    //clear cata rot sensor
    catarot.reset();

    delay(100);

    while(true){
        double left, right;
        if(master.get_digital_new_press(DIGITAL_Y)) tankdrive = !tankdrive;
        if(tankdrive) {
            left = master.get_analog(ANALOG_LEFT_Y);
            right = master.get_analog(ANALOG_RIGHT_Y);
        } 
                
        else {
            double power =  master.get_analog(ANALOG_LEFT_Y);
            double turn = master.get_analog(ANALOG_RIGHT_X);
            left = power + turn;
            right = power - turn;
        }

        onel.move(left);
        twol.move(left);
        threel.move(left);
        fourl.move(left);
        oner.move(right);
        twor.move(right);
        threer.move(right);
        fourr.move(right);
        
        if(master.get_digital_new_press(DIGITAL_R1)) shootcata();
	    
        // rollers.move(120 * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)));

        //cata_control();

        flipper_control();

        current_display();

        delay(5);
    }    
}