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
#PLATFORM= -DCYGWIN	# uncomment for cygwin
#PLATFORM= -DMACOS  	# uncomment for macos
LDFLAGS= -lncurses -lrt	# uncomment linux/cygwin
#LDFLAGS= -lncurses 	# uncomment for macos
#CFLAGS= -DREGISTER	# uncomment if using full engine
INCPATH= ../../dragonfly	# path to engine includes
ENG= ../../dragonfly/libdragonfly.a	# dragonfly engine
GAMESRC= Bullet.cpp \
         EventNuke.cpp \
         Explosion.cpp \
         GameOver.cpp \
         Hero.cpp \
         Saucer.cpp \
         Star.cpp
GAME= game.cpp
EXECUTABLE= game		
OBJECTS= $(GAMESRC:.cpp=.o)
#DEBUG= -g

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENG) $(OBJECTS) $(GAME) $(GAMESRC) Makefile
	$(CC) $(CFLAGS) $(GAME) $(OBJECTS) $(DEBUG) $(ENG) $(PLATFORM) -o $@ -I$(INCPATH) $(LDFLAGS) 

.cpp.o: 
	$(CC) -c $(CFLAGS) $(DEBUG) -I$(INCPATH) $(PLATFORM) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE

