//template<> auto InputData<2024, 1, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2024, 1, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  std::vector<Number> left{};
  std::vector<Number> right{};

  for (const auto& line : v)
  {
    Number l{};
    Number r{};
    int z = sscanf_s(line.c_str(), "%lld %lld", &l, &r);
    assert(z == 2);
    left.push_back(l);
    right.push_back(r);
  }

  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  Number z{ 0 };
  for (int i = 0; i < std::ssize(left); ++i)
  {
    z += std::abs(left[i] - right[i]);
  }

  return z;
}

//template<> auto InputData<2024, 4, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2024, 1, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  std::vector<Number> left{};
  std::map<Number,int> right{};

  for (const auto& line : v)
  {
    Number l{};
    Number r{};
    int z = sscanf_s(line.c_str(), "%lld %lld", &l, &r);
    assert(z == 2);
    left.push_back(l);
    ++right[r];
  }

  Number z{ 0 };
  for (int i = 0; i < std::ssize(left); ++i)
  {
    int n = right[left[i]];
    z += left[i] * n;
  }

  return z;
}
