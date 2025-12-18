# GUI Mini Antivirus - User Guide
## Integrated Cyber Threat Detection Suite v2.0

---

## Overview

This is an enhanced version of the Integrated Cyber Threat Detection Suite that adds daily-use features including:
- **GUI Application** - User-friendly graphical interface (when display is available)
- **CLI Application** - Command-line interface for servers and headless systems
- **Custom Folder Scanning** - Select and scan any folder for threats
- **Network Traffic Monitoring** - Constant monitoring of internet traffic
- **Real-time Protection** - Background threat detection
- **Scan History** - Track all previous scans
- **Configuration Management** - Customize settings and preferences

---

## Installation

### Prerequisites
- Python 3.6 or later
- C++ compiler (g++ 7.0 or later)
- Make (optional but recommended)

### Setup
```bash
# Clone or navigate to the repository
cd Ds-project

# Build the C++ detection modules
make

# Make scripts executable
chmod +x run_antivirus.sh antivirus_cli.py gui_antivirus.py
```

---

## Running the Application

### Automatic Launcher
The `run_antivirus.sh` script automatically detects your environment:
```bash
./run_antivirus.sh
```
- If you have a display (GUI environment), it launches the GUI application
- If no display is available (server/SSH), it launches the CLI application

### GUI Mode (Manual)
```bash
python3 gui_antivirus.py
```

### CLI Mode (Manual)
```bash
# Interactive menu
python3 antivirus_cli.py

# Direct commands
python3 antivirus_cli.py scan --path /path/to/folder
python3 antivirus_cli.py monitor --duration 120
python3 antivirus_cli.py full
python3 antivirus_cli.py status
```

---

## Features

### 1. Custom Folder Scanning

#### GUI Mode
1. Click **File → Scan Folder...** or click the **Browse** button
2. Select the folder you want to scan
3. Click **Start Scan**
4. View results in the **Scan Results** tab
5. Check **Threats Detected** tab for any malware found

#### CLI Mode
```bash
# Interactive
python3 antivirus_cli.py
# Select option 1, enter folder path

# Direct command
python3 antivirus_cli.py scan --path /home/user/Documents
```

**What it does:**
- Recursively scans all files in the selected folder
- Checks files against malware signature database
- Detects suspicious file types (.exe, .dll, .bat, .vbs, etc.)
- Identifies known malware patterns
- Generates detailed threat reports

### 2. Network Traffic Monitoring

#### GUI Mode
1. Click **Tools → Network Monitor** or click **Start Monitoring** button
2. Network activity is logged in the **Network Activity** tab
3. Suspicious connections appear in **Threats Detected** tab
4. Click **Stop Monitoring** to stop

#### CLI Mode
```bash
# Interactive
python3 antivirus_cli.py
# Select option 2, enter duration

# Direct command
python3 antivirus_cli.py monitor --duration 60
```

**What it does:**
- Monitors network connections in real-time
- Checks against blacklisted IPs
- Detects port scanning attempts
- Identifies DDoS patterns
- Logs suspicious network activity

### 3. Full Detection Suite

Runs all integrated security modules:
- **Module 1:** Malware Signature Scanner (Trie, Aho-Corasick)
- **Module 2:** Ransomware Behavior Detector (Graph, DFS/BFS)
- **Module 3:** Network IDS (AVL Tree, Priority Queue)
- **Module 4:** Threat Intelligence & Reporting (Hash Tables, Linked Lists)

#### Running Full Suite
```bash
# CLI
python3 antivirus_cli.py full

# Or directly
./threat_detection_suite
```

### 4. Scan History

#### GUI Mode
- Click **File → View Scan History**

#### CLI Mode
```bash
python3 antivirus_cli.py
# Select option 4
```

### 5. Configuration & Settings

#### GUI Mode
- Click **Tools → Settings**
- Configure:
  - Auto-scan on startup
  - Signature file path
  - Blacklist file path

#### CLI Mode
- Edit `config.json` directly:
```json
{
  "last_scan_path": "/path/to/last/scan",
  "scan_history": [],
  "signature_path": "data/malware_signatures.txt",
  "blacklist_path": "data/blacklisted_ips.txt"
}
```

---

## Understanding Results

### Threat Detection
When a threat is detected, you'll see:
```
⚠ THREAT: /path/to/file.txt
  - Malware signature: trojan
  - Suspicious file type: .exe
```

**Threat Types:**
- **Malware signature detected** - File contains known malicious patterns
- **Suspicious file type** - File extension is commonly used by malware
- **Network threat** - Suspicious network activity detected

### Scan Reports

After each scan, a detailed report is saved to `scan_report.txt`:
```
Scan Date: 2025-12-18 16:11:08
Target Folder: /home/user/Documents
Files Scanned: 150
Threats Detected: 2
Scan Duration: 2.34 seconds

THREATS DETECTED:
1. /home/user/Documents/suspicious.exe
   - Malware signature: trojan
   - Suspicious file type: .exe
```

---

## Daily Usage Scenarios

### Scenario 1: Quick Folder Check
```bash
./run_antivirus.sh
# Select folder to scan
# Review results
```

