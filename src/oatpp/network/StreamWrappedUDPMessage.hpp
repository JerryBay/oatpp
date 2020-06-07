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

#ifndef oatpp_network_StreamWrappedUDPMessage_hpp
#define oatpp_network_StreamWrappedUDPMessage_hpp

#include "oatpp/core/data/stream/Stream.hpp"
#include "oatpp/network/UDPMessage.hpp"

#include <utility>

namespace oatpp { namespace network {

class StreamWrappedUDPMessage : public oatpp::data::stream::IOStream {

 private:
  std::shared_ptr<InputUDPMessage> m_imsg;
  std::shared_ptr<OutputUDPMessage> m_omsg;
  v_io_size m_msgPtr = 0;
  static oatpp::data::stream::DefaultInitializedStreamContext DEFAULT_CONTEXT;
  data::stream::IOMode m_mode;

 public:
  StreamWrappedUDPMessage(std::shared_ptr<InputUDPMessage> imsg, std::shared_ptr<OutputUDPMessage> omsg);

  static std::shared_ptr<StreamWrappedUDPMessage>(std::shared_ptr<InputUDPMessage> imsg, std::shared_ptr<OutputUDPMessage> omsg) {
    return std::make_shared<StreamWrappedUDPMessage>(imsg, omsg);
  }

  /**
   * Override of &id:oatpp::data::stream::IOStream::write. Writes data to a buffer instead of the Network-Stream
   * @param buff - buffer containing data to write.
   * @param count - bytes count you want to write.
   * @param action - async specific action. If action is NOT &id:oatpp::async::Action::TYPE_NONE;, then
   * caller MUST return this action on coroutine iteration.
   * @return - actual amount of bytes written. See &id:oatpp::v_io_size;.
   */
  v_io_size write(const void *buff, v_buff_size count, async::Action &action) final;

  /**
   * Override of &id:oatpp::data::stream::IOStream::write. Reads data from the buffered messages instead of the Network-Stream
   * @param buff - buffer to read data to.
   * @param count - buffer size.
   * @param action - async specific action. If action is NOT &id:oatpp::async::Action::TYPE_NONE;, then
   * caller MUST return this action on coroutine iteration.
   * @return - actual amount of bytes read. See &id:oatpp::v_io_size;.
   */
  v_io_size read(void *buff, v_buff_size count, async::Action &action) final;
  void setOutputStreamIOMode(data::stream::IOMode ioMode) override;
  data::stream::IOMode getOutputStreamIOMode() override;
  data::share::Context &getOutputStreamContext() override;
  void setInputStreamIOMode(data::stream::IOMode ioMode) override;
  data::stream::IOMode getInputStreamIOMode() override;
  data::share::Context &getInputStreamContext() override;

};

}}

#endif //oatpp_network_StreamWrappedUDPMessage_hpp
