#include "Person.hpp"

#include <fmt/format.h>
#include <iostream>
#include <algorithm>

namespace civil_registry {

// cppcheck-suppress passedByValue
Person::Person(std::string t_name) noexcept : m_name(std::move(t_name)) {}

std::string Person::getName() const {
  return m_name;
}

bool Person::setName(const std::string& t_newName) {

  if (std::find(rejectedNames.begin(), rejectedNames.end(), t_newName) != rejectedNames.end()) {
#ifdef __clang__
    fmt::print("Clang: {} was rejected by the government\n", t_newName);
#elif __GNUC__
    fmt::print("GCC: {} was rejected by the government\n", t_newName);
#elif _MSC_VER
    fmt::print("MSVC: {} was rejected by the government\n", t_newName);
#endif
    return false;
  }

  m_name = t_newName;
  return true;
}

}  // namespace civil_registry

std::ostream& operator<<(std::ostream& os, const civil_registry::Person& p) {
  os << "Individual named " << p.getName();
  return os;
}
