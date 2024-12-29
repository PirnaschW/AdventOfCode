//template<> auto InputData<2023, 11, A>() { return
//"...#......\n"
//".......#..\n"
//"#.........\n"
//"..........\n"
//"......#...\n"
//".#........\n"
//".........#\n"
//"..........\n"
//".......#..\n"
//"#...#.....\n";}; // Result: 374
template<> Number AoC<2023, 11, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  std::vector<int> xindex(v[0].size(),0);
  std::vector<int> yindex(v.size(),0);

  auto EmptyV = [&v](int x)->bool
    {
      for (int y = 0; y < std::ssize(v); ++y)
      {
        if (v[y][x] != '.')
        {
          return false;
        }
      }
      return true;
    };
  auto EmptyH = [&v](int y)->bool
    {
      for (int x = 0; x < std::ssize(v[0]); ++x)
      {
        if (v[y][x] != '.')
        {
          return false;
        }
      }
      return true;
    };

  for (int x = 0, xx = 0; x < std::ssize(v[0]); ++x, ++xx)
  {
    xindex[x] = xx;
    if (EmptyV(x)) ++xx;
  }

  for (int y = 0, yy = 0; y < std::ssize(v); ++y, ++yy)
  {
    yindex[y] = yy;
    if (EmptyH(y)) ++yy;
  }

  class Point
  {
  public:
    int x{};
    int y{};
  public:
    bool operator == (const Point& p) const noexcept { return x == p.x && y == p.y; }
    bool operator != (const Point& p) const noexcept { return x != p.x || y != p.y; }
  };

  std::vector<Point> g{};
  for (int x = 0; x < std::ssize(v[0]); ++x)
    for (int y = 0; y < std::ssize(v); ++y)
    {
      if (v[y][x] == '#')
        g.push_back(Point(x, y));
    }

  Number res{ 0 };
  for (int g1 = 0; g1 < std::ssize(g); ++g1)
  {
    for (int g2 = g1+1; g2 < std::ssize(g); ++g2)
    {
      res += std::abs(xindex[g[g2].x] - xindex[g[g1].x]) + std::abs(yindex[g[g2].y] - yindex[g[g1].y]);
    }
  }

  return res;
}

//template<> auto InputData<2023, 11, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 11, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  std::vector<Number> xindex(v[0].size(),0);
  std::vector<Number> yindex(v.size(),0);

  auto EmptyV = [&v](int x)->bool
    {
      for (int y = 0; y < std::ssize(v); ++y)
      {
        if (v[y][x] != '.')
        {
          return false;
        }
      }
      return true;
    };
  auto EmptyH = [&v](int y)->bool
    {
      for (int x = 0; x < std::ssize(v[0]); ++x)
      {
        if (v[y][x] != '.')
        {
          return false;
        }
      }
      return true;
    };

  for (auto x = 0, xx = 0; x < std::ssize(v[0]); ++x, ++xx)
  {
    xindex[x] = xx;
    if (EmptyV(x)) xx += 999'999;
  }

  for (auto y = 0, yy = 0; y < std::ssize(v); ++y, ++yy)
  {
    yindex[y] = yy;
    if (EmptyH(y)) yy += 999'999;
  }

  class Point
  {
  public:
    int x{};
    int y{};
  public:
    bool operator == (const Point& p) const noexcept { return x == p.x && y == p.y; }
    bool operator != (const Point& p) const noexcept { return x != p.x || y != p.y; }
  };

  std::vector<Point> g{};
  for (int x = 0; x < std::ssize(v[0]); ++x)
    for (int y = 0; y < std::ssize(v); ++y)
    {
      if (v[y][x] == '#')
        g.push_back(Point(x, y));
    }

  Number res{ 0 };
  for (int g1 = 0; g1 < std::ssize(g); ++g1)
  {
    for (int g2 = g1+1; g2 < std::ssize(g); ++g2)
    {
      res += std::abs(xindex[g[g2].x] - xindex[g[g1].x]) + std::abs(yindex[g[g2].y] - yindex[g[g1].y]);
    }
  }

  return res;
}
