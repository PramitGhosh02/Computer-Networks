#!/bin/bash

# ============================================================
# DNS Analysis - Computer Networks Lab
#
# Analysis of Application Layer Packets (DNS)
# Covers: Basic DNS Lookup, MX Records, SOA Records
#
# Usage: chmod +x dns_analysis.sh && ./dns_analysis.sh
# ============================================================

DOMAIN="google.com"

echo "   DNS ANALYSIS - Application Layer Packet Analysis"
echo "   Target Domain: $DOMAIN"

# --------------------------------------------------
# 1. BASIC DNS LOOKUP (A Record - IP Address)
# --------------------------------------------------
echo ""
echo "  1. BASIC DNS LOOKUP (A Record)"
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
# 2. MX RECORD ANALYSIS (Mail Exchange)
# --------------------------------------------------
echo ""
echo "  2. MX RECORD ANALYSIS (Mail Exchange Servers)"
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
echo "  3. SOA RECORD ANALYSIS (Start of Authority)"
echo ""
echo "SOA records contain administrative info about the domain:"
echo "  - Primary nameserver"
echo "  - Email of domain admin"
echo "  - Serial number, Refresh, Retry, Expire, TTL"
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
# 4. ADDITIONAL USEFUL QUERIES
# --------------------------------------------------
echo ""
echo "  4. ADDITIONAL DNS QUERIES"
echo ""
echo "--- NS Records (Nameservers) ---"
dig $DOMAIN NS +short
echo ""
echo "--- Reverse DNS Lookup (PTR Record) ---"
IP=$(dig $DOMAIN A +short | head -1)
echo "IP of $DOMAIN: $IP"
nslookup $IP
echo ""
echo "--- Trace DNS Resolution Path ---"
dig $DOMAIN +trace +short

echo ""
echo "   DNS ANALYSIS COMPLETE"
