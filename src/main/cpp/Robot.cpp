// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/Timer.h>
#include <units/voltage.h>

Robot::Robot()
{
  leader.RestoreFactoryDefaults();
  follower.RestoreFactoryDefaults();

  follower.Follow(leader, true); // asuming inverted

  leader.EnableVoltageCompensation(12);
  follower.EnableVoltageCompensation(12);

  // left.SetOpenLoopRampRate(0.1);

  leader.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
  follower.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);

  encoder.SetDistancePerPulse(encoderPulse);
}

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit()
{
  AddPeriodic([&]
              { this->LogFlywheel(); },
              5_ms);

  testStartTime = frc::Timer::GetFPGATimestamp();
}

void Robot::TestPeriodic()
{
  this->RunFlywheel();
}

void Robot::TestExit()
{
  flywheelLogger.printCSV();
  leader.SetVoltage(0_V);
}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

void Robot::RunFlywheel()
{
  leader.SetVoltage(voltage);
  StopFlywheel();
}

void Robot::LogFlywheel()
{
  double currentTimestamp = frc::Timer::GetFPGATimestamp().value();
  double time = currentTimestamp - testStartTime.value();
  double dt = time - lastSavedTime;
  double currentPosition = encoder.GetDistance() / 2.0;
  double velocity = (currentPosition - lastSavedPosition) / (60 * dt);
  flywheelLogger.log(time, {velocity});

  lastSavedTime = time;
  lastSavedPosition = currentPosition;
}

void Robot::StopFlywheel()
{
  leader.SetVoltage(0_V);
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
