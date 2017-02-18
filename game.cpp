//
// game.cpp
// 

#define VERSION 1.1

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
 
// Game includes.
#include "Hero.h"
#include "Star.h"
#include "Saucer.h"

// Function prototypes.
void populateWorld(void);
 
int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Write game version information to logfile.
  LM.writeLog("Saucer Shoot Naiad, version %0.1f", VERSION);

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Setup some objects.
  populateWorld();
 
  // Run game (this blocks until game loop is over).
  GM.run();
 
  // Shut everything down.
  GM.shutDown();
}
 
// Populate world with some objects.
void populateWorld(void) {

  // Spawn some Stars.
  for (int i=0; i<16; i++) 
    new Star;
 
  // Create hero.
  new Hero;

  // Spawn some saucers to shoot.
  for (int i=0; i<16; i++)
    new Saucer;
}
