//template<> auto AdventOfCode::InputData<2016, 18, A>() { return "..^^.\n3\n";}; // Result: 6
//template<> auto AdventOfCode::InputData<2016, 18, A>() { return ".^^.^.^^^^\n10\n";}; // Result: 38
template<> Number AoC<2016, 18, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  int lines = 40;
  if (v.size() > 1)
  {
    int z = sscanf_s(v[1].c_str(), "%d", &lines);
    assert(z == 1);
  }

  // L != R-> Trap
  std::string line{ v[0] };
  auto GetChar = [&line](int i) -> char
    {
      return (i < 0 || i >= line.size()) ? '.' : line[i];
    };
  auto GetTrap = [&GetChar](int i) -> char
    {
      return (GetChar(i - 1) == GetChar(i + 1)) ? '.' : '^';
    };

  int safetiles{ 0 };
  for (int n=0; n < lines; ++n)
  {
    std::string next{ line };
    for (int i = 0; i < line.size(); ++i)
    {
      if (line[i] == '.') ++safetiles;
      next[i] = GetTrap(i);
    }
    std::swap(line, next);
  }

  // 2036 is too high

  return safetiles;
}

//template<> auto InputData<2016, 18, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 18, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  int lines = 400000;
  if (v.size() > 1)
  {
    int z = sscanf_s(v[1].c_str(), "%d", &lines);
    assert(z == 1);
  }

  // L != R-> Trap
  std::string line{ v[0] };
  auto GetChar = [&line](int i) -> char
    {
      return (i < 0 || i >= line.size()) ? '.' : line[i];
    };
  auto GetTrap = [&GetChar](int i) -> char
    {
      return (GetChar(i - 1) == GetChar(i + 1)) ? '.' : '^';
    };

  int safetiles{ 0 };
  for (int n=0; n < lines; ++n)
  {
    std::string next{ line };
    for (int i = 0; i < line.size(); ++i)
    {
      if (line[i] == '.') ++safetiles;
      next[i] = GetTrap(i);
    }
    std::swap(line, next);
  }

  // 2036 is too high

  return safetiles;
}
