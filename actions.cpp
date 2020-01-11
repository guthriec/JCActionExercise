#include <string>
#include "actions.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

std::optional<Actions::JsonError> Actions::Tracker::addAction(std::string actionJson) {
  rapidjson::Document document;
  // load and validate json
  if (document.Parse(actionJson.c_str()).HasParseError()) {
    return Actions::JsonError::MalformedJson;
  }
  if (!document.IsObject()) {
    return Actions::JsonError::NotAnObject;
  }
  if (!document.HasMember("action") || !document.HasMember("time")) {
    return Actions::JsonError::MissingKeys;
  }
  if (!document["action"].IsString() || !document["time"].IsInt()) {
    return Actions::JsonError::IncorrectValueType;
  }
  // extract action info
  std::string actionName = document["action"].GetString();
  int actionTime = document["time"].GetInt();

  // acquire write lock and update allStats object with new action info
  std::unique_lock lock(mapMutex);
  std::map<std::string, std::pair<uint32_t, uint64_t>>::iterator currStatIt =
    allStats.find(actionName);

  if (currStatIt == allStats.end()) {
    // start a stats entry for action name
    allStats.emplace(actionName, std::pair<uint32_t, uint64_t>(1, actionTime));
  } else {
    // log an increase in the total number of actions of type actionName,
    // and increase the total time spent
    currStatIt->second.first += 1;
    currStatIt->second.second += actionTime;
  }
  // success
  return std::nullopt;
}


std::string Actions::Tracker::getStats() {
  // initialize json writer
  rapidjson::StringBuffer s;
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);
  writer.StartArray();

  // acquire read lock and loop over all stats
  std::shared_lock lock(mapMutex);
  for (
    std::map<std::string, std::pair<uint32_t, uint64_t>>::iterator it =
      allStats.begin();
    it != allStats.end();
    ++it
  ) {
    // write a json object for each entry in allStats
    writer.StartObject();
    writer.Key("action");
    writer.String(it->first.c_str());
    writer.Key("avg");
    // integer division for average, is ok
    writer.Int(it->second.second / it->second.first);
    writer.EndObject();
  }
  lock.release();
  writer.EndArray();

  // serialize
  return s.GetString();
}
