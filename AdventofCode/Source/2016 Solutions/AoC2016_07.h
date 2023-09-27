//template<> auto InputData<2016, 7, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 7, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // abba[mnop]qrst

  auto ABBA = [](const std::string& s) -> bool
    {
      for (int i = 0; i < s.size() - 3; ++i)
      {
        if (s[i] == s[i + 3] && s[i + 1] == s[i + 2] && s[i] != s[i + 1]) return true;
      }
      return false;
    };

  int n{ 0 };
  for (const auto& line : v)
  {
    std::vector<std::string> good{};
    std::vector<std::string> bad{};

    bool g{ true };
    std::string collect{};
    for (const char& c : line)
    {
      switch (c)
      {
        case '[': assert(g);  g = false; good.push_back(collect); collect.clear(); break;
        case ']': assert(!g); g = true;  bad. push_back(collect); collect.clear(); break;
        default: collect.push_back(c);
      }
    }
    if (collect.size() > 0)
    {
      assert(g);
      good.push_back(collect);
    }


    g = true;
    for (int i = 0; i < bad.size(); ++i)
    {
      if (ABBA(bad[i]))
      {
        g = false;
        break;
      }
    }
    if (!g) continue;
    for (int i = 0; i < good.size(); ++i)
    {
      if (ABBA(good[i]))
      {
        ++n;
        break;
      }
    }

  }
  return n;
}

//template<> auto InputData<2016, 7, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 7, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using List = std::vector<std::string>;

  // abba[mnop]qrst

  auto ABA = [](const std::string& s) -> List
    {
      List l{};
      for (int i = 0; i < s.size() - 2; ++i)
      {
        if (s[i] == s[i + 2] && s[i] != s[i + 1])
        {
          l.push_back(s.substr(i, 2));
        }
      }
      return l;
    };
  auto BAB = [](const std::string& s) -> List
    {
      List l{};
      for (int i = 0; i < s.size() - 2; ++i)
      {
        if (s[i] == s[i + 2] && s[i] != s[i + 1])
        {
          l.push_back(s.substr(i+1, 1) + s[i]); // insert reverted to enable comparison
        }
      }
      return l;
    };

  int n{ 0 };
  for (const auto& line : v)
  {
    List good{};
    List bad{};

    bool g{ true };
    std::string collect{};
    for (const char& c : line)
    {
      switch (c)
      {
        case '[': assert(g);  g = false; good.push_back(collect); collect.clear(); break;
        case ']': assert(!g); g = true;  bad. push_back(collect); collect.clear(); break;
        default: collect.push_back(c);
      }
    }
    if (collect.size() > 0)
    {
      assert(g);
      good.push_back(collect);
    }


    List b{};
    for (int i = 0; i < bad.size(); ++i)
    {
      b.append_range(BAB(bad[i]));
    }
    bool SSL{ false };
    for (int i = 0; i < good.size(); ++i)
    {
      const List& l = ABA(good[i]);
      for (const auto& sg : l)
      {
        for (const auto& sb : b)
        {
          if (sb == sg) SSL = true;
        }
      }
    }

    if (SSL) ++n;
  }

  // 242 is too low
  return n;
}
