void AoC2021_15A(std::istream& input)
{
  struct H
  {
    static int GetIndex(int x, int y)
    {
      return x * 1000 + y;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  using Number = int;
  struct Path
  {
    Number risk{ 0 };
    int x{ 0 };
    int y{ 0 };
    std::string s{};
  };

  std::map<int, Path> path{};
  Path p{};
  p.s += v[0][0];
  p.risk = 0;
  path.insert({ 0,p });

  std::map<int, Path> path0{};
  bool more = false;
  do
  {
    more = false;
    for (const auto p : path)
    {
      if (p.second.x < v[0].size() - 1)
      {
        Path p0 = p.second;
        p0.x++;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path0.find(H::GetIndex(p0.x, p0.y));
        if (it == path0.end())
        {
          path0.insert({ H::GetIndex(p0.x,p0.y),p0 });
          more = true;
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            more = true;
          }
        }
      }
      if (p.second.x > 0)
      {
        Path p0 = p.second;
        p0.x--;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path0.find(H::GetIndex(p0.x, p0.y));
        if (it == path0.end())
        {
          path0.insert({ H::GetIndex(p0.x,p0.y),p0 });
          more = true;
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            more = true;
          }
        }
      }
      if (p.second.y < v.size() - 1)
      {
        Path p0 = p.second;
        p0.y++;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path0.find(H::GetIndex(p0.x, p0.y));
        if (it == path0.end())
        {
          path0.insert({ H::GetIndex(p0.x,p0.y),p0 });
          more = true;
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            more = true;
          }
        }
      }
      if (p.second.y > 0)
      {
        Path p0 = p.second;
        p0.y--;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path0.find(H::GetIndex(p0.x, p0.y));
        if (it == path0.end())
        {
          path0.insert({ H::GetIndex(p0.x,p0.y),p0 });
          more = true;
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            more = true;
          }
        }
      }

    }
    path = path0;
  } while (more);

  const auto& it = path.find(H::GetIndex(static_cast<int>(v[0].size()) - 1, static_cast<int>(v.size()) - 1));
  int z = 0;
  for (int i = 1; i < it->second.s.size(); ++i)
  {
    z += it->second.s[i] - '0';
  }
  std::cout << it->second.risk << ' ' << z << std::endl;
}

