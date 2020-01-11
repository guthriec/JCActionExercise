#include "actions.h"
#include "gtest/gtest.h"

TEST(ActionsTest, SingleActionTest) {
  Actions::Tracker tracker = Actions::Tracker();
  tracker.addAction("{\"action\":\"jump\", \"time\":100}");
  std::string expected = "[{\"action\":\"jump\", \"avg\":75}]";
  std::cerr << expected;
  ASSERT_STREQ(tracker.getStats().c_str(), expected.c_str());
  ASSERT_EQ(1, 2);
}

TEST(ActionsTest, FailTest) {
  ASSERT_FALSE(true);
}
