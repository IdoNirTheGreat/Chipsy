# Chipsy - A CHIP-8 Emulator in C

## Introduction:
This project is named Chipsy, and it is an emulator for the legacy programming language [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8). Feel free to explore the code, but I do recommend that you read this `README.md` file prior to diving in, and if you want to try this project on your own, I really recommend that you read the 'Lessons Learned' section in this file.

<br />

## Compilation and Execution:
To compile the code, first make sure that you have the GNU GCC compiler installed (if you don't you can use this [link](https://gcc.gnu.org/install/) or simply google how to install it), then write the following line in the terminal:

`gcc fonts.c chip8.c randgen.c opcode.c main.c -o main -LSDL/lib -lmingw32 -lSDL2main -lSDL2 `

To execute the code, simply replace *GAME_FILE* with the name of the game that you want to try. Note that if you want to play the games in the game folder, don't forget to add the directory name, for example:

`.\main.exe .\Games\PONG`
<br />

<span style="color:yellow"> Side note: You can also write the two lines in one terminal command by adding a ';' after copying the first line (compiling the files) and before copying the second line (executing the '.exe' file).</span>
<br />

## Controls:
These are the controls typically used for CHIP-8 emulators:

![Controls](/Screenshots/Controls.png "The CHIP-8 Emulator Controls")

To quit the program, press `esc`.

Note that you can custom change the controls by choosing different keys in the file and function `main.c` -> `update_input`. The program handles the key events through the SDL library, so it should be pretty straight-forward. For more SDL keystrokes information, click this [link](https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html).
<br />

## Screenshots:
<br />

![MISSILE.png](/Screenshots/MISSILE.png "A Screenshot of Missle.")
<br />

![PONG2.png](/Screenshots/PONG2.png "A Screenshot of Pong2.")
<br />

![UFO.png](/Screenshots/UFO.png "A Screenshot of UFO.")
<br />

## Lessons Learned:
* I dove in to the online tutorials, but it was probably better if I had tried to execute the CHIP-8 assembly code first by hand, just a simple file like the IBM logo file. This was the first time I had worked with machine code, so if you want to do a similar project to get familiar with a relatively simple assembly language like I did, you should probably start with understanding the Fetch-Decode-Execute cycle, then learn what the instructions do, and try to execute it by hand. I used [this](https://www.piskelapp.com/p/create/sprite) website to simulate the monitor and painting with sprites like the DXYN instruction does.

* A pretty basic lesson, but don't write a ton of code and only then test it. I should have begun with creating the processor cycles function, then written a single opcode and tested it.

* Not much of a lesson, but this is a really good project to try when learning a new programming language.

* Size does't matter :smirk: ! You could make this project a whole lot less lines of code and make it only one `.c` file, but you really shouldn't. I haven't ever used header files when programming in C, but it *is* the correct way to do things, so I did. Divide your project to different files, use `switch` statements instead of a bunch of `if`s, comment your code etc.
