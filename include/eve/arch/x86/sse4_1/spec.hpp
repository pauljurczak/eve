//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE4_1_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_SSE4_1_SPEC_HPP_INCLUDED

#include <eve/arch/x86/sse4_1/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_HW_X86 == EVE_SSE4_1_VERSION
    #define EVE_CURRENT_ABI ::eve::sse_
    #define EVE_CURRENT_API ::eve::sse4_1_
  #endif
#endif

#if EVE_HW_X86 >= EVE_SSE4_1_VERSION
  #include <smmintrin.h>
  #include <eve/arch/x86/sse2/abi_of.hpp>
  #include <eve/arch/x86/sse2/as_register.hpp>
#endif

#endif