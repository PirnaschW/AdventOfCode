//template<> auto InputData<2015, 1, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 1, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number res{ 0 };
  for (const auto& c : v[0])
  {
    switch (c)
    {
      case '(': ++res; break;
      case ')': --res; break;
      default: assert(false);
    }
  }
  return res;
}

//template<> auto InputData<2015, 1, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 1, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  int res{ 0 };
  for (int i = 0; i < v[0].size(); ++i)
  {
    switch (v[0][i])
    {
      case '(': ++res; break;
      case ')': --res; break;
      default: assert(false);
    }
    if (res < 0) return i + 1;
  }
  return -1;
}
