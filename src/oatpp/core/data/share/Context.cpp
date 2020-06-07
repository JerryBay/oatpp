//
// Created by Benedikt-Alexander Mokroß on 07.06.20.
//

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