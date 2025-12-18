# Session 13: CLI Application Walkthrough

**Duration:** 45-60 minutes  
**Goal:** Understand command-line interface

## Features
- Interactive menu system
- Direct command execution
- Scriptable for automation
- Server-friendly (no GUI needed)

## Commands
```bash
# Interactive mode
python3 antivirus_cli.py

# Direct commands
python3 antivirus_cli.py scan --path /dir
python3 antivirus_cli.py monitor --duration 120
python3 antivirus_cli.py status
```

## Automation
```bash
# Cron job for daily scans
0 2 * * * cd /path && python3 antivirus_cli.py scan --path /home
```

Perfect for servers and automation!

See you in Session 14!
