#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugBox(GetWorld(), Location, FVector(50.f,50.f,50.f), FColor::Cyan, true)
#define DRAW_LINE(Location, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Cyan, true)
#define DRAW_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), EndLineLocation, 8.f, FColor::Cyan, true)
#define DRAW_VECTOR(StartLocation, EndLocation) if (GetWorld()) \
{\
	DRAW_SPHERE(StartLocation); \
	DRAW_LINE(StartLocation, EndLocation); \
	DRAW_POINT(StartLocation); \
}

#define DRAW_SPHERE_SingleFrame(Location) if (GetWorld()) DrawDebugBox(GetWorld(), Location, FVector(50.f,50.f,50.f), FColor::Cyan, false, -1.f)
#define DRAW_LINE_SingleFrame(Location, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), Location, EndLocation, FColor::Cyan, false, -1.f)
#define DRAW_POINT_SingleFrame(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), EndLineLocation, 8.f, FColor::Cyan, false, -1.f)
#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if (GetWorld()) \
{\
	DRAW_SPHERE_SingleFrame(StartLocation); \
	DRAW_LINE_SingleFrame(StartLocation, EndLocation); \
	DRAW_POINT_SingleFrame(StartLocation); \
}