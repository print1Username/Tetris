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
| `include/Window.h`, `src/Window.cpp` | Owns the 800×600 window, title, frame limit, events, game input, timing, and main loop. Provides `SetIcon` for an image supplied later. | 管理 800×600 窗口、标题、帧率限制、事件、游戏按键、计时及主循环，并提供 `SetIcon` 接口供之后传入图片。 |
| `src/main.cpp` | Creates `Piece`, `Board`, `Game`, `Renderer`, and `Window`, then runs the window. | 创建 `Piece`、`Board`、`Game`、`Renderer` 和 `Window`，然后运行窗口。 |
| `Tetris.sln`, `Tetris.vcxproj`, `Tetris.vcxproj.filters` | Visual Studio project and source file registration. | Visual Studio 工程及源文件登记。 |
| `external/` | Bundled SFML distributions. | 随仓库提供的 SFML 文件。 |
| `tetris_tutorial_sdl/` | SDL reference code; its rendering is not used by the SFML project. | SDL 参考代码；SFML 项目不使用其中的绘图实现。 |

## Current status / 当前进度

- EN: `Window` runs the main loop and handles input. Left/Right move, Down moves one row, Z rotates, X hard drops, and Escape closes the window. The title changes from `Tetris` to `Tetris - Game Over` when the game ends. `SetIcon` is ready for an image supplied later; no icon asset is included yet.
- 中文：`Window` 运行主循环并处理输入。左右键移动、下键下降一格、Z 旋转、X 硬降、Esc 关闭窗口。游戏结束时标题从 `Tetris` 变为 `Tetris - Game Over`。`SetIcon` 已准备好接收之后提供的图片，目前尚无图标资源。
