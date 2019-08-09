CC=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic

skipbo: SkipBoGame.o Player.o Hand.o DrawPile.o FaceUpPile.o Pile.o Card.o BuildPile.o
	$(CC) SkipBoGame.o Player.o Hand.o DrawPile.o FaceUpPile.o Pile.o Card.o BuildPile.o -o skipbo

SkipBoGame.o: SkipBoGame.cpp SkipBoGame.h Player.h BuildPile.h DrawPile.h
	$(CC) $(CFLAGS) -c SkipBoGame.cpp Player.cpp BuildPile.cpp DrawPile.cpp

Player.o: Player.cpp Player.h Hand.h PlayPile.h
	$(CC) $(CFLAGS) -c Player.cpp Hand.cpp PlayPile.cpp

Hand.o: Hand.cpp Hand.h Card.h Pile.h DrawPile.h
	$(CC) $(CFLAGS) -c Hand.cpp Card.cpp Pile.cpp DrawPile.cpp

DrawPile.o: DrawPile.cpp DrawPile.h Pile.h
	$(CC) $(CFLAGS) -c DrawPile.cpp Pile.cpp

BuildPile.o: BuildPile.cpp BuildPile.h FaceUpPile.h
	$(CC) $(CFLAGS) -c BuildPile.cpp FaceUpPile.cpp

PlayPile.o: PlayPile.cpp PlayPile.h FaceUpPile.h
	$(CC) $(CFLAGS) -c PlayPile.cpp FaceUpPile.cpp

FaceUpPile.o: FaceUpPile.cpp FaceUpPile.h Pile.h
	$(CC) $(CFLAGS) -c FaceUpPile.cpp Pile.cpp

Pile.o: Pile.cpp Pile.h Card.h
	$(CC) $(CFLAGS) -c Pile.cpp Card.cpp

Card.o: Card.cpp Card.h
	$(CC) $(CFLAGS) -c Card.cpp

clean:
	rm -f *.o skipbo
