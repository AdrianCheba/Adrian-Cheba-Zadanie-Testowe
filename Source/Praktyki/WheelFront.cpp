// Copyright 2023 Teyon. All Rights Reserved.


#include "WheelFront.h"

UWheelFront::UWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedByEngine = true;
	bAffectedBySteering = true;
	MaxSteerAngle = 45;
}
