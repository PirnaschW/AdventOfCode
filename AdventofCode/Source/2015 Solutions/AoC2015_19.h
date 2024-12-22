//template<> auto InputData<2015, 19, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 19, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Map = std::unordered_multimap < std::string, std::string, decltype([](const std::string& s) { return std::hash<std::string>()(s); }), decltype([](const std::string& s1, const std::string& s2) { return s1 == s2; })>;
  Map map{};

  using Repl = std::unordered_set<std::string>;
  Repl repl{};

  constexpr unsigned int BufSize{ 32 };
  for (int i=0; i<v.size()-2; ++i)
  {
    char mol1[BufSize]{};
    char mol2[BufSize]{};
    // Al => ThF
    int z = sscanf_s(v[i].c_str(), "%s => %s", mol1, BufSize, mol2, BufSize);
    assert(z == 2);

    map.insert({ mol1, mol2 });
  }

  std::string start = v[v.size() - 1];

  for (int i = 0; i < start.size(); ++i)
  {
    for (auto it = map.cbegin(); it != map.cend(); ++it)
    {
      size_t len = it->first.size();

      if (start.substr(i, len) == it->first)
      {
        std::string res = start.substr(0, i) + it->second + start.substr(i + len);
        if (!repl.contains(res)) repl.insert(res);
      }
    }
  }

  return repl.size();
}

//template<> auto InputData<2015, 19, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 19, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Map = std::multimap < std::string, std::string, decltype([](const std::string& s1, const std::string& s2) { return s1.size() == s2.size() ? s1 > s2 : s1.size() > s2.size(); })>;
  Map map{};

  constexpr unsigned int BufSize{ 32 };
  for (int i=0; i<v.size()-2; ++i)
  {
    char mol1[BufSize]{};
    char mol2[BufSize]{};
    // Al => ThF
    int z = sscanf_s(v[i].c_str(), "%s => %s", mol1, BufSize, mol2, BufSize);
    assert(z == 2);

    map.insert({ mol2, mol1 }); // in reverse!
  }

  std::string start = v[v.size() - 1];

  Number mincount{ 0 };
  bool goon{ true };
  auto TryReducing = [&map, &mincount, &goon](const std::string& start, const Number& count, auto& TryReducing) -> void
    {
      if (start == "e")
      {
        mincount = count;
        goon = false;
        return;
      }
      for (auto it = map.cbegin(); goon && it != map.cend(); ++it)
      {
        for (int i = 0; goon && i < start.size(); ++i)
        {
          size_t len = it->first.size();

          if (start.substr(i, len) == it->first)
          {
            const std::string next = start.substr(0, i) + it->second + start.substr(i + len);
            TryReducing(next, count + 1, TryReducing);
          }
        }
      }
    };

  TryReducing(start, 0, TryReducing);

  return mincount;
}
