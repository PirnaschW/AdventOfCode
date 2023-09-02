//template<> auto InputData<2019, 22, A>() { return " Testdata\n";}; // 
template<> Number AoC<2019, 22, A>(std::istream& input)
{
  using Coord = char;
  using Point = std::pair<Coord, Coord>;

  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector
  assert(v.size() < std::numeric_limits<Coord>::max());
  assert(v[0].size() < std::numeric_limits<Coord>::max());
  const Coord xSize{ static_cast<Coord>(v[0].size()) };
  const Coord ySize{ static_cast<Coord>(v.size()) };

  auto Char = [&v](Coord x, Coord y) -> char { return v[y][x]; };
  auto Name = [&v, &Char](Coord x1, Coord y1, Coord x2, Coord y2) -> std::string { return std::string({ Char(x1,y1),Char(x2,y2) }); };

  using TeleporterList = std::multimap<std::string, Point>;
  TeleporterList tl{};
  // check for horizontal teleporter points
  for (Coord y = 0; y < ySize; ++y)
  {
    for (Coord x = 1; x < xSize - 1; ++x)
    {
      if (Char(x - 1, y) == '.' && isalpha(Char(x, y)) && isalpha(Char(x + 1, y)))
      {
        tl.emplace(Name(x, y, x + 1, y), Point{ x,y });
      }
      if (Char(x + 1, y) == '.' && isalpha(Char(x, y)) && isalpha(Char(x - 1, y)))
      {
        tl.emplace(Name(x - 1, y, x, y), Point{ x,y });
      }
    }
  }
  // check for vertical teleporter points
  for (Coord x = 0; x < xSize; ++x)
  {
    for (Coord y = 1; y < ySize - 1; ++y)
    {
      if (Char(x, y - 1) == '.' && isalpha(Char(x, y)) && isalpha(Char(x, y + 1)))
      {
        tl.emplace(Name(x, y, x, y + 1), Point{ x,y });
      }
      if (Char(x, y + 1) == '.' && isalpha(Char(x, y)) && isalpha(Char(x, y - 1)))
      {
        tl.emplace(Name(x, y - 1, x, y), Point{ x,y });
      }
    }
  }

  assert(tl.size() > 0);
  assert(tl.size() % 2 == 0);

  using TeleporterMap = std::unordered_map < Point, Point, decltype([](const Point& p) { return p.first << 8 | p.second; }) > ;
  TeleporterMap tm{};
  // build teleporter map

  Point aa{};
  Point zz{};
  for (auto it = tl.begin(); it != tl.end(); ++it)
  {
    const std::string& n1 = it->first;
    const Point p1 = it->second;

    if (n1 == "AA")
    {
      aa = p1;
    }
    else if (n1 == "ZZ")
    {
      zz = p1;
    }
    else
    {
      ++it; assert(it != tl.end());
      const std::string& n2 = it->first;
      const Point p2 = it->second;
      assert(n1 == n2);
      tm.emplace(p1, p2);
      tm.emplace(p2, p1);
    }
  }
  //ShowBucketHistogram(tm);
  assert(tm.size() > 0);
  assert(tm.size() + 2 == tl.size());


  using namespace BFS;

  class GlobalInfo
  {
  public:
    constexpr GlobalInfo(const Input& v, const TeleporterMap& tm, Point aa, Point zz) : v_(v), tm_(tm), sizex_(static_cast<Coord>(v[0].size())), sizey_(static_cast<Coord>(v.size())), aa_(aa), zz_(zz) {};
    constexpr char GetContent(const Point& p) const noexcept
    {
      if (p.first < 0 || p.first >= sizex_) return '\0';
      if (p.second < 0 || p.second >= sizey_) return '\0';
      return v_[p.second][p.first];
    }
    std::pair<bool, Point> GetDestination(Point p) const noexcept
    {
      if (p == zz_) return { true,zz_ };
      const auto it = tm_.find(p);
      return { it != tm_.end(),(it != tm_.end() ? it->second : p) };
    }
  private:

  public:
  private:
    const Input& v_{};
    const TeleporterMap& tm_{};
    const Coord sizex_{};
    const Coord sizey_{};
    const Point aa_{};
    const Point zz_{};
    mutable Number curSteps_{ 0 };
  };
  GlobalInfo g(v, tm, aa, zz);

  class State;
  using StateVec = std::vector<State>;
  class State
  {
  public:
    State(Point p, Number steps) : p_(p), steps_(steps) {}
    State() = delete;

  public:
    size_t Hash() const noexcept { return p_.first << 8 | p_.second; }
    constexpr bool operator ==(const State& s) const noexcept { return s.p_ == p_; }
    constexpr bool IsAlive() const noexcept { return !iterated_; }
    constexpr Number GetSteps() const noexcept { return steps_; }
    constexpr void TryPoint(const GlobalInfo& g, const Point& p0, Coord dx, Coord dy, StateVec& n) const noexcept
    {
      const Point p{ static_cast<Coord>(p0.first + dx), static_cast<Coord>(p0.second + dy) };
      const char content = g.GetContent(p);
      switch (content)
      {
        case '\0': break; // can't go there
        case '#':  break; // wall
        case ' ':  break; // can't go there
        case '.': n.emplace_back(State(p, steps_ + 1)); break;
        default:
          std::pair<bool, Point> res = g.GetDestination(p);
          if (res.first) n.emplace_back(State(res.second, steps_)); break; // found Transporter
      }
    }

    constexpr StateVec Iterate(const GlobalInfo& g) const
    {
      StateVec newlist{};
      if (!iterated_)
      {
        TryPoint(g, p_, +1, +0, newlist);
        TryPoint(g, p_, -1, +0, newlist);
        TryPoint(g, p_, +0, +1, newlist);
        TryPoint(g, p_, +0, -1, newlist);
        iterated_ = true;
      }
      return newlist;
    }

  public:
    const Point p_{};
    const Number steps_{};
    mutable bool iterated_{ false };
  };

  using StateSet = std::unordered_set < State, decltype([](const State& s)->size_t {return s.Hash(); }), decltype([](const State& s1, const State& s2)->bool {return s1 == s2; }) > ;

  State saa(aa, 0);
  State szz(zz, 0);
  BreadthFirstSearch<State, GlobalInfo> bfs(saa, g);


  Number n{ 0 };
  while (true)
  {
    ++n;
    bfs.NextLevel();
    const auto& set{ bfs.GetSet() };
    const auto it = set.find(szz);
    if (it != set.end())
    {
      return it->GetSteps() - 1;
    }
  }
  throw "error";
}

//template<> auto InputData<2019, 22, B>() { return " Testdata\n";}; // 
template<> Number AoC<2019, 22, B>(std::istream& input)
{
  return 0;
}