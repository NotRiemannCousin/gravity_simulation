#include <SFML/Graphics.hpp>

#include <math.h>

using namespace sf;

class Planet

{

  private:

	CircleShape p;	int weight, radius;

	Vector2f force;

	VertexArray vertex;

  public:

	float getRadius() { return p.getRadius(); };

	void updateForce()

	{

		p.move(force.x / weight, force.y / weight );

		vertex.append(Vertex(p.getPosition()));

	};

	Planet(float Weight = 50, float Radius = 50, Color Color = Color::Green, Vector2f x = {0, 0})

	{

//		vertex.setPrimitiveType(bool);

		weight = Weight;

		p.setRadius(Radius);

		p.setFillColor(Color);

		p.setOrigin(p.getPosition().x + Radius, p.getPosition().y + Radius);

		p.setPosition(x);

//		vertex.setPrimitiveType(TriangleFan);

		};

	void addForce(Vector2f Force)

	{

		force += Force;

	};

	void draw(RenderWindow &w)

	{

		w.draw(p);

//		vertex.append(p.getPosition());

		w.draw(vertex);

	};

	Vector2f getPosition() {return p.getPosition();};

	int getMass() {return weight;};

//	float getRadius() {return p.getRadius();}

}

;
