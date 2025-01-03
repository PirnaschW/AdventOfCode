//template<> auto InputData<2023, 18, A>() { return
//"R 6 (#70c710)\n"
//"D 5 (#0dc571)\n"
//"L 2 (#5713f0)\n"
//"D 2 (#d2c081)\n"
//"R 2 (#59c680)\n"
//"D 2 (#411b91)\n"
//"L 5 (#8ceee2)\n"
//"U 2 (#caa173)\n"
//"L 1 (#1b58a2)\n"
//"U 2 (#caa171)\n"
//"R 2 (#7807d2)\n"
//"U 3 (#a77fa3)\n"
//"L 2 (#015232)\n"
//"U 2 (#7a21e3)\n";}; // Result: 62 (38+24)
template<> Number AoC<2023, 18, A>(std::istream& input)
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
  const Direction GoNull {  0,  0 };
  const Direction GoLeft { -1,  0 };
  const Direction GoRight{ +1,  0 };
  const Direction GoUp   {  0, -1 };
  const Direction GoDown {  0, +1 };

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

  std::vector<Point> poly;
  Point p{ 0, 0 };
  int egde{ 0 };
  for (const auto& line : v)
  {
    char dir{};
    int dist{ 0 };
    char r[2]{};
    char g[2]{};
    char b[2]{};
    int n{ 0 };
    int z = sscanf_s(line.c_str(), "%c %d (#%2c%2c%2c)%n", &dir, 1, &dist, r, 2, g, 2, b, 2, &n);
    assert(z == 5);
    assert(n > 12 && n < 15);

    Direction d{ 0, 0 };
    switch (dir)
    {
      case 'R': d = GoRight;  break;
      case 'D': d = GoDown;   break;
      case 'L': d = GoLeft;   break;
      case 'U': d = GoUp;     break;
      default: assert(false); break;
    }

    egde += dist;
    p = p + d * dist;
    poly.push_back(p);
  }
  poly.push_back(poly[0]); // to close the polygon

  int area{ 0 };
  for (int i = 1; i < std::ssize(poly); ++i)
  {
    area += poly[i - 1].x * poly[i].y - poly[i].x * poly[i - 1].y; // Shoelace Formula
  }
  area /= 2;

  int total = area + egde / 2 + 1;  // from Pick's theorem
  return total;
}

//template<> auto InputData<2023, 18, B>() { return
//"R 6 (#70c710)\n"
//"D 5 (#0dc571)\n"
//"L 2 (#5713f0)\n"
//"D 2 (#d2c081)\n"
//"R 2 (#59c680)\n"
//"D 2 (#411b91)\n"
//"L 5 (#8ceee2)\n"
//"U 2 (#caa173)\n"
//"L 1 (#1b58a2)\n"
//"U 2 (#caa171)\n"
//"R 2 (#7807d2)\n"
//"U 3 (#a77fa3)\n"
//"L 2 (#015232)\n"
//"U 2 (#7a21e3)\n";}; // Result: 952408144115
template<> Number AoC<2023, 18, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Coord = Number;
  class Direction
  {
  public:
    constexpr Direction(Coord dx_, Coord dy_) noexcept : dx{ dx_ }, dy{ dy_ } {}
    constexpr bool operator ==(const Direction& d) const noexcept { return dx == d.dx && dy == d.dy; }
    constexpr Direction operator *(Coord factor) const noexcept { return Direction{ static_cast<Coord>(dx * factor), static_cast<Coord>(dy * factor) }; }
    constexpr Direction TurnRight() const noexcept { return Direction{ static_cast<Coord>(-dy), dx }; }
    constexpr Direction TurnLeft() const noexcept { return Direction{ dy, static_cast<Coord>(-dx) }; }
  public:
    Coord dx;
    Coord dy;
  };
  const Direction GoNull {  0,  0 };
  const Direction GoLeft { -1,  0 };
  const Direction GoRight{ +1,  0 };
  const Direction GoUp   {  0, -1 };
  const Direction GoDown {  0, +1 };

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

  std::vector<Point> poly;
  Point p{ 0, 0 };
  Number egde{ 0 };
  for (const auto& line : v)
  {
    char dir{};
    Number dist{ 0 };
    char hex[7]{};
    int n{ 0 };
    int z = sscanf_s(line.c_str(), "%c %lld (#%6c)%n", &dir, 1, &dist, hex, 7, &n);
    assert(z == 3);
    assert(n > 12 && n < 15);

    Direction d{ 0, 0 };
    switch (hex[5])
    {
      case '0': d = GoRight;  break;
      case '1': d = GoDown;   break;
      case '2': d = GoLeft;   break;
      case '3': d = GoUp;     break;
      default: assert(false); break;
    }

    auto Dec = [](char c) -> int
      {
        if (isdigit(c)) return c - '0';
        return c - 'a' + 10;
      };

    dist = 0;
    for (int i = 0; i < 5; ++i)
    {
      dist *= 16;
      dist += Dec(hex[i]);
    }
    egde += dist;
    p = p + d * dist;
    poly.push_back(p);
  }
  poly.push_back(poly[0]); // to close the polygon

  Number area{ 0 };
  for (int i = 1; i < std::ssize(poly); ++i)
  {
    area += poly[i - 1].x * poly[i].y - poly[i].x * poly[i - 1].y; // Shoelace Formula
  }
  area /= 2;

  Number total = area + egde / 2 + 1;  // from Pick's theorem
  return total;
}
