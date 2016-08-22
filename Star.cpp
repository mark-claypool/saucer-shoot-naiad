//
// Star.cpp
//

#include <stdlib.h>		// for rand()

// Engine includes.
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"

// Game includes.
#include "Star.h"

Star::Star() {
  setType("Star");
  setSolidness(df::SPECTRAL);
  setVelocity(df::Vector((float) -1.0 /(rand()%9 + 2), 0));
  setAltitude(0);	// Make them in the background.
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::Vector p(rand()%(int)graphics_manager.getHorizontal(),
	       rand()%(int)graphics_manager.getVertical());
  setPosition(p);
}

void Star::draw() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), STAR_CHAR, df::WHITE); 
}

// Handle event.
// Return 0 if ignored, else 1.
int Star::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::OUT_EVENT) {
    out();
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// If Star moved off screen, move back to far right.
void Star::out() {
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::Vector pos((float) (graphics_manager.getHorizontal() + rand()%20),
		 (float) (rand() % graphics_manager.getVertical()));
  setPosition(pos);
  setVelocity(df::Vector((float) -1.0 /(rand()%9 + 2), 0));
}
