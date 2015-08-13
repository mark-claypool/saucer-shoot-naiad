//
// Hero.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes.
#include "Bullet.h"
#include "EventNuke.h"
#include "Explosion.h"
#include "GameOver.h"
#include "Hero.h"

Hero::Hero() {

  df::LogManager &log_manager = df::LogManager::getInstance();

#ifdef REGISTER
  // Player controls hero, so register with keyboard and mouse.
  registerInterest(df::KEYBOARD_EVENT);
  registerInterest(df::MOUSE_EVENT);

  // Need to update fire rate control each step.
  registerInterest(df::STEP_EVENT);
#endif

  // Set object type.
  setType("Hero");

  // Set starting location.
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::Position pos(7, graphics_manager.getVertical()/2);
  setPosition(pos);

  // Create reticle for firing bullets.
  p_reticle = new Reticle();
  p_reticle->draw();

  // Set firing variables.
  fire_slowdown = 15;
  fire_countdown = fire_slowdown;

  nuke_count = 1;
}

Hero::~Hero() {

  // Create GameOver object.
  GameOver *p_go = new GameOver;
 
  // Make big explosion.
  for (int i=-8; i<=8; i+=5) {
    for (int j=-5; j<=5; j+=3) {
      df::Position temp_pos = this->getPosition();
      temp_pos.setX(this->getPosition().getX() + i);
      temp_pos.setY(this->getPosition().getY() + j);
      Explosion *p_explosion = new Explosion;
      p_explosion -> setPosition(temp_pos);
    }
  }
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_keyboard_event = static_cast <const df::EventKeyboard *> (p_e);
    kbd(p_keyboard_event);
    return 1;
  }

  if (p_e->getType() == df::MOUSE_EVENT) {
    const df::EventMouse *p_mouse_event = static_cast <const df::EventMouse *> (p_e);
    mouse(p_mouse_event);
    return 1;
  }

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse *p_mouse_event) {

  // Pressed button?
  if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
      (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
    fire(p_mouse_event->getMousePosition());
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {
  df::WorldManager &world_manager = df::WorldManager::getInstance();

  switch(p_keyboard_event->getKey()) {
  case df::Keyboard::W:			// up
    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
      move(-1);
    break;
  case df::Keyboard::S:			// down
    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
      move(+1);
    break;
  case df::Keyboard::SPACE:		// nuke!
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      nuke();
    break;
  case df::Keyboard::Q:			// quit
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
      df::WorldManager &world_manager = df::WorldManager::getInstance();
      world_manager.markForDelete(this);
    }
    break;
  };

  return;
}

// Move up or down.
void Hero::move(int dy) {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  df::Position new_pos(getPosition().getX(), getPosition().getY() + dy);

  // If stays on screen, allow move.
  if ((new_pos.getY() >= 0) && 
        (new_pos.getY() < graphics_manager.getVertical()))
      world_manager.moveObject(this, new_pos);
}

// Fire bullet towards target.
void Hero::fire(df::Position target) {

  // See if time to fire.
  if (fire_countdown > 0)
    return;
  fire_countdown = fire_slowdown;

  // Fire Bullet towards target.
  Bullet *p = new Bullet(getPosition());
  p->setYVelocity((float) (target.getY() - getPosition().getY()) /
		  (float) (target.getX() - getPosition().getX()));
}

// Decrease fire restriction.
void Hero::step() {
  fire_countdown--;
  if (fire_countdown < 0)
    fire_countdown = 0;
}

// Send nuke event to all objects.
void Hero::nuke() {

  // Check if nukes left.
  if (!nuke_count) 
    return;
  nuke_count--;

  // Create "nuke" event and send to interested.
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  EventNuke nuke;
  world_manager.onEvent(&nuke);
}

// 
void Hero::draw() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), HERO_CHAR, df::BLUE); 
}
