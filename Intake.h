#pragma once

#include <frc/DigitalInput.h>
#include <ctre/phoenix/motorcontrol/can/TalonSRX.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <rev/CANSparkMax.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Joystick.h>

using namespace ctre::phoenix::motorcontrol;

class Intake
{
private:
    frc::Joystick driverController{0};
    frc::Joystick operatorController{1};
    frc::DoubleSolenoid intakeSolenoid{2, 3};

    frc::DigitalInput breakBeamFull{3};
    frc::DigitalInput breakBeamNewBall{2};
    frc::DigitalInput breakBeamFourthBall{1};
    frc::DigitalInput breakBeamFifthBall{0};

    can::VictorSPX vMotor1{0};
    can::VictorSPX vMotor2{1};
    can::VictorSPX intakeFollower{2};

    bool intakeFull = false;
    bool newBall = false;
    bool fourBalls = false;
    bool fiveBalls = false;

    // Driver's Left Trigger
    bool isIntaking = false;
    // Driver's Left Bumper
    bool isCycling = false;
    // Operator's Left Trigger
    bool isPurging = false;
    // Operator's Right Trigger
    bool isReversingV = false;

    float indexMotorDefault = 0.6;
    float vMotorDefault = 0.7;
    

public:

    rev::CANSparkMax indexMotor{5, rev::CANSparkMax::MotorType::kBrushless};
    can::TalonSRX intakeMotor{5};
    can::TalonSRX conveyorMotor{4};

    void motorSetup();

    void updateButtons();

    void Run(); 
   
    void intake();
    void cycleBalls();
    void purgeSystem();
    void reverseV();
    void shutDown();

    void intakeLogic();
};