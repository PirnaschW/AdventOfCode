//template<> auto InputData<2023, 21, A>() { return
//"...........\n"
//".....###.#.\n"
//".###.##..#.\n"
//"..#.#...#..\n"
//"....#.#....\n"
//".##..S####.\n"
//".##..#...#.\n"
//".......##..\n"
//".##.#.####.\n"
//".##..##.##.\n"
//"...........\n"
//"6\n"; }; // Result: 16
template<> Number AoC<2023, 21, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  int totalSteps{ 64 };
  if (v[std::ssize(v) - 1].size() != v[0].size())  // then it's test data
  {
    int z = sscanf_s(v[std::ssize(v) - 1].c_str(), "%d", &totalSteps);
    assert(z == 1);
    v.pop_back();
  }

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
    const Coord dx;
    const Coord dy;
  };

  class Point
  {
  public:
    constexpr Point(Coord x_, Coord y_) noexcept : x{ x_ }, y{ y_ } {}
    constexpr bool operator ==(const Point& p) const noexcept { return x == p.x && y == p.y; }
    constexpr Point operator +(const Direction& d) const noexcept { return { static_cast<Coord>(x + d.dx), static_cast<Coord>(y + d.dy) }; }
  public:
    const Coord x;
    const Coord y;
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
    void ReplaceWith(const myState& s) const noexcept {}
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;

      auto InsertIfPossible = [&g, &v](const Point& p, int steps) -> void
        {
          if (!g.IsValid(p)) return;
          if (g.v_[p.y][p.x] != '.') return;
          v.emplace_back(p,steps+1);
        };


      InsertIfPossible(p_ + g.GoRight, steps_);
      InsertIfPossible(p_ + g.GoLeft,  steps_);
      InsertIfPossible(p_ + g.GoDown,  steps_);
      InsertIfPossible(p_ + g.GoUp,    steps_);
      return v;
    }
    bool AreStepsEven() const noexcept { return !(steps_ % 2); }
  private:
    const Point p_{ 0, 0 };
    const int steps_{ 0 };
    mutable size_t hash_{ 0 };
    mutable bool alive_{ true };
  };

  auto GetStart = [&v]() -> Point
    {
      for (Coord y = 0; y < std::ssize(v); ++y)
        for (Coord x = 0; x < std::ssize(v[y]); ++x)
          if (v[y][x] == 'S') return { x, y };
      assert(false);
      return { -1, -1 };
    };

  myGlobalInfo g{};
  Point start = GetStart();
  myState s0(start, 0);
  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g, totalSteps * 4);

  for (int z = 0; z < totalSteps; ++z)
  {
    auto n = bfs.NextLevel();
  }

  const auto& states = bfs.GetSet();
  Number z{ 0 };
  for (const auto& s : states)
  {
    if (s.AreStepsEven()) ++z;
  }
  return z;
}

