#!/bin/bash

# Packet Analysis - Computer Networks Lab
# Generates traffic for DNS, HTTP, TCP, UDP, ARP, and ICMP protocols.

echo "Network Traffic Generator for Wireshark Analysis"
echo "Make sure Wireshark is capturing before proceeding."
read -p "Press Enter to start generating traffic..."

# 1. DNS Traffic (Application Layer - Port 53)
echo ""
echo "[1/6] Generating DNS traffic..."
nslookup google.com > /dev/null 2>&1
dig gmail.com MX +short > /dev/null 2>&1
dig google.com SOA +short > /dev/null 2>&1
echo "DNS traffic generated."

sleep 1

# 2. HTTP Traffic (Application Layer - Port 80)
echo ""
echo "[2/6] Generating HTTP traffic..."
curl -s http://example.com > /dev/null 2>&1
curl -s -I http://example.com > /dev/null 2>&1
echo "HTTP traffic generated."

sleep 1

# 3. TCP Traffic (Transport Layer)
echo ""
echo "[3/6] Generating TCP traffic..."
curl -s http://google.com > /dev/null 2>&1
curl -s https://example.com > /dev/null 2>&1
echo "TCP traffic generated."

sleep 1

# 4. UDP Traffic (Transport Layer)
echo ""
echo "[4/6] Generating UDP traffic..."
dig google.com A +short > /dev/null 2>&1
traceroute -m 3 google.com > /dev/null 2>&1
echo "UDP traffic generated."

sleep 1

# 5. ARP Traffic (Data Link Layer)
echo ""
echo "[5/6] Generating ARP traffic..."
GATEWAY=$(ip route | grep default | awk '{print $3}' | head -1)
if [ -n "$GATEWAY" ]; then
    ping -c 2 $GATEWAY > /dev/null 2>&1
else
    ping -c 2 8.8.8.8 > /dev/null 2>&1
fi
echo "ARP traffic generated."

sleep 1

# 6. ICMP Traffic (Network Layer - Ping)
echo ""
echo "[6/6] Generating ICMP ping traffic..."
ping -c 3 google.com > /dev/null 2>&1
echo "ICMP traffic generated."

echo ""
echo "Traffic generation complete."
echo "Stop Wireshark capture and apply the following display filters:"
echo "DNS packets: dns"
echo "HTTP packets: http"
echo "TCP packets: tcp"
echo "UDP packets: udp"
echo "ARP packets: arp"
echo "ICMP packets: icmp"
echo ""
