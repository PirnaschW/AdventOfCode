//template<> auto InputData<2024, 4, A>() { return
//"MMMSXXMASM\n"
//"MSAMXMSMSA\n"
//"AMXSXMAAMM\n"
//"MSAMASMSMX\n"
//"XMASAMXAMM\n"
//"XXAMMXXAMA\n"
//"SMSMSASXSS\n"
//"SAXAMASAAA\n"
//"MAMMMXMMMM\n"
//"MXMXAXMASX\n";}; // Result: 18
template<> Number AoC<2024, 4, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Coord = signed short;
  class Direction
  {
  public:
    constexpr Direction(Coord dx_, Coord dy_) noexcept : dx{ dx_ }, dy{ dy_ } {}
    constexpr bool operator ==(const Direction& d) const noexcept { return dx == d.dx && dy == d.dy; }
    constexpr Direction operator *(int factor) const noexcept { return Direction{ static_cast<Coord>(dx * factor), static_cast<Coord>(dy * factor) }; }
    constexpr Direction TurnRight() const noexcept { return Direction{ static_cast<Coord>(-dy), dx }; }
    constexpr Direction TurnLeft() const noexcept { return Direction{ dy, static_cast<Coord>(-dx) }; }
  public:
    Coord dx;
    Coord dy;
  };

  class Point
  {
  public:
    constexpr Point(Coord x_, Coord y_) noexcept : x{ x_ }, y{ y_ } {}
    constexpr bool operator ==(const Point& p) const noexcept { return x == p.x && y == p.y; }
    constexpr Point operator +(const Direction& d) const noexcept { return { static_cast<Coord>(x + d.dx), static_cast<Coord>(y + d.dy) }; }
  public:
    Coord x;
    Coord y;
  };

  const Direction GoNull     {  0,  0 };
  const Direction GoLeft     { -1,  0 };
  const Direction GoRight    { +1,  0 };
  const Direction GoUp       {  0, -1 };
  const Direction GoDown     {  0, +1 };
  const Direction GoDownRight{ +1, +1 };
  const Direction GoDownLeft { -1, +1 };
  const Direction GoUpRight  { +1, -1 };
  const Direction GoUpLeft   { -1, -1 };

  class V2D
  {
  public:
    V2D() = delete;
    V2D(const Input& v) noexcept : v_{ v }, sizeX_{static_cast<Coord>(v[0].size())}, sizeY_{static_cast<Coord>(v.size())} {};
    char GetChar (const Point& p) const noexcept { return v_[p.y][p.x]; }
    bool IsValid(const Point& p) const noexcept
    {
      if (p.x < 0 || p.x >= sizeX_) return false;
      if (p.y < 0 || p.y >= sizeY_) return false;
      return true;
    }
    Coord SizeX() const noexcept { return sizeX_; }
    Coord SizeY() const noexcept { return sizeY_; }

    const Input& v_;
    const Coord sizeX_;
    const Coord sizeY_;
  };
  V2D v2d(v);

  constexpr char target[] = "XMAS";
  constexpr Coord tlen = sizeof target - 1;

  auto Match = [&v2d,&target,&tlen](Point p, Direction d) -> bool
    {
      for (int i = 0; i < tlen; ++i)
      {
        if (v2d.GetChar(p + d * i) != target[i]) return false;
      }
      return true;
    };
  auto FindAll = [&v2d,&target,&tlen,&Match](Point p, Direction d) -> Number
    {
      Number count{ 0 };
      while (v2d.IsValid(p) && v2d.IsValid(p + d * (tlen - 1)))
      {
        if (Match(p, d))
          ++count;
        p = p + d;
      }
      return count;
    };

  Number res{0};
  for (Coord y = 0; y < std::ssize(v); ++y)
  {
    res += FindAll(Point(0, y), GoRight);
    res += FindAll(Point(v2d.SizeX() - 1, y), GoLeft);

    res += FindAll(Point(0, y), GoDownRight);
    res += FindAll(Point(v2d.SizeX() - 1, y), GoUpLeft);

    res += FindAll(Point(v2d.SizeX()-1, y), GoDownLeft);
    res += FindAll(Point(0, y), GoUpRight);
  }
  for (Coord x = 0; x < std::ssize(v[0]); ++x)
  {
    res += FindAll(Point(x, 0), GoDown);
    res += FindAll(Point(x, v2d.SizeY()-1), GoUp);

    res += FindAll(Point(x+1, 0), GoDownRight);
    res += FindAll(Point(x-1, v2d.SizeY()-1), GoUpLeft);

    res += FindAll(Point(x-1, 0), GoDownLeft);
    res += FindAll(Point(x+1, v2d.SizeY()-1), GoUpRight);
  }

  return res;
}

