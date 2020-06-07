/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *                         Benedikt-Alexander Mokroß <oatpp@bamkrs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include <netinet/in.h>
#include "UDPMessage.hpp"

#define MAX_UDP_PAYLOAD_SIZE 65507

namespace oatpp { namespace network {

oatpp::data::share::DefaultInitializedContext UDPMessage::DEFAULT_CONTEXT;

UDPMessage::UDPMessage(oatpp::v_io_handle handle) : IOMessage() {

}

UDPMessage::~UDPMessage() {

}

void UDPMessage::flush() {
  ssize_t rc;

  // Do we care if the call fails? Probably not, its UDP
  // so don't escalate or throw anything if sendto fails.
  if (m_clientAddress.ss_family == AF_INET) {
    struct sockaddr_in cliaddr;
    memcpy(&cliaddr, &m_clientAddress, sizeof(cliaddr));
    rc = sendto(m_handle, (const char *) getData(), getSize(), 0,
                (struct sockaddr *) &cliaddr, sizeof(cliaddr));
  } else if(m_clientAddress.ss_family == AF_INET6) {
    struct sockaddr_in6 cliaddr;
    memcpy(&cliaddr, &m_clientAddress, sizeof(cliaddr));
    rc = sendto(m_handle, (const char *) getData(), getSize(), 0,
                (struct sockaddr *) &cliaddr, sizeof(cliaddr));
  } else {
    OATPP_LOGE("[oatpp::network::UDPMessage::flush()]", "Error. Unknown ss_family");
    throw std::runtime_error("[oatpp::network::UDPMessage::flus()]: Error. Unknown ss_family.");
  }

  // But at least print this error message...
  if (rc < 0) {
    OATPP_LOGE("[oatpp::network::UDPMessage::flush()]","Error: %s (%d)",strerror(errno), errno);
  }

  // Clear up data and set to 0 before to not leave any sensitive things in memory
  memset(getData(), 0, getSize());
  resize(0);
}

v_io_size UDPMessage::populate() {
  // Allocate buffer
  grow(MAX_UDP_PAYLOAD_SIZE);

  // Prepare the memory to save the senders details
  socklen_t clientAddressSize = sizeof(m_clientAddress);
  memset(&m_clientAddress, 0, clientAddressSize);

  // Read the whole message (as long as the buffer is sufficient).
  // In this case we are safe because there is a hard UDP payload limit.
  // Also we are saving the senders details so we can address it for our response
  ssize_t rc = recvfrom(m_handle, (char *) getData(), MAX_UDP_PAYLOAD_SIZE,
                        MSG_WAITALL, (struct sockaddr *) &m_clientAddress,
                        &clientAddressSize);

  if (rc < 0) {
    OATPP_LOGE("[oatpp::network::UDPMessage::populate()]", "Error. recv failed: %s (%d)", strerror(errno), errno);
    throw std::runtime_error("[oatpp::network::UDPMessage::populate()]: Error. recv failed.");
  }

  // Resize the buffer to the actual amount of data.
  // This is important to save RAM and correct readout later on in `read()`.
  resize(rc);

  return rc;
}

}}
