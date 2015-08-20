/**
 ******************************************************************************
 * @file    spark_wiring_udp.h
 * @author  Satish Nair
 * @version V1.0.0
 * @date    13-March-2013
 * @brief   Header for spark_wiring_udp.cpp module
 ******************************************************************************
  Copyright (c) 2013-2015 Particle Industries, Inc.  All rights reserved.
  Copyright (c) 2008 Bjoern Hartmann

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */

#ifndef __SPARK_WIRING_UDP_H
#define __SPARK_WIRING_UDP_H

#include "spark_wiring.h"
#include "spark_wiring_printable.h"
#include "spark_wiring_stream.h"
#include "socket_hal.h"

#define RX_BUF_MAX_SIZE	512

class UDP : public Stream, public Printable {
private:
	sock_handle_t _sock;
	uint16_t _port;
	IPAddress _remoteIP;
	uint16_t _remotePort;
	sockaddr_t _remoteSockAddr;
	socklen_t _remoteSockAddrLen;
	uint8_t _buffer[RX_BUF_MAX_SIZE];
	uint16_t _offset;
        uint16_t _total;
        network_interface_t _nif;
public:
	UDP();

	virtual uint8_t begin(uint16_t, network_interface_t nif=0);
	virtual void stop();
	virtual int beginPacket(IPAddress ip, uint16_t port);
	virtual int beginPacket(const char *host, uint16_t port);
	virtual int endPacket();
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buffer, size_t size);
	virtual int parsePacket();
	virtual int available();
	virtual int read();
	virtual int read(unsigned char* buffer, size_t len);
	virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };
	virtual int peek();
	virtual void flush();
	virtual IPAddress remoteIP() { return _remoteIP; };
	virtual uint16_t remotePort() { return _remotePort; };

        /**
         * Prints the current read parsed packet to the given output.
         * @param p
         * @return
         */
        virtual size_t printTo(Print& p) const;

	/*
	 * Join a multicast address for all UDP sockets. This will allow reception of multicast packets
	 * sent to the given address for on UDP sockets which have bound the port to which the multicast
	 * packet was sent.
	 * @param addr IP multicast address to join
	 * @return Return the result of the join operation
	 */
	static int joinMulticast(const IPAddress& ip);

	/*
	 * Leave a multicast address previously joined with socket_join_multicast.
	 * @param addr IP multicast address to leave
	 * @return Return the result of the leave operation
	 */
	static int leaveMulticast(const IPAddress& ip);

	using Print::write;
};

#endif
