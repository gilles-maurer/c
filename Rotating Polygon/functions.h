
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#include "primlib.h"

#define NUMBER_OF_TOURS 5
#define NUMBER_OF_SIDE 5
#define ANGLE_INTERVAL (M_PI / 3000)
#define ZOOM_SPEED 4000
#define MAX_RADIUS_TO_SCREEN_HEIGHT_RATIO 5/12


typedef struct {
			float value; 
			bool growing; 
} Radius; 

typedef struct {
		float x;
		float y; 
} Points; 	


Radius compute_radius(Radius polygoneRadius); 

Radius exceeding_verification(Radius polygoneRadius, float radiusMax);

void place_peaks(Points peakArray[NUMBER_OF_SIDE], Points center, Radius polygoneRadius, float angle); 
				
void connect_peaks(Points peakArray[NUMBER_OF_SIDE]); 


#endif /* __FUNCTIONS_H__ */
