#include "StringUtilities.hpp"

string lowerStr(string s) {
  for (auto& x : s) {
    x = tolower(x);
  }
  return s;
}

vector<string> trimString(string s, char sep) {
  s = s + sep;
  vector<string> ans;
  string temp = "";
  for (auto x : s) {
    if (x != sep) {
      temp += x;
    } else {
      ans.push_back(temp);
      temp = "";
    }
  }

  return ans;
}
