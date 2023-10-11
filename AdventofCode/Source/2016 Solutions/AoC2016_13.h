//template<> auto AdventOfCode::InputData<2016, 13, A>() { return "10\n7\n4\n";}; // Result: ?
template<> Number AoC<2016, 13, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Coord = char;

  class myGlobalInfo {
  public:
    Number x{ 31 };
    Number y{ 39 };
    mutable bool done{ false };
    mutable Number best{std::numeric_limits<decltype(best)>::max()};
    Number addon{ 0 };
  };
  myGlobalInfo g{};
  int z0 = sscanf_s(v[0].c_str(), "%lld", &g.addon);
  assert(z0 == 1);
  if (v.size() > 1)
  {
    int z1 = sscanf_s(v[1].c_str(), "%lld", &g.x);
    assert(z1 == 1);
    int z2 = sscanf_s(v[2].c_str(), "%lld", &g.y);
    assert(z2 == 1);
  }

  class myState
  {
  public:
    myState() = delete;
    myState(Coord x, Coord y, Number steps) : x_(x), y_(y), steps_(steps) {}
    size_t Hash() const noexcept { return (x_ << 8) + y_; }
    bool operator ==(const myState& s) const noexcept { return x_ == s.x_ && y_ == s.y_; }
    bool IsAlive() const noexcept { return alive_; }
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      if (x_ == g.x && y_ == g.y)
      {
        g.done = true;
        if (g.best > steps_)
        {
          g.best = steps_;
        }
      }
      alive_ = false;
      std::vector<myState> v;
      auto Func = [&g](const Number x, const Number y) -> Number { return x * x + 3 * x + 2 * x * y + y + y * y + g.addon; };
      auto BitCount = [](const Number z) -> std::size_t { return std::bitset<8*sizeof(Number)>(z).count(); };

      auto Valid = [&BitCount,&Func](const Coord x, const Coord y) -> bool { return x >= 0 && y >= 0 && (BitCount(Func(x,y)) % 2 == 0); };
      auto AddIfValid = [&Valid,&v,this](const Coord x, const Coord y) -> void { if (Valid(x, y)) v.emplace_back(x, y, steps_+1); };

      AddIfValid(x_ - 1, y_);
      AddIfValid(x_ + 1, y_);
      AddIfValid(x_, y_ - 1);
      AddIfValid(x_, y_ + 1);
      return v;
    }
  private:
    const Coord x_{ 0 };
    const Coord y_{ 0 };
    const Number steps_{ 0 };
    mutable bool alive_{ true };
  };

  myState s0(1,1,0);

  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0,g);
  while (!g.done)
  {
    auto z = bfs.NextLevel();
  }

  return g.best;
}

//template<> auto InputData<2016, 13, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 13, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Coord = char;

  class myGlobalInfo {
  public:
    Number n{ 50 };
    mutable bool done{ false };
    mutable Number best{std::numeric_limits<decltype(best)>::max()};
    Number addon{ 0 };
  };
  myGlobalInfo g{};
  int z0 = sscanf_s(v[0].c_str(), "%lld", &g.addon);
  assert(z0 == 1);

  class myState
  {
  public:
    myState() = delete;
    myState(Coord x, Coord y, Number steps) : x_(x), y_(y), steps_(steps) {}
    size_t Hash() const noexcept { return (x_ << 8) + y_; }
    bool operator ==(const myState& s) const noexcept { return x_ == s.x_ && y_ == s.y_; }
    bool IsAlive() const noexcept { return alive_; }
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      if (steps_ == g.n - 1)
      {
        g.done = true;
      }
      alive_ = false;
      std::vector<myState> v;
      auto Func = [&g](const Number x, const Number y) -> Number { return x * x + 3 * x + 2 * x * y + y + y * y + g.addon; };
      auto BitCount = [](const Number z) -> std::size_t { return std::bitset<8*sizeof(Number)>(z).count(); };

      auto Valid = [&BitCount,&Func](const Coord x, const Coord y) -> bool { return x >= 0 && y >= 0 && (BitCount(Func(x,y)) % 2 == 0); };
      auto AddIfValid = [&Valid,&v,this](const Coord x, const Coord y) -> void { if (Valid(x, y)) v.emplace_back(x, y, steps_+1); };

      AddIfValid(x_ - 1, y_);
      AddIfValid(x_ + 1, y_);
      AddIfValid(x_, y_ - 1);
      AddIfValid(x_, y_ + 1);
      return v;
    }
  private:
    const Coord x_{ 0 };
    const Coord y_{ 0 };
    const Number steps_{ 0 };
    mutable bool alive_{ true };
  };

  myState s0(1,1,0);

  BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0,g);
  while (!g.done)
  {
    auto z = bfs.NextLevel();
  }

  return bfs.GetSet().size();
}
