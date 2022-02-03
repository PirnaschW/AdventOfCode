#include "pch.h"

std::vector<std::vector<std::string>> ReadGroups(std::istream& input) // read all lines, grouping multiple lines separated by blank lines into sub-vector 
{
  std::vector<std::vector<std::string>> v{};
  v.reserve(100);

  std::string line{};
  std::vector<std::string> group{};
  while (getline(input, line))
  {
    if (line.size() == 0)
    {
      v.emplace_back(group);
      group.clear();
    }
    else
    {
      group.emplace_back(line);
    }
  }
  return v;
}

std::vector<std::string> ReadLines(std::istream& input) // read all lines into vector 
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string line{};
  while (getline(input, line))
  {
    v.emplace_back(line);
  }
  return v;
}

std::vector<Number> ReadNumbers(std::istream& input, char separator) // read all lines as Number into vector 
{
  std::vector<Number> v{};
  v.reserve(1000);
  std::string line{};
  while (getline(input, line))
  {
    std::istringstream str(line);

    long long int z;
    while (str >> z)
    {
      v.emplace_back(std::move(z));

      char sep;
      if (str >> sep) continue;
      if (sep != separator) { assert(false); continue; }
    }
  }
  return v;
}

std::vector<std::string> ReadWords(std::istream& input) // read all words into vector 
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string s;
  while (input >> s)
  {
    v.emplace_back(s);
  }
  return v;
}
