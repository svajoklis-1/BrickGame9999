# BrickGame9999

A simulator of an old cheap toy game handheld.

## Controls

### System controls

Change background: F8, F9
Change scale: +, -

Reset: F1
Start/Pause: Enter (Return)

## Rain (R)

Control rain direction: left, right
Control rain density: up, down

## Snake (A, B):
* A - level based, collect 20 mice to advance
* B - infinite, you are your only enemy
Arrows - move
Space - speed up

## Arkanoid (C):
Arrows - move paddle
Space - speed up

## System configuration

You can configure framerate limiting in saveData.ini with the window.frameControl value.
0 - no frame limiting, 1 - 250 FPS frame limit, 2 - vsynced.

## Deployment

Run package.bat after building a Deploy version to pack up a release.
Default save data is located in saveData2.ini. Use saveDataRestore.bat or just delete saveData.ini to bring back default values.