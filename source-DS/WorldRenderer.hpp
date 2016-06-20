#pragma once
#include "Backend/Vector.hpp"

#include "DSGraphics.hpp"
#include "World/World.hpp"

class DSGraphics::WorldRenderer
{
friend class DSGraphics;

private:
	WorldRenderer();
	void setTileXY(bool fg,int x,int y,u16 tile,int palette);
	void setTile16(bool fg,int x,int y,int block,int palette);
	bool onScreen(Vector2i cam_pos,int bx,int by);
public:
		
	void render(World& world,Vector2i cam_pos);
};
