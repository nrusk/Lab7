#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 150));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(0.7, 0.3));
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(760, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int thudCount(1);

	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "Thud: " << thudCount << endl;
		thudCount++;
	};

	// Create rightWall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 760));
	rightWall.setCenter(Vector2f(790, 300));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);
	
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "Thud: " << thudCount << endl;
		thudCount++;
	};

	// Create leftWall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 760));
	leftWall.setCenter(Vector2f(10, 300));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);
	
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "Thud: " << thudCount << endl;
		thudCount++;
	};

	// Create ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(760, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "Thud: " << thudCount << endl;
		thudCount++;
	};

	// Create obstacle
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(150, 100));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);
	int bangCount(1);
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "-------- Bang: " << bangCount << endl;
		bangCount++;

		if (bangCount > 3) {
			cout << "-------- Game Over --------" << endl;
			exit(0);
			}
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(rightWall);
		window.draw(leftWall);
		window.draw(ceiling);
		window.draw(obstacle);
		window.display();
	}
}