#include <nds.h>
#include <stdio.h>

#include "Backend/Vector.hpp"

#include "DSGraphics.hpp"
#include "WorldRenderer.hpp"

//-- Dummy Constructor --
DSGraphics::WorldRenderer::WorldRenderer() {}

inline void DSGraphics::WorldRenderer::setTileXY(bool fg,int x,int y,u16 tile,int palette)
{
	u16* map = bgGetMapPtr(fg ? DSGraphics::instance().m_bg2 : DSGraphics::instance().m_bg3);
	map[(x%64) + (y%64)*64] = tile;
}

void DSGraphics::WorldRenderer::setTile16(bool fg,int x,int y,int block,int palette)
{
	setTileXY(fg,x*2  ,y*2  ,block*4  ,palette);
	setTileXY(fg,x*2+1,y*2  ,block*4+2,palette);
	setTileXY(fg,x*2  ,y*2+1,block*4+1,palette);
	setTileXY(fg,x*2+1,y*2+1,block*4+3,palette);
}

bool DSGraphics::WorldRenderer::onScreen(Vector2i cam_pos,int bx,int by)
{
	
	if (bx < 0) return false;
	if (bx > World::WIDTH) return false;
	if (by < 0) return false;
	if (by > World::HEIGHT) return false;
	
	if ((bx*16 + 16 ) > (cam_pos.x + 256 + 32)) return false;
	else if (bx*16 < (cam_pos.x-32)) return false;
	else if ((by*16 + 16) > (cam_pos.y + 192 + 32)) return false;
	else if (by*16 < (cam_pos.y-32)) return false;
	return true;
}

void DSGraphics::WorldRenderer::render(World& world, Vector2i cam_pos)
{
	
	iprintf("\033[10;0H(%d,%d)       ",cam_pos.x,cam_pos.y);
	iprintf("\033[11;0H(%d,%d)       ",cam_pos.x/16-2,cam_pos.y/16-2);
	
	if (cam_pos.x < 0) cam_pos.x = 0;
	else if (cam_pos.x > (World::WIDTH*16 - 256)) cam_pos.x = World::WIDTH*16-256;
	if (cam_pos.y < 0) cam_pos.y = 0;
	else if (cam_pos.y > (World::HEIGHT*16 - 192)) cam_pos.y = World::HEIGHT*16-192;
	
	// Set the camera position
	DSGraphics::instance().setScroll(cam_pos);
	
	iprintf("\033[12;0H(%d,%d)       ",cam_pos.x,cam_pos.y);
	
	for (int i = (cam_pos.x/16 - 2); i < (cam_pos.x/16 + 20); ++i)
	{
		for (int j = (cam_pos.y/16 - 2); j < (cam_pos.y/16 + 20); ++j)
		{
			if (onScreen(cam_pos,i,j))
			{
				//setTile16(false,i,j,(int)world.blocks[World::BG][i][j],0);
				setTile16(true ,i,j,(int)world.blocks[World::FG][i][j],0);
			}
		}
	}
	
}
