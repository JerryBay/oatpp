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

#include "oatpp/core/data/share/LazyStringMap.hpp"
#include "oatpp/core/async/Coroutine.hpp"

#ifndef oatpp_data_share_Context_hpp
#define oatpp_data_share_Context_hpp

namespace oatpp { namespace data { namespace share {

/**
 * Stream Context.
 */
class Context {
 public:
  /**
   * Convenience typedef for &id:oatpp::data::share::LazyStringMap;.
   */
  typedef oatpp::data::share::LazyStringMap<oatpp::data::share::StringKeyLabel> Properties;
 private:
  Properties m_properties;
 protected:
  /**
   * `protected`. Get mutable additional optional context specific properties.
   * @return - &l:Context::Properties;.
   */
  Properties& getMutableProperties();
 public:

  /**
   * Default constructor.
   */
  Context() = default;

  /**
   * Constructor.
   * @param properties - &l:Context::Properties;.
   */
  Context(Properties&& properties);

  /**
   * Virtual destructor.
   */
  virtual ~Context() = default;

  /**
   * Initialize stream context.
   */
  virtual void init() = 0;

  /**
   * Initialize stream context in an async manner.
   * @return - &id:oatpp::async::CoroutineStarter;.
   */
  virtual async::CoroutineStarter initAsync() = 0;

  /**
   * Check if the stream context is initialized.
   * @return - `bool`.
   */
  virtual bool isInitialized() const = 0;

  /**
   * Additional optional context specific properties.
   * @return - &l:Context::Properties;.
   */
  const Properties& getProperties() const;

  inline bool operator == (const Context& other){
    return this == &other;
  }

  inline bool operator != (const Context& other){
    return this != &other;
  }

};

/**
 * The default implementation for context with no initialization.
 */
class DefaultInitializedContext : public oatpp::data::share::Context {
 public:

  /**
   * Constructor.
   */
  DefaultInitializedContext();

  /**
   * Constructor.
   * @param properties - &l:Context::Properties;.
   */
  DefaultInitializedContext(Properties&& properties);

  /**
   * Initialize stream context. <br>
   * *This particular implementation does nothing.*
   */
  void init() override;

  /**
   * Initialize stream context in an async manner.
   * *This particular implementation does nothing.*
   * @return - &id:oatpp::async::CoroutineStarter;.
   */
  async::CoroutineStarter initAsync() override;

  /**
   * Check if the stream context is initialized.
   * *This particular implementation always returns `true`.*
   * @return - `bool`.
   */
  bool isInitialized() const override;

};

}}}

#endif //oatpp_data_share_Context_hpp
