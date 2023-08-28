//template<> auto InputData<2019, 15, A>() { return "10 ORE => 10 A\n1 ORE => 1 B\n7 A, 1 B => 1 C\n7 A, 1 C => 1 D\n7 A, 1 D => 1 E\n7 A, 1 E => 1 FUEL\n"; };  // 31
template<> Number AoC<2019, 15, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');
  IntCodeComputer_2019_200 c(code);

  using Coord = signed char;

  using namespace BFS; // BreadthFirstSearch
  class GlobalInfo {};
  GlobalInfo g{};
  class Space
  {
  public:
    Space(Coord x, Coord y, Coord fx, Coord fy) : x_(x), y_(y), fromx_(fx), fromy_(fy) {}
//    Space() = delete;
    bool IsAlive() const noexcept { return !visited_; }

    bool IsHome() const noexcept { return x_ == 0 && y_ == 0; }
    void SetVisited() const noexcept { visited_ = true; }
    bool IsVisited() const noexcept { return visited_; }
    void SetWall() const noexcept { wall_ = visited_ = iterated_ = true; }
    bool IsWall() const noexcept { return wall_; }
  public:
    Coord x_{ };
    Coord y_{ };
    Coord fromx_{ };
    Coord fromy_{ };
    mutable bool visited_{ false };
    mutable bool wall_{ false };
    mutable bool iterated_{ false };

  public:
    size_t Hash() const noexcept { return (x_ << 8) + y_; }
    bool operator ==(const Space& s) const noexcept { return s.x_ == x_ && s.y_ == y_; }

    std::vector<Space> Iterate([[maybe_unused]] const GlobalInfo& g) const
    {
      std::vector<Space> v;
      if (!iterated_)
      {
        v.push_back(Space(x_ + 1, y_ + 0, x_, y_));
        v.push_back(Space(x_ - 1, y_ + 0, x_, y_));
        v.push_back(Space(x_ + 0, y_ + 1, x_, y_));
        v.push_back(Space(x_ + 0, y_ - 1, x_, y_));
        iterated_ = true;
      }
      return v;
    }
  };

  Space s0(0,0,0,0);
  s0.SetVisited();
  
  BreadthFirstSearch<Space, GlobalInfo> bfs(s0,g);

  while (true)
  {
    /*auto z =*/ bfs.NextLevel();
    auto& spacelist = bfs.GetSet();

    for (auto& s : spacelist)
    {
      if (s.IsVisited()) continue;

      // visit s!
      Space t = s;
      std::queue<int> wayback{};
      std::stack<int> wayout{};
      Number scode{};
      while (!t.IsHome())
      {
        size_t n = wayout.size();
        if (t.x_ < t.fromx_) { wayback.push(4); wayout.push(3); }
        if (t.x_ > t.fromx_) { wayback.push(3); wayout.push(4); }
        if (t.y_ < t.fromy_) { wayback.push(2); wayout.push(1); }
        if (t.y_ > t.fromy_) { wayback.push(1); wayout.push(2); }
        t = *spacelist.find(Space(t.fromx_, t.fromy_, 0, 0));
        assert(wayout.size() == n + 1);
      }
      size_t dist = wayout.size();
      assert(wayout.size() == wayback.size());

      // walk out
      while (wayout.size() > 0)
      {
        int direction = wayout.top();
        wayout.pop();
        c.PushInput(direction);
        c.ExecuteToOutput();
        scode = c.PopOutput(); // we were there before so ignore all except last
      }

      switch (scode)
      {
        case 0:
          s.SetWall();
          wayback.pop();  // remove first return step, as it was never taken
          break;
        case 1:
          s.SetVisited();
          break;
        case 2:
          return dist;
        default:
          assert(false);
          break;
      }

      // walk back
      while (wayback.size() > 0)
      {
        int direction = wayback.front();
        wayback.pop();
        c.PushInput(direction);
        c.ExecuteToOutput();
        scode = c.PopOutput(); // we were there before so ignore all except last
      }
    }
  }
  throw "error!";
}


