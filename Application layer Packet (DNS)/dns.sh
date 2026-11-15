#!/bin/bash

# DNS Analysis - Computer Networks Lab (dns.sh)

DOMAIN="${1:-google.com}"

if ! command -v dig &> /dev/null || ! command -v nslookup &> /dev/null; then
    echo "ERROR: DNS utilities ('dig' or 'nslookup') not found."
    echo "Please install by running: sudo apt update && sudo apt install dnsutils -y"
    exit 1
fi

echo "DNS Analysis for domain: $DOMAIN"
echo ""

echo "1. Basic DNS Lookup (A Record)"
nslookup $DOMAIN
echo ""
dig $DOMAIN A
echo ""
host $DOMAIN
echo ""

echo "2. MX Record Analysis (Mail Exchange Servers)"
nslookup -type=mx $DOMAIN
echo ""
dig $DOMAIN MX
echo ""
host -t MX $DOMAIN
echo ""

echo "3. SOA Record Analysis (Start of Authority)"
nslookup -type=soa $DOMAIN
echo ""
dig $DOMAIN SOA
echo ""
host -t SOA $DOMAIN
echo ""

echo "4. Authoritative Nameservers (NS Records)"
dig $DOMAIN NS +short
echo ""

echo "5. Reverse DNS Lookup (PTR Record)"
IP=$(dig $DOMAIN A +short | head -1)
if [ -n "$IP" ]; then
    echo "Resolved IP: $IP"
    nslookup $IP
fi
echo ""

echo "DNS Analysis complete."
