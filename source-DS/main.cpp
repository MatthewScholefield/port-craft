#include <nds.h>
#include <stdio.h>

#include "DSGraphics.hpp"
#include "WorldRenderer.hpp"

#include "Backend/Vector.hpp"
#include "World/World.hpp"

int main()
{
	// Initialize the exception handler
	defaultExceptionHandler();
	
	// Initialize the sub screen for printing
	consoleDemoInit();
	iprintf("Initialized the console!\n");
	
	// Get a reference to the graphics module
	DSGraphics& dsg = DSGraphics::instance();
	// Ensure that the graphics module is initialized
	dsg.init();
	
	iprintf("Generating a world\n");
	World * w = new World(Vector2f(0.0f,18.0f));
	iprintf("Done!\n");
	
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
		
		dsg.renderer().render(*w,cam_pos);
		
		
		swiWaitForVBlank();
	}
	
}
