/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Encoder.h>
#include <frc/PWMVictorSPX.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <wpi/math>
#include <rev/CANSparkMax.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#define brushless rev::CANSparkMax::MotorType::kBrushless

class SwerveModule {
 public:
  SwerveModule(int driveMotorChannel, int turningMotorChannel);
  frc::SwerveModuleState GetState();
  void SetPID();
  void SetDesiredState(const frc::SwerveModuleState& state);
  rev::CANSparkMax m_driveMotor;
  rev::CANSparkMax m_turningMotor;

  rev::CANEncoder m_driveEncoder = m_driveMotor.GetEncoder();
  rev::CANEncoder m_turningEncoder = m_turningMotor.GetEncoder();
  
  rev::CANPIDController m_drivePIDController = m_driveMotor.GetPIDController();
  rev::CANPIDController m_turnPIDController = m_turningMotor.GetPIDController();

 private:
  static constexpr double kWheelRadius = 0.0508;
  static constexpr int kEncoderResolution = 4096;

  static constexpr auto kModuleMaxAngularVelocity =
      wpi::math::pi * 1_rad_per_s;  // radians per second
  static constexpr auto kModuleMaxAngularAcceleration =
      wpi::math::pi * 2_rad_per_s / 1_s;  // radians per second^2

  //frc::PWMVictorSPX m_driveMotor;   //this is the drive motor for the module
  //frc::PWMVictorSPX m_turningMotor; //this is the turning motor for the module
};