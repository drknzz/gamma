# Gamma
Assignment for IPP course - game in terminal

![Screenshot from 2021-04-16 16-00-22](https://user-images.githubusercontent.com/65187002/115035633-0f78ee80-9ecd-11eb-930d-f8552d3f42c0.png)
---

Gamma is a multi-player game which is played on a rectangular board consisting of identical squares.

Adjacent fields on the boards are those that touch each other on their sides. Fields that touch themselves with corners are not adjacent. Adjacent fields form an area if each field can be reached from one another by only passing through the adjacent spaces. A single field is also an area.

At the beginning of the game, the board is empty. Players take turns to occupy one field, placing their pawn on it.

A player may occupy any unoccupied field, respecting the rule that a set of fields occupied by the same player may not, in any phase of the game, consist of more than the maximum number of areas, which is a parameter of the game.

Each player can make one golden move per game, which consists of taking another player's pawn from the board and placing his pawn in its place, but this move must not violate the rule of the maximum number of occupied areas by any player.

A player who is unable to make a move according to the above rule is out of the game, but may return to play after some golden move of another player.

The game ends when neither player can move anymore. The player with the greatest number of spaces wins.

---
<h2>Play</h2>

./gamma

I \<width\> \<height\> \<players\> \<areas\>

---
<h2>Build</h2>

mkdir release
cd release
cmake ..
make

---
<h2>Documentation</h2>
  
make doc
