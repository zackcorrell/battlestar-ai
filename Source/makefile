# Battlestar-AI makefile
# http://code.google.com/p/battlestar-ai/

# Include source and header files:
SRC = Board.cpp  DumbPlayer.cpp  Game.cpp  HumanPlayer.cpp  Main.cpp  Player.cpp ShooterPlayer.cpp  Util.cpp
HDR = Board.h    DumbPlayer.h    Game.h    HumanPlayer.h    Main.h    Player.h   ShooterPlayer.h    Util.h   Ships.h

# Build all:
all: $(SRC) $(HDR)
	g++ -Wall -Wextra $(SRC) -o battlestar-ai

# Clean all:
clean:
	rm -f *.o

