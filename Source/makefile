# Battlestar-AI makefile
# http://code.google.com/p/battlestar-ai/

# Include source and header files:
SRC = Board.cpp  DumbPlayer.cpp  Game.cpp  GAPlayer.h  HumanPlayer.cpp  Main.cpp  Player.cpp ShooterPlayer.cpp  SinkPlayer.cpp  SmartRandom.cpp  Util.cpp
HDR = Board.h    DumbPlayer.h    Game.h    GAPlayer.h  HumanPlayer.h    Main.h    Player.h   ShooterPlayer.h    SinkPlayer.h    SmartRandom.h    Util.h   Ships.h

# Build all:
all: $(SRC) $(HDR)
	g++ -Wall -Wextra $(SRC) -o battlestar-ai

# Clean all:
clean:
	rm -f *.o