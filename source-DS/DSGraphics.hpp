#pragma once
#include <nds.h>


#include "Backend/Vector.hpp"

// A singleton class used for setting up and maintaining the DS Graphics engine
// Should be accessed with DSGraphics::instance()
class DSGraphics
{
friend class WorldRenderer;
	
private:
	DSGraphics();
	
	//-- Variables --
	//    m_ = main screen
	//    s_ = sub screen
	int m_bg2;
	int m_bg3;
	
	bool inited = false;
	
	
public:
	
	//-- The world renderer is also a singleton --
	class WorldRenderer;
	static WorldRenderer& renderer();
	
	DSGraphics(DSGraphics const&) = delete;
	void operator=(DSGraphics const&) = delete;
	
	void init();
	void setScroll(Vector2i cam_pos);

	static DSGraphics& instance();
	
};
