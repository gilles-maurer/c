#include "primlib.h"
#include "functions.h"


int main(int argc, char* argv[]) {
	if (gfx_init()) {
		exit(3);
	}
		
	Points center; 
	center.x = gfx_screenWidth() / 2; 
	center.y = gfx_screenHeight() /2; 
	
	Radius polygoneRadius; 
	polygoneRadius.value = 0; 
	polygoneRadius.growing = true;  
	
	Points peakArray[NUMBER_OF_SIDE]; 
	
	for (int i = 0; i < NUMBER_OF_TOURS; ++i) {

		for (float t = 0; t < 2*M_PI; t = t + ANGLE_INTERVAL) {
			gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
						
			polygoneRadius = compute_radius(polygoneRadius); 

			place_peaks(peakArray, center, polygoneRadius, t); 
			connect_peaks(peakArray); 

			gfx_updateScreen();
			SDL_Delay(1);
				
			if (gfx_pollkey() == ' ') {
				break; 
			}
		}
	}
	gfx_getkey();
	return 0;
}
