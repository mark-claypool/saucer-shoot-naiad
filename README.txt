SAUCER SHOOT, Naiad Version
v1.2

This is a rendition of the Saucer Shoot tutorial for Dragonfly, but
made to work with the Naiad version of Dragonfly.

Tutorial for full version of game available online:

 http://dragonfly.wpi.edu/tutorial/index.html

And in book:

 Mark Claypool. Dragonfly - Program a Game Engine from Scratch,
 Interactive Media and Game Development, Worcester Polytechnic
 Institute, 2014. Online at: http://dragonfly.wpi.edu/book/

To compile:

1) Create a library of your Dragonfly Naiad engine.  With a Makefile
(Linux or Mac), this can be done by adding the following recipe:

LIBRARY= libdragonfly.a

$(LIBRARY): $(OBJECTS) Makefile
	ar rcs $(LIBRARY) $(OBJECTS)

Note, OBJECTS are all the .o files that make up your engine.

2) Modify INCPATH and ENG in the enclosed Saucer Shoot Naiad Makefile
(Linux or Mac) or adjust your project file accordingly (Windows) to
point to your engine.

If using the full version of Dragonfly (with event filtering),
uncomment the line:

 CFLAGS= -DREGISTER

3) Type "make" (Linux or Mac) or hit F7 (Windows).  This should build
the game.

4) In terminal window (Linux or Mac), type "./game" to run or hit F5
(Windows). This should run the game.

5) Controls: Arrows move, Space fires, Enter nukes, 'q' quits       

For a description of the capabilities of this engine, see:

  http://web.cs.wpi.edu/~claypool/papers/dragonfly-projects/proj2/#2b

For a full version of Saucer Shoot game, see:

  http://dragonfly.wpi.edu/games/saucer-shoot/saucer-shoot.zip

Happy shooting!

-- Mark
