//
// GameOver.h
//

#include "Object.h"

class GameOver : public Object {

 private:
  int time_to_live;
  void step();

 public:
  GameOver();
  ~GameOver();
  int eventHandler(Event *p_e);
  void draw();
};
