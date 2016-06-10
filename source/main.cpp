#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "World/WorldRenderer.hpp" // renderer
#include "World/World.hpp"
#include "TextureManager.hpp"
#include "EntityHandler.hpp" // world
#include <memory>
#include <iostream> // world

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Port Craft", sf::Style::Default);
	window.setFramerateLimit(60); //TODO: Create option for vsync (for me it causes excessive screen tearing)
	sf::View view(window.getDefaultView());

	float zoomFactor = 1;
	view.zoom(zoomFactor);

	sf::Clock deltaClock;

	TextureManager textureManager(view.getSize());
	if (!textureManager.loadTexture())
		return 1;

	std::shared_ptr<World> world(new World(Vector2f(0.f, 5.f)));
	WorldRenderer renderer(*world, textureManager.getTexture()); // TODO: Handle exception
	renderer.calculateBrightness();
	
	EntityHandler entityHandler;
	entityHandler.createPlayer();

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
		world->update(dt);

		renderer.update(view);
		renderer.update(window);
		entityHandler.update(dt, *world);

		window.clear(); //Render block
		{
			textureManager.drawSky(window);
			window.draw(renderer);
		}
		window.display();
	}

	return 0;
}
