#include <nds.h>

#include "DSGraphics.hpp"
#include "WorldRenderer.hpp"

//-- Dummy Constructor --
DSGraphics::WorldRenderer::WorldRenderer() {}

inline void DSGraphics::WorldRenderer::setTileXY(bool fg,int x,int y,u16 tile,int palette)
{
	u16* map = bgGetMapPtr(fg ? DSGraphics::instance().m_bg2 : DSGraphics::instance().m_bg3);
	map[(x%64) + (y%64)*64] = tile | palette << 12;	
}

void DSGraphics::WorldRenderer::setTile16(bool fg,int x,int y,int block,int palette)
{
	setTileXY(fg,x*2  ,y*2  ,block*4  ,palette);
	setTileXY(fg,x*2+1,y*2  ,block*4+2,palette);
	setTileXY(fg,x*2  ,y*2+1,block*4+1,palette);
	setTileXY(fg,x*2+1,y*2+1,block*4+3,palette);
}

void DSGraphics::WorldRenderer::render(World& world, Vector2i cam_pos)
{
	// Set the camera position
	DSGraphics::instance().setScroll(cam_pos);
	
	setTile16(false,0,0,1,0);
	setTile16(true,0,0,4,0);
	
}
