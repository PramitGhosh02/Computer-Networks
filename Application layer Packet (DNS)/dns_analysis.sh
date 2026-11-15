#!/bin/bash

# ============================================================
# DNS Analysis - Computer Networks Lab
#
# Analysis of Application Layer Packets (DNS)
# Covers: Basic DNS Lookup (A), MX Records, SOA Records,
#         NS Records, and Reverse DNS (PTR)
#
# Usage:
#   chmod +x dns_analysis.sh
#   ./dns_analysis.sh              # Defaults to google.com
#   ./dns_analysis.sh yahoo.com    # Or pass any custom domain!
# ============================================================

# Target domain (defaults to google.com, or accepts first argument)
DOMAIN="${1:-google.com}"

# Check if dnsutils tools are installed
if ! command -v dig &> /dev/null || ! command -v nslookup &> /dev/null; then
    echo "============================================================"
    echo "ERROR: DNS utilities ('dig' or 'nslookup') not found!"
    echo "Please install them by running:"
    echo "    sudo apt update && sudo apt install dnsutils -y"
    echo "============================================================"
    exit 1
fi

echo "============================================================"
echo "   DNS ANALYSIS - Application Layer Packet Analysis"
echo "   Target Domain: $DOMAIN"
echo "============================================================"

# --------------------------------------------------
# 1. BASIC DNS LOOKUP (A Record - IPv4 Address)
# --------------------------------------------------
echo ""
echo "============================================================"
echo "  1. BASIC DNS LOOKUP (A Record - IP Address Resolution)"
echo "============================================================"
echo ""
echo "--- Using nslookup ---"
nslookup $DOMAIN
echo ""
echo "--- Using dig ---"
dig $DOMAIN A
echo ""
echo "--- Using host ---"
host $DOMAIN

# --------------------------------------------------
# 2. MX RECORD ANALYSIS (Mail Exchange Servers)
# --------------------------------------------------
echo ""
echo "============================================================"
echo "  2. MX RECORD ANALYSIS (Mail Exchange Servers & Priority)"
echo "============================================================"
echo ""
echo "MX records specify the mail servers responsible for"
echo "accepting email on behalf of the domain."
echo ""
echo "--- Using nslookup ---"
nslookup -type=mx $DOMAIN
echo ""
echo "--- Using dig ---"
dig $DOMAIN MX
echo ""
echo "--- Using host ---"
host -t MX $DOMAIN

# --------------------------------------------------
# 3. SOA RECORD ANALYSIS (Start of Authority)
# --------------------------------------------------
echo ""
echo "============================================================"
echo "  3. SOA RECORD ANALYSIS (Start of Authority)"
echo "============================================================"
echo ""
echo "SOA records contain administrative info about the domain zone:"
echo "  - Primary master nameserver (origin)"
echo "  - Email of domain administrator (mail addr)"
echo "  - Serial number (version of zone file)"
echo "  - Refresh, Retry, Expire timers, and Minimum TTL"
echo ""
echo "--- Using nslookup ---"
nslookup -type=soa $DOMAIN
echo ""
echo "--- Using dig ---"
dig $DOMAIN SOA
echo ""
echo "--- Using host ---"
host -t SOA $DOMAIN

# --------------------------------------------------
# 4. ADDITIONAL USEFUL QUERIES (NS & PTR Records)
# --------------------------------------------------
echo ""
echo "============================================================"
echo "  4. ADDITIONAL DNS QUERIES (NS & Reverse PTR Lookup)"
echo "============================================================"
echo ""
echo "--- NS Records (Authoritative Nameservers) ---"
dig $DOMAIN NS +short
echo ""
echo "--- Reverse DNS Lookup (PTR Record: IP -> Domain) ---"
IP=$(dig $DOMAIN A +short | head -1)
if [ -n "$IP" ]; then
    echo "Resolved IPv4 of $DOMAIN: $IP"
    echo "Reverse lookup for $IP:"
    nslookup $IP
fi
echo ""
echo "--- Trace DNS Resolution Path ---"
dig $DOMAIN +trace +short 2>/dev/null || echo "(Direct root queries filtered by local router/firewall)"

echo ""
echo "============================================================"
echo "   DNS ANALYSIS COMPLETE"
echo "============================================================"
