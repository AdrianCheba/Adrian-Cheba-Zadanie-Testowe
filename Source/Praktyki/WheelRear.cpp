// Copyright 2023 Teyon. All Rights Reserved.


#include "WheelRear.h"

UWheelRear::UWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	FrictionForceMultiplier = 2.5;
	bTractionControlEnabled = true;
	bABSEnabled = true;
	SlipThreshold = 35;
	CorneringStiffness = 1500;
}
