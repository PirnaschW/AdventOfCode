//template<> auto InputData<2015, 17, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 17, A>(std::istream& input)
{
  using Input = std::vector<Number>;
  Input v = ReadNumbers(input);  // read all lines into vector

  std::sort(v.begin(), v.end(), [](const Number& n1, const Number& n2) { return n1 > n2; });
  constexpr int total{ 150 };

  Number nFits{};
  auto TryAdd = [&v, &nFits](const int& index, const int& sofar, auto& TryAdd) -> void
    {
      if (sofar == total)
      {
        ++nFits;
        return;
      }
      assert(sofar < total);

      for (int i = index; i < v.size(); ++i)
      {
        int sofar0 = sofar + static_cast<int>(v[i]);
        if (sofar0 <= total)
        {
          TryAdd(i + 1, sofar0, TryAdd);
        }
      }
    };

  TryAdd(0, 0, TryAdd);

  return nFits;
}

//template<> auto InputData<2015, 17, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 17, B>(std::istream& input)
{
  using Input = std::vector<Number>;
  Input v = ReadNumbers(input);  // read all lines into vector

  std::sort(v.begin(), v.end(), [](const Number& n1, const Number& n2) { return n1 > n2; });
  constexpr int total{ 150 };

  int minContainers{std::numeric_limits<int>::max()};
  int nFits{};
  auto TryAdd = [&v, &nFits, & minContainers](const int& index, const int& sofar, const int& containers, auto& TryAdd) -> void
    {
      if (sofar == total)
      {
        if (containers < minContainers)
        {
          minContainers = containers;
          nFits = 1;
        }
        else if (containers == minContainers)
        {
          ++nFits;
        }
        return;
      }
      assert(sofar < total);

      for (int i = index; i < v.size(); ++i)
      {
        int sofar0 = sofar + static_cast<int>(v[i]);
        if (sofar0 <= total)
        {
          TryAdd(i + 1, sofar0, containers + 1, TryAdd);
        }
      }
    };

  TryAdd(0, 0, 0, TryAdd);

  return nFits;
}
