# Tetris project / Tetris 项目

## Overview / 简介

- EN: A C++ Tetris project using SFML 3 for graphics. The game logic is based on the bundled SDL tutorial, with separate classes for shapes, board rules, game state, and rendering.
- 中文：这是一个使用 SFML 3 绘图的 C++ 俄罗斯方块项目。游戏逻辑参考仓库内的 SDL 教程，并将形状、棋盘规则、游戏状态和绘图分开实现。

## Structure / 结构

| Path / 路径 | English | 中文 |
| --- | --- | --- |
| `include/Piece.h`, `src/Piece.cpp` | Seven tetromino shapes, four rotations, pivot cells, and spawn offsets. | 七种方块、四种旋转状态、旋转中心格及生成位置偏移。 |
| `include/Board.h`, `src/Board.cpp` | 10×20 settled grid, collision checks, locking, line removal, and game-over detection. | 10×20 已落地方块网格、碰撞检查、固定方块、消行及结束判断。 |
| `include/Game.h`, `src/Game.cpp` | Current/next pieces, movement, rotation, drop timing, and game state. | 当前及下一个方块、移动、旋转、下落计时与游戏状态。 |
| `include/Renderer.h`, `src/Renderer.cpp` | SFML drawing for the board, active piece, and next-piece preview at 800×600. | 使用 SFML 在 800×600 画面绘制棋盘、当前方块和下一个方块预览。 |
| `src/main.cpp` | Creates the 800×600 window, handles input and timing, and draws the game through `Renderer`. | 创建 800×600 窗口，处理按键和计时，并通过 `Renderer` 绘制游戏。 |
| `Tetris.sln`, `Tetris.vcxproj`, `Tetris.vcxproj.filters` | Visual Studio project and source file registration. | Visual Studio 工程及源文件登记。 |
| `external/` | Bundled SFML distributions. | 随仓库提供的 SFML 文件。 |
| `tetris_tutorial_sdl/` | SDL reference code; its rendering is not used by the SFML project. | SDL 参考代码；SFML 项目不使用其中的绘图实现。 |

## Current status / 当前进度

- EN: The main loop connects `Piece`, `Board`, `Game`, and `Renderer`. Left/Right move, Down moves one row, Z rotates, X hard drops, and Escape closes the window. The window title changes when the game ends.
- 中文：主循环已连接 `Piece`、`Board`、`Game` 与 `Renderer`。左右键移动、下键下降一格、Z 旋转、X 硬降、Esc 关闭窗口；游戏结束时窗口标题会改变。
