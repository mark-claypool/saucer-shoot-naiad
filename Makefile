#
# Makefile for saucer shoot game using Dragonfly
#
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
# 'make' to build executable
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#   DEBUG can be set to compile in various debug flags
#

CC= g++ 

### Uncomment only 1 of the below! ###

# 1) Uncomment below for Linux (64-bit)
LINKLIB= -ldragonfly-linux64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt
LINKDIR= -L../dragonfly/lib/ # path to dragonfly library
INCDIR= -I../dragonfly/include/ # path to dragonfly includes

LINKLIB= -ldragonfly -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt
LINKDIR= -L../../dragonfly # path to dragonfly library
INCDIR= -I../../dragonfly # path to dragonfly includes

# Uncomment and update below if using local SFML installation.
LINKDIR:= $(LINKDIR) -L/home/claypool/src/SFML-2.5.0/lib 
INCDIR:= $(INCDIR) -I/home/claypool/src/SFML-2.5.0/include

# 2) Uncomment below for Mac (64-bit)
#LINKLIB= -ldragonfly-mac64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
#LINKDIR= -L/usr/local/Cellar/sfml/2.4.0/lib/ -L../dragonfly/lib/ 
#INCDIR= -I/usr/local/Cellar/sfml/2.4.0/include/ -I../dragonfly/include/

######

GAMESRC= Bullet.cpp \
         EventNuke.cpp \
         Explosion.cpp \
         GameOver.cpp \
         Hero.cpp \
         Reticle.cpp \
         Saucer.cpp \
         Star.cpp \

GAME= game.cpp
EXECUTABLE= game		
OBJECTS= $(GAMESRC:.cpp=.o)

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENGINE) $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) -c $(INCDIR) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE

