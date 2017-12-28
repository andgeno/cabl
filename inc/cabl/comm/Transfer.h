/*
        ##########    Copyright (C) 2015 Vincenzo Pacella
        ##      ##    Distributed under MIT license, see file LICENSE
        ##      ##    or <http://opensource.org/licenses/MIT>
        ##      ##
##########      ############################################################# shaduzlabs.com #####*/

#pragma once

#include "cabl/util/Types.h"
#include <cstdint>
#include <ios>
#include <sstream>

#ifdef CABL_USE_NETWORK
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#endif

namespace sl
{
namespace cabl
{

//--------------------------------------------------------------------------------------------------

class Transfer final
{

public:
  Transfer() = default;
  explicit Transfer(unsigned length_);

  Transfer(tRawData data_);
  Transfer(const tRawData& header_, const tRawData& data_);
  Transfer(const tRawData& header_, const uint8_t* pData_, size_t dataLength_);
  Transfer(const tRawData& header_, const uint8_t* pData_, size_t dataLength_, const tRawData& suffix_);

  bool operator==(const Transfer& other_) const;
  bool operator!=(const Transfer& other_) const;

  operator bool() const
  {
    return (m_data.size() > 0);
  }

  inline uint8_t& operator[](int i)
  {
    return m_data[i];
  }

  inline const uint8_t& operator[](int i) const
  {
    return m_data[i];
  }

  void reset();

  const tRawData& data() const
  {
    return m_data;
  }
  void setData(const uint8_t*, size_t);
  void dump ();
  
  size_t size() const noexcept
  {
    return m_data.size();
  }

private:
#ifdef CABL_USE_NETWORK
  friend class cereal::access;

  template <class Archive>
  void serialize(Archive& archive)
  {
    archive(m_data);
  }
#endif

  tRawData m_data;
};

//--------------------------------------------------------------------------------------------------

} // namespace cabl
} // namespace sl
