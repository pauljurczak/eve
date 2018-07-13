//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_SLICE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  //------------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice( pack<T,N,emulated_> const& a ) noexcept
  {
    auto eval = [&](auto... I)
    {
      using pack_t = pack<T,typename N::split_type>;
      using that_t = std::array<pack_t,2>;
      return that_t{pack_t{a[I]...},pack_t{a[I+N::value/2]...}};
    };

    return apply<N::value/2>(eval);
  }

  //------------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE decltype(auto) slice( pack<T,N,aggregated_> const& a ) noexcept
  {
    #if defined(EVE_COMP_IS_GNUC)
    constexpr bool is_gnuc = true;
    #else
    constexpr bool is_gnuc = false;
    #endif

    // g++ has trouble returning the storage properly for large aggregate - we then copy it
    if constexpr(is_gnuc && sizeof(a) > 256)
    {
      auto eval = [&](auto... I)
      {
        using pack_t = pack<T,typename N::split_type>;
        using that_t = std::array<pack_t,2>;
        return that_t{pack_t{a[I]...},pack_t{a[I+N::value/2]...}};
      };

      return apply<N::value/2>(eval);
    }
    else
      return a.storage();
  }
} }

#endif