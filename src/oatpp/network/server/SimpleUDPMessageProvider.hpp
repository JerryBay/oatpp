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

#ifndef oatpp_netword_server_SimpleUDPMessageProvider_hpp
#define oatpp_netword_server_SimpleUDPMessageProvider_hpp

#include "oatpp/network/MessageProvider.hpp"
#include "oatpp/network/UDPMessage.hpp"

#include "oatpp/core/Types.hpp"

namespace oatpp { namespace network { namespace server {

/**
 * Simple provider of Buffered UDP connections.
 */
class SimpleUDPMessageProvider : public base::Countable, public MessageProvider {
 public:

 private:
  v_uint16 m_port;
  std::atomic<bool> m_closed;
  oatpp::v_io_handle m_serverHandle;

 protected:
  oatpp::v_io_handle getHandle();

 private:
  oatpp::v_io_handle instantiateServer();

 public:

  /**
   * Constructor.
   * @param port - port to listen for incoming messages.
   * `false` to use &id:oatpp::network::Connection;.
   */
  SimpleUDPMessageProvider(v_uint16 port);
 public:

  /**
   * Create shared SimpleUDPMessageProvider.
   * @param port - port to listen for incoming connections.
   * @return - `std::shared_ptr` to SimpleUDPMessageProvider.
   */
  static std::shared_ptr<SimpleUDPMessageProvider> createShared(v_uint16 port){
    return std::make_shared<SimpleUDPMessageProvider>(port);
  }

  /**
   * Virtual destructor.
   */
  ~SimpleUDPMessageProvider();

  /**
   * Close accept-socket.
   */
  void close() override;

  /**
   * Get incoming connection.
   * @return &id:oatpp::data::message::IOMessage;.
   */
  std::shared_ptr<IOMessage> getMessage() override;

  /**
   * No need to implement this.<br>
   * For Asynchronous IO in oatpp it is considered to be a good practice
   * to accept connections in a seperate thread with the blocking accept()
   * and then process connections in Asynchronous manner with non-blocking read/write.
   * <br>
   * *It may be implemented later*
   */
  oatpp::async::CoroutineStarterForResult<const std::shared_ptr<oatpp::data::message::IOMessage>&> getMessageAsync() override {
    /*
     *  No need to implement this.
     *  For Asynchronous IO in oatpp it is considered to be a good practice
     *  to accept connections in a seperate thread with the blocking accept()
     *  and then process connections in Asynchronous manner with non-blocking read/write
     *
     *  It may be implemented later
     */
    throw std::runtime_error("[oatpp::network::server::SimpleUDPMessageProvider::getMessageAsync()]: Error. Not implemented.");
  }

  /**
   * Call shutdown read and write on an underlying file descriptor.
   * `connection` **MUST** be an object previously obtained from **THIS** connection provider.
   * @param connection
   */
  void invalidateMessage(const std::shared_ptr<IOMessage>& connection) override;

  /**
   * Get port.
   * @return
   */
  v_uint16 getPort(){
    return m_port;
  }

};

}}}

#endif /* oatpp_netword_server_SimpleUDPMessageProvider_hpp */