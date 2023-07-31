//template<> auto InputData<2019, 10, A>() { return ".#..#\n.....\n#####\n....#\n...##\n"; }  // best is [3][4] -> 8
//template<> auto InputData<2019, 10, A>() { return "......#.#.\n#..#.#....\n..#######.\n.#.#.###..\n.#..#.....\n..#....#.#\n#..#....#.\n.##.#..###\n##...#..#.\n.#....####\n"; }  // best is [5][8] -> 33

template<> Number AoC<2019, 10, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  using Coord = char;

  using AsteroidMap = std::vector<std::vector<bool>>;
  AsteroidMap aMap{};
  aMap.resize(v[0].size());
  for (Coord x = 0; x < v[0].size(); ++x)
  {    
    aMap[x].resize(v.size());
  }

  using Count = std::vector<std::vector<Coord>>;
  Count aCount{};
  aCount.resize(v[0].size());
  for (Coord x = 0; x < v[0].size(); ++x)
  {    
    aCount[x].resize(v.size());
  }

  for (Coord y = 0; y < v.size(); ++y)
  {
    const auto& line = v[y];
    for (Coord x = 0; x < line.size(); ++x)
    {
      aMap[x][y] = (line[x] == '#') ? true : false;
    }
  }

  struct H
  {
    constexpr static bool isSmallPrime(Number a)
    {
      return a == 2 || a == 3 || a == 5 || a == 7 || a == 11 || a == 13 || a == 17 || a == 19 || a == 23 || a == 29;
    }
    constexpr static bool coPrime(Number a, Number b)
    {
      return gcd(a,b) > 1;
    }
    constexpr static Number gcd(Number a, Number b)
    {
      if (a == b) return a;
      if (a == 0) return b;
      if (b == 0) return a;
      return a > b ? gcd(a - b, b) : gcd(b - a, a);
    }

    static bool isLocation(Coord xMax, Coord yMax, Coord x, Coord y)
    {
      if (x < 0 || x >= xMax) return false;
      if (y < 0 || y >= yMax) return false;
      return true;
    }
    static bool canSee(const AsteroidMap& aMap, Coord x0, Coord y0, Coord x, Coord y)
    {
      if (x == x0 && y == y0) return false;
      Coord dx = x - x0;
      Coord dy = y - y0;
      Coord adx = dx > 0 ? dx : -dx;
      Coord ady = dy > 0 ? dy : -dy;
      //if (adx != ady && !(H::isSmallPrime(adx) && H::isSmallPrime(ady)))
      //{
      const Coord div = (Coord) H::gcd(adx, ady);
      dx /= div;
      dy /= div;
      //}

      for (Coord n = 1; x0 + n * dx != x || y0 + n * dy != y; ++n)
      {
        assert(isLocation((Coord) aMap[0].size(), (Coord) aMap.size(), x0 + n * dx, y0 + n * dy));
        if (aMap[x0 + n * dx][y0 + n * dy]) return false;
      }
      return true;
    }
  };

  // try all possible positions
  Number zmax{ 0 };
  Coord xmax{ -1 };
  Coord ymax{ -1 };
  for (Coord y = 0; y < v.size(); ++y)
  {
    for (Coord x = 0; x < v[0].size(); ++x)
    {
      if (!aMap[x][y]) continue; // must be on an asteroid

      Number z{ 0 };

      for (Coord ya = 0; ya < v.size(); ++ya)
      {
        for (Coord xa = 0; xa < v[0].size(); ++xa)
        {
          if (aMap[xa][ya])
          {
            if (H::canSee(aMap, xa, ya, x, y)) ++z;
          }
        }
      }

      if (z > zmax)
      {
        zmax = z;
        xmax = x;
        ymax = y;
      }
      aCount[x][y] = (Coord) z;
    }
  }

  //std::cout << std::endl;
  //for (Coord y = 0; y < v.size(); ++y)
  //{
  //  for (Coord x = 0; x < v[0].size(); ++x)
  //  {
  //    std::cout << (char) (aMap[x][y] ? aCount[x][y] + '0' : '.');
  //  }
  //  std::cout << std::endl;
  //}

  return zmax;
}

