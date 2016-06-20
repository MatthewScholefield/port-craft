#include <nds.h>
#include <stdio.h>
#include "DSGraphics.hpp"

#include "Backend/Vector.hpp"

#include "World/World.hpp"

int main()
{
	// Initialize the exception handler
	defaultExceptionHandler();
	
	// Initialize the sub screen for printing
	consoleDemoInit();
	iprintf("Initialized the console!\n");
	

	DSGraphics::instance().init();
	
	for (int i = 0; i < 120; ++i)
		swiWaitForVBlank();
	
	iprintf("Generating a world for the lolz!\n");
	
	for (int i = 0; i < 10; ++i)
		swiWaitForVBlank();
	BG_PALETTE[0] = 0x7660;
	World * w = new World(Vector2f(0.0f,18.0f));
	Vector2i cam_pos(0,0);
	while(1)
	{
		scanKeys();
		if (keysHeld() & KEY_UP)
			cam_pos.y -= 1;
		if (keysHeld() & KEY_DOWN)
			cam_pos.y += 1;
		if (keysHeld() & KEY_LEFT)
			cam_pos.x -= 1;
		if (keysHeld() & KEY_RIGHT)
			cam_pos.x += 1;
		
		DSGraphics::instance().setScroll(cam_pos);
		
		swiWaitForVBlank();
	}
	
}