### Scenario 2: Continuous Monitoring
```bash
python3 antivirus_cli.py monitor --duration 3600
# Monitors network for 1 hour
```

### Scenario 3: Scheduled Scanning
Add to cron for automatic daily scans:
```bash
# Edit crontab
crontab -e

# Add daily scan at 2 AM
0 2 * * * cd /path/to/Ds-project && python3 antivirus_cli.py scan --path /home/user
```

### Scenario 4: System Tray Monitoring (GUI)
- Launch GUI application
- Start network monitoring
- Minimize to system tray (if supported)
- Receive alerts when threats are detected

---

## Updating Signatures

### Manual Update
1. Edit `data/malware_signatures.txt`
2. Add one signature per line
3. Save and restart application

### Example signatures:
```
malicious_payload
trojan
virus
ransomware
backdoor
keylogger
spyware
rootkit
```

### Blacklist IPs
1. Edit `data/blacklisted_ips.txt`
2. Add one IP per line
3. Save and restart application

Example:
```
192.168.1.100
10.0.0.50
203.0.113.5
```

---

## Troubleshooting

### GUI doesn't start
**Problem:** No display available
**Solution:** Use CLI mode instead:
```bash
python3 antivirus_cli.py
```

### Scan is slow
**Problem:** Large folders with many files
**Solution:** 
- Scan specific subdirectories
- Exclude large media folders
- Increase scan timeout in code if needed

### No threats detected in test
**Problem:** Test files don't contain signatures
**Solution:** Create test file:
```bash
echo "This file contains trojan and malicious_payload" > test_threat.txt
python3 antivirus_cli.py scan --path .
```

### Network monitoring not working
**Problem:** Requires root/admin privileges for packet capture
**Solution:** Run with sudo (for real packet capture):
```bash
sudo python3 antivirus_cli.py monitor
```

**Note:** Current implementation uses simulation. For real packet capture, install and use `scapy` library.

---

## Advanced Features

### Custom Signature Addition
```python
# In your code or via config
signatures = [
    "custom_malware_pattern",
    "suspicious_code_string",
    "crypto_miner_signature"
]
```

### Integration with C++ Modules
The Python applications can call the C++ detection suite:
```bash
python3 antivirus_cli.py full
```

This runs all advanced data structure-based detection algorithms.

---

## Performance

### Scan Speed
- **Small folders (< 100 files):** < 1 second
- **Medium folders (100-1000 files):** 1-5 seconds  
- **Large folders (> 1000 files):** 5-30 seconds

### Resource Usage
- **Memory:** ~50-100 MB (GUI), ~20-50 MB (CLI)
- **CPU:** Low during monitoring, high during active scanning
- **Disk:** Minimal (reports and logs only)

---

## Security Best Practices

1. **Update Regularly** - Keep signature database current
2. **Scan Frequently** - Run full scans at least weekly
3. **Monitor Network** - Enable continuous monitoring for servers
4. **Review Reports** - Check threat reports carefully
5. **Quarantine Threats** - Move detected files to safe location
6. **Backup Data** - Before removing potential threats

---

## Support & Information

**Project:** CS-214 Data Structures Final Project  
**Program:** BS Cyber Security  
**Course:** Data Structures

**Components:**
- GUI Application: `gui_antivirus.py`
- CLI Application: `antivirus_cli.py`
- C++ Detection Suite: `threat_detection_suite`
- Launcher: `run_antivirus.sh`

**Documentation:**
- Technical Documentation: `docs/TECHNICAL_DOCUMENTATION.md`
- User Manual: `docs/USER_MANUAL.md`
- This Guide: `GUI_USER_GUIDE.md`

---

## Keyboard Shortcuts (GUI)

- **Ctrl+O** - Open folder browser (planned)
- **Ctrl+S** - Start scan (planned)
- **Ctrl+M** - Toggle network monitor (planned)
- **Ctrl+Q** - Quit application
- **F1** - Help/About

---

## Command Line Reference

```bash
# CLI Commands
python3 antivirus_cli.py                    # Interactive menu
python3 antivirus_cli.py scan              # Scan last folder
python3 antivirus_cli.py scan --path DIR   # Scan specific folder
python3 antivirus_cli.py monitor           # Monitor for 60 seconds
python3 antivirus_cli.py monitor --duration SEC  # Monitor for SEC seconds
python3 antivirus_cli.py full              # Run full C++ detection suite
python3 antivirus_cli.py status            # Show system status

# GUI Launch
python3 gui_antivirus.py                   # Launch GUI application

# Automatic
./run_antivirus.sh                         # Auto-detect and launch
```

---

## Future Enhancements

Planned features:
- [ ] Real packet capture integration
- [ ] Quarantine management
- [ ] Automatic signature updates
- [ ] Cloud threat intelligence integration
- [ ] System tray integration
- [ ] Email alerts
- [ ] Scheduled scan management
- [ ] Whitelist management

---

**END OF USER GUIDE**

*For technical details about data structures and algorithms, see the technical documentation in the `docs/` directory.*
