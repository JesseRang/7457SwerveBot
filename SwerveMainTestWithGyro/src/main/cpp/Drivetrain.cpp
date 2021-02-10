#include "Drivetrain.h"
#include <frc/SmartDashboard/SmartDashboard.h>
#include <stdio.h>


void Drivetrain::Drive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rot, bool fieldRelative, bool autonomous = 0, double distance = 0, double maxVelocity = 0)
{
  auto states = m_kinematics.ToSwerveModuleStates(fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(xSpeed, ySpeed, rot, GetAngle()) : frc::ChassisSpeeds{xSpeed, ySpeed, rot});

  m_kinematics.NormalizeWheelSpeeds(&states, kMaxSpeed);

  auto [fl, fr, bl, br] = states;
  

  if (xSpeed.to<double>() == 0 && ySpeed.to<double>() == 0 && rot.to<double>() == 0) { //added rot to prevent wheels not changing when trying to rotate
    fl.angle = pfl.angle;
    fr.angle = pfr.angle;
    bl.angle = pbl.angle;
    br.angle = pbr.angle;
  }

  pfl.angle = fl.angle;
  pfr.angle = fr.angle;
  pbl.angle = bl.angle;
  pbr.angle = br.angle;

  flb = m_frontLeft.SetDesiredState(fl, autonomous, distance, maxVelocity);
  frb = m_frontRight.SetDesiredState(fr, autonomous, distance, maxVelocity);
  blb = m_backLeft.SetDesiredState(bl, autonomous, distance, maxVelocity);
  brb = m_backRight.SetDesiredState(br, autonomous, distance, maxVelocity);

  if (flb + frb + blb + brb > 0) {
    arrived = true;
  } else {
    arrived = false;
  }

  frc::SmartDashboard::PutNumber("FLCurrentAngle", m_frontLeft.GetAngle());
}

void Drivetrain::UpdateOdometry()
{
  m_odometry.Update(GetAngle(), m_frontLeft.GetState(), m_frontRight.GetState(),
                    m_backLeft.GetState(), m_backRight.GetState());
}
