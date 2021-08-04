#include <SFML/Graphics.hpp>

#include <vector>

#include <math.h>

#include <Planet.hpp>

using namespace sf;

std::vector<Planet> vetorplanetas;

class Game

{

  private:

	float G = 10.0f;

	RenderWindow mWindow;

	CircleShape mShape;

	View view;

	Clock clock;

  public:

	Game() : mWindow(VideoMode(1080, 2340), "sfml")

	{

		view = mWindow.getView();

		view.setCenter(0, 0);

		view.zoom(5);

		mWindow.setView(view);

		vetorplanetas.push_back(Planet(500, 100, Color::Red, Vector2f(1500, 0)));

		vetorplanetas.push_back(Planet(500, 100, Color::Green, Vector2f(0, 0)));

		vetorplanetas.push_back(Planet(500, 100, Color::Blue, Vector2f(-1500, 0)));

		vetorplanetas.back().addForce(Vector2f(0, 500));

//		vetorplanetas.push_back(Planet(4000, 200, Color::Yellow, Vector2f(1500, 0)));

//		vetorplanetas.back().addForce(Vector2f(0, 7000));

//		vetorplanetas.push_back(Planet(50, 50, Color::Blue,Vector2f(-600, 0)));

//		vetorplanetas.back().addForce(Vector2f(0, 500));

	};

  private:

	void update(){};

	void render()

	{

		mWindow.clear();

		for (int j = 0; j < vetorplanetas.size(); j++)

		{

			vetorplanetas[j].draw(mWindow);

		}

		mWindow.display();

	};

	void events()

	{

		Event e;

		while (mWindow.pollEvent(e))

		{

			switch (e.type)

			{

			case Event::Closed:

				mWindow.close();

				break;

			case Event::TouchBegan:

				if (Touch::isDown(0))

				{ 

					vetorplanetas.push_back(Planet(20,10, Color::White,mWindow.mapPixelToCoords(Touch::Touch::getPosition(0))));

					vetorplanetas.back().addForce(Vector2f(0, 100));

				}

				break;

			case Event::TouchMoved:

				break;

			case sf::Event::TouchEnded:

				break;

			}

		}

	};

  public:

	void run()

	{

		while (mWindow.isOpen())

		{

			events();

			update();

			render();

			if (clock.getElapsedTime().asMilliseconds() >= 2)

			{

				physics();

				clock.restart();

			}

		}

	};

	void applyForce(Planet &a, Planet &b)

	{

		Vector2f forceDirection = a.getPosition() - b.getPosition();

		float distance = sqrt(pow(forceDirection.x, 2) + pow(forceDirection.y, 2));

		forceDirection = Vector2f(forceDirection / distance);

		float Force = G * ((a.getMass() * b.getMass()) / pow(distance, 2));

		if (distance <= a.getRadius() + b.getRadius())

		{

			a.addForce(Force * forceDirection);

			b.addForce(-Force * forceDirection);

		}

		else

		{

			a.addForce(-Force * forceDirection);

			b.addForce(Force * forceDirection);

		}

	};

	void physics()

	{

		for (int j = 0; j < vetorplanetas.size(); j++)

		{

			vetorplanetas[j].updateForce();

			for (int i = j + 1; i < vetorplanetas.size(); i++)

				applyForce(vetorplanetas[i], vetorplanetas[j]);

		}

	};

};

int main()

{

	Game game;

	game.run();

}
