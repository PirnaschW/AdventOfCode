void AoC2020_06B(std::istream& input)
{
  std::vector<std::vector<std::string>> v{};
  v.reserve(100);

  std::string line{};
  std::vector<std::string> gv{};
  while (getline(input, line))
  {
    if (line.size() == 0)
    {
      v.emplace_back(gv);
      gv.clear();
    }
    else
    {
      gv.emplace_back(line);
    }
  }
  // done reading input

  std::vector<size_t> count{};
  count.reserve(v.size());

  size_t z{ 0 };
  std::unordered_set<char> set{};
  for (const auto& g : v)
  {
    switch (g.size())
    {
      case 0: // error
        break;
      case 1:
        z += g[0].size();
        break;
      default: // more than one
        set.clear();
        for (auto& c : g[0])
        {
          set.insert(c);
        }
        for (int i = 1; i < g.size(); ++i)
        {
          std::unordered_set<char> set0{};
          for (auto& c : set)
          {
            if (g[i].contains(c)) set0.insert(c);
          }
          set = set0;
          if (set.size() == 0) break;
        }
        z += set.size();
        break;
    }
  }

  std::cout << z << std::endl;
}

void AoC2020_06A(std::istream& input)
{
  std::vector<std::vector<std::string>> v{};
  v.reserve(100);

  std::string line{};
  std::vector<std::string> gv{};
  while (getline(input, line))
  {
    if (line.size() == 0)
    {
      v.emplace_back(gv);
      gv.clear();
    }
    else
    {
      gv.emplace_back(line);
    }
  }
  // done reading input

  std::vector<size_t> count{};
  count.reserve(v.size());

  size_t z{ 0 };
  for (const auto& g : v)
  {
    std::unordered_set<char> set{};
    for (const auto& s : g)
    {
      for (auto& c : s)
      {
        set.insert(c);
      }
    }
    count.emplace_back(set.size());
    z += set.size();
  }

  std::cout << z << std::endl;
}
