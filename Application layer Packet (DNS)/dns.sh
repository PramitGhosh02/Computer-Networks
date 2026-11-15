    #!/bin/bash

    # ============================================================
    # DNS Analysis - Computer Networks Lab (dns.sh)
    #
    # Usage:
    #   chmod +x dns.sh
    #   ./dns.sh              # Defaults to google.com
    #   ./dns.sh yahoo.com    # Or pass any custom domain!
    # ============================================================

    DOMAIN="${1:-google.com}"

    if ! command -v dig &> /dev/null || ! command -v nslookup &> /dev/null; then
        echo "ERROR: DNS utilities ('dig' or 'nslookup') not found!"
        echo "Please install them by running:"
        echo "    sudo apt update && sudo apt install dnsutils -y"
        exit 1
    fi

    echo "   DNS ANALYSIS - Application Layer Packet Analysis"
    echo "   Target Domain: $DOMAIN"

    echo ""
    echo "  1. BASIC DNS LOOKUP (A Record - IP Address Resolution)"
    echo ""
    echo "--- Using nslookup ---"
    nslookup $DOMAIN
    echo ""
    echo "--- Using dig ---"
    dig $DOMAIN A
    echo ""
    echo "--- Using host ---"
    host $DOMAIN

    echo ""
    echo "  2. MX RECORD ANALYSIS (Mail Exchange Servers & Priority)"
    echo ""
    echo "--- Using nslookup ---"
    nslookup -type=mx $DOMAIN
    echo ""
    echo "--- Using dig ---"
    dig $DOMAIN MX
    echo ""
    echo "--- Using host ---"
    host -t MX $DOMAIN

    echo ""
    echo "  3. SOA RECORD ANALYSIS (Start of Authority)"
    echo ""
    echo "--- Using nslookup ---"
    nslookup -type=soa $DOMAIN
    echo ""
    echo "--- Using dig ---"
    dig $DOMAIN SOA
    echo ""
    echo "--- Using host ---"
    host -t SOA $DOMAIN

    echo ""
    echo "  4. ADDITIONAL DNS QUERIES (NS & Reverse PTR Lookup)"
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
    echo "   DNS ANALYSIS COMPLETE"
