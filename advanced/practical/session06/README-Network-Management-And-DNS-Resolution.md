# Network Management and DNS Resolution in Linux

This README provides comprehensive information and examples on network management and DNS resolution in Linux, covering tools like `nmcli`, `resolvectl`, `cat /etc/resolv.conf`, and DNS hierarchy, including root servers, top-level domains, and authoritative name servers.

# Table of Contents

1. [Network Management with `nmcli`](#network-management-with-nmcli)
    - [Displaying Device Information](#displaying-device-information)
    - [Examples](#examples)
2. [DNS Resolution with `resolvectl`](#dns-resolution-with-resolvectl)
    - [Display DNS Server Information](#display-dns-server-information)
    - [Examples](#examples-1)
3. [Viewing DNS Configuration with `cat /etc/resolv.conf`](#viewing-dns-configuration-with-cat-etcresolvconf)
    - [View DNS Configuration](#view-dns-configuration)
    - [Example Output](#example-output)
4. [DNS Hierarchy](#dns-hierarchy)
    - [DNS Hierarchy Levels](#dns-hierarchy-levels)
    - [Authoritative Name Servers](#authoritative-name-servers)
    - [DNS Resolution Flow](#dns-resolution-flow)
5. [DNS Record Types](#dns-record-types)
    - [Common DNS Record Types](#common-dns-record-types)
    - [Example DNS Record Configuration](#example-dns-record-configuration)
6. [DNS Tools](#dns-tools)
    - [`dig` (Domain Information Groper)](#dig-domain-information-groper)
        - [Example Usage](#example-usage)
        - [Example Output and Explanation](#example-output-and-explanation)
    - [`nslookup`](#nslookup)
        - [Example Usage](#example-usage-1)
    - [`host`](#host)
        - [Example Usage](#example-usage-2)
    - [Practical Examples](#practical-examples)
        - [Using `dig` to Query DNS Records](#using-dig-to-query-dns-records)
        - [Using `nslookup` to Query DNS](#using-nslookup-to-query-dns)
        - [Additional `dig` Options](#additional-dig-options)
    - [Using `resolvectl` for Advanced DNS Management](#using-resolvectl-for-advanced-dns-management)
7. [DNS Caching](#dns-caching)
    - [What is DNS Caching?](#what-is-dns-caching)
    - [How to Clear DNS Cache](#how-to-clear-dns-cache)
8. [DNS Security](#dns-security)
    - [Common DNS Security Issues](#common-dns-security-issues)
    - [Securing DNS](#securing-dns)
        - [Enable DNSSEC on BIND DNS Server](#enable-dnssec-on-bind-dns-server)
9. [DNS over HTTPS (DoH) and DNS over TLS (DoT)](#dns-over-https-doh-and-dns-over-tls-dot)
    - [What is DoH and DoT?](#what-is-doh-and-dot)
    - [Configuring DoH and DoT](#configuring-doh-and-dot)
10. [Summary](#summary)
11. [Additional Resources](#additional-resources)
12. [Example `resolv.conf` Configuration for Static DNS](#example-resolvconf-configuration-for-static-dns)
13. [Troubleshooting DNS Issues](#troubleshooting-dns-issues)
14. [Conclusion](#conclusion)

---

## Network Management with `nmcli`

`nmcli` is a command-line tool for managing NetworkManager and reporting network status.

### Displaying Device Information

To show detailed information about all devices:

```sh
nmcli dev show
```

To filter and display only DNS information:

```sh
nmcli dev show | grep 'IP4.DNS'
```

### Examples

1. **Show all devices and their statuses:**

    ```sh
    nmcli dev status
    ```

2. **Connect to a Wi-Fi network:**

    ```sh
    nmcli dev wifi connect SSID_NAME password YOUR_PASSWORD
    ```

3. **Disconnect a device:**

    ```sh
    nmcli dev disconnect iface INTERFACE_NAME
    ```

4. **Get connection details:**

    ```sh
    nmcli connection show CONNECTION_NAME
    ```

## DNS Resolution with `resolvectl`

`resolvectl` (or `systemd-resolve`) is used to resolve domain names, IPv4 and IPv6 addresses, DNS resource records, and services.

### Display DNS Server Information

To show detailed information about the DNS servers currently in use:

```sh
resolvectl status
```

### Examples

1. **Query an IP address:**

    ```sh
    resolvectl query example.com
    ```

2. **Show DNS server statistics:**

    ```sh
    resolvectl statistics
    ```

3. **Flush DNS cache:**

    ```sh
    resolvectl flush-caches
    ```

## Viewing DNS Configuration with `cat /etc/resolv.conf`

The `/etc/resolv.conf` file contains information that is used by the resolver to translate hostnames into IP addresses.

### View DNS Configuration

To view the contents of `/etc/resolv.conf`:

```sh
cat /etc/resolv.conf
```

### Example Output

```plaintext
# This is /run/systemd/resolve/stub-resolv.conf managed by man:systemd-resolved(8).
# Do not edit.
#
# This file might be symlinked as /etc/resolv.conf. If you're looking at
# /etc/resolv.conf and seeing this text, you have followed the symlink.
#
# This is a dynamic resolv.conf file for connecting local clients to the
# internal DNS stub resolver of systemd-resolved. This file lists all
# configured search domains.
#
# Run "resolvectl status" to see details about the uplink DNS servers
# currently in use.
#
# Third party programs should typically not access this file directly, but only
# through the symlink at /etc/resolv.conf. To manage man:resolv.conf(5) in a
# different way, replace this symlink by a static file or a different symlink.
#
# See man:systemd-resolved.service(8) for details about the supported modes of
# operation for /etc/resolv.conf.

nameserver 127.0.0.53
options edns0 trust-ad
search .
```

## DNS Hierarchy

The Domain Name System (DNS) is a hierarchical and distributed naming system for computers, services, or other resources connected to the internet or a private network. It translates human-readable domain names to IP addresses.

### DNS Hierarchy Levels

1. **Root Level**

    - The root level is the top of the DNS hierarchy.
    - Managed by the root name servers, which are a small number of authoritative servers.
    - Represented by a dot (`.`).

2. **Top-Level Domain (TLD) Level**

    - Directly below the root in the DNS hierarchy.
    - Includes generic TLDs (gTLDs) like `.com`, `.org`, `.net` and country code TLDs (ccTLDs) like `.uk`, `.de`, `.jp`.

3. **Second-Level Domain (SLD) Level**

    - Below the TLDs, these are typically what people refer to as domain names (e.g., `example.com`).

4. **Subdomain Level**

    - Any domain that is a part of a larger domain. For example, `www.example.com` or `mail.example.com`.

### Authoritative Name Servers

- These servers provide answers to queries about domain names that are stored in the corresponding zone file.
- They are responsible for the specific domains and subdomains.

### DNS Resolution Flow

1. **Client Query**: The client (e.g., a web browser) queries a DNS resolver (e.g., provided by your ISP or a public DNS server like Google DNS or Cloudflare DNS).
2. **Root Name Server**: If the resolver doesn't have the answer cached, it queries a root name server.
3. **TLD Name Server**: The root name server responds with the address of a TLD name server.
4. **Authoritative Name Server**: The TLD name server responds with the address of an authoritative name server for the specific domain.
5. **Response to Resolver**: The authoritative name server responds with the IP address for the domain.
6. **Response to Client**: The resolver caches the response and sends it to the client.

## DNS Record Types

### Common DNS Record Types

1. **A Record**: Maps a domain name to an IPv4 address.
2. **AAAA Record**: Maps a domain name to an IPv6 address.
3. **CNAME Record**: Maps a domain name to another domain name (canonical name).
4. **MX Record**: Specifies the mail exchange servers for a domain.
5. **NS Record**: Specifies the authoritative name servers for a domain.
6. **TXT Record**: Stores text information associated with a domain.
7. **SOA Record**: Start of Authority record, provides administrative information about the domain.
8. **PTR Record**: Pointer record, maps an IP address to a domain name (reverse DNS lookup).

### Example DNS Record Configuration

#### Example `example.com` DNS Zone File

```plaintext
$TTL 86400
@   IN  SOA ns1.example.com. admin.example.com. (
            2021071501 ; Serial
            3600       ; Refresh


            1800       ; Retry
            1209600    ; Expire
            86400      ; Minimum TTL
            )
    IN  NS  ns1.example.com.
    IN  NS  ns2.example.com.
    IN  A   93.184.216.34
www IN  CNAME example.com.
mail IN  MX  10 mail.example.com.
mail IN  A   93.184.216.35
```

## DNS Tools

### `dig` (Domain Information Groper)

`dig` is a flexible command-line tool for querying DNS name servers.

#### Example Usage

```sh
dig example.com
```

#### Example Output and Explanation

1. **Query A Record**:
    ```plaintext
    mahmoud@mahmoud:~$ dig google.com A
    
    ; <<>> DiG 9.18.28-0ubuntu0.22.04.1-Ubuntu <<>> google.com A
    ;; global options: +cmd
    ;; Got answer:
    ;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 12637
    ;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 1

    ;; OPT PSEUDOSECTION:
    ; EDNS: version: 0, flags:; udp: 65494
    ;; QUESTION SECTION:
    ;google.com.                    IN      A

    ;; ANSWER SECTION:
    google.com.             292     IN      A       142.250.203.238

    ;; Query time: 36 msec
    ;; SERVER: 127.0.0.53#53(127.0.0.53) (UDP)
    ;; WHEN: Sun Jul 28 16:10:07 EEST 2024
    ;; MSG SIZE  rcvd: 55
    ```
    **Headers Info**
    - **HEADER**: Shows the query details including opcode (QUERY), status (NOERROR), and ID.
    - **QUESTION SECTION**: The domain and record type queried.
    - **ANSWER SECTION**: The response, indicating `google.com` uses `smtp.google.com` as its mail server with priority 10.
    - **Query time**: Time taken to get the response.
    - **SERVER**: The DNS server used for the query.
    - **WHEN**: The time the query was made.
    - **MSG SIZE rcvd**: The size of the response message.
   
    **Explanation**: This query requests the A record for `google.com`, which maps the domain name to an IPv4 address. The answer section shows the IP address `142.250.203.238`.

3. **Query NS Record**:
    ```plaintext
    mahmoud@mahmoud:~$ dig google.com NS
    
    ; <<>> DiG 9.18.28-0ubuntu0.22.04.1-Ubuntu <<>> google.com NS
    ;; global options: +cmd
    ;; Got answer:
    ;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 51896
    ;; flags: qr rd ra; QUERY: 1, ANSWER: 4, AUTHORITY: 0, ADDITIONAL: 1

    ;; OPT PSEUDOSECTION:
    ; EDNS: version: 0, flags:; udp: 65494
    ;; QUESTION SECTION:
    ;google.com.                    IN      NS

    ;; ANSWER SECTION:
    google.com.             42311   IN      NS      ns2.google.com.
    google.com.             42311   IN      NS      ns4.google.com.
    google.com.             42311   IN      NS      ns1.google.com.
    google.com.             42311   IN      NS      ns3.google.com.

    ;; Query time: 32 msec
    ;; SERVER: 127.0.0.53#53(127.0.0.53) (UDP)
    ;; WHEN: Sun Jul 28 16:13:50 EEST 2024
    ;; MSG SIZE  rcvd: 111
    ```
    **Headers Info**
    - **HEADER**: Shows the query details including opcode (QUERY), status (NOERROR), and ID.
    - **QUESTION SECTION**: The domain and record type queried.
    - **ANSWER SECTION**: The response, indicating `google.com` uses `smtp.google.com` as its mail server with priority 10.
    - **Query time**: Time taken to get the response.
    - **SERVER**: The DNS server used for the query.
    - **WHEN**: The time the query was made.
    - **MSG SIZE rcvd**: The size of the response message.
   
    **Explanation**: This query requests the NS records for `google.com`, which specify the authoritative name servers for the domain. The answer section lists four name servers: `ns1.google.com`, `ns2.google.com`, `ns3.google.com`, and `ns4.google.com`.

4. **Query CNAME Record**:
    ```plaintext
    $ dig www.github.com CNAME
    
    ; <<>> DiG 9.18.28-0ubuntu0.22.04.1-Ubuntu <<>> www.github.com CNAME
    ;; global options: +cmd
    ;; Got answer:
    ;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 42710
    ;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 1
    
    ;; OPT PSEUDOSECTION:
    ; EDNS: version: 0, flags:; udp: 65494
    ;; QUESTION SECTION:
    ;www.github.com.               IN      CNAME
    
    ;; ANSWER SECTION:
    www.github.com.        600     IN      CNAME   github.com.
    
    ;; Query time: 32 msec
    ;; SERVER: 127.0.0.53#53(127.0.0.53) (UDP)
    ;; WHEN: Sun Jul 28 16:10:07 EEST 2024
    ;; MSG SIZE  rcvd: 70
    ```
    
    **Headers Info**
    - **HEADER**: Shows the query details including opcode (QUERY), status (NOERROR), and ID.
    - **QUESTION SECTION**: The domain and record type queried.
    - **ANSWER SECTION**: The response, indicating `google.com` uses `smtp.google.com` as its mail server with priority 10.
    - **Query time**: Time taken to get the response.
    - **SERVER**: The DNS server used for the query.
    - **WHEN**: The time the query was made.
    - **MSG SIZE rcvd**: The size of the response message.

    **Explanation**: This query requests the CNAME record for `www.github.com`. The answer section indicates that `www.github.com` is an alias for `github.com`. When accessing `www.github.com`, it will redirect to `github.com`, and the resolver will then look up the A record for `github.com` to get the final IP address. This setup ensures that both `www.github.com` and `github.com` direct users to the same website without needing separate IP addresses.


5. **Query MX Record**:
    ```plaintext
    mahmoud@mahmoud:~$ dig google.com MX
    
    ; <<>> DiG 9.18.28-0ubuntu0.22.04.1-Ubuntu <<>> google.com MX
    ;; global options: +cmd
    ;; Got answer:
    ;; ->>HEADER<<- opcode: QUERY, status: NOERROR, id: 23011
    ;; flags: qr rd ra; QUERY: 1, ANSWER: 1, AUTHORITY: 0, ADDITIONAL: 1

    ;; OPT PSEUDOSECTION:
    ; EDNS: version: 0, flags:; udp: 65494
    ;; QUESTION SECTION:
    ;google.com.                    IN      MX

    ;; ANSWER SECTION:
    google.com.             204     IN      MX      10 smtp.google.com.

    ;; Query time: 40 msec
    ;; SERVER: 127.0.0.53#53(127.0.0.53) (UDP)
    ;; WHEN: Sun Jul 28 16:09:32 EEST 2024
    ;; MSG SIZE  rcvd: 60
    ```

    **Headers Info**
    - **HEADER**: Shows the query details including opcode (QUERY), status (NOERROR), and ID.
    - **QUESTION SECTION**: The domain and record type queried.
    - **ANSWER SECTION**: The response, indicating `google.com` uses `smtp.google.com` as its mail server with priority 10.
    - **Query time**: Time taken to get the response.
    - **SERVER**: The DNS server used for the query.
    - **WHEN**: The time the query was made.
    - **MSG SIZE rcvd**: The size of the response message.

    **Explanation**: This query requests the MX record for `google.com`, which specifies the mail exchange server for the domain. The answer section shows the mail server `smtp.google.com` with a priority of 10.

### `nslookup`

`nslookup` is a command-line tool for querying DNS name servers.

#### Example Usage

```sh
nslookup example.com
```

### `host`

`host` is a simple utility for performing DNS lookups.

#### Example Usage

```sh
host example.com
```

### Practical Examples

#### Using `dig` to Query DNS Records

To query different types of DNS records, you can use the `dig` command with specific options.

- **Query A record**:
  ```sh
  dig example.com A
  ```
- **Query MX record**:
  ```sh
  dig example.com MX
  ```
- **Query NS record**:
  ```sh
  dig example.com NS
  ```

#### Using `nslookup` to Query DNS

To perform similar queries using `nslookup`:

- **Query A record**:
  ```sh
  nslookup -type=A example.com
  ```
- **Query MX record**:
  ```sh
  nslookup -type=MX example.com
  ```
- **Query NS record**:
  ```sh
  nslookup -type=NS example.com
  ```

### Additional `dig` Options

- **Query ANY record**:
  ```sh
  dig example.com ANY
  ```
- **Query SOA record**:
  ```sh
  dig example.com SOA
  ```
- **Specify DNS server**:
  ```sh
  dig @8.8.8.8 example.com
  ```

### Using `resolvectl` for Advanced DNS Management

#### Change DNS Server for a Specific Interface

```sh
resolvectl dns eth0 8.8.8.8
```

#### Set Multiple DNS Servers

```sh
resolvectl dns eth0 8.8.8.8 8.8.4.4
```

#### Reset DNS Servers

```sh
resolvectl revert eth0
```

#### Display DNS Server Information

```sh
resolvectl status eth0
```

## DNS Caching

### What is DNS Caching?

DNS caching refers to the process of storing DNS query results temporarily on a local machine or DNS resolver. This helps reduce latency for repeated queries to the same domain by avoiding the need to perform a full DNS lookup each time.

### How to Clear DNS Cache

#### Clear DNS Cache on Local Machine

1. **Linux (systemd-resolved)**:
    ```sh
    resolvectl flush-caches
    ```

2. **macOS**:
    ```sh
    sudo dscacheutil -flushcache; sudo killall -HUP mDNSResponder
    ```

3. **Windows**:
    ```sh
    ipconfig /flushdns
    ``

`

## DNS Security

### Common DNS Security Issues

1. **DNS Spoofing/Poisoning**: An attacker inserts false DNS entries into the cache of a resolver, redirecting traffic to malicious sites.
2. **DNS Amplification Attack**: A type of DDoS attack that exploits DNS servers to flood a target with traffic.
3. **Cache Poisoning**: Inserting incorrect information into the DNS cache, causing users to be directed to incorrect websites.

### Securing DNS

1. **DNSSEC (DNS Security Extensions)**: Adds security to the DNS protocol by enabling DNS responses to be validated.
2. **TSIG (Transaction SIGnature)**: Used to authenticate updates to DNS zones.
3. **Using Secure DNS Resolvers**: Use DNS over HTTPS (DoH) or DNS over TLS (DoT) to encrypt DNS queries and responses.

#### Enable DNSSEC on BIND DNS Server

To enable DNSSEC on a BIND DNS server, add the following lines to the named.conf.options file:

```plaintext
options {
    dnssec-enable yes;
    dnssec-validation auto;
};
```

## DNS over HTTPS (DoH) and DNS over TLS (DoT)

### What is DoH and DoT?

- **DoH**: DNS over HTTPS, sends DNS queries over HTTPS to encrypt the data between the client and the resolver.
- **DoT**: DNS over TLS, sends DNS queries over TLS, providing a similar level of encryption as HTTPS.

### Configuring DoH and DoT

#### Using `cloudflared` for DNS over HTTPS

1. **Install `cloudflared`**:
    ```sh
    sudo apt install cloudflared
    ```

2. **Configure `cloudflared`**:
    ```sh
    sudo cloudflared service install
    ```

3. **Update `/etc/resolv.conf`** to use `cloudflared`:
    ```plaintext
    nameserver 127.0.0.1
    ```

#### Using `stubby` for DNS over TLS

1. **Install `stubby`**:
    ```sh
    sudo apt install stubby
    ```

2. **Configure `stubby`** in `/etc/stubby/stubby.yml`:
    ```yaml
    upstream_recursive_servers:
      - address_data: 1.1.1.1
        tls_auth_name: "cloudflare-dns.com"
    ```

3. **Update `/etc/resolv.conf`** to use `stubby`:
    ```plaintext
    nameserver 127.0.0.1
    ```

## Additional Resources

- **DNS and BIND**: A comprehensive book on DNS management.
- **How DNS Works**: A detailed article explaining the DNS process.
- **NetworkManager Documentation**: Official documentation for NetworkManager.
- **systemd-resolved Documentation**: Official documentation for systemd-resolved.

### Example `resolv.conf` Configuration for Static DNS

To set a static DNS configuration, you can create or edit the `/etc/resolv.conf` file directly (note that this might conflict with dynamic management by systemd-resolved or NetworkManager).

```plaintext
nameserver 8.8.8.8
nameserver 8.8.4.4
search example.com
```

### Troubleshooting DNS Issues

1. **Check `/etc/resolv.conf`**: Ensure it points to the correct DNS servers.
2. **Restart NetworkManager**: Sometimes, restarting NetworkManager can resolve DNS issues.
   ```sh
   sudo systemctl restart NetworkManager
   ```
3. **Clear DNS Cache**: Clear the DNS cache if entries are stale.
   ```sh
   resolvectl flush-caches
   ```

## Conclusion

Managing network connections and DNS settings in Linux can be efficiently handled using `nmcli`, `resolvectl`, `dig`, `nslookup`, and `host`. Understanding the structure and management of `/etc/resolv.conf` further enhances your ability to configure network settings as per your requirements. These tools are essential for network configuration and troubleshooting in a Linux environment.

---

## Summary

Understanding network management and DNS resolution in Linux involves using tools like `nmcli`, `resolvectl`, `dig`, `nslookup`, and examining `/etc/resolv.conf`. Additionally, knowing the DNS hierarchy and how it operates helps in managing and troubleshooting network issues. This guide provides the foundational knowledge and commands necessary for effective network and DNS management on a Linux system.
