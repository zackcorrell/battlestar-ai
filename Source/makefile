# Battlestar-AI makefile
# http://code.google.com/p/battlestar-ai/

# Include source and header files:
SRC = Board1.cpp DumbPlayer.cpp Game.cpp GAPlacement.cpp GAPlayer.cpp GAShoot.cpp GASinking.cpp GASinkingGene.cpp Main.cpp Player.cpp ShooterPlayer.cpp ShootFourier.cpp ShootGene.cpp ShootGenePool.cpp ShootHarmonic.cpp SinkPlayer.cpp SmartRandom.cpp Util.cpp

COMP = Board1.cpp DumbPlayer.cpp Game.cpp GAPlacement.cpp GAPlayer.cpp GAShoot.cpp GASinking.cpp GASinkingGene.cpp Player.cpp ShooterPlayer.cpp ShootFourier.cpp ShootGene.cpp ShootGenePool.cpp ShootHarmonic.cpp SinkPlayer.cpp SmartRandom.cpp Util.cpp jgb5034.h Board.h Status.h Board1.h DumbPlayer.h Game.h GAPlacement.h GAPlayer.h GAShoot.h GASinking.h GASinkingGene.h Player.h ShooterPlayer.h ShootFourier.h ShootGene.h ShootGenePool.h ShootHarmonic.h SinkPlayer.h SmartRandom.h Util.h

# Build all:
all: $(SRC)
	g++ -m32 -Wall -Wextra $(SRC) -o battlestar-ai

competitor:
	g++ -E -m32 -Wall -Wextra $(COMP) -o competitor

# Clean all:
clean:
	rm -f *.o competitor
