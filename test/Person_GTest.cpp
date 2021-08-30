#include <gtest/gtest.h>

#include "../src/Person.hpp"

#include <sstream>

using namespace civil_registry;

TEST(PersonTest, Ctors) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  ASSERT_NO_THROW(Person("Julien"));
}

TEST(PersonTest, copy) {

  Person p("Julien");
  Person p2 = p;
  EXPECT_EQ(p.getName(), p2.getName());

  EXPECT_FALSE(p2.setName("Adolf"));
  EXPECT_TRUE(p2.setName("Juliet"));
  EXPECT_NE(p.getName(), p2.getName());
}

TEST(PersonTest, ostream) {
  Person p("Julien");
  std::stringstream ss;
  ss << p;
  EXPECT_EQ("Individual named Julien", ss.str());
}
