#pragma once

#include "Shooter.h"
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>


class Shooter 
{
private:

ctre::phoenix::motorcontrol::can::TalonFX::TalonFX shooterMotorL{0}; 
ctre::phoenix::motorcontrol::can::TalonFX::TalonFX shooterMotorR{1}; 

double shooterF = 0.0453;
double shooterP = 0.15;
double shooterI = 0;
double shooterD = 1.5;
double wallP = 0.125;

bool trenchButtonPressed = false;
bool initButtonPressed = false;
bool wallButtonPressed = false;
bool limelightButtonPressed = false;

double trenchSpeed = 0;
double initSpeed = 1;
double wallSpeed = 2;
double limelightSpeed = 3;

public:

void initiatePID();
void Shoot();

void printCurrentValues();
void printModifiableValues();
void setModifiableValues();

void activateConveyor();

void modifyVelocity();
void modifyPID();

void setHoodPosition();
};