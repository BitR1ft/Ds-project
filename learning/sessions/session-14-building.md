# Session 14: Building and Running the Project

**Duration:** 30-45 minutes  
**Goal:** Master compilation and execution

## Build Process
```bash
# Using Make
make

# Manual compilation
g++ -std=c++17 -I./include src/*.cpp -o threat_detection_suite
```

## Running Options
1. **C++ Core:** `./threat_detection_suite`
2. **GUI:** `python3 gui_antivirus.py`
3. **CLI:** `python3 antivirus_cli.py`
4. **Launcher:** `./run_antivirus.sh`

## Troubleshooting
- Compiler version: g++ 7.0+
- Python version: 3.6+
- Dependencies: tkinter for GUI

## Makefile Explained
- Targets: all, clean, install
- Dependencies: automatic
- Incremental builds

Everything you need to get running!

See you in Session 15!
