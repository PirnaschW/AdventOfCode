template<> Number AoC<2019, 4, A>(std::istream& input)
{
  //  auto v1 = ReadWords(input, ',');
  //  auto v2 = ReadWords(input, ',');

  const std::string testdata1{ "R8,U5,L5,D3\nU7,R6,D4,L4" };
  const std::string testdata2{ "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83" };
  const std::string testdata3{ "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7" };

  std::istringstream input0(testdata3);
  auto v1 = ReadWords(input, ',');
  auto v2 = ReadWords(input, ',');

  struct Point {
    Number x{ 0 };
    Number y{ 0 };
    auto operator <=>(const Point&) const noexcept = default;
    Number MDist(void) const noexcept { return std::abs(x) + std::abs(y); }
  };

  struct Line {
    Point from{};
    Point to{};
    bool horizontal{ true };  // all our lines are horizontal or (not horizontal) = vertical
    Point Cross(const Line& l) const noexcept
    {
      constexpr const Point none{ 0,0 };
      if (l.horizontal == horizontal) return none;
      if (std::max(l.from.x, l.to.x) < std::min(from.x, to.x)) return none;
      if (std::min(l.from.x, l.to.x) > std::max(from.x, to.x)) return none;
      if (std::max(l.from.y, l.to.y) < std::min(from.y, to.y)) return none;
      if (std::min(l.from.y, l.to.y) > std::max(from.y, to.y)) return none;

      return horizontal ? Point(l.from.x, from.y) : Point(from.x, l.from.y);
    }
  };

  struct H {
    static std::vector<Line> GetWire(std::vector<std::string> v)
    {
      std::vector<Line> wire{ v.size() };
      Point p{};
      int i{ 0 };
      for (const auto& vv : v)
      {
        const Point p0 = p;
        const Number z = std::stoll(vv.c_str() + 1);
        bool h{ true };
        switch (vv[0])
        {
          case 'R': p.x += z; h = true;  break;
          case 'L': p.x -= z; h = true;  break;
          case 'U': p.y += z; h = false; break;
          case 'D': p.y -= z; h = false; break;
          default:  assert(false); break;
        }
        wire[i++] = Line(p0, p, h);
      }
      return wire;
    }
  };

  const auto wire1 = H::GetWire(v1);
  const auto wire2 = H::GetWire(v2);

  Number dmin = std::numeric_limits<Number>::max();
  const Point origin{ 0,0 };
  for (const auto& l1 : wire1)
  {
    for (const auto& l2 : wire2)
    {
      assert(l1.Cross(l2) == l2.Cross(l1));
      const Point p = l1.Cross(l2);
      if (p == origin) continue;
      const Number d = p.MDist();
      if (d < dmin) dmin = d;
    }
  }
  return dmin;
}

template<> Number AoC<2019, 4, B>(std::istream& input)
{
  //  auto v1 = ReadWords(input, ',');
  //  auto v2 = ReadWords(input, ',');

  const std::string testdata1{ "R8,U5,L5,D3\nU7,R6,D4,L4" };
  const std::string testdata2{ "R75,D30,R83,U83,L12,D49,R71,U7,L72\nU62,R66,U55,R34,D71,R55,D58,R83" };
  const std::string testdata3{ "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51\nU98,R91,D20,R16,D67,R40,U7,R15,U6,R7" };

  std::istringstream input0(testdata3);
  auto v1 = ReadWords(input, ',');
  auto v2 = ReadWords(input, ',');

  struct Point {
    Number x{ 0 };
    Number y{ 0 };
    auto operator <=>(const Point&) const noexcept = default;
    Number MDist(void) const noexcept { return std::abs(x) + std::abs(y); }
  };

  struct Line {
    Point from{};
    Point to{};
    bool horizontal{ true };  // all our lines are horizontal or (not horizontal) = vertical
    Number length{ 0 };
    Number totallength{ 0 };
    Point Cross(const Line& l) const noexcept
    {
      constexpr const Point none{ 0,0 };
      if (l.horizontal == horizontal) return none;
      if (std::max(l.from.x, l.to.x) < std::min(from.x, to.x)) return none;
      if (std::min(l.from.x, l.to.x) > std::max(from.x, to.x)) return none;
      if (std::max(l.from.y, l.to.y) < std::min(from.y, to.y)) return none;
      if (std::min(l.from.y, l.to.y) > std::max(from.y, to.y)) return none;

      return horizontal ? Point(l.from.x, from.y) : Point(from.x, l.from.y);
    }
    Number DistToPoint(const Point& p) const noexcept
    {
      if (horizontal)
        return totallength - length + std::abs(p.x - from.x);
      else
        return totallength - length + std::abs(p.y - from.y);
    }
  };

  struct Wire
  {
    std::vector<Line> w{};
    Wire(std::vector<std::string> v)
    {
      w.resize(v.size());
      Point p{};
      Number zz{ 0 };
      int i{ 0 };
      for (const auto& vv : v)
      {
        const Point p0 = p;
        const Number z = std::stoll(vv.c_str() + 1);
        bool h{ true };
        switch (vv[0])
        {
          case 'R': p.x += z; h = true;  break;
          case 'L': p.x -= z; h = true;  break;
          case 'U': p.y += z; h = false; break;
          case 'D': p.y -= z; h = false; break;
          default:  assert(false); break;
        }
        zz += z;
        w[i++] = Line(p0, p, h, z, zz);
      }
    }
  };

  struct H {
  };

  const Wire wire1{ v1 };
  const Wire wire2{ v2 };

  Number dmin = std::numeric_limits<Number>::max();
  const Point origin{ 0,0 };
  for (const auto& l1 : wire1.w)
  {
    for (const auto& l2 : wire2.w)
    {
      assert(l1.Cross(l2) == l2.Cross(l1));
      const Point p = l1.Cross(l2);
      if (p == origin) continue;
      const Number d = l1.DistToPoint(p) + l2.DistToPoint(p);
      if (d < dmin) dmin = d;
    }
  }
  return dmin;
}
