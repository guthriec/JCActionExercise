#ifndef ACTIONS_H
#define ACTIONS_H

#include <string>
#include <optional>
#include <map>

namespace Actions {
  /// Enum for action input errors
  enum class JsonError {
    MalformedJson,
    MissingKeys
  };

  class Tracker {
  private:
    std::map<std::string, std::pair<int, int>> actionStats;
  
  public:
    /** 
     * Ingests an action for statistical summary
     * @param actionJson JSON string with two keys "action" (string) and "time"
     *   (integer) representing the action taken and time taken
     * @return empty optional on success, ActionError on failure specifying failure type
     */
    std::optional<JsonError> addAction(std::string actionJson);

    /**
     * Computes action statistics
     * @return JSON string, containing a list of objects with two keys:
     *   "action" (string), and "avg" (integer) representing the action taken
     *   and average time taken to complete the action
     */
    std::string getStats();
  };
}

#endif
