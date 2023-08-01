//template<> auto InputData<2019, 12, A>() { return "<x=-1, y=0, z=2>\n<x=2, y=-10, z=-7>\n<x=4, y=-8, z=8>\n<x=3, y=5, z=-1>\n10\n"; }  // after 10 steps: 179
//template<> auto InputData<2019, 12, A>() { return "<x=-8, y=-10, z=0>\n<x=5, y=5, z=10>\n<x=2, y=-7, z=3>\n<x=9, y=-8, z=-3>\n100\n"; }  // after 100 steps: 1940

template<> Number AoC<2019, 12, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  using Coord = short;  // char turns out to be not sufficient!
  constexpr size_t moonCount{ 4 };

  std::array<Coord,moonCount> x{};
  std::array<Coord,moonCount> y{};
  std::array<Coord,moonCount> z{};
  std::array<Coord,moonCount> vx{};
  std::array<Coord,moonCount> vy{};
  std::array<Coord,moonCount> vz{};

  for (int m = 0; m < moonCount; ++m)
  {
    const auto& line = v[m];
    int n = sscanf_s(line.c_str(), "<x=%hd, y=%hd, z=%hd>", &x[m], &y[m], &z[m]);
    assert(n == 3);
  }

  auto diff = [](const Coord& c1, const Coord& c2)->Coord { if (c1 > c2) return 1; if (c1 < c2) return -1; return 0; };

  Number tmax{ 1000 };
  if (v.size() == 5) // it's a test case! the tmax is coming in an extra line
  {
    int n = sscanf_s(v[moonCount].c_str(), "%lld", &tmax);
    assert(n == 1);
  }
  for (int t = 0; t < tmax; ++t)
  {
    std::array<Coord,moonCount> dvx{};
    std::array<Coord,moonCount> dvy{};
    std::array<Coord,moonCount> dvz{};

    for (int m1 = 0; m1 < moonCount; ++m1)
    {
      for (int m2 = 0; m2 < moonCount; ++m2)
      {
        dvx[m1] += diff(x[m2], x[m1]);
        dvy[m1] += diff(y[m2], y[m1]);
        dvz[m1] += diff(z[m2], z[m1]);
      }
    }
    for (int m = 0; m < moonCount; ++m)
    {
      vx[m] += dvx[m];
      vy[m] += dvy[m];
      vz[m] += dvz[m];
    }

    for (int m = 0; m < moonCount; ++m)
    {
      x[m] += vx[m];
      y[m] += vy[m];
      z[m] += vz[m];

      assert(x[m] < std::numeric_limits<Coord>::max() - 1);
      assert(y[m] < std::numeric_limits<Coord>::max() - 1);
      assert(z[m] < std::numeric_limits<Coord>::max() - 1);
      assert(x[m] > std::numeric_limits<Coord>::min() + 1);
      assert(y[m] > std::numeric_limits<Coord>::min() + 1);
      assert(z[m] > std::numeric_limits<Coord>::min() + 1);
    }
  }

  auto tenergy = [](const std::array<Coord, moonCount>& x, const std::array<Coord, moonCount>& y, const std::array<Coord, moonCount>& z, int m)->Number
    { return (Number) (x[m] > 0 ? x[m] : -x[m]) + (Number) (y[m] > 0 ? y[m] : -y[m]) + (Number) (z[m] > 0 ? z[m] : -z[m]); };
  
  Number res{ 0 };
  for (int m = 0; m < moonCount; ++m)
  {
    res += tenergy(x,y,z,m) * tenergy(vx,vy,vz,m);
  }

  return res;
}

//template<> auto InputData<2019, 12, B>() { return "<x=-1, y=0, z=2>\n<x=2, y=-10, z=-7>\n<x=4, y=-8, z=8>\n<x=3, y=5, z=-1>\n10\n"; }  // after 10 steps: 179
//template<> auto InputData<2019, 12, B>() { return "<x=-8, y=-10, z=0>\n<x=5, y=5, z=10>\n<x=2, y=-7, z=3>\n<x=9, y=-8, z=-3>\n100\n"; }  // after 100 steps: 1940
template<> Number AoC<2019, 12, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  using Coord = short;  // char turns out to be not sufficient!
  constexpr size_t moonCount{ 4 };

  std::array<Coord,moonCount> x{};
  std::array<Coord,moonCount> y{};
  std::array<Coord,moonCount> z{};
  std::array<Coord,moonCount> vx{};
  std::array<Coord,moonCount> vy{};
  std::array<Coord,moonCount> vz{};

  for (int m = 0; m < moonCount; ++m)
  {
    const auto& line = v[m];
    int n = sscanf_s(line.c_str(), "<x=%hd, y=%hd, z=%hd>", &x[m], &y[m], &z[m]);
    assert(n == 3);
  }

  auto diff = [](const Coord& c1, const Coord& c2)->Coord { if (c1 > c2) return 1; if (c1 < c2) return -1; return 0; };

  const std::array<Coord,moonCount> x0{x};
  const std::array<Coord,moonCount> y0{y};
  const std::array<Coord,moonCount> z0{z};
  const std::array<Coord,moonCount> vx0{vx};
  const std::array<Coord,moonCount> vy0{vy};
  const std::array<Coord,moonCount> vz0{vz};
  Number xrepeat{ 0 };
  Number yrepeat{ 0 };
  Number zrepeat{ 0 };
  for (int t = 0; !(xrepeat && yrepeat && zrepeat); ++t)
  {
    std::array<Coord, moonCount> dvx{};
    std::array<Coord, moonCount> dvy{};
    std::array<Coord, moonCount> dvz{};

    for (int m1 = 0; m1 < moonCount; ++m1)
    {
      for (int m2 = 0; m2 < moonCount; ++m2)
      {
        dvx[m1] += diff(x[m2], x[m1]);
        dvy[m1] += diff(y[m2], y[m1]);
        dvz[m1] += diff(z[m2], z[m1]);
      }
    }
    for (int m = 0; m < moonCount; ++m)
    {
      vx[m] += dvx[m];
      vy[m] += dvy[m];
      vz[m] += dvz[m];
    }

    for (int m = 0; m < moonCount; ++m)
    {
      x[m] += vx[m];
      y[m] += vy[m];
      z[m] += vz[m];
    }

    if (!xrepeat && x0 == x && vx0 == vx) xrepeat = t + 1;
    if (!yrepeat && y0 == y && vy0 == vy) yrepeat = t + 1;
    if (!zrepeat && z0 == z && vz0 == vz) zrepeat = t + 1;
  }

  struct H
  {
    constexpr static Number gcd(Number a, Number b)
    {
      if (a == b) return a;
      if (a == 0) return b;
      if (b == 0) return a;
      return a > b ? gcd(a % b, b) : gcd(b % a, a);
    }

    constexpr static Number lcm(Number a, Number b)
    {
      if (a == 0 && b == 0) return 0;
      return a / gcd(a, b) * b;
    }
  };

  Number res = H::lcm(H::lcm(xrepeat, yrepeat), zrepeat);

  return res;
}
