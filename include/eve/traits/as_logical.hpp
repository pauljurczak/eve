//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/logical.hpp>

namespace eve
{
  template<typename T>
  struct as_logical
  {
    using type = logical<T>;
  };

  template<>
  struct as_logical<bool>
  {
    using type = bool;
  };

  template<typename T>
  struct as_logical<logical<T>>
  {
    using type = logical<T>;
  };

  template<typename T>
  using as_logical_t = typename as_logical<T>::type;
}
