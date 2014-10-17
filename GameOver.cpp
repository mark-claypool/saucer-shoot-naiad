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
  GraphicsManager &graphics_manager = GraphicsManager::getInstance();
  int world_horiz = graphics_manager.getHorizontal();
  int world_vert = graphics_manager.getVertical();
  Position p(world_horiz/2, world_vert/2);
  setPosition(p);

  // Exit after about 3 seconds.  
  time_to_live = 100;

  // Make like a View Object
  setSolidness(SPECTRAL);
  setAltitude(DF_MAX_ALTITUDE);

#ifdef REGISTER
  // Register for step event.
  registerInterest(DF_STEP_EVENT);
#endif
}

// When done, game over.
GameOver::~GameOver() {
  WorldManager &world_manager = WorldManager::getInstance();

  // Remove Saucers.
  ObjectList object_list = world_manager.getAllObjects(true);
  ObjectListIterator i(&object_list);
  for (i.first(); !i.isDone(); i.next()) {
    Object *p_o = i.currentObject();
    if (p_o -> getType() == "Saucer")
      world_manager.markForDelete(p_o);
  }
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_STEP_EVENT) {
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
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(this);
    GameManager::getInstance().setGameOver();
  }
}

void GameOver::draw() {
  GraphicsManager &graphics_manager = GraphicsManager::getInstance();
  graphics_manager.drawString(getPosition(), "Game Over!", 
			      CENTER_JUSTIFIED, COLOR_WHITE);
}
