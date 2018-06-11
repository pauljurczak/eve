//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#include <eve/function/scalar/popcnt.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE( "Check popcnt correctness on 8 bits unsigned integrals" )
{
  using eve::popcnt;

  TTS_EQUAL( popcnt(std::uint8_t{0})         , 0);
  TTS_EQUAL( popcnt(std::uint8_t{255})       , 8);
  TTS_EQUAL( popcnt(std::uint8_t{0b10101010}), 4);
}
