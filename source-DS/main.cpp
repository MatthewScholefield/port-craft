#include <nds.h>
#include <stdio.h>

#include "Backend/Vector.hpp"

#include "World/World.hpp"

#include "blocks.h"

int topNums[] = {4,18,27,28,48};
int bottomNums[] = {1,2,3};

int main()
{
	// Initialize the sub screen for printing
	consoleDemoInit();
	defaultExceptionHandler();
	iprintf("Initialized the console!\n");
	
	// Setup the VRAM Banks
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	iprintf("Initialized the vram!\n");
	
	// Setup the main backgrounds
	videoSetMode(MODE_0_3D);
	int bg2 = bgInit(2, BgType_Text8bpp, BgSize_T_512x256, 16, 0);
	int bg3 = bgInit(3, BgType_Text8bpp, BgSize_T_512x256, 18, 0);
	iprintf("Initialized the backgrounds!\n");
	
	// Copy the graphics into memory
	dmaCopy(blocksTiles, bgGetGfxPtr(bg2), sizeof(blocksTiles));
	dmaCopy(blocksPal, BG_PALETTE, sizeof(blocksPal));
	iprintf("Initialized the graphics!\n");
	
	// Create a default map
	u16* map2 = (u16*)bgGetMapPtr(bg2);
	u16* map3 = (u16*)bgGetMapPtr(bg3);
	int t = 0;
	int b = 0;
	for (int i = 0; i < 16; ++i)
		for (int j = 0; j < 16; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				map2[i*2+((k&0x02)>>1)+(j*2+((k&0x01)))*32] = topNums[t]*4+k;
				map3[i*2+((k&0x02)>>1)+(j*2+((k&0x01)))*32] = bottomNums[b]*4+k;
			}
			b += 1;
			t += 1;
			t = t % 5;
			b = b % 3;
		}

	iprintf("Initialized the maps!\n");
	
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
		
		bgSetScroll(bg2,cam_pos.x,cam_pos.y);
		bgSetScroll(bg3,cam_pos.x,cam_pos.y);
		bgUpdate();
		swiWaitForVBlank();
	}
	
}
