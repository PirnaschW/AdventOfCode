//template<> auto InputData<2023, 10, A>() { return "-L|F7\n7S-7|\nL|7||\n-L-J|\nL|-JF\n"; } // Result: 4
//template<> auto InputData<2023, 10, A>() { return "7-F7-\n.FJ|7\nSJLL7\n|F--J\nLJ.LJ\n"; } // Result: 8
template<> Number AoC<2023, 10, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Direction;
  class Offset
  {
  public:
    int dx{};
    int dy{};
  };
  constexpr Offset GoLeft { -1,  0 };
  constexpr Offset GoRight{ +1,  0 };
  constexpr Offset GoUp   {  0, -1 };
  constexpr Offset GoDown {  0, +1 };

  class Point
  {
  public:
    int x{};
    int y{};
  public:
    Point operator + (const Offset& o) const noexcept { return Point(x + o.dx, y + o.dy); }
    bool operator == (const Point& p) const noexcept { return x == p.x && y == p.y; }
    bool operator != (const Point& p) const noexcept { return x != p.x || y != p.y; }
  };

  auto FindStart = [&v]()->Point
    {
      for (int y = 0; y < v.size(); ++y)
        for (int x = 0; x < v[0].size(); ++x)
          if (v[y][x] == 'S') return Point(x, y);
      assert(false);
      return Point(0, 0);
    };

  class Direction
  {
  public:
    unsigned char d{ 0 };
  public:
    Direction operator | (const Direction& dd) const noexcept { return Direction(dd.d | d); }
    Direction operator & (const Direction& dd) const noexcept { return Direction(dd.d & d); }
    Direction operator - () const noexcept { return Direction(static_cast<unsigned char>((d & 0x03) ? (d ^ 0x03) : (d ^ 0x0c))); }
    Direction operator ~ () const noexcept { return Direction(~d); }
    bool operator == (const Direction& dd) const noexcept { return d == dd.d; }
    operator bool () const noexcept { return d != 0; }
  };
  constexpr Direction None { 0x00 };
  constexpr Direction Left { 0x01 };
  constexpr Direction Right{ 0x02 };
  constexpr Direction Up   { 0x04 };
  constexpr Direction Down { 0x08 };
  constexpr Direction Start{ 0x10 };

  assert(-Left  == Right);
  assert(-Right == Left );
  assert(-Up    == Down );
  assert(-Down  == Up   );

  auto GetOffset = [](const Direction& dd)->Offset
    {
      switch (dd.d)
      {
        case Left.d:  return GoLeft;
        case Right.d: return GoRight;
        case Up.d:    return GoUp;
        case Down.d:  return GoDown;
        default: assert(false); return Offset(0, 0);
      }
    };

  auto GetDirections = [&v](const Point& p)->Direction
    {
      switch (v[p.y][p.x])
      {
        case '|': return Up | Down;
        case '-': return Left | Right;
        case 'L': return Up | Right;
        case 'J': return Up | Left;
        case '7': return Left | Down;
        case 'F': return Right | Down;
        case '.': return None;
        case 'S': return Start;
        default: assert(false); return None;
      }
    };


  Point s{ FindStart() };
  Point current{s};
  Direction currdir{None};
  if (s.x > 0             && GetDirections(s + GoLeft ) & Right) { currdir = Left ; }
  if (s.y > 0             && GetDirections(s + GoRight) & Left ) { currdir = Right; }
  if (s.x < v[0].size()-1 && GetDirections(s + GoUp   ) & Down ) { currdir = Up   ; }
  if (s.y < v.size()-1    && GetDirections(s + GoDown ) & Up   ) { currdir = Down ; }
  assert(currdir != None);

  Number steps{ 0 };
  do {
    ++steps;
    current = current + GetOffset(currdir);
    Direction nextdir = Direction(GetDirections(current) & (~-currdir));  // "remove the reversed direction", so we don't go back
    currdir = nextdir;
  } while (current != s);
  

  return steps/2;
}

