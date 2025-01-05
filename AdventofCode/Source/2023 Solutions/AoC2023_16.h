//template<> auto InputData<2023, 16, A>() { return 
//R"(.|...\....)" "\n"
//R"(|.-.\.....)" "\n"
//R"(.....|-...)" "\n"
//R"(........|.)" "\n"
//R"(..........)" "\n"
//R"(.........\)" "\n"
//R"(..../.\\..)" "\n"
//R"(.-.-/..|..)" "\n"
//R"(.|....-|.\)" "\n"
//R"(..//.|....)" "\n";}; // Result: 46
template<> Number AoC<2023, 16, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr static int Fac{ 2 << 16 };  // to separate x and y
  constexpr static int Off{ 2 << 12 };  // to keep x and y positive
  class Offset
  {
  public:
    constexpr Offset(int i) noexcept : d(i) {}
    constexpr Offset(int dx, int dy) noexcept : d{ (dy + Off) * Fac + dx + Off } {}
    constexpr int X() const noexcept { return d % Fac - Off; }
    constexpr int Y() const noexcept { return d / Fac - Off; }
    constexpr operator int() const noexcept { return d; }
  public:
    const int d{};
  };
  constexpr Offset GoLeft { -1,  0 };
  constexpr Offset GoRight{ +1,  0 };
  constexpr Offset GoUp   {  0, -1 };
  constexpr Offset GoDown {  0, +1 };

  class Point
  {
  public:
    constexpr Point(int z) noexcept : z{ z } {}
    constexpr Point(int x, int y) noexcept : z{ (y + Off) * Fac + x + Off } {}
    constexpr int X() const noexcept { return z % Fac - Off; }
    constexpr int Y() const noexcept { return z / Fac - Off; }
  public:
    int z{};
  public:
    constexpr Point operator + (const Offset& o) const noexcept { return Point(X() + o.X(), Y() + o.Y()); }
    constexpr bool operator == (const Point& p) const noexcept { return z == p.z; }
    constexpr bool operator != (const Point& p) const noexcept { return !(*this == p); }
  };

  class Sit
  {
  public:
    Point p;
    Offset o;
  };
  std::unordered_set<Sit,
    decltype([](const Sit& s)->size_t { return (std::hash<int>()(s.p.z) << 4) ^ std::hash<int>()(s.o.d); }),
    decltype([](const Sit& s1, const Sit& s2)->bool {return s1.p == s2.p && s1.o == s2.o; })> h{};

  using BVec2D = std::vector<std::vector<bool>>;
  BVec2D e(std::ssize(v), std::vector<bool>(std::ssize(v[0]), false));

  auto Beam = [&v, &e, &h, &GoLeft,&GoRight,&GoDown,&GoUp](Point p, Offset o, auto& Beam) -> void
    {
      while (true)
      {
        if (p.X() < 0) return;
        if (p.X() >= std::ssize(v[0])) return;
        if (p.Y() < 0) return;
        if (p.Y() >= std::ssize(v)) return;

        if (h.contains(Sit(p, o))) return;
        h.insert(Sit(p, o));

        e[p.Y()][p.X()] = true;
        if (v[p.Y()][p.X()] != '.') break;

        p = p + o; // this shortcuts the recursion for simple 'nothing there' locations
      }

      switch (v[p.Y()][p.X()])
      {
        case '.': assert(false); return Beam(p + o, o, Beam);
        case '/':
          switch (o)
          {
            case GoLeft:  return Beam(p + GoDown,  GoDown,  Beam);
            case GoRight: return Beam(p + GoUp,    GoUp,    Beam);
            case GoUp:    return Beam(p + GoRight, GoRight, Beam);
            case GoDown:  return Beam(p + GoLeft,  GoLeft,  Beam);
          }
        case '\\':
          switch (o)
          {
            case GoRight: return Beam(p + GoDown,  GoDown,  Beam);
            case GoLeft:  return Beam(p + GoUp,    GoUp,    Beam);
            case GoDown:  return Beam(p + GoRight, GoRight, Beam);
            case GoUp:    return Beam(p + GoLeft,  GoLeft,  Beam);
          }
        case '|':
          switch (o)
          {
            case GoRight: [[fallthrough]];
            case GoLeft:
              Beam(p + GoDown, GoDown, Beam);
              Beam(p + GoUp,   GoUp,   Beam);
              return;
            case GoDown:  return Beam(p + GoDown, GoDown, Beam);
            case GoUp:    return Beam(p + GoUp,   GoUp,   Beam);
          }
        case '-':
          switch (o)
          {
            case GoDown: [[fallthrough]];
            case GoUp:
              Beam(p + GoRight, GoRight, Beam);
              Beam(p + GoLeft,  GoLeft,  Beam);
              return;
            case GoRight: return Beam(p + GoRight, GoRight, Beam);
            case GoLeft:  return Beam(p + GoLeft,  GoLeft,  Beam);
          }
      }
    };

  auto Count = [](const BVec2D& e) -> int
    {
      int z{ 0 };
      for (int y = 0; y < std::ssize(e); ++y)
      {
        for (int x = 0; x < std::ssize(e[0]); ++x)
        {
          if (e[y][x]) ++z;
        }
      }
      return z;
    };

  Beam(Point(0, 0), GoRight, Beam);
  int res = Count(e);
  
  return res;
}

