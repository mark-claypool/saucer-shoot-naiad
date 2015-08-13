//
// Star.cpp
//

#include <stdlib.h>		// for random

// Engine includes.
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"

// Game includes.
#include "Star.h"

Star::Star() {
  setType("Star");
  setSolidness(df::SPECTRAL);
  setXVelocity(-1.0 / (random()%10 + 1));
  setAltitude(0);	// Make them in the background.
  df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
  df::Position pos(random()%graphics_manager.getHorizontal(),
	       random()%graphics_manager.getVertical());
  setPosition(pos);
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
  df::Position pos(graphics_manager.getHorizontal() + random()%20,
	       random() % graphics_manager.getVertical());
  setPosition(pos);
  setXVelocity(-1.0 / (random()%10 + 1));
}
