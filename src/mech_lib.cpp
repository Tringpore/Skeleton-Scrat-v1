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
bool shoot = true;

//intake
Motor rollers(rollers_port, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
Motor flipper(flipper_port, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
bool flipper_lifted = true;


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

void flipper_control(){
    
    double flipper_power = 100;

    /*
    if(master.get_digital(DIGITAL_R2)){
        if(flipper_lifted){
            flipper.move(-flipper_power);
            delay(275);
            flipper_lifted = false;
        }

        else{
            flipper.move(flipper_power);
            delay(400);
            flipper_lifted = true;
        }
    }

    else if(master.get_digital(DIGITAL_X)){
        if (flipper.get_position() < 60){
            flipper.move(50);
        }
    }

    else if(master.get_digital(DIGITAL_B)){
        if (flipper.get_position() >0){
            flipper.move(-50);
        }
    }

    else{
       flipper.move(0);
    }
    */
   
   /*
   if(master.get_digital(DIGITAL_R2)){
        if(flipper_lifted){
            flipper.move(-flipper_power);
            delay(275);
            flipper.move(-flipper_power/ 10);
            delay(500);
            flipper.tare_position();
            flipper_lifted = false;
            flipper.move(0);
        }

        else{
            flipper.move(flipper_power);
            delay(400);
            flipper_lifted = true;
        }
   }
    */

   if(master.get_digital(DIGITAL_R2)){
    if(flipper.get_position() < 100){
        flipper.move(-flipper_power);
    }
    
    else if(flipper.get_position() > 200){
        flipper.move(flipper_power);
    }

    else{
        flipper.move(0);
    }
   }
   

    //prints weird values
    //master.print(1, 0, "Flipper: %d", flipper.get_position());
}

void cata_control(){
    double cata_power = 120 * (-0.000000008 * pow(catarot.get_angle()/ 100, 4) + 1);
    if(shoot){
        catal.move(120);
        catar.move(120);
        delay(200);
        catal.move(0);
        catar.move(0);
        delay(100);
        shoot = false;
        catarot.reset();
    }

    else if(catarot.get_angle() < 8100){
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