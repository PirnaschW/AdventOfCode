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
//"6\n10\n50\n100\n500\n1000\n5000\n"; }; // Result: 6 -> 16, 10 -> 50, 50 -> 1594, 100 -> 6536, 500 -> 167004, 1000 -> 668697, 5000 -> 16733044
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
    bool wrapAround{ false };
    Point WrapAround(const Point p) const noexcept
    {
      static Coord width = static_cast<Coord>(std::size(v_));
      auto Wrap = [](Coord width, Coord z) -> Coord { if (z < 0) z += width * (-z / width + 1); return z % width; };
      return Point(Wrap(width, p.x), Wrap(width, p.y));
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
          const Point& p0 = g.wrapAround ? g.WrapAround(p) : p;
          if (!g.IsValid(p0)) return;
          if (g.v_[p0.y][p0.x] != '.') return;
          v.emplace_back(p,steps+1);
        };


      InsertIfPossible(p_ + g.GoRight, steps_);
      InsertIfPossible(p_ + g.GoLeft,  steps_);
      InsertIfPossible(p_ + g.GoDown,  steps_);
      InsertIfPossible(p_ + g.GoUp,    steps_);
      return v;
    }
    Parity GetLocationParity() const noexcept { return ((p_.x + p_.y) % 2) ? Odd: Even; }
    int GetSteps() const noexcept { return steps_; }
  private:
  public:
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


  auto GetBFS = [&g](const Point& s, Number steps) -> BFS::BreadthFirstSearch<myState, myGlobalInfo>
    {
      myState s0(s, 0);
      BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g);
      for (int z = 0; z < steps; ++z)
      {
        auto n = bfs.NextLevel();
        if (n == 0)
          break;
      }
      return bfs;
    };

  auto CountByParity = [](BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs, Parity parity, int minSteps = -1) -> Number
    {
      Number count{ 0 };
      for (const auto& s : bfs.GetSet())
      {
//        std::cout << s.p_.x << "," << s.p_.y << "; steps = " << s.steps_ << ", parity = " << s.GetLocationParity() << std::endl;
        if (s.GetSteps() > minSteps && s.GetLocationParity() == parity)
        {
          ++count;
        }
      }
      return count;
    };

  assert(std::size(v[0]) == std::size(v));
  assert(start.x == start.y);
  Coord width = static_cast<Coord>(std::size(v));

  auto Calculate1 = [&CountByParity,&GetBFS,&g,width,start](Number totalSteps) -> Number
    {
      g.wrapAround = false;
      Parity p = totalSteps % 2 ? Odd : Even;
      Parity q = totalSteps % 2 ? Even : Odd;
      if (totalSteps < width)
      {
        auto bfs = GetBFS(start, totalSteps);
        Number completePoints = CountByParity(bfs,p);
        return completePoints;
      }
      else
      {
        auto bfs = GetBFS(start, width);
        Number nComplete = totalSteps / width - 1;
        Parity parity  = nComplete % 2 ? Odd : Even;
        Parity reverse = nComplete % 2 ? Even : Odd;

        // o and e refer to the graphic!
        Number oPoints = CountByParity(bfs,p); // 65+65  is even
        Number ePoints = CountByParity(bfs,q); // 65+65 +131 is odd

        Number completeO = parity == Odd ?  nComplete      *  nComplete      : (nComplete + 1) * (nComplete + 1);
        Number completeE = parity == Odd ? (nComplete + 1) * (nComplete + 1) :  nComplete      *  nComplete;
        Number completePoints = completeO * oPoints + completeE * ePoints;

        Number remainingSteps;
        Parity pp;

        remainingSteps = totalSteps - nComplete * width - start.x - 1;
        pp = (remainingSteps-1) % 2 == totalSteps % 2 ? p : q;
        Number pointsLeft   = CountByParity(GetBFS(Point(width - 1,   start.y), remainingSteps), pp);   // left
        Number pointsRight  = CountByParity(GetBFS(Point(        0,   start.y), remainingSteps), pp);   // right
        Number pointsTop    = CountByParity(GetBFS(Point(  start.x, width - 1), remainingSteps), pp);   // top
        Number pointsBottom = CountByParity(GetBFS(Point(  start.x,         0), remainingSteps), pp);   // bottom
        completePoints += pointsLeft;
        completePoints += pointsRight;
        completePoints += pointsTop;
        completePoints += pointsBottom;

        remainingSteps = totalSteps - nComplete * width - 1;
        pp = remainingSteps % 2 == totalSteps % 2 ? p : q;
        Number points1TopLeft     = CountByParity(GetBFS(Point(width - 1, width - 1), remainingSteps), pp);   // left
        Number points1TopRight    = CountByParity(GetBFS(Point(        0, width - 1), remainingSteps), pp);   // right
        Number points1BottomLeft  = CountByParity(GetBFS(Point(width - 1,         0), remainingSteps), pp);   // top
        Number points1BottomRight = CountByParity(GetBFS(Point(        0,         0), remainingSteps), pp);   // bottom
        completePoints += nComplete * points1TopLeft;
        completePoints += nComplete * points1TopRight;
        completePoints += nComplete * points1BottomLeft;
        completePoints += nComplete * points1BottomRight;

        remainingSteps = totalSteps - (nComplete + 1) * width - 1;
        pp = remainingSteps % 2 == totalSteps % 2 ? p : q;
        Number points2TopLeft     = CountByParity(GetBFS(Point(width - 1, width - 1), remainingSteps), pp);   // left
        Number points2TopRight    = CountByParity(GetBFS(Point(        0, width - 1), remainingSteps), pp);   // right
        Number points2BottomLeft  = CountByParity(GetBFS(Point(width - 1,         0), remainingSteps), pp);   // top
        Number points2BottomRight = CountByParity(GetBFS(Point(        0,         0), remainingSteps), pp);   // bottom
        completePoints += (nComplete + 1) * points2TopLeft;
        completePoints += (nComplete + 1) * points2TopRight;
        completePoints += (nComplete + 1) * points2BottomLeft;
        completePoints += (nComplete + 1) * points2BottomRight;
        return completePoints;
      }
    };

  auto Calculate2 = [&CountByParity,&GetBFS,&g,width,start](Number totalSteps) -> Number
    {
      g.wrapAround = false;
      Parity p = totalSteps % 2 ? Odd : Even;
      Parity q = totalSteps % 2 ? Even : Odd;
      Number n = (totalSteps - width / 2) / width; // 202300
      // o and e refer to the graphic!
      auto states = GetBFS(start, width);
      Number ePoints = CountByParity(states, p); // 65+65  is even
      Number oPoints = CountByParity(states, q); // 65+65 +131 is odd
      Number eCorners = CountByParity(states, p, 65);  // count if further than 65 steps
      Number oCorners = CountByParity(states, q, 65);

      // n=0: 1 E -  4/4 EC  + 0 O + 0/4 OC 
      // n=1: 1 E +  4/4 EC  + 4 O - 8/4 OC
      // n=2: 9 E - 12/4 EC  + 4 O + 8/4 OC
      if (n % 2 == 0) // for even n
      {
        Number completePoints = (n + 1) * (n + 1) * ePoints - (n + 1) * eCorners  + n * n * oPoints + n * oCorners;
        return completePoints;
      }
      else // for odd n
      {
        Number completePoints = n * n * ePoints + n * eCorners  + (n + 1) * (n + 1) * oPoints - (n + 1) * oCorners;
        return completePoints;
      }
    };

  auto Calculate3 = [&CountByParity,&GetBFS,&g,width,start](Number totalSteps) -> Number
    {
      g.wrapAround = true;
      Parity p = totalSteps % 2 ? Odd : Even;
      Parity q = totalSteps % 2 ? Even : Odd;
      auto states = GetBFS(start, totalSteps);
      return CountByParity(states, p); // 65+65  is even
    };

  Number res1{ 0 };
  Number res2{ 0 };
  Number res3{ 0 };
  //totalSteps.clear();
  //Number remainder = targetSteps % 131;
  //for (int i = 0; i < 12; ++i)
  //  totalSteps.push_back(remainder + 131 * i);
  //totalSteps.push_back(targetSteps);

  for (int i = 0; i < std::ssize(totalSteps); ++i)
  {
    res1 = Calculate1(totalSteps[i]);
//    res2 = Calculate2(totalSteps[i]);
    //if (totalSteps[i] < 500)
    //  res3 = Calculate3(totalSteps[i]);
//    std::cout << totalSteps[i] << " res1 = " << res1 << " res2 = " << res2 << " res3 = " << res3 << std::endl;
  }
  return res1;
}
