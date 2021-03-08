//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/real/math/detail/generic/rempio2_kernel.hpp>

#include <array>
#include <type_traits>

namespace eve::detail
{
  template<decorator D, floating_value T>
  EVE_FORCEINLINE auto rempio2_(EVE_SUPPORTS(cpu_), D const &, T const &xx) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( std::is_same_v<D, eve::small_type> )
      {
        return rempio2_small(xx);
      }
      else if constexpr( std::is_same_v<D, eve::medium_type> )
      {
        return rempio2_medium(xx);
      }
      else if constexpr( std::is_same_v<D, eve::big_type> )
      {
        return rempio2_big(xx);
      }
      else if constexpr( std::is_same_v<D, eve::regular_type> )
      {
        return rempio2(xx);
      }
    }
    else
      return apply_over3(D()(rempio2), xx);
  }

  template<floating_value T> EVE_FORCEINLINE
  std::array<T, 3> rempio2_(EVE_SUPPORTS(cpu_), T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if( eve::all(x <= Rempio2_limit(restricted_type(), as(x))) )
        return {T(0), x, T(0)};
      else if( eve::all(x <= Rempio2_limit(small_type(), as(x))) )
        return small(rempio2)(x);
      else if( eve::all(x <= Rempio2_limit(medium_type(), as(x))) )
        return medium(rempio2)(x);
      else
        return big(rempio2)(x);
    }
    else
      return apply_over3(rempio2, x);
  }
}
