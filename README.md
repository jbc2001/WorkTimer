# WorkTimer
A lightweight desktop application built in Qt. This was created as a tool to fill a personal usecase and as a simple excercise to learn about Qt development.

## Overview
This software tracks time spent working per day and saves it to a persistent local log file.
This log file include a human readable portion for the user to keep track of their hours worked on previous days

## Build Requirements
- Qt 6.x
- C++17 compatible compiler
- Qt Creator (recommended)

## Build Instructions
### Windows
1. Open the project in Qt Creator
2. Select a Release build
3. Build the project
4. use Qt commandline tool and navigate to current build directory
5. run this command```windeployqt WorkTimer.exe```

###Mac
1. Open the project in Qt Creator
2. Select a Release build
3. Build the project
4. open terminal and naviagate to the current build directory
5. run this command ```macdeployqt WorkTimer.app```

## Limitations
- No project/task separation
- Timer accuracy depends on system scheduling

## Possible Future Improvements
- support for multiple timers or projects
- CSV / JSON export
- System-time–based elapsed tracking
- User configurable storage location
  
This is released freely under the MIT License. Feel free to use any of the code for learning or in your own projects
