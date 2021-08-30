#include "Person.hpp"

#include <fmt/format.h>
#include <iostream>
#include <algorithm>

namespace civil_registry {

Person::Person(std::string t_name) noexcept : m_name(std::move(t_name)) {}

std::string Person::getName() const {
  return m_name;
}

bool Person::setName(const std::string& t_newName) {

  if (std::find(rejectedNames.begin(), rejectedNames.end(), t_newName) != rejectedNames.end()) {
    fmt::print("{} was rejected by the government\n", t_newName);
    return false;
  } else {
    m_name = t_newName;
    return true;
  }
}

}  // namespace civil_registry

std::ostream& operator<<(std::ostream& os, const civil_registry::Person& p) {
  os << "Individual named " << p.getName();
  return os;
}
