#!/bin/bash

# ============================================================
# Packet Analysis - Computer Networks Lab
#
# This script generates network traffic for various protocols
# so that Wireshark can capture and analyze them.
#
# Protocols covered: DNS, HTTP, ARP, TCP, UDP, IP
#
# Usage:
#   1. Start Wireshark capture FIRST
#   2. Then run: chmod +x generate_traffic.sh && ./generate_traffic.sh
# ============================================================

echo "============================================================"
echo "   NETWORK TRAFFIC GENERATOR FOR WIRESHARK ANALYSIS"
echo "============================================================"
echo ""
echo "Make sure Wireshark is CAPTURING before running this script!"
echo ""
read -p "Press Enter to start generating traffic..."

# --------------------------------------------------
# 1. DNS TRAFFIC (Application Layer - Port 53)
# --------------------------------------------------
echo ""
echo "[1/6] Generating DNS traffic..."
echo "  → A Record lookup"
nslookup google.com > /dev/null 2>&1
echo "  → MX Record lookup"
dig gmail.com MX +short > /dev/null 2>&1
echo "  → SOA Record lookup"
dig google.com SOA +short > /dev/null 2>&1
echo "  ✓ DNS traffic generated"

sleep 1

# --------------------------------------------------
# 2. HTTP TRAFFIC (Application Layer - Port 80)
# --------------------------------------------------
echo ""
echo "[2/6] Generating HTTP traffic..."
echo "  → HTTP GET request to example.com"
curl -s http://example.com > /dev/null 2>&1
echo "  → HTTP HEAD request"
curl -s -I http://example.com > /dev/null 2>&1
echo "  ✓ HTTP traffic generated"

sleep 1

# --------------------------------------------------
# 3. TCP TRAFFIC (Transport Layer)
# --------------------------------------------------
echo ""
echo "[3/6] Generating TCP traffic..."
echo "  → TCP connection to google.com:80 (3-way handshake)"
curl -s http://google.com > /dev/null 2>&1
echo "  → TCP connection to example.com:443 (HTTPS)"
curl -s https://example.com > /dev/null 2>&1
echo "  ✓ TCP traffic generated (SYN → SYN-ACK → ACK visible)"

sleep 1

# --------------------------------------------------
# 4. UDP TRAFFIC (Transport Layer)
# --------------------------------------------------
echo ""
echo "[4/6] Generating UDP traffic..."
echo "  → DNS queries use UDP port 53"
dig google.com A +short > /dev/null 2>&1
dig yahoo.com A +short > /dev/null 2>&1
echo "  → Traceroute uses UDP (on Linux)"
traceroute -m 5 google.com > /dev/null 2>&1
echo "  ✓ UDP traffic generated"

sleep 1

# --------------------------------------------------
# 5. ARP TRAFFIC (Data Link Layer)
# --------------------------------------------------
echo ""
echo "[5/6] Generating ARP traffic..."
echo "  → Displaying current ARP table"
arp -a
echo "  → Pinging gateway to trigger ARP resolution"
GATEWAY=$(ip route | grep default | awk '{print $3}' | head -1)
if [ -n "$GATEWAY" ]; then
    ping -c 2 $GATEWAY > /dev/null 2>&1
    echo "  → Pinged gateway: $GATEWAY"
else
    ping -c 2 8.8.8.8 > /dev/null 2>&1
    echo "  → Pinged 8.8.8.8"
fi
echo "  ✓ ARP traffic generated"

sleep 1

# --------------------------------------------------
# 6. IP TRAFFIC (Network Layer)
# --------------------------------------------------
echo ""
echo "[6/6] Generating IP traffic..."
echo "  → ICMP ping (IP protocol)"
ping -c 3 google.com
echo "  → Traceroute (shows IP hops)"
traceroute -m 5 google.com 2>/dev/null || tracepath google.com 2>/dev/null
echo "  ✓ IP/ICMP traffic generated"

echo ""
echo "============================================================"
echo "   ALL TRAFFIC GENERATED SUCCESSFULLY!"
echo "   Now go to Wireshark and STOP the capture."
echo "   Use the filters below to analyze each protocol."
echo "============================================================"
echo ""
echo "  WIRESHARK DISPLAY FILTERS:"
echo "  ─────────────────────────────────────────"
echo "  DNS packets   →  dns"
echo "  HTTP packets  →  http"
echo "  TCP packets   →  tcp"
echo "  UDP packets   →  udp"
echo "  ARP packets   →  arp"
echo "  ICMP packets  →  icmp"
echo "  IP address    →  ip.addr == <IP_ADDRESS>"
echo "  ─────────────────────────────────────────"
echo ""
