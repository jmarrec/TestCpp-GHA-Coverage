#ifndef PERSON_HPP
#define PERSON_HPP

#include <array>
#include <optional>
#include <string>
#include <string_view>

namespace civil_registry {

class Person
{
 public:
  inline constexpr static std::array<std::string_view, 1> rejectedNames = {"Adolf"};

  Person(std::string t_name) noexcept;

  [[nodiscard]] std::string getName() const;
  bool setName(const std::string& t_newName);

 private:
  std::string m_name;
};

}  // namespace civil_registry

std::ostream& operator<<(std::ostream&, const civil_registry::Person&);

#endif  // ifndef PERSON_HPP