//template<> auto InputData<2023, 16, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 16, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr static int Fac{ 2 << 16 };  // to separate x and y
  constexpr static int Off{ 2 << 12 };  // to keep x and y positive
  class Offset
  {
  public:
    constexpr Offset(int i) noexcept : d(i) {}
    constexpr Offset(int dx, int dy) noexcept : d{ (dy + Off) * Fac + dx + Off } {}
    constexpr int X() const noexcept { return d % Fac - Off; }
    constexpr int Y() const noexcept { return d / Fac - Off; }
    constexpr operator int() const noexcept { return d; }
  public:
    const int d{};
  };
  constexpr Offset GoLeft { -1,  0 };
  constexpr Offset GoRight{ +1,  0 };
  constexpr Offset GoUp   {  0, -1 };
  constexpr Offset GoDown {  0, +1 };

  class Point
  {
  public:
    constexpr Point(int z) noexcept : z{ z } {}
    constexpr Point(int x, int y) noexcept : z{ (y + Off) * Fac + x + Off } {}
    constexpr int X() const noexcept { return z % Fac - Off; }
    constexpr int Y() const noexcept { return z / Fac - Off; }
  public:
    int z{};
  public:
    constexpr Point operator + (const Offset& o) const noexcept { return Point(X() + o.X(), Y() + o.Y()); }
    constexpr bool operator == (const Point& p) const noexcept { return z == p.z; }
    constexpr bool operator != (const Point& p) const noexcept { return !(*this == p); }
  };

  class Sit
  {
  public:
    Point p;
    Offset o;
  };
  std::unordered_set<Sit,
    decltype([](const Sit& s)->size_t { return (std::hash<int>()(s.p.z) << 4) ^ std::hash<int>()(s.o.d); }),
    decltype([](const Sit& s1, const Sit& s2)->bool {return s1.p == s2.p && s1.o == s2.o; })> h{};

  using BVec2D = std::vector<std::vector<bool>>;
  BVec2D e0(std::ssize(v), std::vector<bool>(std::ssize(v[0]), false));
  BVec2D e{};

  auto Beam = [&v, &e, &h, &GoLeft,&GoRight,&GoDown,&GoUp](Point p, Offset o, auto& Beam) -> void
    {
      while (true)
      {
        if (p.X() < 0) return;
        if (p.X() >= std::ssize(v[0])) return;
        if (p.Y() < 0) return;
        if (p.Y() >= std::ssize(v)) return;

        if (h.contains(Sit(p, o))) return;
        h.insert(Sit(p, o));

        e[p.Y()][p.X()] = true;
        if (v[p.Y()][p.X()] != '.') break;

        p = p + o; // this shortcuts the recursion for simple 'nothing there' locations
      }

      switch (v[p.Y()][p.X()])
      {
        case '.': assert(false); return Beam(p + o, o, Beam);
        case '/':
          switch (o)
          {
            case GoLeft:  return Beam(p + GoDown,  GoDown,  Beam);
            case GoRight: return Beam(p + GoUp,    GoUp,    Beam);
            case GoUp:    return Beam(p + GoRight, GoRight, Beam);
            case GoDown:  return Beam(p + GoLeft,  GoLeft,  Beam);
          }
        case '\\':
          switch (o)
          {
            case GoRight: return Beam(p + GoDown,  GoDown,  Beam);
            case GoLeft:  return Beam(p + GoUp,    GoUp,    Beam);
            case GoDown:  return Beam(p + GoRight, GoRight, Beam);
            case GoUp:    return Beam(p + GoLeft,  GoLeft,  Beam);
          }
        case '|':
          switch (o)
          {
            case GoRight: [[fallthrough]];
            case GoLeft:
              Beam(p + GoDown, GoDown, Beam);
              Beam(p + GoUp,   GoUp,   Beam);
              return;
            case GoDown:  return Beam(p + GoDown, GoDown, Beam);
            case GoUp:    return Beam(p + GoUp,   GoUp,   Beam);
          }
        case '-':
          switch (o)
          {
            case GoDown: [[fallthrough]];
            case GoUp:
              Beam(p + GoRight, GoRight, Beam);
              Beam(p + GoLeft,  GoLeft,  Beam);
              return;
            case GoRight: return Beam(p + GoRight, GoRight, Beam);
            case GoLeft:  return Beam(p + GoLeft,  GoLeft,  Beam);
          }
      }
    };

  auto Count = [](const BVec2D& e) -> int
    {
      int z{ 0 };
      for (int y = 0; y < std::ssize(e); ++y)
      {
        for (int x = 0; x < std::ssize(e[0]); ++x)
        {
          if (e[y][x]) ++z;
        }
      }
      return z;
    };

  int max{ 0 };
  auto TryOne = [&h,&e,&e0,&Beam,&Count,&max](const Point& p, const Offset& o) -> void
    {
      h.clear();
      e = e0;
      Beam(p, o, Beam);
      int c = Count(e);
      if (c > max) max = c;
    };

  for (int y = 0; y < std::ssize(e0); ++y)
  {
    TryOne(Point(0, y), GoRight);
    TryOne(Point(static_cast<int>(std::ssize(e0[0]) - 1), y), GoLeft);
  }
  for (int x = 0; x < std::ssize(e0[0]); ++x)
  {
    TryOne(Point(x, 0), GoDown);
    TryOne(Point(x, static_cast<int>(std::ssize(e0) - 1)), GoUp);
  }

  return max;
}
