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
#include "test.hpp"

#include <tts/tests/relation.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <list>

template<typename T, typename N>
auto data_block()
{
  using alloc_t = eve::aligned_allocator<T, eve::wide<T, N>::static_alignment>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - N::value;
  std::vector<T, alloc_t> ref(nb_elem);

  T k = {};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

TTS_CASE_TPL("Check ctor from unaligned pointer for wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  auto [data,idx] = data_block<EVE_TYPE, T>();
  auto* ref_ptr   = &data[idx];

  eve::wide<EVE_TYPE, T> simd(ref_ptr);
  eve::wide<EVE_TYPE, T> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check ctor from const unaligned pointer for wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  auto [data,idx]     = data_block<EVE_TYPE, T>();
  auto const* ref_ptr = &data[idx];

  eve::wide<EVE_TYPE, T> simd(ref_ptr);
  eve::wide<EVE_TYPE, T> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check ctor from aligned pointer for wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  auto constexpr algt = eve::wide<EVE_TYPE, T>::static_alignment;
  auto [data,idx]     = data_block<EVE_TYPE, T>();
  auto* ref_ptr       = &data[idx];

  eve::wide<EVE_TYPE, T> simd(eve::as_aligned<algt>(ref_ptr));
  eve::wide<EVE_TYPE, T> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check ctor from const aligned pointer for wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  auto constexpr algt = eve::wide<EVE_TYPE, T>::static_alignment;
  auto [data,idx]     = data_block<EVE_TYPE, T>();
  auto const* ref_ptr = &data[idx];

  eve::wide<EVE_TYPE, T> simd(eve::as_aligned<algt>(ref_ptr));
  eve::wide<EVE_TYPE, T> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL("Check ctor from range for wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  std::list<EVE_TYPE> ref_ptr(T::value);

  EVE_TYPE k = {};
  for(auto &e : ref_ptr) e = k++;

  eve::wide<EVE_TYPE, T> ref;

  k = {};

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, k++);

  {
    eve::wide<EVE_TYPE, T> simd(ref_ptr);
    TTS_EQUAL(simd, ref);
  }

  {
    eve::wide<EVE_TYPE, T> simd(ref_ptr.begin(), ref_ptr.end());
    TTS_EQUAL(simd, ref);
  }
}