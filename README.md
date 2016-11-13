# BrickGame9999

A simulator of an old cheap toy game handheld.

## Controls

### System controls

Change background: F8, F9

Change scale: +, -

Reset: F1

Start/Pause: Enter (Return)

### Rain (R)

Control rain direction: left, right

Control rain density: up, down

### Snake (A, B):
* A - level based, collect 20 mice to advance
* B - infinite, you are your only enemy

Arrows - move

Space - speed up

### Arkanoid (C):
Arrows - move paddle

Space - speed up

## System configuration

You can configure framerate limiting in saveData.ini with the window.frameControl value.

0 - no frame limiting, 1 - 250 FPS frame limit, 2 - vsynced.

## Deployment

Run package.bat after building a Deploy version to pack up a release.
Default save data file for packaging is located in project root.

## Development setup

### Set up include files

* In your `{VisualStudio}\VC\include\` folder create a folder named SDL2
* Add contents of `include/` folders from: SDL devel VC 2.0.X, SDL_Image devel VC 2.0.1, SDL_Mixer devel VC 2.0.1

This project requires foreach and property_tree libraries from Boost. These are header-only so no Boost package building is required.

* In your `{VisualStudio}\VC\include\` folder create a folder named boost_1_62_0
* Copy the `boost\` folder from your Boost archive to the new folder

### Set up libraries

* In your `{VisualStudio}\VC\lib` folder create a folder named SDL2
* Add .lib files of `lib\x86` from: SDL devel VC 2.0.X, SDL_Image devel VC 2.0.1, SDL_Mixer devel VC 2.0.1

### Set up dynamic libraries

You have to add the following files to your `{ProjectDir}\BrickGame9999` folder:

* `SDL2.dll` from `SDL devel VC 2.0.X\lib\x86`
* `SDL2_image.dll` from `SDL_Image devel VC 2.0.1\lib\x86`
* `libpng16-16.dll` from `SDL_Image devel VC 2.0.1\lib\x86`
* `zlib.dll` from `SDL_Image devel VC 2.0.1\lib\x86`
* `SDL2_Mixer.dll` from `SDL_Mixer devel VC 2.0.1\lib\x86`

### Save data

Backup test data is located in `BrickGame9999\saveData2.ini`, use `saveDataRestore.bat` to replace the current saveData.ini with saveData2.ini. Useful when working on data save logic.