//template<> auto InputData<2023, 10, B>() { return "-L|F7\n7S-7|\nL|7||\n-L-J|\nL|-JF\n"; } // Result: 1
//template<> auto InputData<2023, 10, B>() { return "7-F7-\n.FJ|7\nSJLL7\n|F--J\nLJ.LJ\n"; } // Result: 1
//template<> auto InputData<2023, 10, B>() { return
//"...........\n"
//".S-------7.\n"
//".|F-----7|.\n"
//".||OOOOO||.\n"
//".||OOOOO||.\n"
//".|L-7OF-J|.\n"
//".|II|O|II|.\n"
//".L--JOL--J.\n"
//".....O.....\n"; } // Result: 4
//template<> auto InputData<2023, 10, B>() { return
//"..........\n"
//".S------7.\n"
//".|F----7|.\n"
//".||OOOO||.\n"
//".||OOOO||.\n"
//".|L-7F-J|.\n"
//".|II||II|.\n"
//".L--JL--J.\n"
//"..........\n"; } // Result: 4
//template<> auto InputData<2023, 10, B>() { return
//".F----7F7F7F7F-7....\n"
//".|F--7||||||||FJ....\n"
//".||.FJ||||||||L7....\n"
//"FJL7L7LJLJ||LJ.L-7..\n"
//"L--J.L7...LJS7F-7L7.\n"
//"....F-J..F7FJ|L7L7L7\n"
//"....L7.F7||L7|.L7L7|\n"
//".....|FJLJ|FJ|F7|.LJ\n"
//"....FJL-7.||.||||...\n"
//"....L---J.LJ.LJLJ...\n"; } // Result: 8
template<> Number AoC<2023, 10, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Direction;
  class Offset
  {
  public:
    int dx{};
    int dy{};
  };
  constexpr Offset GoLeft { -1,  0 };
  constexpr Offset GoRight{ +1,  0 };
  constexpr Offset GoUp   {  0, -1 };
  constexpr Offset GoDown {  0, +1 };

  class Point
  {
  public:
    int x{};
    int y{};
  public:
    Point operator + (const Offset& o) const noexcept { return Point(x + o.dx, y + o.dy); }
    bool operator == (const Point& p) const noexcept { return x == p.x && y == p.y; }
    bool operator != (const Point& p) const noexcept { return x != p.x || y != p.y; }
  };

  auto FindStart = [&v]()->Point
    {
      for (int y = 0; y < v.size(); ++y)
        for (int x = 0; x < v[0].size(); ++x)
          if (v[y][x] == 'S') return Point(x, y);
      assert(false);
      return Point(0, 0);
    };

  class Direction
  {
  public:
    unsigned char d{ 0 };
  public:
    Direction operator | (const Direction& dd) const noexcept { return Direction(dd.d | d); }
    Direction operator & (const Direction& dd) const noexcept { return Direction(dd.d & d); }
    Direction operator - () const noexcept { return Direction(static_cast<unsigned char>((d & 0x03) ? (d ^ 0x03) : (d ^ 0x0c))); }
    Direction operator ~ () const noexcept { return Direction(~d); }
    bool operator == (const Direction& dd) const noexcept { return d == dd.d; }
    operator bool () const noexcept { return d != 0; }
  };
  constexpr Direction None { 0x00 };
  constexpr Direction Left { 0x01 };
  constexpr Direction Right{ 0x02 };
  constexpr Direction Up   { 0x04 };
  constexpr Direction Down { 0x08 };
  constexpr Direction Start{ 0x10 };

  assert(-Left  == Right);
  assert(-Right == Left );
  assert(-Up    == Down );
  assert(-Down  == Up   );

  auto GetOffset = [](const Direction& dd)->Offset
    {
      switch (dd.d)
      {
        case Left.d:  return GoLeft;
        case Right.d: return GoRight;
        case Up.d:    return GoUp;
        case Down.d:  return GoDown;
        default: assert(false); return Offset(0, 0);
      }
    };

  auto GetDirections = [&v](const Point& p)->Direction
    {
      switch (v[p.y][p.x])
      {
        case '|': return Up | Down;
        case '-': return Left | Right;
        case 'L': return Up | Right;
        case 'J': return Up | Left;
        case '7': return Left | Down;
        case 'F': return Right | Down;
        case '.': return None;
        case 'S': return Start;
        default: assert(false); return None;
      }
    };


  Point s{ FindStart() };
  Point current{s};
  Direction currdir{None};
  if (s.x > 0             && GetDirections(s + GoLeft ) & Right) { currdir = Left ; }
  if (s.y > 0             && GetDirections(s + GoRight) & Left ) { currdir = Right; }
  if (s.x < v[0].size()-1 && GetDirections(s + GoUp   ) & Down ) { currdir = Up   ; }
  if (s.y < v.size()-1    && GetDirections(s + GoDown ) & Up   ) { currdir = Down ; }
  assert(currdir != None);

  std::vector<Point> polygon{};
  
  Number steps{ 0 };
  do {
    ++steps;
    polygon.push_back(current);
    current = current + GetOffset(currdir);
    Direction nextdir = Direction(GetDirections(current) & (~-currdir));  // "remove the reversed direction", so we don't go back
    currdir = nextdir;
  } while (current != s);
  polygon.push_back(current);
  assert(polygon.size() == steps + 1);

  Number area{ 0 };
  for (int i = 0; i < steps; ++i)
  {
    area += polygon[i].x * polygon[i + 1].y - polygon[i + 1].x * polygon[i].y;
  }
  area = std::abs(area) / 2;

  Number res = area + 1 - steps / 2;
  return res;
}
