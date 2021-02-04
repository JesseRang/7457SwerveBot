#include "Drivetrain.h"
#include <frc/SmartDashboard/SmartDashboard.h>
#include <stdio.h>


void Drivetrain::Drive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rot, bool fieldRelative)
{

  auto states = m_kinematics.ToSwerveModuleStates(fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(xSpeed, ySpeed, rot, GetAngle()) : frc::ChassisSpeeds{xSpeed, ySpeed, rot});

  m_kinematics.NormalizeWheelSpeeds(&states, kMaxSpeed);

  auto [fl, fr, bl, br] = states;
  

  if (xSpeed.to<double>() == 0 && ySpeed.to<double>() == 0 && rot.to<double>() == 0) {
    fl.angle = pfl.angle;
    fr.angle = pfr.angle;
    bl.angle = pbl.angle;
    br.angle = pbr.angle;
  }

  pfl.angle = fl.angle;
  pfr.angle = fr.angle;
  pbl.angle = bl.angle;
  pbr.angle = br.angle;

  m_frontLeft.SetDesiredState(fl);
  m_frontRight.SetDesiredState(fr);
  m_backLeft.SetDesiredState(bl);
  m_backRight.SetDesiredState(br);

  frc::SmartDashboard::PutNumber("FLCurrentAngle", m_frontLeft.GetAngle());
}

void Drivetrain::UpdateOdometry()
{
  m_odometry.Update(GetAngle(), m_frontLeft.GetState(), m_frontRight.GetState(),
                    m_backLeft.GetState(), m_backRight.GetState());
}
