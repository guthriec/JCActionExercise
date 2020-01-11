#include <thread>
#include <vector>

#include "actions.h"
#include "gtest/gtest.h"

class TrackerTest : public ::testing::Test {
protected:
  Actions::Tracker tracker;
};

/**
 * test whether adding a single action with a single time
 * leads to correct result from getStats()
 */
TEST_F(TrackerTest, SingleActionTest) {
  tracker.addAction("{\"action\":\"jump\", \"time\":100}");
  std::string expected = "[{\"action\":\"jump\",\"avg\":100}]";
  ASSERT_STREQ(tracker.getStats().c_str(), expected.c_str());
}

/// test multiple actions with multiple times
TEST_F(TrackerTest, MultipleActionTest) {
  tracker.addAction("{\n\"action\":\"jump\",  \"time\":100\n}");
  tracker.addAction("{\"action\":\"jump\",\"time\":50}");
  tracker.addAction("{\"action\":\"run\",\"time\":200}");
  std::string expected = "[{\"action\":\"jump\",\"avg\":75},{\"action\":\"run\",\"avg\":200}]";
  ASSERT_STREQ(tracker.getStats().c_str(), expected.c_str());
}

/// test a big time
TEST_F(TrackerTest, LargeNumberTest) {
  for (int i=1; i < 1000; i++) {
    tracker.addAction("{\"action\":\"jump\",\"time\":100000000}");
  }
  std::string expected = "[{\"action\":\"jump\",\"avg\":100000000}]";
  ASSERT_STREQ(tracker.getStats().c_str(), expected.c_str());
}

/// check that bad inputs are caught and good inputs don't return errors
TEST_F(TrackerTest, AddActionReturnValueTest) {
  std::optional<Actions::JsonError> res =
    tracker.addAction("{\"action\":\"jump\",\"time\":100}");
  ASSERT_EQ(res, std::nullopt);
  
  res = tracker.addAction("{[{\"action\":\"jump\",\"time\":100}");
  ASSERT_EQ(res.value(), Actions::JsonError::MalformedJson);
  
  res = tracker.addAction("{\"task\":\"jump\",\"time\":100}");
  ASSERT_EQ(res.value(), Actions::JsonError::MissingKeys);

  res = tracker.addAction("{\"action\":\"jump\",\"time\":\"10 seconds\"}");
  ASSERT_EQ(res.value(), Actions::JsonError::IncorrectValueType);

  res = tracker.addAction("[{\"action\":\"jump\",\"time\":100}]");
  ASSERT_EQ(res.value(), Actions::JsonError::NotAnObject);
}

/// Long-running, non-deterministic test to try to catch race conditions
TEST_F(TrackerTest, ConcurrentWriteTest) {
  std::vector<std::thread> writerThreads;
  for (int i=1; i < 30000; i++) {
    // start a new thread and add a "jump" action
    writerThreads.push_back(std::thread([this, i]() {
      std::string actionJson = "{\"action\":\"jump\",\"time\":" + std::to_string(i) + "}";
      this->tracker.addAction(actionJson);
    }));
  }
  // wait for threads to finish
  std::for_each(writerThreads.begin(), writerThreads.end(), [](std::thread &currThread) {
    currThread.join();
  });

  // read stats once, check average is 15000
  std::string expected = "[{\"action\":\"jump\",\"avg\":15000}]";
  ASSERT_STREQ(tracker.getStats().c_str(), expected.c_str());
}
