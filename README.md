# Magic Jars
## Goal

The player begins with 3 lives.
5 jars are in front of him.
A jar contains either a magic key or a snake.
If the player chooses a jar containing a magic key, he goes to the next round.
Otherwise, he loses a life.

## Parts and Rounds
The game is divided into 4 parts which have 3 rounds.
In the first round there is a snake among the 5 jars.
In the next round, snakes' and keys' disposition changes, except if the player chose a jar containing a snake.
In the next part there is one more snake in one of the 5 jars.
The player wins if he passes all the rounds.

## Why I made this game
This project has been inspired by [Graven's](https://www.youtube.com/channel/UCIHVyohXw6j2T-83-uLngEg) exercise. 
Originally, It was a console game, but then I used pygame to make it graphical. 
However, the code was messy and I had learnt raylib in the meantime. So I remade this game using  [raylib](https://github.com/raysan5/raylib) and [raylib-cpp](https://github.com/RobLoach/raylib-cpp). \
Since raylib uses by default static linking, you don't need to install anyhing to launch the game, whether you are on Windows or Linux.

## Credits
All the images come from [flaticon](https://www.flaticon.com) (more details in the file `credits.txt`) and 
all the sound effects have been made thanks to [bfxr](https://www.bfxr.net/).
