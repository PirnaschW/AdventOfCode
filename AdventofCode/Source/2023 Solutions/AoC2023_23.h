//template<> auto InputData<2023, 23, A>() { return
//"#.#####################\n"
//"#.......#########...###\n"
//"#######.#########.#.###\n"
//"###.....#.>.>.###.#.###\n"
//"###v#####.#v#.###.#.###\n"
//"###.>...#.#.#.....#...#\n"
//"###v###.#.#.#########.#\n"
//"###...#.#.#.......#...#\n"
//"#####.#.#.#######.#.###\n"
//"#.....#.#.#.......#...#\n"
//"#.#####.#.#.#########v#\n"
//"#.#...#...#...###...>.#\n"
//"#.#.#v#######v###.###v#\n"
//"#...#.>.#...>.>.#.###.#\n"
//"#####v#.#.###v#.#.###.#\n"
//"#.....#...#...#.#.#...#\n"
//"#.#########.###.#.#.###\n"
//"#...###...#...#...#.###\n"
//"###.###.#.###v#####v###\n"
//"#...#...#.#.>.>.#.>.###\n"
//"#.###.###.#.###.#.#v###\n"
//"#.....###...###...#...#\n"
//"#####################.#\n";}; // Result: 94
template<> Number AoC<2023, 23, A>(std::istream& input)
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


  class myGlobalInfo {
  public:
    const Input& v_{ v };

    const Direction GoNull{ 0,  0 };
    const Direction GoLeft{ -1,  0 };
    const Direction GoRight{ +1,  0 };
    const Direction GoUp{ 0, -1 };
    const Direction GoDown{ 0, +1 };
    bool IsValid(Point p) const noexcept
    {
      if (p.x < 0) return false;
      if (p.x >= std::ssize(v_[0])) return false;
      if (p.y < 0) return false;
      if (p.y >= std::ssize(v_)) return false;
      return true;
    }
    mutable Point end{ -1, -1 };
    mutable int longest{ 0 };
  };

  class myState
  {
  public:
    myState() = delete;
    myState(Point p, int steps) : p_{ p }, steps_{ steps } {}
    size_t Hash() const noexcept {
      if (hash_ == 0) hash_ = std::hash<size_t>()((p_.x << 16) + (p_.y << 0));
      return hash_;
    }
    bool operator ==(const myState& s) const noexcept { return p_ == s.p_; }
    bool IsAlive() const noexcept { return alive_; }
    void ReplaceWith(const myState& s) const noexcept { if (s.steps_ > steps_) { steps_ = s.steps_; alive_ = true; } }
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;

      if (p_ == g.end)
      {
        if (steps_ > g.longest) g.longest = steps_;
        return v;
      }

      auto CanGo = [&g](const Point& p, const Direction& d) -> bool
        {
          const Point q{ p + d };
          if (!g.IsValid(q)) return false;

          switch (g.v_[q.y][q.x])
          {
            case '.': return true;
            case '#': return false;
            case '>': return d == g.GoRight;
            case '<': return d == g.GoLeft;
            case '^': return d == g.GoUp;
            case 'v': return d == g.GoDown;
            default: assert(false); return false;
          }
        };

      auto IsTrail = [&g](const Point& p, const Direction& d) -> bool
        {
          const Point q{ p + d };
          if (!g.IsValid(q)) return false;
          return g.v_[q.y][q.x] != '#';
        };

      auto WayCount = [&g, &IsTrail](const Point& p) -> int
        {
          int count{ 0 };
          if (IsTrail(p, g.GoRight)) ++count;
          if (IsTrail(p, g.GoLeft )) ++count;
          if (IsTrail(p, g.GoDown )) ++count;
          if (IsTrail(p, g.GoUp   )) ++count;
          return count;
        };

      auto IsJunction = [&WayCount](const Point& p) -> bool
        {
          return WayCount(p) > 2;
        };

      auto InsertIfPossible = [&g, &v](const Point& p, int steps) -> void
        {
          if (!g.IsValid(p)) return;
          switch (g.v_[p.y][p.x])
          {
            case '#': return;
            case '>': v.emplace_back(p + g.GoRight, steps + 2);
            case '^': v.emplace_back(p + g.GoUp, steps + 2);
            case '<': v.emplace_back(p + g.GoLeft, steps + 2);
            case 'v': v.emplace_back(p + g.GoDown, steps + 2);
            case '.': v.emplace_back(p, steps + 1);
          };
        };

      auto NextDirection = [&g, &v, &CanGo](const Point& p, const Direction& d) -> Direction
        {
          if (d != g.GoLeft  && CanGo(p, g.GoRight)) return g.GoRight;
          if (d != g.GoRight && CanGo(p, g.GoLeft )) return g.GoLeft ;
          if (d != g.GoUp    && CanGo(p, g.GoDown )) return g.GoDown ;
          if (d != g.GoDown  && CanGo(p, g.GoUp   )) return g.GoUp   ;
          assert(false);
          return d;
        };

      auto FollowTrail = [&g, &v, &CanGo, &IsJunction, &NextDirection, &WayCount](Point p, Direction d) -> std::pair<int,Point>
        {
          int steps{ 0 };
            do
            {
              if (p + d == g.end)
              {
                p = p + d;
                ++steps;
                break;
              }
              if (!CanGo(p, d) || WayCount(p + d) < 2)
                return { 0, p };  // it's a dead end
              p = p + d;
              ++steps;
              d = NextDirection(p, d);
            } while (!IsJunction(p));
          return {steps, p};
        };

      auto TryDirection = [&FollowTrail, &v](const Point& p0, const Direction& d, int steps) -> void
        {
          auto [newSteps, p] = FollowTrail(p0, d);
          if (newSteps > 0) { v.emplace_back(p, steps + newSteps); }
        };

      //assert(IsJunction(p_));

      TryDirection(p_, g.GoRight, steps_);
      TryDirection(p_, g.GoLeft,  steps_);
      TryDirection(p_, g.GoDown,  steps_);
      TryDirection(p_, g.GoUp,    steps_);
      return v;
    }

  private:
    const Point p_{ 0, 0 };
    mutable int steps_{ 0 };
    mutable size_t hash_{ 0 };
    mutable bool alive_{ true };
  };

  auto GetStart = [&v]() -> Point
    {
      for (Coord x = 0; x < std::ssize(v[0]); ++x)
        if (v[0][x] == '.') return { x, 0 };
      assert(false);
      return { -1, -1 };
    };
  auto GetEnd = [&v]() -> Point
    {
      const Coord y = static_cast<Coord>(std::ssize(v) - 1);
      for (Coord x = 0; x < std::ssize(v[y]); ++x)
        if (v[y][x] == '.') return { x, y };
      assert(false);
      return { -1, -1 };
    };

  myGlobalInfo g{};
  Point start = GetStart();
  g.end = GetEnd();
  myState s0(start, 0);
  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g);

  while (bfs.NextLevel() > 0);


  return g.longest;
}

