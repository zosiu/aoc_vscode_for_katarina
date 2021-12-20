#include "DayTest.h"

#include <unordered_map>
#include <string>
#include <iostream>

void PrintMap() {
  std::unordered_map<int, std::string> myMap = {
        {1, "egy"},
        {2, "ketto"},
        {4, "negy"},
        {8, "nyolc"}
  };

  for (auto& [key, value] : myMap) {
    std::cout << "key: " << key << ", value: " << value << "\n";
  }
}
