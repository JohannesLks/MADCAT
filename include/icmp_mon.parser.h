/*******************************************************************************
This file is part of MADCAT, the Mass Attack Detection Acceptance Tool.
    MADCAT is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    MADCAT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with MADCAT.  If not, see <http://www.gnu.org/licenses/>.

 Diese Datei ist Teil von MADCAT, dem Mass Attack Detection Acceptance Tool.
    MADCAT ist Freie Software: Sie können es unter den Bedingungen
    der GNU General Public License, wie von der Free Software Foundation,
    Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
    veröffentlichten Version, weiter verteilen und/oder modifizieren.
    MADCAT wird in der Hoffnung, dass es nützlich sein wird, aber
    OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
    Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
    Siehe die GNU General Public License für weitere Details.
    Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
    Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
*******************************************************************************/
/* MADCAT - Mass Attack Detecion Connection Acceptance Tool
 * ICMP monitor parser headerfile.
 *
 * Netfilter should be configured to block outgoing ICMP Destination unreachable (Port unreachable) packets, e.g.:
 *      iptables -I OUTPUT -p icmp --icmp-type destination-unreachable -j DROP
 *
 * BSI 2018-2023
*/


#ifndef ICMP_MON_PARSER_H
#define ICMP_MON_PARSER_H

#include "icmp_mon.h"
/**
 * \brief Parse IP Options
 *
 *     Parses IP Options and returns false in case of an error.
 *
 * \param opt_cpclno Option Number as defined by IANA
 * \param opt_name Option Name
 * \param opt_ptr_ptr Pointer to options number in raw data
 * \param beginofoptions_addr Beginning Address of options
 * \param endofoptions_addr End Address of options
 * \param json if set to NULL, the global json_dict(...) function is used to obtain dictionary, else a new dict spawned by dict_new(...) shall be passed and data is returned using this pointer
 *
 * \return true for success, fals in case of an error.
 *
 */
bool parse_ipopt(int opt_cpclno, \
                 const char* opt_name, \
                 unsigned char** opt_ptr_ptr, \
                 const unsigned char* beginofoptions_addr, \
                 const unsigned char* endofoptions_addr, \
                 struct dict** json);

/**
  * \brief Parse and analyze IP Header
  *
  *     Parses and analyzes a IP Header
  *
  * \param packet Pointer to the raw packet data
  * \param caplen length of raw packet data
  * \param json if set to NULL, the global json_dict(...) function is used to obtain dictionary, else a new dict spawned by dict_new(...) shall be passed and data is returned using this pointer
  *
  * \return true for success, fals in case of an error.
  *
  */
bool analyze_ip_header(const unsigned char* packet, int recv_len, struct dict** json);

/**
  * \brief Parse TCP Options
  *
  *     Parses TCP Options and returns false in case of an error.
  *
  * \param opt_kind Option Number as defined by IANA/RFCs
  * \param opt_len Option length as defined by IANA/RFCs
  * \param opt_name Option Name
  * \param opt_ptr_ptr Pointer to options number in raw data
  * \param beginofoptions_addr Beginning Address of options
  * \param endofoptions_addr End Address of options
  * \param json if set to NULL, the global json_dict(...) function is used to obtain dictionary, else a new dict spawned by dict_new(...) shall be passed and data is returned using this pointer
  *
  * \return true for success, fals in case of an error.
  *
  */
bool parse_tcpopt_w_length(int opt_kind, int opt_len, \
                           const char* opt_name, \
                           unsigned char** opt_ptr_ptr, \
                           const unsigned char* beginofoptions_addr, \
                           const unsigned char* endofoptions_addr, \
                           struct dict** json);

/**
  * \brief Parse and analyze UDP Header
  *
  *     Parses and analyzes a UDP Header
  *
  * \param packet Pointer to the raw packet data
  * \param caplen length of raw packet data
  * \param json if set to NULL, the global json_dict(...) function is used to obtain dictionary, else a new dict spawned by dict_new(...) shall be passed and data is returned using this pointer
  *
  * \return Number of bytes in UDP Payload, <0 in case of an error.
  *
  */
int analyze_udp_header(const unsigned char* packet, int recv_len, struct dict** json);

/**
  * \brief Parse and analyze TCP Header
  *
  *     Parses and analyzes a TCP Header
  *
  * \param packet Pointer to the raw packet data
  * \param caplen length of raw packet data
  * \param json if set to NULL, the global json_dict(...) function is used to obtain dictionary, else a new dict spawned by dict_new(...) shall be passed and data is returned using this pointer
  *
  * \return Number of bytes in TCP Payload, <0 in case of an error.
  *
  */
int analyze_tcp_header(const unsigned char* packet, int recv_len, struct dict** json);

/**
  * \brief Parse TCP Options
  *
  *     Parses TCP Options and returns false in case of an error.
  *
  * \param opt_kind Option Number as defined by IANA/RFCs
  * \param opt_len Option length as defined by IANA/RFCs
  * \param opt_name Option Name
  * \param opt_ptr_ptr Pointer to options number in raw data
  * \param beginofoptions_addr Beginning Address of options
  * \param endofoptions_addr End Address of options
  * \param json if set to NULL, the global json_dict(...) function is used to obtain dictionary, else a new dict spawned by dict_new(...) shall be passed and data is returned using this pointer
  *
  * \return true for success, fals in case of an error.
  *
  */
bool parse_tcpopt_w_length(int opt_kind, int opt_len, const char* opt_name, \
                           unsigned char** opt_ptr_ptr, const unsigned char* beginofoptions_addr, const unsigned char* endofoptions_addr, struct dict** json);
#endif
