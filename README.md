<h1 align="center">Terminal Snake</h1>
<img src="https://cloud-pjvzscu3s-hack-club-bot.vercel.app/0screenshot_2024-08-22_at_6.06.21_pm.png" width="auto" height="auto" alt="Debug menu">

<div align="center">
A ncurses snake game

This is my first time using ncurses (finally allocated a bit of time for it), so please don't be too harsh please.
</div>

# Building
Dependencies: ncurses, git and cmake

*nix systems:
```
$ `Package manager` install git cmake ncurses
$ git clone --depth 1 https://github.com/cheyao/snake.git
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
$ ./Snake
```

Windows:
1. Uninstall Windows
2. Install Linux
3. Follow guide for *nix systems

# Game modes
1: Normal mode, same as any snake game
2: Double fruit, two fruits spawn for every one you eat

