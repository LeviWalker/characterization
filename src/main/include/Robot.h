// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include "datalogging.hpp"

#include <frc/Encoder.h>
#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <units/time.h>

class Robot : public frc::TimedRobot
{
private:
  static const int V = 7;
  static const int seconds = 15;
  static const int leaderID = 16, followerID = 17;
  static const int encoderA = 8, encoderB = 9;
  static const bool encoderInverted = false;
  static constexpr double encoderPulse = 1.0 / 360.0;
  static const frc::Encoder::EncodingType encoderType = frc::Encoder::EncodingType::k4X;

  const units::voltage::volt_t voltage{V};
  data::TimeSignatureLogger<1> flywheelLogger{seconds * 50};
  rev::CANSparkMax leader{leaderID, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax follower{followerID, rev::CANSparkMax::MotorType::kBrushless};
  frc::Encoder encoder{encoderA, encoderB, encoderInverted, encoderType};
  units::second_t testStartTime;
  double lastSavedTime = 0;
  double lastSavedPosition = 0;

public:
  Robot();

  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
  void TestExit() override;

  void SimulationInit() override;
  void SimulationPeriodic() override;

  void LogFlywheel();
  void RunFlywheel();
  void StopFlywheel();
};
