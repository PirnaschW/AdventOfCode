//template<> auto InputData<2015, 2, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 2, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number sum{ 0 };
  for (const std::string& line : v)
  {
    Number x{};
    Number y{};
    Number z{};
    int n = sscanf_s(line.c_str(), "%lldx%lldx%lld", &x, &y, &z);
    assert(n == 3);
 
    auto smallest = [](auto x, auto y, auto z)
      {
        if (x >= y && x >= z) return y * z;
        if (y >= x && y >= z) return x * z;
        if (z >= x && z >= y) return x * y;
        assert(false);
        return 0LL;
      };

    sum += (x * y + x * z + y * z) * 2 + smallest(x, y, z);
  }

  return sum;
}

//template<> auto InputData<2015, 2, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 2, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number sum{ 0 };
  for (const std::string& line : v)
  {
    Number x{};
    Number y{};
    Number z{};
    int n = sscanf_s(line.c_str(), "%lldx%lldx%lld", &x, &y, &z);
    assert(n == 3);

    auto smallest = [](auto x, auto y, auto z)
      {
        if (x >= y && x >= z) return y + z;
        if (y >= x && y >= z) return x + z;
        if (z >= x && z >= y) return x + y;
        assert(false);
        return 0LL;
      };

    sum += x * y * z + smallest(x, y, z) * 2LL;
  }

  return sum;
}
