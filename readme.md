Breakout by Hamza Usmani
------
### About the Game

Breakout is a game where you have a paddle, a ball, and levels with breaks that you have to break by hitting with the ball! In this implementation of Breakout in C++, there are 2 game types:
1. Basic Mode
The first level starts with 5 rows and 10 columns of randomly generated blocks. Each block is worth 1 point.
After every 5 points, the speed of the ball increaes by 1. Each level after is randomly generated with 
a similar difficulty to the first.

2. Advanced Mode
The first level is an advanced pattern which is much more difficult to complete. This mode includes
stronger bricks which may take more than 1 hit to break. The speed of the ball also increases by 
1 after every 5 points in this mode. For more experienced players.

### Command Line Options

There are 2 optional command line parameters when running the game. The first is FPS (frames per second). The second is the initial speed of the ball.
The game can be run with no arguments, 1 argument (FPS), or both arguments (FPS followed by Speed). The default FPS is 60, and default speed is 2.

```make
./Breakout
```

```make
./Breakout 60
```
```make
./Breakout 60 4
```

### Starting the Game

After running the program, press the 's' key to start, choose your game type using left and right arrows, then press 's' to select again.
Upon losing, you can press 'r' to return to the main menue. You can press the 'q' key at any time to quit.

### Technical Information

The game uses C++ and Xlib for graphics, as well as techniques such as an event loop, double buffering, and is single threaded. Run `make` to compile, or `make run` to compile and run using default FPS/speed.