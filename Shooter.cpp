#include "Shooter.h"
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "Intake.h"

void Shooter::initiatePID()
{
    int timeoutMS = 30;

    shooterMotorL.Config_kF(0, shooterF, timeoutMS);
    shooterMotorL.Config_kP(0, shooterP, timeoutMS);
    shooterMotorL.Config_kI(0, shooterI, timeoutMS);
    shooterMotorL.Config_kD(0, shooterD, timeoutMS);
}

void Shooter::Shoot()
{
    modifyVelocity();
    activateConveyor();
}

void Shooter::printModifiableValues()
{

frc::SmartDashboard::PutNumber("Trench Speed", 6000);
frc::SmartDashboard::PutNumber("Init Speed", 5500);
frc::SmartDashboard::PutNumber("Wall Speed", 2700);
frc::SmartDashboard::PutNumber("limelightSpeed", limelightSpeed);

frc::SmartDashboard::PutNumber("ShooterVelocity", 0);

frc::SmartDashboard::PutNumber("ShooterF", 0.047);
frc::SmartDashboard::PutNumber("ShooterP", 0.125);
frc::SmartDashboard::PutNumber("ShooterI", 0);
frc::SmartDashboard::PutNumber("ShooterD", 1.5);
frc::SmartDashboard::PutNumber("WallP", 0.125);
}

void Shooter::setModifiableValues()
{

trenchSpeed = frc::SmartDashboard::GetNumber("Trench Speed", 6000);
initSpeed = frc::SmartDashboard::GetNumber("Init Speed", 5500);
wallSpeed = frc::SmartDashboard::GetNumber("Wall Speed", 2700);
limelightSpeed = frc::SmartDashboard::GetNumber("limelightSpeed", 0);

shooterF = frc::SmartDashboard::GetNumber("ShooterF", 0.047);
shooterP = frc::SmartDashboard::GetNumber("ShooterP", 0.125);
shooterI = frc::SmartDashboard::GetNumber("ShooterI", 0);
shooterD = frc::SmartDashboard::GetNumber("ShooterD", 1.5);
wallP = frc::SmartDashboard::GetNumber("WallP", 0);

}

void Shooter::activateConveyor()
{

}

void Shooter::modifyVelocity()
{

    double modValue = 3.4133;
    double flyWheelDesiredSpeed = 0;

    if (trenchButtonPressed)
    {
        flyWheelDesiredSpeed = trenchSpeed * modValue;
    }
    else if (initButtonPressed)
    {
        flyWheelDesiredSpeed = initSpeed * modValue;
    }
    else if (wallButtonPressed)
    {
        flyWheelDesiredSpeed = wallSpeed * modValue;
    }
    else if (limelightButtonPressed)
    {
        flyWheelDesiredSpeed = limelightSpeed * modValue;
    }
    else
    {
        flyWheelDesiredSpeed = 0;
    }

    shooterMotorL.Set(TalonFXControlMode::Velocity, flyWheelDesiredSpeed) ;

}

void Shooter::modifyPID()
{

}

void Shooter::setHoodPosition() 
{
    //Fill out when we have the actuator Docs
}