#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
#include <optional>

namespace civil_registry {

class Person
{
 public:
  inline static std::vector<std::string> rejectedNames = {"Adolf"};

  Person(std::string t_name) noexcept;

  std::string getName() const;
  bool setName(const std::string& t_newName);

  unsigned getIndex() const;

 private:
  std::string m_name;
};

}  // namespace civil_registry

std::ostream& operator<<(std::ostream&, const civil_registry::Person&);

#endif  // ifndef PERSON_HPP
