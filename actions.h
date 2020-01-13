#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
#include <optional>
#include <map>
#include <shared_mutex>

namespace Actions {
  /// Enum for action input errors
  enum class JsonError {
    MalformedJson,
    NotAnObject,
    MissingKeys,
    IncorrectValueType
  };

  class Tracker {
  private:
    /// map of action name -> (number of actions, total time taken on all actions)
    std::map<std::string, std::pair<uint32_t, uint64_t>> allStats;
    std::shared_mutex mapMutex;
  
  public:
    /** 
     * Ingests an action for statistical summary
     * @param actionJson JSON string with two keys "action" (string) and "time"
     *   (unsigned integer) representing the action taken and time taken.
     * @return empty optional on success, JsonError on failure
     */
    std::optional<JsonError> addAction(std::string actionJson);

    /**
     * Computes action statistics
     * @return JSON string, containing a list of objects with two keys:
     *   "action" (string), and "avg" (unsigned integer) representing
     *   the action taken and average time taken to complete the action
     *   (rounded down to the nearest integer)
     */
    std::string getStats();
  };
}

#endif
