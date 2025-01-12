#include <eve/constant/pio_2.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> pio_2(as<wide_ft>())  = " << eve::pio_2(eve::as<wide_ft>()) << std::endl
            << "-> pio_2(as(wxf))        = " << eve::pio_2(eve::as(wxf))       << std::endl; 

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> pio_2(as<float>())         = " << eve::pio_2(eve::as(float())) << std::endl
            << "-> pio_2(as<xf))              = " << eve::pio_2(eve::as(xf)) << std::endl; 

  return 0;
}
