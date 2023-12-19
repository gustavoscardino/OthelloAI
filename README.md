# Othello/Reversi

Othello/Reversi is a strategy board game for two players, played on an 8×8 board, the game begins with four disks placed in a square in the middle of the grid, two facing white-side-up, two dark-side-up, so that the same-coloured disks are on a diagonal.

<div align="center">
  <img src="https://user-images.githubusercontent.com/83798084/158694935-54883de6-0fc6-428c-906b-7bc67dfd4a14.png" width="300">
</div>
<br>

The dark player moves first, followed by the white player, alternating between themselves, until there is no legal move available, or until the board is completely filled. The player with the most disks in the end wins the game.

## What's a legal move?

To be considered legal, a move must respect the following rules:

1. The disk must be placed onto a spot that was previously empty
2. When placing the disk, it must surround one or more of the opponet's disks, in line horizontally, vertically or diagonally. (To surround means to have in between two disks of the same colour one or more consecutve disks of the other colour)

The result of a legal move is to change the colour of the other player's disks to the colour of your own (see example below). If an illegal move is performed the player will be punished with the defeat.

Example:

<img src="https://user-images.githubusercontent.com/83798084/158694935-54883de6-0fc6-428c-906b-7bc67dfd4a14.png" height="250"> <img src="https://user-images.githubusercontent.com/83798084/158712130-2d27a411-35d4-496e-86b5-2432d05a593a.png" height="250"> <img src="https://user-images.githubusercontent.com/83798084/158712240-ec66a296-4047-4256-98a2-4ee74e49c738.png" height="250">

## The Project

This project was created as an university assignment, and is hereby published under the GPL 3.0 license so that its code is freely available for everyone. The game is 100% CLI-based and can be executed by compiling the code contained in any of the .c files of this repository. Each file represents a diferent AI, with diferent approaches to the game (read code comments for further information).
