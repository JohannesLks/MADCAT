#!/bin/bash
#Set iptables rules for TCP- and UDP-Modules
sudo iptables -t nat -A PREROUTING -i enp0s8 -p tcp --dport 1:65534 -j DNAT --to 192.168.1.100:65535
sudo iptables -I OUTPUT -p icmp --icmp-type destination-unreachable -j DROP
# Stelle sicher, dass FIFO sauber vorhanden ist
FIFO="/tmp/logs.erm"
rm -f "$FIFO"
mkfifo "$FIFO"

# Starte Enrichment Processor → liest von FIFO, schreibt JSON in Datei
/usr/bin/python3 /opt/madcat/enrichment_processor.py /etc/madcat/config.lua \
  >> /data/enriched.json.log 2>> /data/error.enrichment.log &

# Kurze Wartezeit, damit FIFO geöffnet wird
sleep 1

# Starte UDP-, ICMP- und RAW-Module → schreiben ins FIFO
/opt/madcat/udp_ip_port_mon /etc/madcat/config.lua \
  >> "$FIFO" 2>> /data/error.udp.log &

/opt/madcat/icmp_mon /etc/madcat/config.lua \
  >> "$FIFO" 2>> /data/error.icmp.log &

/opt/madcat/raw_mon /etc/madcat/config.lua \
  >> "$FIFO" 2>> /data/error.raw.log &

# Starte TCP-Module → schreibt NICHT direkt ins FIFO
/opt/madcat/tcp_ip_port_mon /etc/madcat/config.lua \
  >> /dev/null 2>> /data/error.tcp.log &

# Kurze Wartezeit, damit FIFO-Dateien erstellt werden
sleep 1

# Starte Postprocessor → schreibt ins FIFO
/usr/bin/python3 /opt/madcat/tcp_ip_port_mon_postprocessor.py /etc/madcat/config.lua \
  >> "$FIFO" 2>> /data/error.postprocessor.log &