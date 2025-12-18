"""
Shared constants for the antivirus application
Integrated Cyber Threat Detection Suite
"""

# Default malware signatures
DEFAULT_MALWARE_SIGNATURES = [
    "malicious_payload",
    "trojan",
    "virus",
    "ransomware",
    "backdoor",
    "keylogger",
    "spyware",
    "adware",
    "worm",
    "rootkit",
    "exploit",
    "malware"
]

# Suspicious file extensions
SUSPICIOUS_FILE_EXTENSIONS = [
    '.exe', '.dll', '.bat', '.cmd', '.vbs', 
    '.js', '.ps1', '.sh', '.msi', '.scr'
]

# Default blacklisted IPs
DEFAULT_BLACKLIST_IPS = [
    "192.168.1.100",
    "10.0.0.50",
    "203.0.113.5"
]

# Configuration defaults
DEFAULT_CONFIG = {
    "last_scan_path": ".",
    "scan_history": [],
    "signature_path": "data/malware_signatures.txt",
    "blacklist_path": "data/blacklisted_ips.txt",
    "report_path": "threat_report.txt",
    "auto_scan": False,
    "network_monitoring": False
}

# Scan limits
MAX_FILE_SIZE = 10 * 1024 * 1024  # 10 MB