//template<> auto InputData<2019, 10, B>() { return ".#..#\n.....\n#####\n....#\n...##\n"; }  // best is [3][4] -> 8
//template<> auto InputData<2019, 10, B>() { return "......#.#.\n#..#.#....\n..#######.\n.#.#.###..\n.#..#.....\n..#....#.#\n#..#....#.\n.##.#..###\n##...#..#.\n.#....####\n"; }  // best is [5][8] -> 33
template<> Number AoC<2019, 10, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  using Coord = char;

  using AsteroidMap = std::vector<std::vector<bool>>;
  AsteroidMap aMap{};
  aMap.resize(v[0].size());
  for (Coord x = 0; x < v[0].size(); ++x)
  {
    aMap[x].resize(v.size());
  }

  using Count = std::vector<std::vector<Coord>>;
  Count aCount{};
  aCount.resize(v[0].size());
  for (Coord x = 0; x < v[0].size(); ++x)
  {
    aCount[x].resize(v.size());
  }

  for (Coord y = 0; y < v.size(); ++y)
  {
    const auto& line = v[y];
    for (Coord x = 0; x < line.size(); ++x)
    {
      aMap[x][y] = (line[x] == '#') ? true : false;
    }
  }

  struct H
  {
    constexpr static bool isSmallPrime(Number a)
    {
      return a == 2 || a == 3 || a == 5 || a == 7 || a == 11 || a == 13 || a == 17 || a == 19 || a == 23 || a == 29;
    }
    constexpr static bool coPrime(Number a, Number b)
    {
      return gcd(a, b) > 1;
    }
    constexpr static Number gcd(Number a, Number b)
    {
      if (a == b) return a;
      if (a == 0) return b;
      if (b == 0) return a;
      return a > b ? gcd(a - b, b) : gcd(b - a, a);
    }

    static bool isLocation(Coord xMax, Coord yMax, Coord x, Coord y)
    {
      if (x < 0 || x >= xMax) return false;
      if (y < 0 || y >= yMax) return false;
      return true;
    }
    static bool canSee(const AsteroidMap& aMap, Coord x0, Coord y0, Coord x, Coord y)
    {
      if (x == x0 && y == y0) return false;
      Coord dx = x - x0;
      Coord dy = y - y0;
      Coord adx = dx > 0 ? dx : -dx;
      Coord ady = dy > 0 ? dy : -dy;
      //if (adx != ady && !(H::isSmallPrime(adx) && H::isSmallPrime(ady)))
      //{
      const Coord div = (Coord) H::gcd(adx, ady);
      dx /= div;
      dy /= div;
      //}

      for (Coord n = 1; x0 + n * dx != x || y0 + n * dy != y; ++n)
      {
        assert(isLocation((Coord) aMap[0].size(), (Coord) aMap.size(), x0 + n * dx, y0 + n * dy));
        if (aMap[x0 + n * dx][y0 + n * dy]) return false;
      }
      return true;
    }
    static Coord depthTo(const AsteroidMap& aMap, Coord x0, Coord y0, Coord x, Coord y)
    {
      Coord depth{ 1 };
      assert(x != x0 || y != y0);

      Coord dx = x - x0;
      Coord dy = y - y0;
      Coord adx = dx > 0 ? dx : -dx;
      Coord ady = dy > 0 ? dy : -dy;
      const Coord div = (Coord) H::gcd(adx, ady);
      dx /= div;
      dy /= div;

      for (Coord n = 1; x0 + n * dx != x || y0 + n * dy != y; ++n)
      {
        assert(isLocation((Coord) aMap[0].size(), (Coord) aMap.size(), x0 + n * dx, y0 + n * dy));
        if (aMap[x0 + n * dx][y0 + n * dy]) ++depth;
      }
      return depth;
    }
  };

  // try all possible positions
  Number zmax{ 0 };
  Coord xmax{ -1 };
  Coord ymax{ -1 };
  for (Coord y = 0; y < v.size(); ++y)
  {
    for (Coord x = 0; x < v[0].size(); ++x)
    {
      if (!aMap[x][y]) continue; // must be on an asteroid

      Number z{ 0 };

      for (Coord ya = 0; ya < v.size(); ++ya)
      {
        for (Coord xa = 0; xa < v[0].size(); ++xa)
        {
          if (aMap[xa][ya])
          {
            if (H::canSee(aMap, xa, ya, x, y)) ++z;
          }
        }
      }

      if (z > zmax)
      {
        zmax = z;
        xmax = x;
        ymax = y;
      }
      aCount[x][y] = (Coord) z;
    }
  }

  // best position is now known
  Coord x0 = xmax;
  Coord y0 = ymax;

  class AsteroidDepth
  {
  public:
    double angle{};  // viewing angle, with 0 = north, then clockwise to 2*pi
    Coord depth{};    // viewing depth of the asteroid (1 = visible, 2 = once hidden, etc.
    Coord x{};  // location of the asteroid
    Coord y{};  // location of the asteroid
  };

  using DepthList = std::vector<AsteroidDepth>;
  DepthList adList{};

  for (Coord ya = 0; ya < v.size(); ++ya)
  {
    for (Coord xa = 0; xa < v[0].size(); ++xa)
    {
      if (xa == x0 && ya == y0) continue;

      if (aMap[xa][ya])
      {
        Coord depth = H::depthTo(aMap, xa, ya, x0, y0);
        double dx = xa - x0;
        double dy = ya - y0;
        double angle = -atan2(dx,dy);
        adList.push_back(AsteroidDepth{ angle,depth,xa,ya });
      }
    }
  }

  std::sort(adList.begin(), adList.end(), [](const AsteroidDepth& a, const AsteroidDepth& b) { if (a.depth > b.depth) return false; if (a.depth < b.depth) return true; return a.angle < b.angle; });

  Number z = 100 * adList[199].x + adList[199].y;
  return z;
}
