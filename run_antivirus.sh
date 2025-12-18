#!/bin/bash
# Launcher script for the Integrated Cyber Threat Detection Suite
# Automatically detects GUI availability and runs appropriate interface

echo "========================================================================"
echo "  INTEGRATED CYBER THREAT DETECTION SUITE"
echo "  CS-214 Data Structures Project"
echo "========================================================================"
echo

# Check if display is available for GUI
if [ -n "$DISPLAY" ]; then
    echo "Display detected: Launching GUI application..."
    python3 gui_antivirus.py
else
    echo "No display detected: Launching CLI application..."
    echo
    python3 antivirus_cli.py "$@"
fi
