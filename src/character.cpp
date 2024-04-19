#include "mathfu/vector.h"
#include "character.h"
#include "LEAGUE/physics.h"
#include "LEAGUE/engine.h"
#include <iostream>
#include <string>
#include <box2d/box2d.h>

Character::Character(PhysicsWorld* physics) {
    x_vel = 0;
    y_vel = 0;
    loadImage("./assets/hummingZoon.png");

    // Define body
    bodyDef = new b2BodyDef;
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(4.0f, -1.5f); // Set initial position

    // Create body in physics world
    body = physics->addBody(bodyDef);

    // Define shape
    b2PolygonShape myShape;
    myShape.SetAsBox(0.5f, 0.5f); // Set the shape as a box

    // Define fixture
    b2FixtureDef boxFixture;
    boxFixture.shape = &myShape;
    boxFixture.density = 0.1f;
    boxFixture.friction = 0.01f;
    boxFixture.restitution = 0.1f;

    // Attach fixture to body
    body->CreateFixture(&boxFixture);
}

Character::~Character(){
    delete bodyDef;
}

void Character::setBody(b2Body* body){
	this->body = body;
}

b2BodyDef* Character::getBodyDef(){
	return bodyDef;
} 

void Character::update(double delta) {
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    // Reset forces
    b2Vec2 force(0, 0);

    // Update force based on arrow key inputs
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        force.x -= 90 * delta; // Apply force to the left
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        force.x += 90 * delta; // Apply force to the right
    }
    if (keyboardState[SDL_SCANCODE_UP]) {
        force.y += 75 *delta; // Apply force upwards
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        force.y -= 75 * delta; // Apply force downwards
    }

    // Apply the accumulated force to the center of the character's physics body
    body->SetLinearVelocity(force);
}

void Character::draw(SDL_Renderer* renderer){
	SDL_Rect dest;
	b2Vec2 pos = body->GetPosition();
	dest.x = pos.x * 100;
	dest.y = (1 - pos.y) * 100; // Adjusting for upside-down rendering

	dest.w = rect.w;
	dest.h = rect.h;
	int result = SDL_RenderCopy(renderer, texture, NULL, &dest);
	if(result != 0){
		std::cout << SDL_GetError() << std::endl;
	}
}

b2Body* Character::getBody(){
	return body;
}
