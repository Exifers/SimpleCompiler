#include <regex.h>
#include <iostream>

#include "regex.hh"

bool regexmatch(std::string pattern, std::string value) {
  regex_t regex;
  int res;
  if (regcomp(&regex, pattern.c_str(), 0)) {
    std::cerr << "Cannot compile regex : " << pattern << std::endl;
    exit(1);
  }
  res = regexec(&regex, value.c_str(), 0, nullptr, 0);
  regfree(&regex);
  return res == 0;
}
