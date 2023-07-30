template<> Number AoC<2020, 24, A>(std::istream& input)
{
  struct H
  {
    static int Index(int x, int y) { return (x << 16) + y; }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::unordered_set<int> black{};
  for (const auto& line : v)
  {
    int p{ 0 };
    int x{ 0 };
    int y{ 0 };
    while (p < line.size())
    {
      switch (line[p++])
      {
        case 'e': ++x; break;
        case 'w': --x; break;
        case 'n':
          switch (line[p++])
          {
            case 'e': ++y;      break;
            case 'w': ++y; --x; break;
            default: assert(false); break;
          }
          break;
        case 's':
          switch (line[p++])
          {
            case 'e': --y; ++x; break;
            case 'w': --y;      break;
            default: assert(false); break;
          }
          break;
        default: assert(false); break;
      }
    }

    if (!black.erase(H::Index(x,y))) black.insert(H::Index(x, y));
  }

  return black.size();
}

template<> Number AoC<2020, 24, B>(std::istream& input)
{
  struct H
  {
    static int Index(int x, int y) { return ((x + (1 << 14)) << 16) + (y + (1 << 14)); }
    static int GetX(int index) { return (index >> 16) - (1<<14); }
    static int GetY(int index) { return (index % (1 << 16)) - (1 << 14); }
    static int GetMaxX(const std::unordered_set<int>& black) { int max{ -(1 << 16) };  for (const auto& t : black) if (GetX(t) > max) max = GetX(t); return max; }
    static int GetMinX(const std::unordered_set<int>& black) { int min{   1 << 16  };  for (const auto& t : black) if (GetX(t) < min) min = GetX(t); return min; }
    static int GetMaxY(const std::unordered_set<int>& black) { int max{ -(1 << 16) };  for (const auto& t : black) if (GetY(t) > max) max = GetY(t); return max; }
    static int GetMinY(const std::unordered_set<int>& black) { int min{   1 << 16  };  for (const auto& t : black) if (GetY(t) < min) min = GetY(t); return min; }
    static int CountBlackNeighborTiles(const std::unordered_set<int>& black, int x, int y)
    {
      int n{ 0 };
      if (black.contains(Index(x + 1, y))) n++;
      if (black.contains(Index(x, y + 1))) n++;
      if (black.contains(Index(x - 1, y + 1))) n++;
      if (black.contains(Index(x - 1, y))) n++;
      if (black.contains(Index(x, y - 1))) n++;
      if (black.contains(Index(x + 1, y - 1))) n++;
      return n;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::unordered_set<int> black{};
  for (const auto& line : v)
  {
    int p{ 0 };
    int x{ 0 };
    int y{ 0 };
    while (p < line.size())
    {
      switch (line[p++])
      {
        case 'e': ++x; break;
        case 'w': --x; break;
        case 'n':
          switch (line[p++])
          {
            case 'e': ++y;      break;
            case 'w': ++y; --x; break;
            default: assert(false); break;
          }
          break;
        case 's':
          switch (line[p++])
          {
            case 'e': --y; ++x; break;
            case 'w': --y;      break;
            default: assert(false); break;
          }
          break;
        default: assert(false); break;
      }
    }

    if (!black.erase(H::Index(x, y))) black.insert(H::Index(x, y));
  }

  for (int i = 0; i < 100; ++i)
  {
    std::unordered_set<int> black0 = black;
    int minx = H::GetMinX(black) - 2;
    int maxx = H::GetMaxX(black) + 2;
    int miny = H::GetMinY(black) - 2;
    int maxy = H::GetMaxY(black) + 2;
    for (int x = minx; x <= maxx; ++x)
      for (int y = miny; y <= maxy; ++y)
      {
        if (black.contains(H::Index(x, y)))
        {
          int b = H::CountBlackNeighborTiles(black, x, y);
          if (b != 1 && b != 2) black0.erase(H::Index(x, y));
        }
        else
        {
          int b = H::CountBlackNeighborTiles(black, x, y);
          if (b == 2) black0.insert(H::Index(x, y));
        }
      }
    black = black0;
  }

  return black.size();
}