//template<> auto InputData<2024, 4, B>() { return
//"MMMSXXMASM\n"
//"MSAMXMSMSA\n"
//"AMXSXMAAMM\n"
//"MSAMASMSMX\n"
//"XMASAMXAMM\n"
//"XXAMMXXAMA\n"
//"SMSMSASXSS\n"
//"SAXAMASAAA\n"
//"MAMMMXMMMM\n"
//"MXMXAXMASX\n";}; // Result: 9
template<> Number AoC<2024, 4, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Coord = signed short;
  class Direction
  {
  public:
    constexpr Direction(Coord dx_, Coord dy_) noexcept : dx{ dx_ }, dy{ dy_ } {}
    constexpr bool operator ==(const Direction& d) const noexcept { return dx == d.dx && dy == d.dy; }
    constexpr Direction operator *(int factor) const noexcept { return Direction{ static_cast<Coord>(dx * factor), static_cast<Coord>(dy * factor) }; }
    constexpr Direction TurnRight() const noexcept { return Direction{ static_cast<Coord>(-dy), dx }; }
    constexpr Direction TurnLeft() const noexcept { return Direction{ dy, static_cast<Coord>(-dx) }; }
  public:
    Coord dx;
    Coord dy;
  };

  class Point
  {
  public:
    constexpr Point(Coord x_, Coord y_) noexcept : x{ x_ }, y{ y_ } {}
    constexpr bool operator ==(const Point& p) const noexcept { return x == p.x && y == p.y; }
    constexpr Point operator +(const Direction& d) const noexcept { return { static_cast<Coord>(x + d.dx), static_cast<Coord>(y + d.dy) }; }
  public:
    Coord x;
    Coord y;
  };

  const Direction GoNull     {  0,  0 };
  const Direction GoLeft     { -1,  0 };
  const Direction GoRight    { +1,  0 };
  const Direction GoUp       {  0, -1 };
  const Direction GoDown     {  0, +1 };
  const Direction GoDownRight{ +1, +1 };
  const Direction GoDownLeft { -1, +1 };
  const Direction GoUpRight  { +1, -1 };
  const Direction GoUpLeft   { -1, -1 };

  class V2D
  {
  public:
    V2D() = delete;
    V2D(const Input& v) noexcept : v_{ v }, sizeX_{static_cast<Coord>(v[0].size())}, sizeY_{static_cast<Coord>(v.size())} {};
    char GetChar (const Point& p) const noexcept { return v_[p.y][p.x]; }
    bool IsValid(const Point& p) const noexcept
    {
      if (p.x < 0 || p.x >= sizeX_) return false;
      if (p.y < 0 || p.y >= sizeY_) return false;
      return true;
    }
    Coord SizeX() const noexcept { return sizeX_; }
    Coord SizeY() const noexcept { return sizeY_; }

    const Input& v_;
    const Coord sizeX_;
    const Coord sizeY_;
  };
  V2D v2d(v);

  constexpr char target[] = "XMAS";
  constexpr Coord tlen = sizeof target - 1;

  auto Match = [&v2d,&target,&tlen](Point p, Direction d) -> bool
    {
      for (int i = 0; i < tlen; ++i)
      {
        if (v2d.GetChar(p + d * i) != target[i]) return false;
      }
      return true;
    };
  auto FindAll = [&v2d,&target,&tlen,&Match](Point p, Direction d) -> Number
    {
      Number count{ 0 };
      while (v2d.IsValid(p) && v2d.IsValid(p + d * (tlen - 1)))
      {
        if (Match(p, d))
          ++count;
        p = p + d;
      }
      return count;
    };

  Number res{0};
  for (Coord x = 0; x < v2d.SizeX(); ++x)
  {
    for (Coord y = 0; y < v2d.SizeY(); ++y)
    {
      const Point p{ x,y };
      if (v2d.GetChar(p) == 'A')
      {
        Point ul{ p + GoUpLeft    };
        Point ur{ p + GoUpRight   };
        Point dl{ p + GoDownLeft  };
        Point dr{ p + GoDownRight };

        if (!v2d.IsValid(ul) || !v2d.IsValid(ur) || !v2d.IsValid(dl) || !v2d.IsValid(dr)) continue;

        char cul = v2d.GetChar(ul);
        char cur = v2d.GetChar(ur);
        char cdl = v2d.GetChar(dl);
        char cdr = v2d.GetChar(dr);

        if ((cul != 'M' || cdr != 'S') && (cul != 'S' || cdr != 'M')) continue;
        if ((cur != 'M' || cdl != 'S') && (cur != 'S' || cdl != 'M')) continue;
        ++res;
      }
    }
  }
  return res;
}
