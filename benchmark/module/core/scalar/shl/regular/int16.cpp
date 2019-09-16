//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/shl.hpp>

#define TYPE()        int16_t
#define FUNCTION()    eve::shl
#define SAMPLES(N)    random<T>(N,-100.,100.),random<int>(N, 0UL, sizeof(typename TYPE()::value_type)-1)

#include "bench.hpp"
