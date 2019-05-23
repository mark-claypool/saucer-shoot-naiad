//
// GameOver.cpp
//

// Engine includes.
#include "DisplayManager.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes.
#include "DisplayManager.h"
#include "GameOver.h"

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

GameOver::GameOver() {

  setType("GameOver");

  // Put in center of screen.
  int world_horiz = (int) DM.getHorizontal();
  int world_vert = (int) DM.getVertical();
  df::Vector p((float)(world_horiz/2.0f), (float) (world_vert/2.0f));
  setPosition(p);

  // Exit after about 3 seconds.  
  time_to_live = 100;

  // Make like a View Object
  setSolidness(df::SPECTRAL);
  setAltitude(df::MAX_ALTITUDE);

  // Register for step event.
  registerInterest(df::STEP_EVENT);
}

// When done, game over.
GameOver::~GameOver() {

  // Remove Saucers.
  df::ObjectList object_list = WM.getAllObjects(true);
  df::ObjectListIterator i(&object_list);
  for (i.first(); !i.isDone(); i.next()) {
    df::Object *p_o = i.currentObject();
    if (p_o -> getType() == "Saucer")
      WM.markForDelete(p_o);
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
    WM.markForDelete(this);
    GM.setGameOver();
  }
}

int GameOver::draw() {
  DM.drawString(getPosition(), "Game Over!", df::CENTER_JUSTIFIED, df::WHITE);
}
