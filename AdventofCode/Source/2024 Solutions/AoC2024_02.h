//template<> auto InputData<2024, 2, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2024, 2, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto IsSafe = [](const std::string& line) -> bool
    {
      int n;
      Number r1{};
      Number r2{};
      int z = sscanf_s(line.c_str(), "%lld %lld %n", &r1, &r2, &n);
      assert(z == 2);

      bool asc = r2 > r1;
      Number d = std::abs(r2 - r1);
      if (d < 1 || d > 3) return false;

      int p{ n };
      Number rn{};
      while (sscanf_s(line.c_str() + p, "%lld %n", &rn, &n) == 1)
      {
        d = std::abs(rn - r2);
        if (d < 1 || d > 3) return false;
        if ((rn > r2) != asc) return false;
        r2 = rn;
        p += n;
      }
      return true;
    };

  Number res{ 0 };
  for (const auto& line : v)
  {
    if (IsSafe(line))
      ++res;
  }

  return res;
}

//template<> auto InputData<2024, 2, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2024, 2, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto ReadLine = [](const std::string& line) -> std::vector<Number>
    {
      std::vector<Number> r{};
      int p{ 0 };
      int n{ 0 };
      Number rn{};
      while (sscanf_s(line.c_str() + p, "%lld %n", &rn, &n) == 1)
      {
        r.push_back(rn);
        p += n;
      }
      return r;
    };

  auto IsSafe = [](const std::vector<Number>& r) -> bool
    {
      assert(std::ssize(r) > 1);

      for (int i = 0; i < std::ssize(r) - 1; ++i)
      {
        if ((r[i + 1] > r[i]) != (r[1] > r[0])) return false;
        Number d = std::abs(r[i + 1] - r[i]);
        if (d < 1 || d > 3) return false;
      }
      return true;
    };

  auto IsReportSafe = [&IsSafe](const std::vector<Number>& r) -> bool
    {
      for (int i = 0; i < std::ssize(r); ++i)
      {
        std::vector<Number> r0{ r };
        r0.erase(r0.begin() + i);
        if (IsSafe(r0)) return true;
      }
      return false;
    };

  Number res{ 0 };
  for (const auto& line : v)
  {
    std::vector<Number> r = ReadLine(line);
    if (IsReportSafe(r))
      ++res;
  }

  return res;
}
