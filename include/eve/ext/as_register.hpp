//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_AS_REGISTER_HPP_INCLUDED
#define EVE_EXT_AS_REGISTER_HPP_INCLUDED

#include <array>

namespace eve { namespace ext
{
  template< typename Type, int Cardinal, typename ABI
          , typename EnableIf = void
          >
  struct as_register;

  template< typename Type, int Cardinal, typename ABI>
  using as_register_t = typename as_register<Type,Cardinal,ABI>::type;
} }

#endif