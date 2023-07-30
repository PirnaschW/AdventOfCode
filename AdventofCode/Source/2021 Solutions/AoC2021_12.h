void TryAll(const std::unordered_multimap<std::string, std::string>& conn, std::vector< std::vector<std::string>>& paths, std::vector<std::string>& path, const std::string& from)
{
  auto list = conn.equal_range(from);
  for (auto& it = list.first; it != list.second; ++it)
  {
    if (islower(it->second[0]))
    {
      bool go = true;
      for (const auto& p : path)
      {
        if (p == it->second)
        {
          go = false;
          break;  // don't go backwards
        }
      }
      if (!go) continue;
    }
    auto path0 = path;
    path0.emplace_back(it->second);
    if (it->second == "end")
    {
      paths.emplace_back(path0);
    }
    else {
      auto conn0 = conn;
      for (auto it0 = conn0.begin(); it0 != conn0.end(); ++it0)
      {
        if (it0->first == it->first && it0->second == it->second)
        {
          conn0.erase(it0);
          break;
        }
      }
      TryAll(conn0, paths, path0, it->second);
    }
  }
}

void TryAllB(const std::unordered_multimap<std::string, std::string>& conn, std::vector< std::vector<std::string>>& paths, std::vector<std::string>& path, const std::string& from, bool allowdouble)
{
  auto list = conn.equal_range(from);
  for (auto& it = list.first; it != list.second; ++it)
  {
    bool allowdouble0 = allowdouble;
    if (islower(it->second[0]))
    {
      bool go = true;
      if (it->second == "start")
      {
        go = false;
      }
      else for (const auto& p : path)
      {
        if (p == it->second)
        {
          if (allowdouble0)
          {
            allowdouble0 = false;
            break;
          }
          else
          {
            go = false;
            break;  // don't go backwards
          }
        }
      }
      if (!go) continue;
    }
    auto path0 = path;
    path0.emplace_back(it->second);
    if (it->second == "end")
    {
      paths.emplace_back(path0);
    }
    else {
//      auto conn0 = conn;
      TryAllB(conn, paths, path0, it->second, allowdouble0);
    }
  }
}

template<> Number AoC<2021, 12, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::unordered_multimap<std::string, std::string> conn{};

  for (const auto& line : v)
  {
    size_t n = line.find('-');
    std::string p1 = line.substr(0, n);
    std::string p2 = line.substr(n + 1, line.size() - n - 1);

    conn.emplace(p1, p2);
    conn.emplace(p2, p1);
  }

  std::vector< std::vector<std::string>> paths{};
  std::vector<std::string> path{};
  path.emplace_back("start");
  TryAll(conn, paths, path, "start");

  return paths.size();
}

template<> Number AoC<2021, 12, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::unordered_multimap<std::string, std::string> conn{};

  for (const auto& line : v)
  {
    size_t n = line.find('-');
    std::string p1 = line.substr(0, n);
    std::string p2 = line.substr(n + 1, line.size() - n - 1);

    conn.emplace(p1, p2);
    conn.emplace(p2, p1);
  }

  std::vector< std::vector<std::string>> paths{};
  std::vector<std::string> path{};
  path.emplace_back("start");
  TryAllB(conn, paths, path, "start", true);

  return paths.size();
}
