// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>

#include <magic_enum.hpp>

enum class AnimalFlags : std::uint64_t { HasClaws = 1, CanFly = 2, EatsFish = 4, Endangered = 8 };

namespace magic_enum {
  template <>
  struct enum_range<AnimalFlags> {
    static constexpr bool is_flags = true;
  };
}

int main() {
  // Enum variable to string name.
  AnimalFlags f1 = AnimalFlags::CanFly;
  auto f1_name = magic_enum::enum_name(f1);
  std::cout << f1_name << std::endl; // CanFly

  // String enum name sequence.
  constexpr auto names = magic_enum::enum_names<AnimalFlags>();
  std::cout << "AnimalFlags names:";
  for (auto n : names) {
    std::cout << " " << n;
  }
  std::cout << std::endl;
  // AnimalFlags names: HasClaws CanFly EatsFish Endangered

  // String name to enum value.
  auto f2 = magic_enum::enum_cast<AnimalFlags>("EatsFish");
  if (f2.has_value() && f2.value() == AnimalFlags::EatsFish) {
    std::cout << "EatsFish = " << static_cast<int>(f2.value()) << std::endl; // EatsFish = 4
  }

  // Integer value to enum value.
  auto f3 = magic_enum::enum_cast<AnimalFlags>(8);
  if (f3.has_value() && f3.value() == AnimalFlags::Endangered) {
    std::cout << "Endangered = " << magic_enum::enum_integer(f3.value()) << std::endl; // Endangered = 8
  }

  // Enum value to integer value.
  auto f4_integer = magic_enum::enum_integer(AnimalFlags::HasClaws);
  if (f4_integer == static_cast<std::underlying_type_t<AnimalFlags>>(AnimalFlags::HasClaws)) {
    std::cout << "HasClaws = " << f4_integer << std::endl; // HasClaws = 1
  }

  using namespace magic_enum::ostream_operators; // out-of-the-box ostream operator for all enums.
  // ostream operator for enum.
  std::cout << f1 << " " << f2 << " " << f3 << std::endl; // CanFly EatsFish Endangered

  // Number of enum values.
  std::cout << "AnimalFlags enum size: " << magic_enum::enum_count<AnimalFlags>() << std::endl; // AnimalFlags enum size: 4

  // Indexed access to enum value.
  std::cout << "AnimalFlags[0] = " << magic_enum::enum_value<AnimalFlags>(0) << std::endl; // AnimalFlags[0] = HasClaws

  // Enum value sequence.
  constexpr auto values = magic_enum::enum_values<AnimalFlags>();
  std::cout << "AnimalFlags values:";
  for (AnimalFlags f : values) {
    std::cout << " " << f; // ostream operator for enum.
  }
  std::cout << std::endl;
  // AnimalFlags sequence: HasClaws CanFly EatsFish Endangered

  using namespace magic_enum::bitwise_operators; // out-of-the-box bitwise operators for all enums.
  // Support operators: ~, |, &, ^, |=, &=, ^=.
  AnimalFlags flag = AnimalFlags::HasClaws | AnimalFlags::CanFly;
  std::cout << flag << std::endl;

  // Enum pair (value enum, string enum name) sequence.
  constexpr auto entries = magic_enum::enum_entries<AnimalFlags>();
  std::cout << "AnimalFlags entries:";
  for (auto e : entries) {
    std::cout << " "  << e.second << " = " << static_cast<int>(e.first);
  }
  std::cout << std::endl;
  // AnimalFlags entries: HasClaws = 1 CanFly = 2 EatsFish = 4 Endangered = 8

  return 0;
}
