#include "functions.h"


Radius compute_radius(Radius polygoneRadius){
	
	float radiusMax = gfx_screenHeight() * MAX_RADIUS_TO_SCREEN_HEIGHT_RATIO; 
	
	if (polygoneRadius.growing) {
		polygoneRadius.value = polygoneRadius.value + (radiusMax / ZOOM_SPEED); 
	} else {
		polygoneRadius.value = polygoneRadius.value - (radiusMax / ZOOM_SPEED); 	
	}
	polygoneRadius = exceeding_verification(polygoneRadius, radiusMax);
	return polygoneRadius;
}

Radius exceeding_verification(Radius polygoneRadius, float radiusMax){
	if (polygoneRadius.value > radiusMax) {
		polygoneRadius.growing = false; 
		polygoneRadius.value = radiusMax; 
	} else if (polygoneRadius.value < 0){
		polygoneRadius.growing = true; 
		polygoneRadius.value = 0; 	
	}
	return polygoneRadius;
}


void place_peaks(Points peakArray[NUMBER_OF_SIDE], Points center, Radius polygoneRadius, float angle){
	
	float peakInterval = (2 * M_PI) / NUMBER_OF_SIDE; 
	
	for (int i = 0; i < NUMBER_OF_SIDE; i++) {
		peakArray[i].x = center.x + polygoneRadius.value * cos(angle + (i * peakInterval)); 
		peakArray[i].y = center.y + polygoneRadius.value * sin(angle + (i * peakInterval)); 
	}
	
}
				
void connect_peaks(Points peakArray[NUMBER_OF_SIDE]){
	
	for (int i = 0; i < NUMBER_OF_SIDE; i++) {
		gfx_line(peakArray[i].x, peakArray[i].y, peakArray[(i+1)%NUMBER_OF_SIDE].x, peakArray[(i+1)%NUMBER_OF_SIDE].y, YELLOW); 
	}
	
}









