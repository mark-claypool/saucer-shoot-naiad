//
// Saucer.cpp
//
 
#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventCollision.h"
#include "EventNuke.h"
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
 
// Game includes.
#include "Explosion.h"
#include "Saucer.h"

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

Saucer::Saucer() {
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Set object type.
  setType("Saucer");

  // Set speed in horizontal direction.
  setVelocity(df::Vector(-0.25,0)); // 1 space left every 4 frames

  moveToStart();

  // Register interest in "nuke" event.
  registerInterest(NUKE_EVENT);
}

// Handle event.
// Return 0 if ignored, else 1.
int Saucer::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == NUKE_EVENT) {
 
    // Create explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());
 
    // Delete self.
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    world_manager.markForDelete(this);
 
    // Saucers appear stay around perpetually
    new Saucer;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// If moved off left edge, move back to far right.
void Saucer::out() {

  // If haven't moved off left edge, then nothing to do.
  if (getPosition().getX() >= 0)
    return;

  // Otherwise, move back to far right.
  moveToStart();

  // Spawn new Saucer to make the game get harder.
  new Saucer;

}

// If saucer and player collide, mark both for deletion.
void Saucer::hit(const df::EventCollision *p_c) {

  // If Saucer on Saucer, ignore.
  if ((p_c -> getObject1() -> getType() == "Saucer") &&
      (p_c -> getObject2() -> getType() == "Saucer"))
    return;

  // If Bullet ...
  if ((p_c -> getObject1() -> getType() == "Bullet") ||
      (p_c -> getObject2() -> getType() == "Bullet")) {

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

    // Saucers appear stay around perpetually.
    new Saucer;
  }

  // If Hero, mark both objects for destruction.
  if (((p_c -> getObject1() -> getType()) == "Hero") || 
      ((p_c -> getObject2() -> getType()) == "Hero")) {
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject1());
    world_manager.markForDelete(p_c -> getObject2());
  }

}

// Move saucer to starting location on right side of screen.
void Saucer::moveToStart() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  df::Vector temp_pos;

  // Get world boundaries.
  int world_horiz = (int) graphics_manager.getHorizontal();
  int world_vert = (int) graphics_manager.getVertical();

  // x is off right side of screen.
  temp_pos.setX(world_horiz + rand()%world_horiz + 3.0f);

  // y is in vertical range.
  temp_pos.setY(rand()%(world_vert) + 0.0f);

  // If collision, move right slightly until empty space.
  df::ObjectList collision_list = world_manager.isCollision(this, temp_pos);
  while (!collision_list.isEmpty()) {
    temp_pos.setX(temp_pos.getX()+1.0f);
    collision_list = world_manager.isCollision(this, temp_pos);
  }

  world_manager.moveObject(this, temp_pos);
}

void Saucer::draw() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), SAUCER_CHAR, df::GREEN); 
}
