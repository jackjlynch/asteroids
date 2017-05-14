# Asteroids

Compiling and running
----------
` g++ Object.cpp Bullet.cpp Ship.cpp EventReceiver.cpp Asteroid.cpp Game.cpp asteroids.cpp -lIrrlicht -std=c++11 && ./a.out`

Controls
--------------
A and D to turn, W to thrust, space to shoot, and H for hyperspace (teleport to a random location). After dying, press any of those controls to restart the game.

Scoring and Mechanics
--------------------
The current score is displayed in the top left corner of the screen. Points are awarded proportionately to asteroid size every time one is destroyed.

Todo
----------------
* Wrap objects near screen edge
* Add UFO enemies
* more options
