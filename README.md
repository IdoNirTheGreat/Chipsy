# Chipsy - A CHIP-8 Emulator in C

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
