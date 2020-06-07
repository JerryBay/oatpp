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

#ifndef oatpp_data_buffer_DynamicBuffer_hpp
#define oatpp_data_buffer_DynamicBuffer_hpp

#include <vector>
#include "oatpp/core/IODefinitions.hpp"
#include "oatpp/core/Types.hpp"

namespace oatpp { namespace data { namespace buffer {

class DynamicBuffer {

 private:
  std::vector<v_char8> m_buffer;

 public:
  DynamicBuffer();

  DynamicBuffer(const p_char8 data, v_io_size n);

  explicit DynamicBuffer(const oatpp::String &data);

  explicit DynamicBuffer(DynamicBuffer &buffer);

  static std::shared_ptr<DynamicBuffer> createShared() {
    return std::make_shared<DynamicBuffer>();
  }

  static std::shared_ptr<DynamicBuffer> createShared(const p_char8 data, v_io_size n) {
    return std::make_shared<DynamicBuffer>(data, n);
  }

  static std::shared_ptr<DynamicBuffer> createShared(const oatpp::String &data) {
    return std::make_shared<DynamicBuffer>(data);
  }

  static std::shared_ptr<DynamicBuffer> createShared(DynamicBuffer &buffer) {
    return std::make_shared<DynamicBuffer>(buffer);
  }

  oatpp::v_io_size append(p_char8 data, v_io_size n);

  oatpp::v_io_size append(const oatpp::String &data);

  oatpp::v_io_size append(DynamicBuffer &buffer);

  p_char8 getData();

  oatpp::v_io_size getSize();

  /**
   * Grows the buffer by `n` bytes.
   * @param n - the amount of bytes to grow by
   * @return - new size
   */
  oatpp::v_io_size grow(v_io_size n);

  /**
   * Resizes to n bytes
   * @param n - the amount of bytes to resize to
   * @return - new size
   */
  oatpp::v_io_size resize(v_io_size n);
};

}}}


#endif //oatpp_data_buffer_DynamicBuffer_hpp
