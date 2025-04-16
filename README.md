#C++ To-Do GUI App(FLTK)

A lightweight to-do list app built in C++ with a simple GUI using the FLTK toolkit.

##Features

-Add,delete, and mark tasks as done
-Persistent storage using `tasks.txt`
-Click to select tasks via GUI

##Build & Run

```bash
g++ todo_gui.cpp -o todo_gui `fltk-config --cxxflags --ldflags`
./todo_gui
