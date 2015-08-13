//
// GameOver.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameOver.h"
#include "GraphicsManager.h"

GameOver::GameOver() {

  setType("GameOver");

  // Put in center of screen.
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  int world_horiz = graphics_manager.getHorizontal();
  int world_vert = graphics_manager.getVertical();
  df::Position p(world_horiz/2, world_vert/2);
  setPosition(p);

  // Exit after about 3 seconds.  
  time_to_live = 100;

  // Make like a View Object
  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE);

#ifdef REGISTER
  // Register for step event.
  registerInterest(df::STEP_EVENT);
#endif
}

// When done, game over.
GameOver::~GameOver() {
  df::WorldManager &world_manager = df::WorldManager::getInstance();

  // Remove Saucers.
  df::ObjectList object_list = world_manager.getAllObjects(true);
  df::ObjectListIterator i(&object_list);
  for (i.first(); !i.isDone(); i.next()) {
    df::Object *p_o = i.currentObject();
    if (p_o -> getType() == "Saucer")
      world_manager.markForDelete(p_o);
  }
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// Count down to end of message.
void GameOver::step() {
  time_to_live--;
  if (time_to_live <= 0) { 
    df::WorldManager &world_manager = df::WorldManager::getInstance();
    world_manager.markForDelete(this);
    df::GameManager::getInstance().setGameOver();
  }
}

void GameOver::draw() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  graphics_manager.drawString(getPosition(), "Game Over!", 
			      df::CENTER_JUSTIFIED, df::WHITE);
}