void AoC2021_15B(std::istream& input)
{

  struct H
  {
    static int GetIndex(int x, int y)
    {
      return x * 1000 + y;
    }

    static void inc(std::vector<std::string>& v)
    {
      for (int i = 0; i < v.size(); ++i)
        for (int j = 0; j < v[0].size(); ++j)
        {
          if (++v[i][j] == ':') v[i][j] = '1';
        }
    }
  };

  std::vector<std::string> v0 = ReadLines(input);                // read all lines into vector

  std::vector<std::string> v1 = v0;
  H::inc(v1);
  std::vector<std::string> v2 = v1;
  H::inc(v2);
  std::vector<std::string> v3 = v2;
  H::inc(v3);
  std::vector<std::string> v4 = v3;
  H::inc(v4);
  std::vector<std::string> v5 = v4;
  H::inc(v5);
  std::vector<std::string> v6 = v5;
  H::inc(v6);
  std::vector<std::string> v7 = v6;
  H::inc(v7);
  std::vector<std::string> v8 = v7;
  H::inc(v8);

  std::vector<std::string> v;
  v.resize(v0.size() * 5);
  size_t N = v0.size();
  for (int i = 0; i < N; ++i)
  {
    v[i + 0 * N] = v0[i] + v1[i] + v2[i] + v3[i] + v4[i];
    v[i + 1 * N] = v1[i] + v2[i] + v3[i] + v4[i] + v5[i];
    v[i + 2 * N] = v2[i] + v3[i] + v4[i] + v5[i] + v6[i];
    v[i + 3 * N] = v3[i] + v4[i] + v5[i] + v6[i] + v7[i];
    v[i + 4 * N] = v4[i] + v5[i] + v6[i] + v7[i] + v8[i];
  }

  using Number = long long;
  struct Path
  {
    Number risk{ 0 };
    int x{ 0 };
    int y{ 0 };
    bool try_xp{ true };
    bool try_xm{ true };
    bool try_yp{ true };
    bool try_ym{ true };
    std::string s{};
  };

  std::map<int, Path> path{};
  Path p{};
  p.s += v[0][0];
  p.risk = 0;
  path.insert({ 0,p });

  std::map<int, Path> path0{};
  bool more = false;
  do
  {
    more = false;
    path0.clear();
    for (auto& p : path)
    {
      if (p.second.x < v[0].size() - 1 && p.second.try_xp)
      {
        Path p0 = p.second;
        p.second.try_xp = false;
        p0.x++;
        p0.try_xm = true;
        p0.try_xp = true;
        p0.try_ym = true;
        p0.try_yp = true;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path.find(H::GetIndex(p0.x, p0.y));
        if (it == path.end())
        {
          const auto& it0 = path0.find(H::GetIndex(p0.x, p0.y));
          if (it0 == path0.end())
          {
            path0.insert({ H::GetIndex(p0.x, p0.y),p0 });
            more = true;
          }
          else
          {
            if (it0->second.risk > p0.risk)
            {
              it0->second.s = p0.s;
              it0->second.risk = p0.risk;
              it0->second.try_xm = true;
              it0->second.try_xp = true;
              it0->second.try_ym = true;
              it0->second.try_yp = true;
              more = true;
            }
          }
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            it->second.try_xm = true;
            it->second.try_xp = true;
            it->second.try_ym = true;
            it->second.try_yp = true;
            more = true;
          }
        }
      }
      if (p.second.x > 0 && p.second.try_xm)
      {
        Path p0 = p.second;
        p.second.try_xm = false;
        p0.x--;
        p0.try_xm = true;
        p0.try_xp = true;
        p0.try_ym = true;
        p0.try_yp = true;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path.find(H::GetIndex(p0.x, p0.y));
        if (it == path.end())
        {
          const auto& it0 = path0.find(H::GetIndex(p0.x, p0.y));
          if (it0 == path0.end())
          {
            path0.insert({ H::GetIndex(p0.x, p0.y),p0 });
            more = true;
          }
          else
          {
            if (it0->second.risk > p0.risk)
            {
              it0->second.s = p0.s;
              it0->second.risk = p0.risk;
              it0->second.try_xm = true;
              it0->second.try_xp = true;
              it0->second.try_ym = true;
              it0->second.try_yp = true;
              more = true;
            }
          }
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            it->second.try_xm = true;
            it->second.try_xp = true;
            it->second.try_ym = true;
            it->second.try_yp = true;
            more = true;
          }
        }
      }
      if (p.second.y < v.size() - 1 && p.second.try_yp)
      {
        Path p0 = p.second;
        p.second.try_yp = false;
        p0.y++;
        p0.try_xm = true;
        p0.try_xp = true;
        p0.try_ym = true;
        p0.try_yp = true;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path.find(H::GetIndex(p0.x, p0.y));
        if (it == path.end())
        {
          const auto& it0 = path0.find(H::GetIndex(p0.x, p0.y));
          if (it0 == path0.end())
          {
            path0.insert({ H::GetIndex(p0.x, p0.y),p0 });
            more = true;
          }
          else
          {
            if (it0->second.risk > p0.risk)
            {
              it0->second.s = p0.s;
              it0->second.risk = p0.risk;
              it0->second.try_xm = true;
              it0->second.try_xp = true;
              it0->second.try_ym = true;
              it0->second.try_yp = true;
              more = true;
            }
          }
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            it->second.try_xm = true;
            it->second.try_xp = true;
            it->second.try_ym = true;
            it->second.try_yp = true;
            more = true;
          }
        }
      }
      if (p.second.y > 0 && p.second.try_ym)
      {
        Path p0 = p.second;
        p.second.try_ym = false;
        p0.y--;
        p0.try_xm = true;
        p0.try_xp = true;
        p0.try_ym = true;
        p0.try_yp = true;
        p0.s += v[p0.y][p0.x];
        p0.risk += v[p0.y][p0.x] - '0';
        const auto& it = path.find(H::GetIndex(p0.x, p0.y));
        if (it == path.end())
        {
          const auto& it0 = path0.find(H::GetIndex(p0.x, p0.y));
          if (it0 == path0.end())
          {
            path0.insert({ H::GetIndex(p0.x, p0.y),p0 });
            more = true;
          }
          else
          {
            if (it0->second.risk > p0.risk)
            {
              it0->second.s = p0.s;
              it0->second.risk = p0.risk;
              it0->second.try_xm = true;
              it0->second.try_xp = true;
              it0->second.try_ym = true;
              it0->second.try_yp = true;
              more = true;
            }
          }
        }
        else
        {
          if (it->second.risk > p0.risk)
          {
            it->second.s = p0.s;
            it->second.risk = p0.risk;
            it->second.try_xm = true;
            it->second.try_xp = true;
            it->second.try_ym = true;
            it->second.try_yp = true;
            more = true;
          }
        }
      }

    }
    path.insert(path0.begin(), path0.end());
  } while (more);

  const auto& it = path.find(H::GetIndex(static_cast<int>(v[0].size()) - 1, static_cast<int>(v.size()) - 1));
  Number z = 0;
  for (int i = 1; i < it->second.s.size(); ++i)
  {
    z += it->second.s[i] - '0';
  }
  std::cout << it->second.risk << ' ' << z << std::endl;
  std::cout << it->second.s << std::endl;

}
