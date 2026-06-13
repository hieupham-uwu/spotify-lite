#include "StringUtils.hpp"

#include <cctype>
string lowerStr(string s) {
  for (auto& x : s) {
    x = tolower(x);
  }
  return s;
}

string normalizeDisplayName(const string& s) {
  string result;
  bool previousWasSpace = false;

  for (char ch : s) {
    if (isspace((unsigned char)ch)) {
      if (!result.empty() && !previousWasSpace) {
        result += ' ';
        previousWasSpace = true;
      }
    } else {
      result += ch;
      previousWasSpace = false;
    }
  }

  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }

  return result;
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

string formatDuration(int totalSeconds) {
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;

  string minStr =
      (minutes < 10) ? "0" + to_string(minutes) : to_string(minutes);
  string secStr =
      (seconds < 10) ? "0" + to_string(seconds) : to_string(seconds);

  return minStr + ":" + secStr;
}
