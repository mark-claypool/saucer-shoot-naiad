//
// game.cpp
// 

#define VERSION 1.0

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
  df::LogManager &log_manager = df::LogManager::getInstance();

  // Start up game manager.
  df::GameManager &game_manager = df::GameManager::getInstance();
  if (game_manager.startUp())  {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 0;
  }

  // Write game version information to logfile.
  log_manager.writeLog("Saucer Shoot Naiad, version %0.1f", VERSION);

  // Set flush of logfile during development (when done, make false).
  log_manager.setFlush(true);

  // Setup some objects.
  populateWorld();
 
  // Run game (this blocks until game loop is over).
  game_manager.run();
 
  // Shut everything down.
  game_manager.shutDown();
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
