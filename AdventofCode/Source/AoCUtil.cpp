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

std::vector<Number> ReadNumbers(std::istream& input, char separator) // read input as Number into vector 
{
  std::vector<Number> v{};
  v.reserve(100);
  std::string line{};
  while (getline(input, line))
  {
    std::istringstream str(line);

    long long int z;
    while (str >> z)
    {
      v.emplace_back(std::move(z));

      char sep;
      if (!(str >> sep)) break;
      if (sep != separator) { assert(false); continue; }
    }
  }
  return v;
}

std::vector<std::string> ReadWords(std::istream& input, char separator) // read input as words into vector 
{
  assert(separator != '%');
  assert(separator != '\0');

  char format[]{ "%[^#]%c" };
  assert(format[3] == '#');
  format[3] = separator;

  std::vector<std::string> v{};
  v.reserve(100);
  std::string line{};

  while (getline(input, line))
  {
    constexpr unsigned buffersize = 2U << 16;
    char buffer[buffersize]{};
    char sep{};
    size_t ptr{ 0 };
    while (true)
    {
      switch (sscanf_s(line.c_str() + ptr, format, buffer, buffersize - 1, &sep, 1U))
      {
        case 2:  v.emplace_back(buffer); break;     // normal
        case 1:  v.emplace_back(buffer); return v;  // last one
        default: assert(false); return v;
      }
      ptr += strlen(buffer) + 1;
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
