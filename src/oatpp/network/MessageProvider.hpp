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

#ifndef oatpp_network_ConnectionsProvider_hpp
#define oatpp_network_ConnectionsProvider_hpp

#include "oatpp/core/data/share/MemoryLabel.hpp"
#include "oatpp/core/data/message/Message.hpp"
#include "oatpp/core/async/Coroutine.hpp"
#include <unordered_map>

namespace oatpp { namespace network {

/**
 * Abstract MessageProvider. <br>
 * Basically it returns whatever stream (&id:oatpp::data::stream::IOStream;). <br>
 * User of MessageProvider should care about IOStream only.
 * All other properties are optional.
 */
class MessageProvider {
 public:
  /**
   * Predefined property key for HOST.
   */
  static const char* const PROPERTY_HOST;

  /**
   * Predefined property key for PORT.
   */
  static const char* const PROPERTY_PORT;
 public:
  /**
   * Convenience typedef for &id:oatpp::data::stream::IOStream;.
   */
  typedef oatpp::data::message::IOMessage IOMessage;

  /**
   * Convenience typedef for &id:oatpp::async::Action;.
   */
  typedef oatpp::async::Action Action;
  typedef oatpp::async::Action (oatpp::async::AbstractCoroutine::*AsyncCallback)(const std::shared_ptr<IOMessage>&);
 private:
  std::unordered_map<oatpp::data::share::StringKeyLabelCI, oatpp::data::share::StringKeyLabel> m_properties;
 protected:

  /*
   * Set optional property
   */
  void setProperty(const oatpp::String& key, const oatpp::String& value);
 public:

  /**
   * Virtual default destructor.
   */
  virtual ~MessageProvider() = default;

  /**
   * Implement this method.
   * Get IOMessage representing connection to resource.
   * @return - &id:oatpp::data::stream::IOStream;.
   */
  virtual std::shared_ptr<IOMessage> getMessage() = 0;

  /**
   * Implement this method.
   * Obtain IOStream representing connection to resource.
   * @return - &id:oatpp::async::CoroutineStarterForResult;.
   */
  virtual oatpp::async::CoroutineStarterForResult<const std::shared_ptr<oatpp::data::message::IOMessage>&> getMessageAsync() = 0;

  /**
   * Invalidate connection that was previously created by this provider.
   * Ex.: if provider is pool based - you can signal that this connection should not be reused anymore.
   * @param connection
   */
  virtual void invalidateMessage(const std::shared_ptr<IOMessage>& connection) = 0;

  /**
   * Should close all handles here.
   */
  virtual void close() = 0;

  /**
   * Some optional properties that user might want to know. <br>
   * Note: All properties are optional and user should not rely on this.
   */
  const std::unordered_map<oatpp::data::share::StringKeyLabelCI, oatpp::data::share::StringKeyLabel>& getProperties();

  /**
   * Get optional property
   */
  oatpp::data::share::StringKeyLabel getProperty(const oatpp::String& key);

};

/**
 * No properties here. It is just a logical division
 */
class ServerMessageProvider : public MessageProvider {
};

/**
 * No properties here. It is just a logical division
 */
class ClientMessageProvider : public MessageProvider {
};

}}

#endif /* oatpp_network_ConnectionsProvider_hpp */
