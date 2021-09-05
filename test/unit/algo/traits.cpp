//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/algo/traits.hpp>

TTS_CASE("eve.algo basic traits testing")
{
  {
    []<typename Traits>(Traits) {
      TTS_CONSTEXPR_EXPECT_NOT(Traits::contains(eve::algo::unroll_key));
      TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<Traits>() == 1);
    } (eve::algo::traits());
  }
  {
    auto just_unroll = eve::algo::traits(eve::algo::unroll<4>);
    []<typename Traits>(Traits){
      TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<Traits>() == 4);
    }(just_unroll);
  }
  {
    auto divisible_by_cardinal = eve::algo::traits(eve::algo::divisible_by_cardinal);
    []<typename Traits>(Traits){
      TTS_CONSTEXPR_EXPECT(Traits::contains(eve::algo::divisible_by_cardinal));
    }(divisible_by_cardinal);
  }
}

TTS_CASE("eve.algo defaulting")
{
  {
    eve::algo::traits out =
      eve::algo::default_to(eve::algo::traits(eve::algo::unroll<1>), eve::algo::traits(eve::algo::unroll<4>));
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(out)>() == 1);
    TTS_CONSTEXPR_EXPECT(!decltype(out)::contains((eve::algo::divisible_by_cardinal)));
    TTS_CONSTEXPR_EXPECT(!decltype(out)::contains((eve::algo::no_aligning)));
  }
  {
    eve::algo::traits out = eve::algo::default_to(
      eve::algo::traits(eve::algo::divisible_by_cardinal),
      eve::algo::traits(eve::algo::unroll<4>,
                        eve::algo::no_aligning));
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(out)>() == 4);
    TTS_CONSTEXPR_EXPECT(decltype(out)::contains((eve::algo::divisible_by_cardinal)));
    TTS_CONSTEXPR_EXPECT(decltype(out)::contains((eve::algo::no_aligning)));
  }
  {
    constexpr auto expected = eve::algo::traits(eve::algo::divisible_by_cardinal);
    constexpr auto actual = eve::algo::default_to(eve::algo::traits(), expected);

    TTS_TYPE_IS(decltype(expected), decltype(actual));
  }
}

TTS_CASE("eve.algo.traits, type and cardinal")
{
  {
    eve::algo::traits tr;
    TTS_TYPE_IS((eve::algo::iteration_type_t<decltype(tr), int>), int);
    TTS_TYPE_IS((eve::algo::iteration_cardinal_t<decltype(tr), int>), eve::fixed<eve::expected_cardinal_v<int>>);
  }
  {
    eve::algo::traits tr{eve::algo::force_cardinal<2>};
    TTS_TYPE_IS((eve::algo::iteration_type_t<decltype(tr), int>), int);
    TTS_TYPE_IS((eve::algo::iteration_cardinal_t<decltype(tr), int>), eve::fixed<2>);
  }
  {
    eve::algo::traits tr{eve::algo::force_type<char>};
    TTS_TYPE_IS((eve::algo::iteration_type_t<decltype(tr), int>), char);
    TTS_TYPE_IS((eve::algo::iteration_cardinal_t<decltype(tr), int>), eve::fixed<eve::expected_cardinal_v<char>>);
  }
  {
    eve::algo::traits tr{eve::algo::common_with_types<char>};
    TTS_TYPE_IS((eve::algo::iteration_type_t<decltype(tr), int>), int);
    TTS_TYPE_IS((eve::algo::iteration_cardinal_t<decltype(tr), int>), eve::fixed<eve::expected_cardinal_v<int>>);
  }
}

// Funciton with traits support

template <typename TraitsSupport>
struct func_ : TraitsSupport
{
  using traits_type = typename TraitsSupport::traits_type;

  constexpr std::ptrdiff_t get_unrolling() const
  {
    return eve::algo::get_unrolling<traits_type>();
  }

  constexpr bool is_divisible_by_cardinal() const
  {
    return traits_type::contains(eve::algo::divisible_by_cardinal);
  }
};

inline constexpr auto func = eve::algo::function_with_traits<func_>;

TTS_CASE("eve.algo.support_traits") {
  constexpr auto unroll = func[eve::algo::traits{eve::algo::unroll<2>}];
  TTS_CONSTEXPR_EQUAL(unroll.get_unrolling(), 2);

  constexpr auto is_divisible = unroll[eve::algo::divisible_by_cardinal];
  TTS_CONSTEXPR_EXPECT(is_divisible.is_divisible_by_cardinal());
  TTS_CONSTEXPR_EQUAL(is_divisible.get_unrolling(), 2);
}
