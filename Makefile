# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.\lib\SFML\include\
LDFLAGS = -L.\lib\SFML\lib\
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SFMLPATH = .\lib\SFML\
SRC = src
OBJ = $(SRC)/main.o $(SRC)/Game.o $(SRC)/Player.o $(SRC)/Alien.o $(SRC)/Bullet.o

# Base rule
all: SpaceInvaders

# Rules
SpaceInvaders: $(OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(SFMLFLAGS)

$(SRC)/%.o: $(SRC)/%.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
    rm -f $(OBJ) SpaceInvaders