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

#include "Context.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Context

namespace oatpp { namespace data { namespace share {

Context::Context(Properties &&properties)
    : m_properties(std::forward<Properties>(properties)) {}

const Context::Properties &Context::getProperties() const {
  return m_properties;
}

Context::Properties &Context::getMutableProperties() {
  return m_properties;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DefaultInitializedContext

DefaultInitializedContext::DefaultInitializedContext()
{}

DefaultInitializedContext::DefaultInitializedContext(Properties&& properties)
    : Context(std::forward<Properties>(properties))
{}

void DefaultInitializedContext::init() {
  // DO NOTHING
}

async::CoroutineStarter DefaultInitializedContext::initAsync() {
  return nullptr;
}

bool DefaultInitializedContext::isInitialized() const {
  return true;
}


}}}