
int spread(std::vector<std::vector<int>>& e, int x, int y);

int increase(std::vector<std::vector<int>>& e, int x, int y)
{
  if (x < 0 || y < 0 || x >= e.size() || y >= e[0].size()) return 0;
  if (e[x][y] == 0) return 0; // no double flashes
  if (++e[x][y] > 9)
  {
    e[x][y] = 0;
    return 1 + spread(e, x, y);
  }
  return 0;
}

int spread(std::vector<std::vector<int>>& e, int x, int y)
{
  int z{ 0 };
  z += increase(e, x + 1, y - 1);
  z += increase(e, x + 1, y);
  z += increase(e, x + 1, y + 1);
  z += increase(e, x, y - 1);
  z += increase(e, x, y + 1);
  z += increase(e, x - 1, y - 1);
  z += increase(e, x - 1, y);
  z += increase(e, x - 1, y + 1);
  return z;
}


void AoC2021_11A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<std::vector<int>> e{};
  e.resize(v.size());
  for (auto& l : e) l.resize(v[0].size());

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      e[i][j] = v[i][j] - '0';
    }
  }

  int z{ 0 };
  for (int l = 0; l < 100; ++l) // do a hndred times
  {
    auto e0 = e;
    for (int i = 0; i < v.size(); ++i)
    {
      for (int j = 0; j < v[i].size(); ++j)
      {
        ++e0[i][j];
      }
    }
    for (int i = 0; i < v.size(); ++i)
    {
      for (int j = 0; j < v[i].size(); ++j)
      {
        if (e0[i][j] > 9)
        {
          e0[i][j] = 0;
          ++z;
          z += spread(e0, i, j);
        }
      }
    }

    e = e0;
  }

  std::cout << z << std::endl;
}

void AoC2021_11B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<std::vector<int>> e{};
  e.resize(v.size());
  for (auto& l : e) l.resize(v[0].size());

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      e[i][j] = v[i][j] - '0';
    }
  }

  int z{ 0 };
  for (int l = 0; l < 100000000; ++l) // do a hndred times
  {
    auto e0 = e;
    for (int i = 0; i < v.size(); ++i)
    {
      for (int j = 0; j < v[i].size(); ++j)
      {
        ++e0[i][j];
      }
    }
    for (int i = 0; i < v.size(); ++i)
    {
      for (int j = 0; j < v[i].size(); ++j)
      {
        if (e0[i][j] > 9)
        {
          e0[i][j] = 0;
          ++z;
          z += spread(e0, i, j);
        }
      }
    }

    bool sync = true;
    for (int i = 0; i < v.size(); ++i)
    {
      for (int j = 0; j < v[i].size(); ++j)
      {
        if (e0[i][j] != 0) sync = false;
      }
    }
    if (sync)
    {
      std::cout << l << std::endl;
      return;
    }

    e = e0;
  }

  std::cout << z << std::endl;
}
