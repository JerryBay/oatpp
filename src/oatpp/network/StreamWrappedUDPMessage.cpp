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

#include "StreamWrappedUDPMessage.hpp"

#include <utility>

namespace oatpp { namespace network {

StreamWrappedUDPMessage::StreamWrappedUDPMessage(std::shared_ptr<InputUDPMessage> imsg,
                                                 std::shared_ptr<OutputUDPMessage> omsg)
                                                 : m_imsg(imsg)
                                                 , m_omsg(omsg) {

}

v_io_size StreamWrappedUDPMessage::write(const void *buff, v_buff_size count, async::Action &action) {
  if (m_omsg->getSize() == UDPMessage::MAX_UDP_PAYLOAD) {
    return -ENOMEM;
  }

  if (m_omsg->getSize() + count > UDPMessage::MAX_UDP_PAYLOAD) {
    count = UDPMessage::MAX_UDP_PAYLOAD - m_omsg->getSize();
  }

  m_omsg->append((p_char8)buff, count);
  return count;
}

v_io_size StreamWrappedUDPMessage::read(void *buff, v_buff_size count, async::Action &action) {
  if (m_imsg->getSize() < (m_msgPtr + count)) {
    count =m_imsg->getSize() - m_msgPtr;
  }

  memcpy(buff, m_imsg->getData() + m_msgPtr, count);
  m_msgPtr += count;
  return count;
}

///////////////////////////////////////////////////////////////////////////////////
/// Default IOStream related stuff

oatpp::data::stream::DefaultInitializedStreamContext StreamWrappedUDPMessage::DEFAULT_CONTEXT(data::stream::StreamType::STREAM_FINITE);

void StreamWrappedUDPMessage::setOutputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode StreamWrappedUDPMessage::getOutputStreamIOMode() {
  return m_mode;
}

data::share::Context &StreamWrappedUDPMessage::getOutputStreamContext() {
  return DEFAULT_CONTEXT;
}

void StreamWrappedUDPMessage::setInputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode StreamWrappedUDPMessage::getInputStreamIOMode() {
  return m_mode;
}
data::share::Context &StreamWrappedUDPMessage::getInputStreamContext() {
  return DEFAULT_CONTEXT;
}

}}