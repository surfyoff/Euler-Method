# Euler Method Calculator

## Description
Euler Method Calculator for first degree differential equations _(dy/dx) = f(y <sup>n</sup>)_ to use for physics implementations (making a method for every possible implementation is way too hard lol).

## Set-up
If you want to clone this repository to do whatever you like with the code or the executable, you have to take care of a couple of things:
1. Make sure to have **SDL2**, **SDL2_image** and **SDL2_ttf** on your system, so that CMake knows how to handle the source's dependencies. You can put them wherever you want on your system, just make sure to change the contents of `CMakeLists.txt` accordingly (pls know what ur doing with cmake).
2. Once CMake finds the SDL2 libraries and the executable is compiled successfully, copy and paste `SDL2.dll`, `SDL2_image.dll`, `SDL2_ttf.dll` and the `res/` folder in the executable directory.

## Usage
Once the executable is running, you have to know how to use the program:
1. Fill all the input boxes with the appropriate data.
2. Press `b` to begin the calculating process. Note that each time you modify the inputs, you have to press `b` again to re-initiate the calculating process.
3. Press `r` to render the results as a graph, or if you don't want to look at the graph, the calculations will be printed out in the console window.
4. Press `s` to stop rendering the graph.

There are two additional commands, such as:
+ Pressing `p`, which just prints out the input texts as strings to the console window (used to check if the input is received well).
+ Pressing `n`, which prints out the numerical values of the inputs (used to check if the `stoi` and `stod` conversions went well).

Lastly, keep in mind that if your input is a scientific notation, for example ` 3.57 x10^3 ` , just simply write it as `3.57e3`.
