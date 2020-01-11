#include <string>
#include <iostream>
#include "actions.h"

std::optional<Actions::JsonError> Actions::Tracker::addAction(std::string actionJson) {
  return std::nullopt;
}

std::string Actions::Tracker::getStats() {
  return "";
}

/*
int main(int argc, const char * argv[]) {
    std::cout << "hello Visual Studio Code! :)" << '\n'; 
    return 0;
}
*/
