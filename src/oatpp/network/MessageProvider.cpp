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

#ifndef oatpp_network_MessageProvider_hpp
#define oatpp_network_MessageProvider_hpp

#include "oatpp/network/MessageProvider.hpp"

namespace oatpp { namespace network {

const char* const MessageProvider::PROPERTY_HOST = "host";
const char* const MessageProvider::PROPERTY_PORT = "port";

void MessageProvider::setProperty(const oatpp::String& key, const oatpp::String& value) {
  m_properties[key] = value;
}

const std::unordered_map<oatpp::data::share::StringKeyLabelCI, oatpp::data::share::StringKeyLabel>& MessageProvider::getProperties() {
  return m_properties;
}

oatpp::data::share::StringKeyLabel MessageProvider::getProperty(const oatpp::String& key) {
  auto it = m_properties.find(key);
  if(it == m_properties.end()) {
    return nullptr;
  }
  return it->second;
}

}}

#endif