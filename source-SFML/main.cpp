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
	
	sf::RenderWindow window(sf::VideoMode(640, 480), "Port Craft", sf::Style::Default);
	window.setFramerateLimit(60); //TODO: Create option for vsync (for me it causes excessive screen tearing)
	sf::View view(window.getDefaultView());

	float zoomFactor = 1.f;
	view.zoom(zoomFactor);

	sf::Clock deltaClock;

	SFMLGraphics textureManager(view.getSize());
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
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				view.setSize(event.size.width, event.size.height);
				view.zoom(zoomFactor);
				textureManager.resize(view.getSize());
			}
		}

		window.setView(view);
		//world->update(dt, player);
		world->updateCamera(dt,player.getPixPos(window));
		
		renderer.update(view);
		renderer.update(window);
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
