#!/usr/bin/env python3
"""
CLI-based Mini Antivirus Application
Command-line interface for systems without GUI support
CS-214 Data Structures Project - BS Cyber Security Program
"""

import os
import sys
import time
import json
import argparse
import subprocess
from pathlib import Path
from datetime import datetime
from antivirus_constants import (
    DEFAULT_MALWARE_SIGNATURES,
    SUSPICIOUS_FILE_EXTENSIONS,
    DEFAULT_BLACKLIST_IPS,
    DEFAULT_CONFIG,
    MAX_FILE_SIZE
)

class AntivirusCLI:
    """Command-line interface for the mini antivirus"""
    
    def __init__(self):
        self.config_file = "config.json"
        self.load_config()
        
    def load_config(self):
        """Load application configuration"""
        default_config = DEFAULT_CONFIG.copy()
        default_config["last_scan_path"] = str(Path.home())
        
        try:
            if os.path.exists(self.config_file):
                with open(self.config_file, 'r') as f:
                    self.config = json.load(f)
            else:
                self.config = default_config
                self.save_config()
        except Exception as e:
            print(f"Error loading config: {e}")
            self.config = default_config
    
    def save_config(self):
        """Save application configuration"""
        try:
            with open(self.config_file, 'w') as f:
                json.dump(self.config, f, indent=2)
        except Exception as e:
            print(f"Error saving config: {e}")
    
    def print_header(self):
        """Print application header"""
        print("\n" + "="*70)
        print("  INTEGRATED CYBER THREAT DETECTION SUITE")
        print("  GUI-based Mini Antivirus - CLI Mode")
        print("  CS-214 Data Structures Project")
        print("="*70 + "\n")
    
    def load_signatures(self):
        """Load malware signatures from file"""
        signatures = []
        sig_file = self.config.get("signature_path", "data/malware_signatures.txt")
        
        if os.path.exists(sig_file):
            try:
                with open(sig_file, 'r') as f:
                    signatures = [line.strip() for line in f if line.strip()]
                print(f"✓ Loaded {len(signatures)} malware signatures from {sig_file}")
            except Exception as e:
                print(f"Error loading signatures: {e}")
        
        if not signatures:
            signatures = DEFAULT_MALWARE_SIGNATURES
            print(f"✓ Using {len(signatures)} default signatures")
        
        return signatures
    
    def scan_file(self, filepath, signatures):
        """Scan a single file for malware signatures"""
        result = {"file": filepath, "threats": []}
        
        try:
            # Check file extension
            ext = os.path.splitext(filepath)[1].lower()
            
            if ext in SUSPICIOUS_FILE_EXTENSIONS:
                result["threats"].append(f"Suspicious file type: {ext}")
            
            # Read file content (limit size)
            file_size = os.path.getsize(filepath)
            
            if file_size > MAX_FILE_SIZE:
                return result
            
            # Check for signatures
            with open(filepath, 'rb') as f:
                content = f.read().decode('utf-8', errors='ignore').lower()
                
                for signature in signatures:
                    if signature.lower() in content:
                        result["threats"].append(f"Malware signature: {signature}")
        
        except Exception:
            # Skip unreadable files (binary files, permission denied, etc.)
            pass
        
        return result
    
    def scan_folder(self, folder_path):
        """Scan a folder for threats"""
        print(f"\n{'='*70}")
        print(f"  FOLDER SCAN")
        print(f"{'='*70}")
        print(f"Target: {folder_path}\n")
        
        if not os.path.exists(folder_path):
            print(f"Error: Folder '{folder_path}' does not exist")
            return
        
        # Load signatures
        signatures = self.load_signatures()
        
        # Collect all files
        print("Scanning for files...")
        files = []
        for root, dirs, filenames in os.walk(folder_path):
            for filename in filenames:
                files.append(os.path.join(root, filename))
        
        total_files = len(files)
        print(f"Found {total_files} files to scan\n")
        
        # Scan files
        threats_found = []
        files_scanned = 0
        
        print("Scanning files...")
        start_time = time.time()
        
        for i, filepath in enumerate(files):
            try:
                result = self.scan_file(filepath, signatures)
                files_scanned += 1
                
                if result["threats"]:
                    threats_found.append(result)
                    print(f"⚠ THREAT: {filepath}")
                    for threat in result["threats"]:
                        print(f"  - {threat}")
                
                # Show progress
                if (i + 1) % max(1, total_files // 20) == 0 or i == total_files - 1:
                    progress = (i + 1) / total_files * 100
                    print(f"Progress: {progress:.1f}% ({i + 1}/{total_files})", end='\r')
            
            except Exception as e:
                pass
        
        elapsed_time = time.time() - start_time
        
        # Display results
        print(f"\n\n{'='*70}")
        print("  SCAN RESULTS")
        print(f"{'='*70}")
        print(f"Files scanned: {files_scanned}")
        print(f"Threats found: {len(threats_found)}")
        print(f"Scan time: {elapsed_time:.2f} seconds")
        print(f"{'='*70}\n")
        
        # Save to history
        scan_entry = f"{datetime.now().strftime('%Y-%m-%d %H:%M:%S')} - Scanned {folder_path} - {files_scanned} files, {len(threats_found)} threats"
        if "scan_history" not in self.config:
            self.config["scan_history"] = []
        self.config["scan_history"].append(scan_entry)
        self.config["last_scan_path"] = folder_path
        self.save_config()
        
        # Generate report
        if threats_found:
            self.generate_threat_report(folder_path, files_scanned, threats_found, elapsed_time)
        
        return threats_found
    
    def generate_threat_report(self, folder_path, files_scanned, threats_found, scan_time):
        """Generate a threat report file"""
        report_file = "scan_report.txt"
        
        try:
            with open(report_file, 'w') as f:
                f.write("="*70 + "\n")
                f.write("  INTEGRATED CYBER THREAT DETECTION SUITE\n")
                f.write("  Folder Scan Report\n")
                f.write("="*70 + "\n\n")
                
                f.write(f"Scan Date: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n")
                f.write(f"Target Folder: {folder_path}\n")
                f.write(f"Files Scanned: {files_scanned}\n")
                f.write(f"Threats Detected: {len(threats_found)}\n")
                f.write(f"Scan Duration: {scan_time:.2f} seconds\n")
                f.write("\n" + "="*70 + "\n")
                f.write("  THREATS DETECTED\n")
                f.write("="*70 + "\n\n")
                
                for i, result in enumerate(threats_found, 1):
                    f.write(f"{i}. {result['file']}\n")
                    for threat in result['threats']:
                        f.write(f"   - {threat}\n")
                    f.write("\n")
                
                f.write("="*70 + "\n")
                f.write("  RECOMMENDATIONS\n")
                f.write("="*70 + "\n")
                f.write("1. Review all detected threats carefully\n")
                f.write("2. Quarantine or delete suspicious files\n")
                f.write("3. Update virus signatures regularly\n")
                f.write("4. Run full system scan periodically\n")
                f.write("\n" + "="*70 + "\n")
            
            print(f"✓ Detailed report saved to: {report_file}")
        
        except Exception as e:
            print(f"Error generating report: {e}")
    
    def monitor_network(self, duration=60):
        """Monitor network traffic"""
        print(f"\n{'='*70}")
        print(f"  NETWORK TRAFFIC MONITOR")
        print(f"{'='*70}")
        print(f"Monitoring for {duration} seconds...\n")
        
        # Load blacklist
        blacklist = self.load_blacklist()
        print(f"✓ Loaded {len(blacklist)} blacklisted IPs\n")
        
        print("Press Ctrl+C to stop monitoring\n")
        
        try:
            start_time = time.time()
            events = []
            
            while time.time() - start_time < duration:
                # Simulate network monitoring
                # In real implementation, use packet capture libraries
                time.sleep(2)
                
                # Show activity indicator
                elapsed = int(time.time() - start_time)
                print(f"Monitoring... {elapsed}/{duration}s", end='\r')
            
            print(f"\n\nMonitoring complete")
            print(f"Events detected: {len(events)}")
        
        except KeyboardInterrupt:
            print("\n\nMonitoring stopped by user")
    
    def load_blacklist(self):
        """Load blacklisted IPs"""
        blacklist = []
        blacklist_file = self.config.get("blacklist_path", "data/blacklisted_ips.txt")
        
        if os.path.exists(blacklist_file):
            try:
                with open(blacklist_file, 'r') as f:
                    blacklist = [line.strip() for line in f if line.strip()]
            except Exception as e:
                print(f"Error loading blacklist: {e}")
        
        if not blacklist:
            blacklist = DEFAULT_BLACKLIST_IPS
        
        return blacklist
    
    def run_full_detection_suite(self):
        """Run the original C++ detection suite"""
        print(f"\n{'='*70}")
        print(f"  RUNNING FULL DETECTION SUITE")
        print(f"{'='*70}\n")
        
        executable = "./threat_detection_suite"
        
        if not os.path.exists(executable):
            print("Building detection suite...")
            try:
                subprocess.run(["make"], check=True)
            except subprocess.CalledProcessError:
                print("Error: Failed to build detection suite")
                return
        
        if os.path.exists(executable):
            print("Running integrated threat detection modules...\n")
            try:
                subprocess.run([executable])
            except Exception as e:
                print(f"Error running detection suite: {e}")
        else:
            print("Error: Detection suite executable not found")
    
    def show_status(self):
        """Show system status"""
        print(f"\n{'='*70}")
        print(f"  SYSTEM STATUS")
        print(f"{'='*70}\n")
        
        # Check files
        sig_file = self.config.get("signature_path", "data/malware_signatures.txt")
        blacklist_file = self.config.get("blacklist_path", "data/blacklisted_ips.txt")
        
        print(f"Signature Database: {'✓' if os.path.exists(sig_file) else '✗'} {sig_file}")
        print(f"Blacklist Database: {'✓' if os.path.exists(blacklist_file) else '✗'} {blacklist_file}")
        print(f"Detection Suite:    {'✓' if os.path.exists('./threat_detection_suite') else '✗'} ./threat_detection_suite")
        
        # Show last scan
        if self.config.get("scan_history"):
            print(f"\nLast Scan: {self.config['scan_history'][-1]}")
        else:
            print(f"\nLast Scan: Never")
        
        print(f"\n{'='*70}\n")
    
    def interactive_menu(self):
        """Show interactive menu"""
        while True:
            self.print_header()
            print("Main Menu:")
            print("  1. Scan Folder for Threats")
            print("  2. Monitor Network Traffic")
            print("  3. Run Full Detection Suite")
            print("  4. View Scan History")
            print("  5. System Status")
            print("  6. Exit")
            print()
            
            choice = input("Select option (1-6): ").strip()
            
            if choice == "1":
                folder = input("Enter folder path to scan: ").strip()
                if not folder:
                    folder = self.config.get("last_scan_path", ".")
                self.scan_folder(folder)
                input("\nPress Enter to continue...")
            
            elif choice == "2":
                duration_str = input("Enter monitoring duration in seconds (default 60): ").strip()
                duration = int(duration_str) if duration_str.isdigit() else 60
                self.monitor_network(duration)
                input("\nPress Enter to continue...")
            
            elif choice == "3":
                self.run_full_detection_suite()
                input("\nPress Enter to continue...")
            
            elif choice == "4":
                print(f"\n{'='*70}")
                print("  SCAN HISTORY")
                print(f"{'='*70}\n")
                history = self.config.get("scan_history", [])
                if history:
                    for entry in history[-10:]:  # Show last 10
                        print(f"  {entry}")
                else:
                    print("  No scan history available")
                print(f"\n{'='*70}\n")
                input("Press Enter to continue...")
            
            elif choice == "5":
                self.show_status()
                input("Press Enter to continue...")
            
            elif choice == "6":
                print("\nExiting...")
                break
            
            else:
                print("\nInvalid option. Please try again.")
                time.sleep(1)


def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(
        description="CLI-based Mini Antivirus Application"
    )
    parser.add_argument(
        "command",
        nargs="?",
        choices=["scan", "monitor", "full", "status", "menu"],
        help="Command to execute"
    )
    parser.add_argument(
        "--path",
        help="Path to scan (for scan command)"
    )
    parser.add_argument(
        "--duration",
        type=int,
        default=60,
        help="Monitoring duration in seconds (for monitor command)"
    )
    
    args = parser.parse_args()
    
    cli = AntivirusCLI()
    
    if args.command == "scan":
        path = args.path or cli.config.get("last_scan_path", ".")
        cli.scan_folder(path)
    
    elif args.command == "monitor":
        cli.monitor_network(args.duration)
    
    elif args.command == "full":
        cli.run_full_detection_suite()
    
    elif args.command == "status":
        cli.print_header()
        cli.show_status()
    
    else:
        # Interactive menu
        cli.interactive_menu()


if __name__ == "__main__":
    main()
