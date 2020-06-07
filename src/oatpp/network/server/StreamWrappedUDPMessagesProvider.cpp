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

#include "oatpp/network/UDPMessage.hpp"
#include "oatpp/network/StreamWrappedUDPMessage.hpp"
#include "StreamWrappedUDPMessagesProvider.hpp"

namespace oatpp { namespace network { namespace server {

StreamWrappedUDPMessagesProvider::StreamWrappedUDPMessagesProvider(const std::shared_ptr<MessageProvider> &msgProvider)
  : m_msgprov(msgProvider) {

}

std::shared_ptr<ConnectionProvider::IOStream> StreamWrappedUDPMessagesProvider::getConnection() {
  auto imsg = std::static_pointer_cast<UDPMessage>(m_msgprov->getMessage());
  if (imsg == nullptr) {
    return nullptr;
  }
  auto omsg = imsg->copyRecipient();
  return StreamWrappedUDPMessage::createShared(imsg, omsg);
}

}}}