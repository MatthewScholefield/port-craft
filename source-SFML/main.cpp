#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "SoundManager.hpp"
#include "World/Entities/Mobs/Player.hpp"
#include "World/Entities/Entity.hpp"
#include "World/WorldRenderer.hpp" // renderer
#include "World/World.hpp"
#include "SFMLGraphics.hpp"
#include "EntityHandler.hpp"
#include "MiningHandler.hpp" // world
#include <memory>
#include <iostream> // world

int main()
{
	Entity::init();
	
	RenderWindow window;
	sf::Clock deltaClock;

	SFMLGraphics textureManager(window.getSize());
	if (!textureManager.loadTexture())
		return 1;
	
	SoundManager soundManager;
	if (!soundManager.loudSounds())
		return 1;
	soundManager.play();
	soundManager.playSfx(SoundType::DESTROY, SoundAudio::GRASS);

	std::shared_ptr<World> world(new World(Vector2f(0.f, 18.f)));
	WorldRenderer renderer(*world, textureManager.getTexture()); // TODO: Handle exception
	
	MiningHandler miningHandler;
	EntityHandler entityHandler;
	const Player &player = entityHandler.createPlayer();

	while (window.isOpen())
	{
		float dt = deltaClock.restart().asSeconds();
		window.updateInternal(textureManager);
		world->updateCamera(dt, (Vector2f)world->coordToPix(player.getPos()), window);
		
		window.updateRenderer(renderer);
		entityHandler.update(dt, *world);
		bool changedBlock = miningHandler.update(*world, window);
		if (changedBlock)
			world->triggerBrightnessUpdate();
		world->checkBrightnessUpdate(renderer, window);

		window.clear(); //Render block
		{
			textureManager.drawSky(window);
			window.draw(renderer);
			entityHandler.draw(window, *world);
		}
		window.display();
	}

	return 0;
}
