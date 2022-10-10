# Chipsy - A CHIP-8 Emulator in C

## Introduction:
This project is called Chipsy, and it is an emulator for the legacy programming language [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8). Feel free to explore the code, but I do recommend that you read this file (`README.md`) before diving in, and if you want to try this project on your own, I really recommend that you read the 'Lessons Learned' section in this file.

<br />

## Build and Execution:
To compile the code, first make sure that you have the GNU GCC compiler installed (if it's not installed you can use this [link](https://gcc.gnu.org/install/) or simply google how to install it), then write the following line in the terminal:

`gcc fonts.c chip8.c randgen.c opcode.c main.c -o main -LSDL/lib -lmingw32 -lSDL2main -lSDL2`

To execute the code, simply replace *GAME_FILE* with the name of the game that you want to try:

`.\main.exe GAME_FILE`

Don't forget to add the directory name if you want to play the games in a folder. You can also write the two lines in one terminal command by adding a semicolon after copying the first line (compiling the files) and before copying the second line (executing the '.exe' file). For example:

`gcc fonts.c chip8.c randgen.c opcode.c main.c -o main -LSDL/lib -lmingw32 -lSDL2main -lSDL2; .\main.exe .\Games\PONG`

If you do not specify a file to run, then the program will run a default file, defined in `main.c`.

<br />

## Controls:
These are the controls typically used for CHIP-8 emulators:

![Controls](/Screenshots/Controls.png "The CHIP-8 Emulator Controls")

To quit the program, press `esc`.

Note that you can custom change the controls by choosing different keys in the file and function `main.c` -> `update_input`. The program handles the key events through the SDL library, so it should be pretty straight-forward. For more SDL keystroke event information, click this [link](https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html).

<br />

## Files and Directories:

`.\main.c`: Contains the main function, and the overall program management.

`.\chip8.c`: Contains the CHIP-8 struct functions such as initialization and cycle handling.

`.\chip8.h`: Contains the definition of the CHIP-8 struct, declaration and documentation for all `chip8.c` functions.

`.\opcode.c`: Contains the implementation of the decode and execute stages of the MIPS cycle.

`.\opcode.h`: Contains declaration and documentation for all `opcode.c` functions.

`.\randGen.*`: Generates random integers for use in the CHIP-8 system.

`.\fonts.*`: Contains the data for the CHIP-8 fonts.

`.\Games\*`: Contains ROMs for games and tests. Also contains the intro an credits ROMs.

`.\SDL\*`, `.\SDL2.dll`: Contains the SDL2 library files nessecary to run graphics of CHIP-8.

<br />

## Screenshots:
<br />

![MISSILE.png](/Screenshots/MISSILE.png "A Screenshot of the game 'Missile'.")
<br />

![PONG2.png](/Screenshots/PONG2.png "A Screenshot of the game 'Pong2'.")
<br />

![UFO.png](/Screenshots/UFO.png "A Screenshot of the game 'UFO'.")
<br />

## Lessons Learned:
* I had tried to execute the CHIP-8 assembly code first by hand, just a simple file like the IBM logo file. This was the first time I had worked with machine code, so if you want to do a similar project to get familiar with a relatively simple assembly language like I did, you should probably start with understanding Fetch-Decode-Execute cycle of running CPU instructions, then learn what the instructions do, and try to execute it by hand. I used [this](https://www.piskelapp.com/p/create/sprite) website to simulate the monitor and paint with sprites like the DXYN instruction does.

* A pretty basic lesson, but don't write a ton of code and only then test it. I should have begun with creating the processor cycles function, then written a single opcode and tested it.

* Not much of a lesson, but this is a really good project to try when learning a new programming language, so you should think about leaving your comfort zone (that is why I chose to implement the project in C).

* Size doesn't matter :smirk:! You could make this project a whole lot less lines of code and make it only one `.c` file, but you really shouldn't. I haven't ever used header files when programming in C, but it *is* the correct way to do things, so I did. Divide your project to different files, use `switch` statements instead of a bunch of `if`s, comment your code etc.
