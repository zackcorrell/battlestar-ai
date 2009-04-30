# Battlestar-AI makefile
# http://code.google.com/p/battlestar-ai/

# Include source and header files:
SRC = Board1.cpp DumbPlayer.cpp Game.cpp GAPlacement.cpp GAPlayer.cpp GAShoot.cpp GASinking.cpp GASinkingGene.cpp Main.cpp Player.cpp ShooterPlayer.cpp ShootFourier.cpp ShootGene.cpp ShootGenePool.cpp ShootHarmonic.cpp SinkPlayer.cpp SmartRandom.cpp Util.cpp

# Build all:
all: $(SRC)
	g++ -m32 -Wall -Wextra -lm $(SRC) -o battlestar-ai

# Clean all:
clean:
	rm -f *.o