//template<> auto InputData<2023, 23, B>() { return
//"#.#####################\n"
//"#.......#########...###\n"
//"#######.#########.#.###\n"
//"###.....#.>.>.###.#.###\n"
//"###v#####.#v#.###.#.###\n"
//"###.>...#.#.#.....#...#\n"
//"###v###.#.#.#########.#\n"
//"###...#.#.#.......#...#\n"
//"#####.#.#.#######.#.###\n"
//"#.....#.#.#.......#...#\n"
//"#.#####.#.#.#########v#\n"
//"#.#...#...#...###...>.#\n"
//"#.#.#v#######v###.###v#\n"
//"#...#.>.#...>.>.#.###.#\n"
//"#####v#.#.###v#.#.###.#\n"
//"#.....#...#...#.#.#...#\n"
//"#.#########.###.#.#.###\n"
//"#...###...#...#...#.###\n"
//"###.###.#.###v#####v###\n"
//"#...#...#.#.>.>.#.>.###\n"
//"#.###.###.#.###.#.#v###\n"
//"#.....###...###...#...#\n"
//"#####################.#\n";}; // Result: 154
template<> Number AoC<2023, 23, B>(std::istream& input)
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


  using BitField = long long unsigned int;
  static_assert(sizeof(BitField) == 8, "BitField needs to have 64 bits");
  using Index = unsigned short;

  class myGlobalInfo {
  public:
    const Input& v_{ v };

    const Direction GoNull{ 0,  0 };
    const Direction GoLeft{ -1,  0 };
    const Direction GoRight{ +1,  0 };
    const Direction GoUp{ 0, -1 };
    const Direction GoDown{ 0, +1 };
    bool IsValid(Point p) const noexcept
    {
      if (p.x < 0) return false;
      if (p.x >= std::ssize(v_[0])) return false;
      if (p.y < 0) return false;
      if (p.y >= std::ssize(v_)) return false;
      return true;
    }
    bool CanGo(const Point& p, const Direction& d) const noexcept
    {
      const Point q{ p + d };
      if (!IsValid(q)) return false;

      switch (v_[q.y][q.x])
      {
        case '.': return true;
        case '#': return false;
        case '>': return true; //d == g.GoRight;
        case '<': return true; //d == g.GoLeft;
        case '^': return true; //d == g.GoUp;
        case 'v': return true; //d == g.GoDown;
        default: assert(false); return false;
      }
    }
    bool IsTrail(const Point& p, const Direction& d) const noexcept
    {
      const Point q{ p + d };
      if (!IsValid(q)) return false;
      return v_[q.y][q.x] != '#';
    }
    int WayCount(const Point& p) const noexcept
    {
      int count{ 0 };
      if (!IsTrail(p, GoNull)) return count;
      if (IsTrail(p, GoRight)) ++count;
      if (IsTrail(p, GoLeft)) ++count;
      if (IsTrail(p, GoDown)) ++count;
      if (IsTrail(p, GoUp)) ++count;
      return count;
    }
    bool IsJunction(const Point& p) const noexcept
    {
      return junction.contains(p);
    }
    Direction NextDirection(const Point& p, const Direction& d) const noexcept
    {
      if (d != GoLeft && CanGo(p, GoRight)) return GoRight;
      if (d != GoRight && CanGo(p, GoLeft)) return GoLeft;
      if (d != GoUp && CanGo(p, GoDown)) return GoDown;
      if (d != GoDown && CanGo(p, GoUp)) return GoUp;
      assert(false);
      return d;
    }
    std::pair<int, Point> FollowTrail(Point p, Direction d) const noexcept
    {
      int steps{ 0 };
      do
      {
        const auto it = junction.find(p + d);
        if (it != junction.cend() && it->second == end)
        {
          p = p + d;
          ++steps;
          break;
        }
        if (!CanGo(p, d) || WayCount(p + d) < 2)
          return { 0, p };  // it's a dead end
        p = p + d;
        ++steps;
        d = NextDirection(p, d);
      } while (!IsJunction(p));
      return { steps, p };
    }

    std::unordered_map < Point, Index,
      decltype([](const Point& p) -> size_t { return std::hash<size_t>()((p.x << 16) + p.y); }),
      decltype([](const Point& p1, const Point& p2) -> bool { return p1 == p2; }) > junction{};
    std::unordered_map < Index, Point,
      decltype([](const Index& i) -> size_t { return std::hash<size_t>()(i); }),
      decltype([](const Index& i1, const Index& i2) -> bool { return i1 == i2; }) > reversejunction{};
    Index start{};
    Index end{};
    mutable int longest{ 0 };
  };
  myGlobalInfo g{};

  class myState
  {
  public:
    myState() = delete;
    myState(Index p, BitField hist, int steps) : p_{ p }, hist_{ hist }, steps_{ steps } {}
    size_t Hash() const noexcept {
      if (hash_ == 0) hash_ = std::hash<BitField>()((hist_ << 8) + p_);
      return hash_;
    }
    bool operator ==(const myState& s) const noexcept { return p_ == s.p_ && hist_ == s.hist_; }
    bool IsAlive() const noexcept { return alive_; }
    void ReplaceWith(const myState& s) const noexcept
    {
      if (s.steps_ > steps_)
      {
        steps_ = s.steps_;
        hist_ = s.hist_;
        alive_ = true;
      }
    }
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;

      if (p_ == g.end)
      {
        if (steps_ > g.longest) g.longest = steps_;
        return v;
      }
      auto TryDirection = [&v, &g](Index p0, const Direction& d, BitField hist, int steps) -> void
        {
          Point pp = g.reversejunction.find(p0)->second;
          auto [newSteps, p] = g.FollowTrail(pp, d);
          if (newSteps > 0)
          {
            const auto it = g.junction.find(p);
            assert(it != g.junction.cend());
            if (hist & (1ULL << it->second))
              return; // been there before
            v.emplace_back(it->second, hist | (1ULL << it->second), steps + newSteps);
          }
        };

      TryDirection(p_, g.GoRight, hist_, steps_);
      TryDirection(p_, g.GoLeft, hist_, steps_);
      TryDirection(p_, g.GoDown, hist_, steps_);
      TryDirection(p_, g.GoUp, hist_, steps_);
      return v;
    }

  private:
    const Index p_{ 0 };
    mutable BitField hist_{ 0 };
    mutable size_t hash_{ 0 };
    mutable int steps_{ 0 };
    mutable bool alive_{ true };
  };

  auto GetStart = [&v]() -> Point
    {
      for (Coord x = 0; x < std::ssize(v[0]); ++x)
        if (v[0][x] == '.') return { x, 0 };
      assert(false);
      return { -1, -1 };
    };
  auto GetEnd = [&v]() -> Point
    {
      const Coord y = static_cast<Coord>(std::ssize(v) - 1);
      for (Coord x = 0; x < std::ssize(v[y]); ++x)
        if (v[y][x] == '.') return { x, y };
      assert(false);
      return { -1, -1 };
    };

  g.start = (g.junction.insert({ GetStart(), static_cast<Index>(g.junction.size() + 1) }).first)->second;
  g.reversejunction.insert({ g.start, GetStart() });
  g.end = (g.junction.insert({ GetEnd(), static_cast<Index>(g.junction.size() + 1) }).first)->second;
  g.reversejunction.insert({ g.end, GetEnd() });

  for (Coord y = 0; y < std::ssize(v); ++y)
    for (Coord x = 0; x < std::ssize(v[y]); ++x)
    {
      const Point p{ x, y };
      if (g.WayCount(p) > 2)
      {
        g.junction.insert({ p, static_cast<Index>(g.junction.size() + 1) });
        g.reversejunction.insert({ static_cast<Index>(g.junction.size()), p });
      }
    }

  myState s0(g.start, 1ULL << g.start, 0);
  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g);

  while (true)
  {
    size_t z = bfs.NextLevel();
    //std::cout << "+ " << z << " = " << bfs.GetSet().size() << ", longest = " << g.longest << std::endl;
    if (z == 0) break;
  }
  return g.longest;
}
