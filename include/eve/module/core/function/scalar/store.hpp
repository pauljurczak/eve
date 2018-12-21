//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T> EVE_FORCEINLINE
  void store_(EVE_SUPPORTS(cpu_), T value, T* ptr) noexcept
  {
    *ptr = value;
  }

  // -----------------------------------------------------------------------------------------------
  // Aligned case
  template<typename T, std::size_t N> EVE_FORCEINLINE
  void store_(EVE_SUPPORTS(cpu_), T value, aligned_ptr<T,N> ptr) noexcept
  {
    *ptr = value;
  }
} }

#endif