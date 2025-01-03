//template<> auto InputData<2023, 17, A>() { return
//"2413432311323\n"
//"3215453535623\n"
//"3255245654254\n"
//"3446585845452\n"
//"4546657867536\n"
//"1438598798454\n"
//"4457876987766\n"
//"3637877979653\n"
//"4654967986887\n"
//"4564679986453\n"
//"1224686865563\n"
//"2546548887735\n"
//"4322674655533\n";}; // Result: 102
template<> Number AoC<2023, 17, A>(std::istream& input)
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
    const Point p{ static_cast<Coord>(std::ssize(v[0]) - 1), static_cast<Coord>(std::ssize(v) - 1) };
    mutable bool done{ false };
    mutable Number best{std::numeric_limits<decltype(best)>::max()};

    const Direction GoNull {  0,  0 };
    const Direction GoLeft { -1,  0 };
    const Direction GoRight{ +1,  0 };
    const Direction GoUp   {  0, -1 };
    const Direction GoDown {  0, +1 };
    Number Loss(Point p) const { return v_[p.y][p.x] - '0'; }
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
    myState(Point p, Direction d, Number loss) : p_{p}, d_{d}, loss_{loss} {}
    size_t Hash() const noexcept {
      if (hash_ == 0) hash_ = std::hash<size_t>()(((p_.x << 24) + (p_.y << 16)) ^ ((d_.dx << 4) + d_.dy));
      return hash_;
    }
    bool operator ==(const myState& s) const noexcept { return p_ == s.p_ && d_ == s.d_; }
    bool IsAlive() const noexcept { return alive_; }
    void ReplaceWith(const myState& s) const noexcept { if (s.loss_ < loss_) { loss_ = s.loss_; alive_ = true; } }  // use this to 'update' the state in the set (this) to the data from s, if s is 'better'
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;
      if (p_ == g.p)
      {
        if (loss_ < g.best)
        {
          g.best = loss_;
          return v;
        }
      }
      
      Number l = loss_;
      for (int z = 1; z <= 3; ++z)
      {
        Point p = p_ + d_ * z;
        if (!g.IsValid(p))
          break;
        l += g.Loss(p);
        v.emplace_back(p, d_.TurnRight(), l);
        v.emplace_back(p, d_.TurnLeft(), l);
      }
      return v;
    }
  private:
    const Point p_{ 0, 0 };
    const Direction d_{ 0, 0 };
    mutable Number loss_{ 0 };
    mutable size_t hash_{ 0 };
    mutable bool alive_{ true };
  };

  myGlobalInfo g{};
  myState s0({ 0, 0 }, g.GoRight, 0);
  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g, std::ssize(v)* std::ssize(v[0]) * 4);
  myState s1({ 0, 0 }, g.GoDown, 0);
  bfs.GetSet().insert(s1);

  size_t n{ 1 };
  Number z{ 0 };
  while (n>0)
  {
    n = bfs.NextLevel();
    std::cout << ++z << ": + " << n << " = " << bfs.GetSet().size() << std::endl;
  }

  return g.best;
}

//template<> auto InputData<2023, 17, B>() { return
//"2413432311323\n"
//"3215453535623\n"
//"3255245654254\n"
//"3446585845452\n"
//"4546657867536\n"
//"1438598798454\n"
//"4457876987766\n"
//"3637877979653\n"
//"4654967986887\n"
//"4564679986453\n"
//"1224686865563\n"
//"2546548887735\n"
//"4322674655533\n";}; // Result: 71
template<> Number AoC<2023, 17, B>(std::istream& input)
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
    const Point p{ static_cast<Coord>(std::ssize(v[0]) - 1), static_cast<Coord>(std::ssize(v) - 1) };
    mutable bool done{ false };
    mutable Number best{ std::numeric_limits<decltype(best)>::max() };

    const Direction GoNull {  0,  0 };
    const Direction GoLeft { -1,  0 };
    const Direction GoRight{ +1,  0 };
    const Direction GoUp   {  0, -1 };
    const Direction GoDown {  0, +1 };
    Number Loss(Point p) const { return v_[p.y][p.x] - '0'; }
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
    myState(Point p, Direction d, Number loss) : p_{ p }, d_{ d }, loss_{ loss } {}
    size_t Hash() const noexcept {
      if (hash_ == 0) hash_ = std::hash<size_t>()(((p_.x << 24) + (p_.y << 16)) ^ ((d_.dx << 4) + d_.dy));
      return hash_;
    }
    bool operator ==(const myState& s) const noexcept { return p_ == s.p_ && d_ == s.d_; }
    bool IsAlive() const noexcept { return alive_; }
    void ReplaceWith(const myState& s) const noexcept { if (s.loss_ < loss_) { loss_ = s.loss_; alive_ = true; } }  // use this to 'update' the state in the set (this) to the data from s, if s is 'better'
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;

      if (p_ == g.p)
      {
        if (loss_ < g.best)
        {
          g.best = loss_;
          return v;
        }
      }

      Number l = loss_;
      for (int z = 1; z <= 10; ++z)
      {
        Point p = p_ + d_ * z;
        if (!g.IsValid(p))
          break;
        l += g.Loss(p);
        if (z >= 4)
        {
          v.emplace_back(p, d_.TurnRight(), l);
          v.emplace_back(p, d_.TurnLeft(), l);
        };
      }
      return v;
    }
  private:
    const Point p_{ 0, 0 };
    const Direction d_{ 0, 0 };
    mutable Number loss_{ 0 };
    mutable size_t hash_{ 0 };
    mutable bool alive_{ true };
  };

  myGlobalInfo g{};
  myState s0({ 0, 0 }, g.GoRight, 0);
  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g, std::ssize(v) * std::ssize(v[0]) * 4);
  myState s1({ 0, 0 }, g.GoDown, 0);
  bfs.GetSet().insert(s1);

  size_t n{ 1 };
  Number z{ 0 };
  while (n > 0)
  {
    n = bfs.NextLevel();
    std::cout << ++z << ": + " << n << " = " << bfs.GetSet().size() << std::endl;
  }

  return g.best;
}
