#include "main.h"

//controller
Controller master(pros::E_CONTROLLER_MASTER);

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
bool shoot = false;

//intake
Motor rollers(rollers_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
Motor flipper(flipper_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES); //change to gearset_36 if using flipper
Rotation flipperrot(flipperrot_port);
// bool flipper_lifted = true;


void current_display(){
    screen::print(TEXT_SMALL, 0, "onel: %3d", onel.get_current_draw());
    screen::print(TEXT_SMALL, 1, "twol: %3d", twol.get_current_draw());
    screen::print(TEXT_SMALL, 2, "threel: %3d", threel.get_current_draw());
    screen::print(TEXT_SMALL, 3, "fourl: %3d", fourl.get_current_draw());
    screen::print(TEXT_SMALL, 4, "oner: %3d", oner.get_current_draw());
    screen::print(TEXT_SMALL, 5, "twor: %3d", twor.get_current_draw());
    screen::print(TEXT_SMALL, 6, "threer: %3d", threer.get_current_draw());
    screen::print(TEXT_SMALL, 7, "fourr: %3d", fourr.get_current_draw());
    screen::print(TEXT_SMALL, 8, "catal: %3d", catal.get_current_draw());
    screen::print(TEXT_SMALL, 9, "catar: %3d", catar.get_current_draw());
    screen::print(TEXT_SMALL, 10, "rollers: %3d", rollers.get_current_draw());
    screen::print(TEXT_SMALL, 11, "flipper: %3d", flipper.get_current_draw());
}

double flipper_targ = 0, flipper_power = 100, flipper_kp = 15, intake_power = 120, flipper_pos = (flipper_targ - flipper.get_position()) * flipper_kp;
int flipper_state = 0;

void flipper_control(){
    rollers.move(-intake_power * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)));
    flipper.move(intake_power * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)));
    if(flipperrot.get_position() > 0){
       //flipper_targ = 0;
       //rollers.move((flipper_targ - flipperrot.get_position()) * flipper_kp);
       rollers.move(-40);
       flipper.move(0);
       //flipper.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }

    else{
        flipper.move(0);
        rollers.move(0);
    }
    
   
    /*
    if(master.get_digital(DIGITAL_L2)){
        //outake
        rollers.move(intake_power);
        flipper.move(-intake_power);
    }

    else if(master.get_digital(DIGITAL_L1)){
        //intake
        rollers.move(-intake_power);
        flipper.move(intake_power);
    }

    else{
        rollers.move(0);
        flipper.move(0);
    }
    */

    // rollers.move(intake_power * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)));
    // flipper.move(-intake_power * (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)));
    

    /*
    if(master.get_digital_new_press(DIGITAL_R2)){
        if(flipper_state = 0){
            //flipper is now up
            flipper_targ = 275; //change 120 to down state
            flipper.move(flipper_pos);
            rollers.move(-flipper_pos);
            flipper_state = 1;
            //flipper is now down
        }

        else{
            //flipper is now down
            flipper_targ = 0; //change 0 to up state
            flipper.move(-flipper_pos);
            flipper.move(flipper_pos);
            flipper_state = 0;
            //flipper is now up
        }
    }
    */

    /*
    double flipper_power = 100;
    double flipper_kp = 2;
    flipper.set_brake_mode(E_MOTOR_BRAKE_HOLD);

    flipper.move((flipper_targ - flipper.get_position()) * flipper_kp);

    if(master.get_digital_new_press(DIGITAL_R2)){
        if(flipper_state != 2){
            flipper_targ = -120;
            flipper_state = 2;
            //flipper is now up
        }
        else{
            flipper_targ = -5;
            flipper_state = 0;
            //flipper is now down
        }
    }

    else if(master.get_digital_new_press(DIGITAL_X)){
        flipper_targ = -60;
        flipper_state = 1;
        //flipper is now in middle pos
    }
    */
}

void cata_control(){
    // double cata_power = 120 * (-0.000000008 * pow(catarot.get_angle()/ 100, 4) + 1);
    double cata_error = 36000 - catarot.get_angle();
    double cata_power = 127 * 1/ 4.8 * (log((cata_error/100) + 18));
    
    if(shoot){
        catal.move(120);
        catar.move(120);
        delay(200);
        catal.move(0);
        catar.move(0);
        delay(100);
        shoot = false;
    }

    else if(cata_error > 620){
        catal.move(cata_power);
        catar.move(cata_power);
    }
    
    else{
        catal.move(0);
        catar.move(0);
    }

    master.print(0, 0, "Rot Angle: %d", catarot.get_angle());
    delay(5);
}

void shootcata(){
    shoot = true;
}