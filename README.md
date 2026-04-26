# Project README

## Overview
- The project is a simple GUI application written in C using a hypothetical Windowing API (`WindowingAPI`) that supports cross-platform development (Linux, Windows, WebAssembly, Wine). It demonstrates basic GUI functionality such as creating a window, handling events, and rendering shapes.

## Features
- **GUI Creation**: Creates a window with a specified title and dimensions.
- **Event Handling**: Handles window close events.
- **Rendering**: Renders circles of different colors based on the data stored in an internal data structure.
- **Cross-platform Build**: Supports building for Linux, Windows, WebAssembly (via Emscripten), and Wine.

## Project Structure
```
KNN/
├── build/              
├── src/                
│   ├── Main.c          
│   └── WindowingAPI.h  
├── Makefile.linux      
├── Makefile.windows    
├── Makefile.wine       
└── README.md           
└── LICENCE             
└── .gitignore
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - Linux: X11 for GUI, libpng/libjpeg for image handling.
  - Windows: user32.dll, gdi32.dll, winmm.dll.
  - WebAssembly: Emscripten SDK.
  - Wine: mingw-w64 compiler.

## Build & Run
### Linux
- To build the project:
  ```bash
  make -f Makefile.linux all
  ```
- To run the application:
  ```bash
  make -f Makefile.linux exe
  ```

### Windows
- To build the project:
  ```bash
  make -f Makefile.windows all
  ```
- To run the application:
  ```bash
  make -f Makefile.windows exe
  ```

### WebAssembly (Emscripten)
- To build the project:
  ```bash
  make -f Makefile.web all
  ```
- To serve and run the application locally:
  ```bash
  make -f Makefile.web exe
  ```

### Wine
- To build the project:
  ```bash
  make -f Makefile.wine all
  ```
- To debug the application using WINE:
  ```bash
  make -f Makefile.wine debug
  ```
- To run the application using WINE:
  ```bash
  make -f Makefile.wine exe
  ```

---

**Note**: The actual implementation of the WindowingAPI and other dependencies are assumed to be correctly set up in the project environment.