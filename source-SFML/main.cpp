#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "World/Entities/Mobs/Player.hpp"
#include "World/Entities/Entity.hpp"
#include "World/WorldRenderer.hpp" // renderer
#include "World/World.hpp"
#include "SFMLGraphics.hpp"
#include "EntityHandler.hpp" // world
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

	std::shared_ptr<World> world(new World(Vector2f(0.f, 18.f)));
	WorldRenderer renderer(*world, textureManager.getTexture()); // TODO: Handle exception
	renderer.calculateBrightness();
	
	EntityHandler entityHandler;
	const Player &player = entityHandler.createPlayer();

	while (window.isOpen())
	{
		float dt = deltaClock.restart().asSeconds();
		window.updateInternal(textureManager);
		world->updateCamera(dt, (Vector2f)world->coordToPix(player.getPos()));
		
		window.updateRenderer(renderer);
		entityHandler.update(dt, *world);

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
