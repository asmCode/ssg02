#include "GameProps.h"
#include <math.h>

const float GameProps::RespawnDelay = 2.0f;
const float GameProps::ReproductionDelay = 5.0f;

const float GameProps::FarmerMoveSpeed = 10.0f;
const float GameProps::HealthyBunnyWalkSpeed = 5.0f;
const float GameProps::HealthyBunnyRunSpeed = 8.0f;
const float GameProps::HealthyBunnyResistance = 0.2f;
const float GameProps::InfectedBunnyHuntingSpeed = 10.0f;
const float GameProps::InfectedBunnyRestingSpeed = 5.0f;
const float GameProps::DangerShotAngle = 0.98f; // value of cos(angle)
const float GameProps::HealthyBunnyDistanceToFarmer = 4.0f;
const float GameProps::ReproductionTime = 4.0f;
const float GameProps::RestingAfterReproduction = 6.0f;
const float GameProps::GrowingUpTime = 7.0f;
const float GameProps::BorningTime = 2.0f;
const float GameProps::SpawningTime = 3.0f;
const float GameProps::RestingAfterFuckingTimeFrom = 4.0f;
const float GameProps::RestingAfterFuckingTimeTo = 8.0f;
const float GameProps::RestingAfterTryingToFuckTimeFrom = 2.0f;
const float GameProps::RestingAfterTryingToFuckTimeTo = 4.0f;
const float GameProps::RestingAfterChangedToInfectedTime = 2.0f;
const float GameProps::RefreshNewTargetPositionFrom = 0.5f;
const float GameProps::RefreshNewTargetPositionTo = 5.0f;
const float GameProps::FuckingTime = 4.0f;
const float GameProps::RunningAwayDistance = 10.0f;
const float GameProps::SickBunnySpeed = 2.0f;
const float GameProps::ChangingToInfectedTime = 5.0f;

const float GameProps::ShotgunShotDelay = 1.45f;
const float GameProps::ShotgunRange = 20.0f;
const float GameProps::ShotgunFieldOfDamage = cosf(3.1415f / 32.0f);
const float GameProps::ShotgunDamage = 100.0f;

const float GameProps::PlayerHeight = 3.0f;

const float GameProps::SplashScreenDuration = 1.0f;