//template<> auto InputData<2019, 15, B>() { return "157 ORE => 5 NZVS\n165 ORE => 6 DCFZ\n12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"; }; // 
template<> Number AoC<2019, 15, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');
  IntCodeComputer_2019_200 c(code);

  using Coord = signed char;

  using namespace BFS; // BreadthFirstSearch
  class GlobalInfo {};
  GlobalInfo g{};
  class Space
  {
  public:
    Space(Coord x, Coord y, Coord fx, Coord fy) : x_(x), y_(y), fromx_(fx), fromy_(fy) {}
    //    Space() = delete;
    bool IsAlive() const noexcept { return !visited_; }
    static void Cleanup([[maybe_unused]] StateSet<Space>& deadstates, [[maybe_unused]] StateSet<Space>& livestates) {} // allow optional removal of inferior States

    bool IsHome() const noexcept { return x_ == fromx_ && y_ == fromy_; }
    void SetVisited() const noexcept { visited_ = true; }
    bool IsVisited() const noexcept { return visited_; }
    void SetWall() const noexcept { wall_ = visited_ = iterated_ = true; }
    bool IsWall() const noexcept { return wall_; }
  public:
    Coord x_{ };
    Coord y_{ };
    Coord fromx_{ };
    Coord fromy_{ };
    mutable bool visited_{ false };
    mutable bool wall_{ false };
    mutable bool iterated_{ false };

  public:
    size_t Hash() const noexcept { return (x_ << 8) + y_; }
    bool operator ==(const Space& s) const noexcept { return s.x_ == x_ && s.y_ == y_; }

    std::vector<Space> Iterate([[maybe_unused]] const GlobalInfo& g) const
    {
      std::vector<Space> v;
      if (!iterated_)
      {
        v.push_back(Space(x_ + 1, y_ + 0, x_, y_));
        v.push_back(Space(x_ - 1, y_ + 0, x_, y_));
        v.push_back(Space(x_ + 0, y_ + 1, x_, y_));
        v.push_back(Space(x_ + 0, y_ - 1, x_, y_));
        iterated_ = true;
      }
      return v;
    }
  };

  struct H
  {
    static Space findOxy(IntCodeComputer_2019_200&c)
    {
      GlobalInfo g{};
      Space s0(0, 0, 0, 0);
      s0.SetVisited();

      BreadthFirstSearch<Space, GlobalInfo> bfs(s0,g);
      while (true)
      {
        /*auto z =*/ bfs.NextLevel();
        auto& spacelist = bfs.GetSet();

        for (auto& s : spacelist)
        {
          if (s.IsVisited()) continue;

          // visit s!
          Space t = s;
          std::queue<int> wayback{};
          std::stack<int> wayout{};
          Number scode{};
          while (!t.IsHome())
          {
            size_t n = wayout.size();
            if (t.x_ < t.fromx_) { wayback.push(4); wayout.push(3); }
            if (t.x_ > t.fromx_) { wayback.push(3); wayout.push(4); }
            if (t.y_ < t.fromy_) { wayback.push(2); wayout.push(1); }
            if (t.y_ > t.fromy_) { wayback.push(1); wayout.push(2); }
            t = *spacelist.find(Space(t.fromx_, t.fromy_, 0, 0));
            assert(wayout.size() == n + 1);
          }
          //size_t dist = wayout.size();
          assert(wayout.size() == wayback.size());

          // walk out
          while (wayout.size() > 0)
          {
            int direction = wayout.top();
            wayout.pop();
            c.PushInput(direction);
            c.ExecuteToOutput();
            scode = c.PopOutput(); // we were there before so ignore all except last
          }

          switch (scode)
          {
            case 0:
              s.SetWall();
              wayback.pop();  // remove first return step, as it was never taken
              break;
            case 1:
              s.SetVisited();
              break;
            case 2:
              return s;
            default:
              assert(false);
              break;
          }

          // walk back
          while (wayback.size() > 0)
          {
            int direction = wayback.front();
            wayback.pop();
            c.PushInput(direction);
            c.ExecuteToOutput();
            scode = c.PopOutput(); // we were there before so ignore all except last
          }
        }
      }
    }
  };

  Space oxy = H::findOxy(c);  // find the oxygen system

  oxy.fromx_ = oxy.x_;  // make it 'home'
  oxy.fromy_ = oxy.y_;
  oxy.SetVisited();

  BreadthFirstSearch<Space, GlobalInfo> bfs(oxy,g);

  size_t max{0};
  bool more{ true };
  while (more)
  {
    more = false;
    /*auto z =*/ bfs.NextLevel();
    auto& spacelist = bfs.GetSet();

    for (auto& s : spacelist)
    {
      if (s.IsVisited()) continue;

      // visit s!
      Space t = s;
      std::queue<int> wayback{};
      std::stack<int> wayout{};
      Number scode{};
      while (!t.IsHome())
      {
        size_t n = wayout.size();
        if (t.x_ < t.fromx_) { wayback.push(4); wayout.push(3); }
        if (t.x_ > t.fromx_) { wayback.push(3); wayout.push(4); }
        if (t.y_ < t.fromy_) { wayback.push(2); wayout.push(1); }
        if (t.y_ > t.fromy_) { wayback.push(1); wayout.push(2); }
        t = *spacelist.find(Space(t.fromx_, t.fromy_, 0, 0));
        assert(wayout.size() == n + 1);
      }
      assert(wayout.size() == wayback.size());

      // walk out
      while (wayout.size() > 0)
      {
        int direction = wayout.top();
        wayout.pop();
        c.PushInput(direction);
        c.ExecuteToOutput();
        scode = c.PopOutput(); // we were there before so ignore all except last
      }

      switch (scode)
      {
        case 0:
          s.SetWall();
          wayback.pop();  // remove first return step, as it was never taken
          break;
        case 1:
          s.SetVisited();
          more = true;
          if (wayback.size() > max) max = wayback.size();
          break;
        case 2:
          s.SetVisited();
          more = true;
          if (wayback.size() > max) max = wayback.size();
          break;
        default:
          assert(false);
          break;
      }

      // walk back
      while (wayback.size() > 0)
      {
        int direction = wayback.front();
        wayback.pop();
        c.PushInput(direction);
        c.ExecuteToOutput();
        scode = c.PopOutput(); // we were there before so ignore all except last
      }
    }
  }
  return max;
}