//template<> auto InputData<2023, 21, B>() { return
//"...........\n"
//".....###.#.\n"
//".###.##..#.\n"
//"..#.#...#..\n"
//"....#.#....\n"
//".##..S####.\n"
//".##..#...#.\n"
//".......##..\n"
//".##.#.####.\n"
//".##..##.##.\n"
//"...........\n"
//"10\n50\n100\n500\n1000\n5000\n"; }; // Result: 10 -> 50, 50 -> 1594, 100 -> 6536, 500 -> 167004, 1000 -> 668697, 5000 -> 16733044
template<> Number AoC<2023, 21, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number targetSteps{ 26'501'365 };
  std::vector<Number> totalSteps{};
  bool testing{ false };
  if (v[std::ssize(v) - 1].size() != v[0].size())  // then it's test data
  {
    testing = true;
    for (int i = 1; i < std::ssize(v); ++i)
    {
      if (v[i].size() == v[0].size()) continue;
      Number steps{ 0 };
      int z = sscanf_s(v[i].c_str(), "%lld", &steps);
      assert(z == 1);
      totalSteps.push_back(steps);
    }
    for (int i = 1; i < std::ssize(v); ++i)
    {
      if (v[i].size() == v[0].size()) continue;
      v.erase(v.begin() + i, v.end());
      break;
    }
  }
  else totalSteps.push_back(targetSteps);

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
    const Coord dx;
    const Coord dy;
  };

  class Point
  {
  public:
    constexpr Point(Coord x_, Coord y_) noexcept : x{ x_ }, y{ y_ } {}
    constexpr bool operator ==(const Point& p) const noexcept { return x == p.x && y == p.y; }
    constexpr Point operator +(const Direction& d) const noexcept { return { static_cast<Coord>(x + d.dx), static_cast<Coord>(y + d.dy) }; }
  public:
    const Coord x;
    const Coord y;
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
  };

  enum Parity
  {
    Even = 0,
    Odd = 1,
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
    void ReplaceWith(const myState& s) const noexcept {}
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;

      auto InsertIfPossible = [&g, &v](const Point& p, int steps) -> void
        {
          if (!g.IsValid(p)) return;
          if (g.v_[p.y][p.x] != '.') return;
          v.emplace_back(p,steps+1);
        };


      InsertIfPossible(p_ + g.GoRight, steps_);
      InsertIfPossible(p_ + g.GoLeft,  steps_);
      InsertIfPossible(p_ + g.GoDown,  steps_);
      InsertIfPossible(p_ + g.GoUp,    steps_);
      return v;
    }
    Parity GetStepsParity() const noexcept { return (steps_ % 2) ? Even : Odd; }
  private:
    const Point p_{ 0, 0 };
    const int steps_{ 0 };
    mutable size_t hash_{ 0 };
    mutable bool alive_{ true };
  };

  auto GetStart = [&v]() -> Point
    {
      for (Coord y = 0; y < std::ssize(v); ++y)
        for (Coord x = 0; x < std::ssize(v[y]); ++x)
          if (v[y][x] == 'S')
          {
            v[y][x] = '.';
            return { x, y };
          }
      assert(false);
      return { -1, -1 };
    };

  myGlobalInfo g{};
  Point start = GetStart();


  auto GetCount = [&g](const Point& s, Number steps, Parity parity) -> Number
    {
      myState s0(s, 0);
      BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g);
      for (int z = 0; z < steps; ++z)
      {
        auto n = bfs.NextLevel();
        if (n == 0)
          break;
      }
      const auto& states = bfs.GetSet();
      Number count{ 0 };
      for (const auto& s : states)
      {
        if (s.GetStepsParity() == parity) ++count;
      }
      return count;
    };



  assert(std::size(v[0]) == std::size(v));
  assert(start.x == start.y);
  Coord width = static_cast<Coord>(std::size(v));
  //totalSteps = width * 5 / 2;  // for testing

  auto Calculate = [&GetCount,width,start](Number totalSteps) -> Number
    {

      Number completePoints{ 0 };
      if (totalSteps < width / 2)
      {
        completePoints = GetCount(start, width, Odd);
      }
      else
      {
        Number nComplete = totalSteps / width - 1;
        Parity parity  = nComplete % 2 ? Odd : Even;
        Parity reverse = nComplete % 2 ? Even : Odd;
        if (nComplete < 0)
        {
          nComplete = 0;
          completePoints = 0;
        }
        else
        {
          Number completeOdd = parity == Odd ? nComplete * nComplete : (nComplete + 1) * (nComplete + 1);
          Number completeEven = parity == Odd ? (nComplete + 1) * (nComplete + 1) : nComplete * nComplete;
          Number oddPoints = GetCount(start, width, parity);
          Number evenPoints = GetCount(start, width, reverse);
          completePoints = completeOdd * oddPoints + completeEven + evenPoints;
        }

        Number remainingSteps;

        remainingSteps = totalSteps - nComplete * width - start.x;
        Number pointsLeft = GetCount(Point(width - 1, start.y), remainingSteps, parity);   // left
        Number pointsRight = GetCount(Point(0, start.y), remainingSteps, parity);   // right
        Number pointsTop = GetCount(Point(start.x, width - 1), remainingSteps, parity);   // top
        Number pointsBottom = GetCount(Point(start.x, 0), remainingSteps, parity);   // bottom
        completePoints += pointsLeft;
        completePoints += pointsRight;
        completePoints += pointsTop;
        completePoints += pointsBottom;

        remainingSteps = totalSteps - nComplete * width;
        Number points1TopLeft = GetCount(Point(width - 1, width - 1), remainingSteps, parity);   // left
        Number points1TopRight = GetCount(Point(0, width - 1), remainingSteps, parity);   // right
        Number points1BottomLeft = GetCount(Point(width - 1, 0), remainingSteps, parity);   // top
        Number points1BottomRight = GetCount(Point(0, 0), remainingSteps, parity);   // bottom
        completePoints += nComplete * points1TopLeft;
        completePoints += nComplete * points1TopRight;
        completePoints += nComplete * points1BottomLeft;
        completePoints += nComplete * points1BottomRight;

        remainingSteps = totalSteps - (nComplete + 1) * width;
        Number points2TopLeft = GetCount(Point(width - 1, width - 1), remainingSteps, reverse);   // left
        Number points2TopRight = GetCount(Point(0, width - 1), remainingSteps, reverse);   // right
        Number points2BottomLeft = GetCount(Point(width - 1, 0), remainingSteps, reverse);   // top
        Number points2BottomRight = GetCount(Point(0, 0), remainingSteps, reverse);   // bottom
        completePoints += (nComplete + 1) * points2TopLeft;
        completePoints += (nComplete + 1) * points2TopRight;
        completePoints += (nComplete + 1) * points2BottomLeft;
        completePoints += (nComplete + 1) * points2BottomRight;
      }
      return completePoints;
    };

  Number res{ 0 };
  for (int i = 0; i < std::ssize(totalSteps); ++i)
  {
    res = Calculate(totalSteps[i]);
    std::cout << totalSteps[i] << " " << res << std::endl;
  }
  return res;
  // FL: 316560330685443 is too low
  // FL: 316560299935843 is too low
  // FL: 316560257858007 is probably too low too
  // FL: 315946384577007 is probably too low too
}
