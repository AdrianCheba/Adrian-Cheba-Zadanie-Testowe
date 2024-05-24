// Copyright 2023 Teyon. All Rights Reserved.


#include "WheelFront.h"

UWheelFront::UWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedByEngine = true;
	bAffectedBySteering = true;
	MaxSteerAngle = 40;
	FrictionForceMultiplier = 2.5;
	bABSEnabled = true;
	bTractionControlEnabled = true;
	SlipThreshold = 35;
	CorneringStiffness = 1500;
}
