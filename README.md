# Computer Networks Lab Practicals

A complete repository containing source code, theory, and execution instructions for Computer Networks laboratory experiments on Ubuntu / Linux.

---

## Repository Contents

| #   | Topic / Practical               | Folder                                        | Files Included                                                      |
| --- | ------------------------------- | --------------------------------------------- | ------------------------------------------------------------------- |
| 1   | **TCP Server**                  | `TCP server/`                                 | `tcp_server.c`, `theory.txt`                                        |
| 2   | **TCP Client**                  | `TCP client/`                                 | `tcp_client.c`, `theory.txt`                                        |
| 3   | **UDP Server**                  | `UDP server/`                                 | `udp_server.c`, `theory.txt`                                        |
| 4   | **UDP Client**                  | `UDP client/`                                 | `udp_client.c`, `theory.txt`                                        |
| 5   | **DNS Analysis**                | `Application layer Packet (DNS)/`             | `dns_analysis.sh`, `wireshark_guide.txt`, `theory.txt`              |
| 6   | **Packet Analysis (Wireshark)** | `Packet analysis using a packet tracer tool/` | `generate_traffic.sh`, `wireshark_analysis_guide.txt`, `theory.txt` |
| 7   | **Sliding Window Protocol**     | `Sliding window protocol/`                    | `sliding_window.c`, `theory.txt`                                    |
| 8   | **Leaky Bucket Algorithm**      | `Leaky Bucket Algorithm/`                     | `leaky_bucket.c`, `theory.txt`                                      |
| 9   | **Token Bucket Algorithm**      | `Token Bucket Algorithm/`                     | `token_bucket.c`, `theory.txt`                                      |
| 10  | **Distance Vector Algorithm**   | `Distance Vector Algorithm/`                  | `distance_vector.c`, `theory.txt`                                   |

---

## Quick Execution Guide (Ubuntu Terminal)

### 1. TCP Server & Client

**Terminal 1 (Server):**

```bash
cd "TCP server"
gcc tcp_server.c -o tcp_server
./tcp_server
```

**Terminal 2 (Client):**

```bash
cd "TCP client"
gcc tcp_client.c -o tcp_client
./tcp_client
```

---

### 2. UDP Server & Client

**Terminal 1 (Server):**

```bash
cd "UDP server"
gcc udp_server.c -o udp_server
./udp_server
```

**Terminal 2 (Client):**

```bash
cd "UDP client"
gcc udp_client.c -o udp_client
./udp_client
```

---

### 3. Application Layer Packet (DNS)

```bash
cd "Application layer Packet (DNS)"
chmod +x dns_analysis.sh
./dns_analysis.sh
```

---

### 4. Packet Analysis (Wireshark)

1. Start Wireshark: `wireshark &`
2. Select your interface and click **Start**.
3. Generate traffic:

```bash
cd "Packet analysis using a packet tracer tool"
chmod +x generate_traffic.sh
./generate_traffic.sh
```

4. Filter by `dns`, `http`, `tcp`, `udp`, `arp`, or `icmp` in Wireshark.

---

### 5. Sliding Window Protocol

```bash
cd "Sliding window protocol"
gcc sliding_window.c -o sliding_window
./sliding_window
```

---

### 6. Leaky Bucket Algorithm

```bash
cd "Leaky Bucket Algorithm"
gcc leaky_bucket.c -o leaky_bucket
./leaky_bucket
```

---

### 7. Token Bucket Algorithm

```bash
cd "Token Bucket Algorithm"
gcc token_bucket.c -o token_bucket
./token_bucket
```

---

### 8. Distance Vector Routing Algorithm

```bash
cd "Distance Vector Algorithm"
gcc distance_vector.c -o distance_vector
./distance_vector
```


---

## 🌐 Running on Two Different Computers (LAN / Wi-Fi)

To run the Server on **Computer A** and the Client on **Computer B**:

1. **Find Server IP (Computer A):**
   ```bash
   hostname -I
   # Example output: 192.168.1.15
   ```

2. **Allow Firewall Port on Server (if needed):**
   ```bash
   sudo ufw allow 8080/tcp    # For TCP Server
   sudo ufw allow 9090/udp    # For UDP Server
   ```

3. **Update Client Code (Computer B):**
   In `tcp_client.c` (or `udp_client.c`), replace `"127.0.0.1"` with the Server's IP:
   ```c
   inet_pton(AF_INET, "192.168.1.15", &server_address.sin_addr);
   ```

4. **Verify Connectivity & Run:**
   ```bash
   # From Computer B, ping Computer A:
   ping 192.168.1.15

   # Run client:
   gcc tcp_client.c -o tcp_client && ./tcp_client
   ```
