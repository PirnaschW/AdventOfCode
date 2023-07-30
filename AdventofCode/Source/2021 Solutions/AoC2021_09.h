
bool isSmaller(const std::vector<std::vector <int>>& d, int x0, int y0, int x, int y)
{
  if (x < 0 || y < 0 || x >= d.size() || y >= d[0].size()) return true;
  if (d[x0][y0] < d[x][y]) return true;
  return false;
}

bool isReallySmaller(const std::vector<std::vector <int>>& d, int x0, int y0, int x, int y)
{
  if (x < 0 || y < 0 || x >= d.size() || y >= d[0].size()) return false;
  if (d[x0][y0] < d[x][y]) return true;
  return false;
}

bool isPart(const std::vector<std::vector <int>>& d, int /*x0*/, int /*y0*/, int x, int y)
{
  if (x < 0 || y < 0 || x >= d.size() || y >= d[0].size()) return false;
  if (d[x][y] > 8) return false;
  return true;
}

template<> Number AoC<2021, 9, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::vector <int>> d{};
  d.resize(v.size());
  for (int i = 0; i < v.size(); ++i) d[i].resize(v[0].size());

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      d[i][j] = v[i][j] - '0';
    }
  }

  int z{ 0 };
  int n{ 0 };
  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      if (isSmaller(d, i, j, i - 1, j) && isSmaller(d, i, j, i + 1, j) && isSmaller(d, i, j, i, j - 1) && isSmaller(d, i, j, i, j + 1))
      {
        ++n;
        z += d[i][j] + 1;
      }
    }
  }

  return z;
}



void spread(std::vector<std::vector <int>>& d, int x, int y, int bid)
{
  if (isPart(d, x, y, x - 1, y))
  {
    d[x - 1][y] = bid;
    spread(d, x - 1, y, bid);
  }
  if (isPart(d, x, y, x + 1, y))
  {
    d[x + 1][y] = bid;
    spread(d, x + 1, y, bid);
  }
  if (isPart(d, x, y, x, y - 1))
  {
    d[x][y - 1] = bid;
    spread(d, x, y - 1, bid);
  }
  if (isPart(d, x, y, x, y + 1))
  {
    d[x][y + 1] = bid;
    spread(d, x, y + 1, bid);
  }
}

template<> Number AoC<2021, 9, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::vector <int>> d{};
  d.resize(v.size());
  for (int i = 0; i < v.size(); ++i) d[i].resize(v[0].size());

  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      d[i][j] = v[i][j] - '0';
    }
  }

  auto b = d;
  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      if (d[i][j] == 9) b[i][j] = 0;
      else b[i][j] = 1;
    }
  }


  int bid{ 10 };
  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      if (d[i][j] > 8) continue;
      //if (b[i][j] != 0) continue;
      //b[i][j] = bid;
      spread(d, i, j, bid);
      ++bid;
    }
  }

  std::vector<int> basins{};
  basins.resize(bid - 10);
  for (int i = 0; i < v.size(); ++i)
  {
    for (int j = 0; j < v[i].size(); ++j)
    {
      if (d[i][j] > 9) ++basins[d[i][j] - 10];
    }
  }

  std::sort(basins.begin(), basins.end());

//  std::cout << basins[basins.size() - 1] * basins[basins.size() - 2] * basins[basins.size() - 3] << std::endl;
  return basins[basins.size() - 1] * basins[basins.size() - 2] * basins[basins.size() - 3];
}
