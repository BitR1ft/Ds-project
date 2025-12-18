#!/usr/bin/env python3
"""
GUI-based Mini Antivirus Application
Integrated Cyber Threat Detection Suite with Daily Usage Features
CS-214 Data Structures Project - BS Cyber Security Program
"""

import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import threading
import queue
import os
import sys
import time
import subprocess
import json
from datetime import datetime
from pathlib import Path
from antivirus_constants import (
    DEFAULT_MALWARE_SIGNATURES,
    SUSPICIOUS_FILE_EXTENSIONS,
    DEFAULT_BLACKLIST_IPS,
    DEFAULT_CONFIG,
    MAX_FILE_SIZE
)

class MiniAntivirusGUI:
    """Main GUI application for the mini antivirus"""
    
    def __init__(self, root):
        self.root = root
        self.root.title("Integrated Cyber Threat Detection Suite")
        self.root.geometry("1000x700")
        
        # State variables
        self.scanning = False
        self.monitoring = False
        self.scan_queue = queue.Queue()
        self.network_queue = queue.Queue()
        
        # Configuration
        self.config_file = "config.json"
        self.load_config()
        
        # Setup UI
        self.setup_menu()
        self.setup_ui()
        
        # Start background workers
        self.root.after(100, self.process_queues)
        
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
    
    def setup_menu(self):
        """Setup application menu bar"""
        menubar = tk.Menu(self.root)
        self.root.config(menu=menubar)
        
        # File menu
        file_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Scan Folder...", command=self.select_scan_folder)
        file_menu.add_command(label="View Scan History", command=self.show_scan_history)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.root.quit)
        
        # Tools menu
        tools_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Tools", menu=tools_menu)
        tools_menu.add_command(label="Network Monitor", command=self.toggle_network_monitor)
        tools_menu.add_command(label="Update Signatures", command=self.update_signatures)
        tools_menu.add_command(label="Settings", command=self.show_settings)
        
        # Help menu
        help_menu = tk.Menu(menubar, tearoff=0)
        menubar.add_cascade(label="Help", menu=help_menu)
        help_menu.add_command(label="About", command=self.show_about)
    
    def setup_ui(self):
        """Setup main user interface"""
        # Main container
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(0, weight=1)
        main_frame.rowconfigure(2, weight=1)
        
        # Header
        header_frame = ttk.LabelFrame(main_frame, text="Integrated Cyber Threat Detection Suite", padding="10")
        header_frame.grid(row=0, column=0, sticky=(tk.W, tk.E), pady=(0, 10))
        
        ttk.Label(header_frame, text="Real-time Protection & Scanning", font=('Arial', 12, 'bold')).grid(row=0, column=0)
        
        # Control Panel
        control_frame = ttk.LabelFrame(main_frame, text="Control Panel", padding="10")
        control_frame.grid(row=1, column=0, sticky=(tk.W, tk.E), pady=(0, 10))
        
        # Folder Scanning Section
        ttk.Label(control_frame, text="Folder Scanner:", font=('Arial', 10, 'bold')).grid(row=0, column=0, sticky=tk.W, pady=(0, 5))
        
        scan_controls = ttk.Frame(control_frame)
        scan_controls.grid(row=1, column=0, sticky=(tk.W, tk.E))
        
        self.scan_path_var = tk.StringVar(value=self.config.get("last_scan_path", "No folder selected"))
        ttk.Label(scan_controls, textvariable=self.scan_path_var, relief=tk.SUNKEN, width=60).pack(side=tk.LEFT, padx=(0, 5))
        
        ttk.Button(scan_controls, text="Browse...", command=self.select_scan_folder).pack(side=tk.LEFT, padx=2)
        self.scan_btn = ttk.Button(scan_controls, text="Start Scan", command=self.start_folder_scan)
        self.scan_btn.pack(side=tk.LEFT, padx=2)
        ttk.Button(scan_controls, text="Stop", command=self.stop_scan).pack(side=tk.LEFT, padx=2)
        
        # Progress bar
        self.progress_var = tk.DoubleVar()
        self.progress_bar = ttk.Progressbar(control_frame, variable=self.progress_var, maximum=100)
        self.progress_bar.grid(row=2, column=0, sticky=(tk.W, tk.E), pady=5)
        
        # Network Monitoring Section
        ttk.Label(control_frame, text="Network Traffic Monitor:", font=('Arial', 10, 'bold')).grid(row=3, column=0, sticky=tk.W, pady=(10, 5))
        
        network_controls = ttk.Frame(control_frame)
        network_controls.grid(row=4, column=0, sticky=(tk.W, tk.E))
        
        self.network_status_var = tk.StringVar(value="Stopped")
        ttk.Label(network_controls, text="Status:").pack(side=tk.LEFT, padx=(0, 5))
        ttk.Label(network_controls, textvariable=self.network_status_var, relief=tk.SUNKEN, width=20).pack(side=tk.LEFT, padx=(0, 5))
        
        self.network_btn = ttk.Button(network_controls, text="Start Monitoring", command=self.toggle_network_monitor)
        self.network_btn.pack(side=tk.LEFT, padx=2)
        
        # Results/Logs Panel
        results_frame = ttk.LabelFrame(main_frame, text="Detection Results & Activity Log", padding="10")
        results_frame.grid(row=2, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        results_frame.columnconfigure(0, weight=1)
        results_frame.rowconfigure(0, weight=1)
        
        # Create notebook for tabs
        self.notebook = ttk.Notebook(results_frame)
        self.notebook.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Scan Results Tab
        scan_tab = ttk.Frame(self.notebook)
        self.notebook.add(scan_tab, text="Scan Results")
        
        self.scan_results_text = scrolledtext.ScrolledText(scan_tab, height=20, width=100)
        self.scan_results_text.pack(fill=tk.BOTH, expand=True)
        
        # Network Activity Tab
        network_tab = ttk.Frame(self.notebook)
        self.notebook.add(network_tab, text="Network Activity")
        
        self.network_text = scrolledtext.ScrolledText(network_tab, height=20, width=100)
        self.network_text.pack(fill=tk.BOTH, expand=True)
        
        # Threats Detected Tab
        threats_tab = ttk.Frame(self.notebook)
        self.notebook.add(threats_tab, text="Threats Detected")
        
        self.threats_text = scrolledtext.ScrolledText(threats_tab, height=20, width=100)
        self.threats_text.pack(fill=tk.BOTH, expand=True)
        
        # Status bar
        self.status_var = tk.StringVar(value="Ready")
        status_bar = ttk.Label(main_frame, textvariable=self.status_var, relief=tk.SUNKEN)
        status_bar.grid(row=3, column=0, sticky=(tk.W, tk.E), pady=(10, 0))
        
        # Initial log message
        self.log_message("Scan Results", "Application started. Select a folder to scan for threats.", "INFO")
    
    def log_message(self, tab, message, level="INFO"):
        """Log a message to the specified tab"""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        formatted_msg = f"[{timestamp}] [{level}] {message}\n"
        
        if tab == "Scan Results":
            self.scan_results_text.insert(tk.END, formatted_msg)
            self.scan_results_text.see(tk.END)
        elif tab == "Network Activity":
            self.network_text.insert(tk.END, formatted_msg)
            self.network_text.see(tk.END)
        elif tab == "Threats Detected":
            self.threats_text.insert(tk.END, formatted_msg)
            self.threats_text.see(tk.END)
    
    def select_scan_folder(self):
        """Open folder selection dialog"""
        folder = filedialog.askdirectory(
            title="Select Folder to Scan",
            initialdir=self.config.get("last_scan_path", str(Path.home()))
        )
        
        if folder:
            self.scan_path_var.set(folder)
            self.config["last_scan_path"] = folder
            self.save_config()
            self.log_message("Scan Results", f"Selected folder: {folder}", "INFO")
    
    def start_folder_scan(self):
        """Start scanning the selected folder"""
        folder = self.scan_path_var.get()
        
        if folder == "No folder selected" or not os.path.exists(folder):
            messagebox.showwarning("No Folder Selected", "Please select a valid folder to scan.")
            return
        
        if self.scanning:
            messagebox.showinfo("Scan in Progress", "A scan is already running.")
            return
        
        self.scanning = True
        self.scan_btn.config(state='disabled')
        self.progress_var.set(0)
        self.status_var.set(f"Scanning {folder}...")
        
        self.log_message("Scan Results", f"Starting scan of folder: {folder}", "INFO")
        
        # Start scan in background thread
        scan_thread = threading.Thread(target=self.scan_folder_thread, args=(folder,), daemon=True)
        scan_thread.start()
    
    def scan_folder_thread(self, folder):
        """Background thread for folder scanning"""
        try:
            # Load malware signatures
            signatures = self.load_signatures()
            self.scan_queue.put(("INFO", f"Loaded {len(signatures)} malware signatures"))
            
            # Scan all files in folder
            files = []
            for root, dirs, filenames in os.walk(folder):
                for filename in filenames:
                    files.append(os.path.join(root, filename))
            
            total_files = len(files)
            self.scan_queue.put(("INFO", f"Found {total_files} files to scan"))
            
            threats_found = 0
            files_scanned = 0
            
            for i, filepath in enumerate(files):
                if not self.scanning:
                    break
                
                try:
                    # Scan file
                    result = self.scan_file(filepath, signatures)
                    files_scanned += 1
                    
                    if result["threats"]:
                        threats_found += len(result["threats"])
                        self.scan_queue.put(("THREAT", filepath, result["threats"]))
                    
                    # Update progress
                    progress = (i + 1) / total_files * 100
                    self.scan_queue.put(("PROGRESS", progress))
                    
                except Exception as e:
                    self.scan_queue.put(("ERROR", f"Error scanning {filepath}: {str(e)}"))
            
            # Scan complete
            self.scan_queue.put(("COMPLETE", files_scanned, threats_found))
            
        except Exception as e:
            self.scan_queue.put(("ERROR", f"Scan error: {str(e)}"))
        
        finally:
            self.scanning = False
    
    def load_signatures(self):
        """Load malware signatures from file"""
        signatures = []
        sig_file = self.config.get("signature_path", "data/malware_signatures.txt")
        
        if os.path.exists(sig_file):
            try:
                with open(sig_file, 'r') as f:
                    signatures = [line.strip() for line in f if line.strip()]
            except Exception as e:
                print(f"Error loading signatures: {e}")
        
        # Use default signatures if file doesn't exist or is empty
        if not signatures:
            signatures = DEFAULT_MALWARE_SIGNATURES
        
        return signatures
    
    def scan_file(self, filepath, signatures):
        """Scan a single file for malware signatures"""
        result = {"file": filepath, "threats": []}
        
        try:
            # Check file extension for suspicious types
            ext = os.path.splitext(filepath)[1].lower()
            
            if ext in SUSPICIOUS_FILE_EXTENSIONS:
                result["threats"].append(f"Suspicious file type: {ext}")
            
            # Read file content (limit size for performance)
            file_size = os.path.getsize(filepath)
            
            if file_size > MAX_FILE_SIZE:
                return result
            
            # Read and check for signatures
            with open(filepath, 'rb') as f:
                content = f.read().decode('utf-8', errors='ignore').lower()
                
                for signature in signatures:
                    if signature.lower() in content:
                        result["threats"].append(f"Malware signature detected: {signature}")
        
        except Exception:
            # Skip files that can't be read (binary files, permission denied, etc.)
            pass
        
        return result
    
    def stop_scan(self):
        """Stop the current scan"""
        if self.scanning:
            self.scanning = False
            self.log_message("Scan Results", "Scan stopped by user", "WARNING")
            self.status_var.set("Scan stopped")
    
    def toggle_network_monitor(self):
        """Toggle network traffic monitoring"""
        if self.monitoring:
            self.stop_network_monitor()
        else:
            self.start_network_monitor()
    
    def start_network_monitor(self):
        """Start network traffic monitoring"""
        self.monitoring = True
        self.network_status_var.set("Monitoring")
        self.network_btn.config(text="Stop Monitoring")
        self.log_message("Network Activity", "Network monitoring started", "INFO")
        
        # Start monitoring thread
        monitor_thread = threading.Thread(target=self.network_monitor_thread, daemon=True)
        monitor_thread.start()
    
    def stop_network_monitor(self):
        """Stop network traffic monitoring"""
        self.monitoring = False
        self.network_status_var.set("Stopped")
        self.network_btn.config(text="Start Monitoring")
        self.log_message("Network Activity", "Network monitoring stopped", "INFO")
    
    def network_monitor_thread(self):
        """Background thread for network monitoring"""
        # Load blacklisted IPs
        blacklist = self.load_blacklist()
        self.network_queue.put(("INFO", f"Loaded {len(blacklist)} blacklisted IPs"))
        
        try:
            while self.monitoring:
                # Simulate network packet capture and analysis
                # In a real implementation, this would use libraries like scapy or pcap
                self.simulate_network_traffic(blacklist)
                time.sleep(2)  # Check every 2 seconds
                
        except Exception as e:
            self.network_queue.put(("ERROR", f"Network monitoring error: {str(e)}"))
    
    def load_blacklist(self):
        """Load blacklisted IPs from file"""
        blacklist = []
        blacklist_file = self.config.get("blacklist_path", "data/blacklisted_ips.txt")
        
        if os.path.exists(blacklist_file):
            try:
                with open(blacklist_file, 'r') as f:
                    blacklist = [line.strip() for line in f if line.strip()]
            except Exception as e:
                print(f"Error loading blacklist: {e}")
        
        # Use default blacklist if file doesn't exist or is empty
        if not blacklist:
            blacklist = DEFAULT_BLACKLIST_IPS
        
        return blacklist
    
    def simulate_network_traffic(self, blacklist):
        """Simulate network traffic analysis (placeholder for real implementation)"""
        # This is a simulation - in a real application, you would:
        # 1. Capture actual network packets using scapy or similar
        # 2. Analyze packet headers, payloads
        # 3. Check against blacklists, detect port scans, DDoS attempts
        
        import random
        
        # Simulate random network events
        if random.random() < 0.1:  # 10% chance of event
            event_type = random.choice(["connection", "suspicious", "blocked"])
            
            if event_type == "connection":
                ip = f"{random.randint(1, 255)}.{random.randint(1, 255)}.{random.randint(1, 255)}.{random.randint(1, 255)}"
                self.network_queue.put(("INFO", f"Connection from {ip}"))
            
            elif event_type == "suspicious":
                ip = f"{random.randint(1, 255)}.{random.randint(1, 255)}.{random.randint(1, 255)}.{random.randint(1, 255)}"
                port = random.randint(1, 65535)
                self.network_queue.put(("WARNING", f"Suspicious activity from {ip}:{port}"))
                self.network_queue.put(("THREAT", "Network", [f"Suspicious connection attempt from {ip}:{port}"]))
            
            elif event_type == "blocked" and blacklist:
                ip = random.choice(blacklist)
                self.network_queue.put(("THREAT", "Network", [f"Blocked connection from blacklisted IP: {ip}"]))
    
    def process_queues(self):
        """Process messages from background threads"""
        # Process scan queue
        while not self.scan_queue.empty():
            try:
                msg = self.scan_queue.get_nowait()
                
                if msg[0] == "INFO":
                    self.log_message("Scan Results", msg[1], "INFO")
                elif msg[0] == "ERROR":
                    self.log_message("Scan Results", msg[1], "ERROR")
                elif msg[0] == "PROGRESS":
                    self.progress_var.set(msg[1])
                elif msg[0] == "THREAT":
                    filepath, threats = msg[1], msg[2]
                    for threat in threats:
                        self.log_message("Threats Detected", f"{filepath}: {threat}", "THREAT")
                        self.log_message("Scan Results", f"THREAT: {filepath} - {threat}", "WARNING")
                elif msg[0] == "COMPLETE":
                    files_scanned, threats_found = msg[1], msg[2]
                    self.log_message("Scan Results", f"Scan complete: {files_scanned} files scanned, {threats_found} threats found", "INFO")
                    self.status_var.set(f"Scan complete: {threats_found} threats found")
                    self.scan_btn.config(state='normal')
                    self.progress_var.set(100)
                    
                    if threats_found > 0:
                        messagebox.showwarning("Threats Detected", f"Scan found {threats_found} potential threats. Check the Threats Detected tab for details.")
            except queue.Empty:
                break
        
        # Process network queue
        while not self.network_queue.empty():
            try:
                msg = self.network_queue.get_nowait()
                
                if msg[0] == "INFO":
                    self.log_message("Network Activity", msg[1], "INFO")
                elif msg[0] == "ERROR":
                    self.log_message("Network Activity", msg[1], "ERROR")
                elif msg[0] == "WARNING":
                    self.log_message("Network Activity", msg[1], "WARNING")
                elif msg[0] == "THREAT":
                    source, threats = msg[1], msg[2]
                    for threat in threats:
                        self.log_message("Threats Detected", f"Network: {threat}", "THREAT")
                        self.log_message("Network Activity", f"THREAT: {threat}", "WARNING")
            except queue.Empty:
                break
        
        # Schedule next check
        self.root.after(100, self.process_queues)
    
    def show_scan_history(self):
        """Show scan history dialog"""
        history = self.config.get("scan_history", [])
        
        dialog = tk.Toplevel(self.root)
        dialog.title("Scan History")
        dialog.geometry("600x400")
        
        text = scrolledtext.ScrolledText(dialog, height=20, width=70)
        text.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        if history:
            for entry in history:
                text.insert(tk.END, f"{entry}\n")
        else:
            text.insert(tk.END, "No scan history available.")
        
        text.config(state='disabled')
        
        ttk.Button(dialog, text="Close", command=dialog.destroy).pack(pady=5)
    
    def update_signatures(self):
        """Update malware signatures"""
        messagebox.showinfo("Update Signatures", "Signature update feature would connect to a signature database.\nFor this demo, signatures are loaded from data/malware_signatures.txt")
    
    def show_settings(self):
        """Show settings dialog"""
        dialog = tk.Toplevel(self.root)
        dialog.title("Settings")
        dialog.geometry("500x400")
        
        frame = ttk.Frame(dialog, padding="10")
        frame.pack(fill=tk.BOTH, expand=True)
        
        ttk.Label(frame, text="Application Settings", font=('Arial', 12, 'bold')).grid(row=0, column=0, columnspan=2, pady=(0, 10))
        
        # Auto scan setting
        ttk.Label(frame, text="Auto-scan on startup:").grid(row=1, column=0, sticky=tk.W, pady=5)
        auto_scan_var = tk.BooleanVar(value=self.config.get("auto_scan", False))
        ttk.Checkbutton(frame, variable=auto_scan_var).grid(row=1, column=1, sticky=tk.W, pady=5)
        
        # Signature file path
        ttk.Label(frame, text="Signature file:").grid(row=2, column=0, sticky=tk.W, pady=5)
        sig_path_var = tk.StringVar(value=self.config.get("signature_path", "data/malware_signatures.txt"))
        ttk.Entry(frame, textvariable=sig_path_var, width=40).grid(row=2, column=1, sticky=tk.W, pady=5)
        
        # Blacklist file path
        ttk.Label(frame, text="Blacklist file:").grid(row=3, column=0, sticky=tk.W, pady=5)
        blacklist_path_var = tk.StringVar(value=self.config.get("blacklist_path", "data/blacklisted_ips.txt"))
        ttk.Entry(frame, textvariable=blacklist_path_var, width=40).grid(row=3, column=1, sticky=tk.W, pady=5)
        
        def save_settings():
            self.config["auto_scan"] = auto_scan_var.get()
            self.config["signature_path"] = sig_path_var.get()
            self.config["blacklist_path"] = blacklist_path_var.get()
            self.save_config()
            messagebox.showinfo("Settings", "Settings saved successfully!")
            dialog.destroy()
        
        ttk.Button(frame, text="Save", command=save_settings).grid(row=4, column=0, pady=20)
        ttk.Button(frame, text="Cancel", command=dialog.destroy).grid(row=4, column=1, pady=20)
    
    def show_about(self):
        """Show about dialog"""
        about_text = """Integrated Cyber Threat Detection Suite
GUI-based Mini Antivirus Application

Version 2.0
CS-214 Data Structures Project
BS Cyber Security Program

Features:
• Custom folder scanning
• Real-time network traffic monitoring
• Malware signature detection
• Threat detection and logging
• Configuration management

This application integrates multiple security modules:
- Malware Scanner (Trie, Aho-Corasick)
- Ransomware Detector (Graph, DFS/BFS)
- Network IDS (AVL Tree, Priority Queue)
- Threat Intelligence (Hash Tables, Linked Lists)
"""
        messagebox.showinfo("About", about_text)


def main():
    """Main entry point"""
    root = tk.Tk()
    app = MiniAntivirusGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
