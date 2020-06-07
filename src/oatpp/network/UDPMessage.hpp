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

#ifndef oatpp_network_UDPMessage_hpp
#define oatpp_network_UDPMessage_hpp

#include <sys/socket.h>

#include "oatpp/core/Types.hpp"
#include "oatpp/core/data/share/Context.hpp"
#include "oatpp/core/data/message/Message.hpp"

namespace oatpp { namespace network {

class UDPMessage : public oatpp::data::message::IOMessage {
 private:
  struct sockaddr_storage m_clientAddress;
  static oatpp::data::share::DefaultInitializedContext DEFAULT_CONTEXT;
  v_io_handle m_handle;

 public:

  /**
   * Constructor.
   */
  explicit UDPMessage(oatpp::v_io_handle handle);

  /**
   * Flushing the data just before this connection is dropped (i.E. all data written).
   */
  ~UDPMessage();

  /**
   * Clears the output buffer and writes it to the Network-Stream
   */
  void flush();

  /**
   * Reads all data from the message and puts it into `m_in`.
   * @return read bytes
   */
  v_io_size populate();
};

}}

#endif //oatpp_network_UDPMessage_hpp
