//template<> auto InputData<2019, 18, A>() { return "Testdata\n"; }; // 
template<> Number AoC<2019, 18, A>(std::istream& input)
{
  using Coord = char;
  using Point = std::pair<Coord, Coord>;
  class GlobalInfo
  {
  public:
    constexpr GlobalInfo(const std::vector<std::string>& v) : v_(v), sizex_(static_cast<Coord>(v[0].size())), sizey_(static_cast<Coord>(v.size())) {};
    constexpr Point GetEntry() const noexcept
    {
      if (!entryknown_) FindEntry();
      return entry_;
    }
    constexpr char GetContent(const Point& p) const noexcept
    {
      if (p.first < 0 || p.first >= sizex_) return '\0';
      if (p.second < 0 || p.second >= sizey_) return '\0';
      return v_[p.second][p.first];
    }
    constexpr Number GetMinSteps() const noexcept { return minSteps_; }
  private:
    constexpr void FindEntry() const noexcept
    {
      for (Coord x = 0; x < sizex_; ++x)
      {
        for (Coord y = 0; y < sizey_; ++y)
        {
          if (v_[y][x] == '@')
          {
            entry_ = { x,y };
            entryknown_ = true;
            return;
          }
        }
      }
    }

  public:
    const std::vector<std::string>& v_{};
    const Coord sizex_{};
    const Coord sizey_{};
    mutable Number curSteps_{ 0 };
    mutable Number minSteps_{ 0 };
    mutable char maxKeys_{ 0 };
  private:
    mutable Point entry_{};
    mutable bool entryknown_{ false };
  };

  const auto v = ReadLines(input);  // read all lines into vector
  const GlobalInfo g(v);

  using Key = char;

  constexpr char BitCount{ 26 };
  class Keys
  {
  public:
    constexpr bool operator ==(Keys k) const noexcept { return keylist == k.keylist; }
    constexpr void SetKey(Key k) noexcept { keylist.set(k - 'a'); }
    constexpr bool HasKey(Key k) const noexcept { return keylist.test(k - 'a'); }
    constexpr size_t Count() const noexcept { return keylist.count(); }

  public:
    std::bitset<BitCount> keylist;
  };

  class State;
  using StateVec = std::vector<State>;
  class State
  {
  public:
    State(Point p, Keys k, Number steps) : p_(p), k_(k), steps_(steps) {}
    State() = delete;

  public:
    static_assert(sizeof(size_t) >= 4);
    size_t Hash() const noexcept { return std::hash<decltype(k_.keylist)>()(k_.keylist); }
    constexpr bool operator ==(const State& s) const noexcept { return s.k_ == k_; }
    constexpr bool IsAlive() const noexcept { return !iterated_; }
    constexpr bool IsDeleted() const noexcept { return deleted_; }
    constexpr void Delete() const noexcept { deleted_ = true; }
    constexpr void TryPoint(const GlobalInfo& g, const Point& p, const Keys& k, StateVec& n) const noexcept
    {
      const char content = g.GetContent(p);
      switch (content)
      {
        case '\0': break; // can't go there
        case '#':  break; // wall
        case '.': n.push_back(State(p, k, g.curSteps_)); break;
        case '@': n.push_back(State(p, k, g.curSteps_)); break;
        default:  // found key or door
          if (islower(content))
          {
            Keys newk{ k };
            if (!newk.HasKey(content))
            {
              newk.SetKey(content);  // add key to our keylist
              if (newk.Count() > g.maxKeys_)
              {
                g.maxKeys_ = static_cast<char>(newk.Count());
                g.minSteps_ = g.curSteps_;
                //std::cout << newk.keylist.to_string() << ' ' << g.minSteps_ << std::endl;
              }
            }
            n.push_back(State(p, newk, g.curSteps_));
          }
          else
          {
            if (k.HasKey((char) tolower((int) content)))  // Door - do we have this key?
            {
              n.push_back(State(p, k, g.curSteps_));  // may enter through this door
            }
          }
          break;
      }
    }

    constexpr StateVec Iterate(const GlobalInfo& g) const
    {
      StateVec newlist{};
      if (!iterated_)
      {
        TryPoint(g, { (Coord) (p_.first + 1), (Coord) (p_.second + 0) }, k_, newlist);
        TryPoint(g, { (Coord) (p_.first - 1), (Coord) (p_.second + 0) }, k_, newlist);
        TryPoint(g, { (Coord) (p_.first + 0), (Coord) (p_.second + 1) }, k_, newlist);
        TryPoint(g, { (Coord) (p_.first + 0), (Coord) (p_.second - 1) }, k_, newlist);
        iterated_ = true;
      }
      return newlist;
    }
    constexpr bool IsSubsetOf(const State& s) const noexcept // is *this a subset of s?
    {
      const auto res = ~s.k_.keylist & k_.keylist;
      //std::cout << k_.keylist << " is superseded by " << s.k_.keylist << " ? -> " << (!res.any()) << std::endl;
      return !(res.any());
    }

  public:
    const Point p_{};
    const Keys k_{};
    const Number steps_{};
    mutable bool iterated_{ false };
    mutable bool deleted_{ false };
  };

  class StateHash {
  public: size_t operator() (const State& s) const noexcept { return s.Hash(); }
  };
  class StateEqual {
  public: bool operator() (const State& s1, const State& s2) const noexcept { return s1 == s2; }
  };

  using StateSet = std::unordered_set<State, StateHash, StateEqual>;

  std::vector<std::vector<StateSet>> states{};
  states.resize(g.sizex_);
  for (auto i = 0; i < g.sizex_; ++i) states[i].resize(g.sizey_);

  const State s0(g.GetEntry(), Keys(), 0);
  states[s0.p_.first][s0.p_.second].insert(s0);

  StateVec newstates{}; // this will collect the new states
  newstates.reserve(7000);
  static size_t maxnewstates{ 0 };
  while (true)
  {
    ++g.curSteps_;

    newstates.clear();
    for (auto x = 0; x < g.sizex_; ++x)
    {
      for (auto y = 0; y < g.sizey_; ++y)
      {
        for (const auto& s : states[x][y])
        {
          if (s.IsAlive())
          {
            newstates.append_range(s.Iterate(g));
            if (g.maxKeys_ == BitCount)
              return g.curSteps_;
          }
        }
      }
    }
    for (const auto& s : newstates)
    {
      StateSet& set{ states[s.p_.first][s.p_.second] };
      if (!set.contains(s))
      {
        for (const auto& ss : set)
        {
          if (ss.IsSubsetOf(s))
          {
            ss.Delete();
          }
        }
        // erase all deleted states
        std::erase_if(set, [](const State& s) -> bool { return s.IsDeleted(); });
        set.insert(s);
      }
    }

    if (newstates.size() == 0)
    {
      assert(false);
      break;
    }
  }

  Number n = g.minSteps_;
  return n;
}

//template<> auto InputData<2019, 18, B>() { return "Testdata\n"; }; // 
template<> Number AoC<2019, 18, B>(std::istream& input)
{
  using Coord = char;
  using Point = std::pair<Coord, Coord>;
  class GlobalInfo
  {
  public:
    constexpr GlobalInfo(const std::vector<std::string>& v) : v_(v), sizex_(static_cast<Coord>(v[0].size())), sizey_(static_cast<Coord>(v.size())) {};
    constexpr Point GetEntry() const noexcept
    {
      if (!entryknown_) FindEntry();
      return entry_;
    }
    constexpr char GetContent(const Point& p) const noexcept
    {
      if (p.first < 0 || p.first >= sizex_) return '\0';
      if (p.second < 0 || p.second >= sizey_) return '\0';
      return v_[p.second][p.first];
    }
    constexpr Number GetMinSteps() const noexcept { return minSteps_; }
  private:
    constexpr void FindEntry() const noexcept
    {
      for (Coord x = 0; x < sizex_; ++x)
      {
        for (Coord y = 0; y < sizey_; ++y)
        {
          if (v_[y][x] == '@')
          {
            entry_ = { x,y };
            entryknown_ = true;
            return;
          }
        }
      }
    }

  public:
    const std::vector<std::string>& v_{};
    const Coord sizex_{};
    const Coord sizey_{};
    mutable Number curSteps_{ 0 };
    mutable Number minSteps_{ 0 };
    mutable char maxKeys_{ 0 };
  private:
    mutable Point entry_{};
    mutable bool entryknown_{ false };
  };

  auto v = ReadLines(input);  // read all lines into vector

  // need to modify v, and cut into multiple parts
  v[39][39] = '@';
  v[39][40] = '#';
  v[39][41] = '@';
  v[40][39] = '#';
  v[40][40] = '#';
  v[40][41] = '#';
  v[41][39] = '@';
  v[41][40] = '#';
  v[41][41] = '@';

  std::vector<std::string> v1{}; // top left
  std::vector<std::string> v2{}; // top right
  std::vector<std::string> v3{}; // bottom left
  std::vector<std::string> v4{}; // bottom right

  const Coord halfX{ static_cast<Coord>((v[0].size()+1)/2) };
  const Coord halfY{ static_cast<Coord>((v.size()+1)/2) };

  for (Coord y = 0; y < v.size(); ++y)
  {
    if (y < halfY)
    {
      v1.push_back(v[y].substr(0, halfX));
      v2.push_back(v[y].substr(halfX-1, halfX));
    }
    if (y >= halfY-1)
    {
      v3.push_back(v[y].substr(0, halfX));
      v4.push_back(v[y].substr(halfX-1, halfX));
    }
  }

  const GlobalInfo g1(v1);
  const GlobalInfo g2(v2);
  const GlobalInfo g3(v3);
  const GlobalInfo g4(v4);

  using Key = char;

  constexpr char KeyCount{ 26 };
  class Keys
  {
  public:
    constexpr bool operator ==(Keys k) const noexcept { return keylist == k.keylist; }
    constexpr void SetKey(Key k) noexcept { keylist.set(k - 'a'); }
    constexpr bool HasKey(Key k) const noexcept { return keylist.test(k - 'a'); }
    constexpr size_t Count() const noexcept { return keylist.count(); }

  public:
    std::bitset<KeyCount> keylist;
  };

  class State;
  using StateVec = std::vector<State>;
  class State
  {
  public:
    State(Point p, Keys k, Number steps) : p_(p), k_(k), steps_(steps) {}
    State() = delete;

  public:
    static_assert(sizeof(size_t) >= 4);
    size_t Hash() const noexcept { return std::hash<decltype(k_.keylist)>()(k_.keylist); }
    constexpr bool operator ==(const State& s) const noexcept { return s.k_ == k_; }
    constexpr bool IsAlive() const noexcept { return !iterated_; }
    constexpr bool IsDeleted() const noexcept { return deleted_; }
    constexpr void Delete() const noexcept { deleted_ = true; }
    constexpr void TryPoint(const GlobalInfo& g, const Point& p, const Keys& k, StateVec& n) const noexcept
    {
      const char content = g.GetContent(p);
      switch (content)
      {
        case '\0': break; // can't go there
        case '#':  break; // wall
        case '.': n.push_back(State(p, k, g.curSteps_)); break;
        case '@': n.push_back(State(p, k, g.curSteps_)); break;
        default:  // found key or door
          if (islower(content))
          {
            Keys newk{ k };
            if (!newk.HasKey(content))
            {
              newk.SetKey(content);  // add key to our keylist
              if (newk.Count() > g.maxKeys_)
              {
                g.maxKeys_ = static_cast<char>(newk.Count());
                g.minSteps_ = g.curSteps_;
                //std::cout << newk.keylist.to_string() << ' ' << g.minSteps_ << std::endl;
              }
            }
            n.push_back(State(p, newk, g.curSteps_));
          }
          else
          {
            //if (k.HasKey((char) tolower((int) content)))  // Door - do we have this key?
            //{
              n.push_back(State(p, k, g.curSteps_));  // may enter through this door
            //}
          }
          break;
      }
    }

    constexpr StateVec Iterate(const GlobalInfo& g) const
    {
      StateVec newlist{};
      if (!iterated_)
      {
        TryPoint(g, { (Coord) (p_.first + 1), (Coord) (p_.second + 0) }, k_, newlist);
        TryPoint(g, { (Coord) (p_.first - 1), (Coord) (p_.second + 0) }, k_, newlist);
        TryPoint(g, { (Coord) (p_.first + 0), (Coord) (p_.second + 1) }, k_, newlist);
        TryPoint(g, { (Coord) (p_.first + 0), (Coord) (p_.second - 1) }, k_, newlist);
        iterated_ = true;
      }
      return newlist;
    }
    constexpr bool IsSubsetOf(const State& s) const noexcept // is *this a subset of s?
    {
      const auto res = ~s.k_.keylist & k_.keylist;
      //std::cout << k_.keylist << " is superseded by " << s.k_.keylist << " ? -> " << (!res.any()) << std::endl;
      return !(res.any());
    }

  public:
    const Point p_{};
    const Keys k_{};
    const Number steps_{};
    mutable bool iterated_{ false };
    mutable bool deleted_{ false };
  };

  class StateHash {
  public: size_t operator() (const State& s) const noexcept { return s.Hash(); }
  };
  class StateEqual {
  public: bool operator() (const State& s1, const State& s2) const noexcept { return s1 == s2; }
  };

  using StateSet = std::unordered_set<State, StateHash, StateEqual>;

  StateVec newstates{}; // this will collect the new states
  newstates.reserve(500);

  auto StepsNeeded = [&newstates](const GlobalInfo& g) -> Number
    {
      std::vector<std::vector<StateSet>> states{};
      states.resize(g.sizex_);
      for (auto i = 0; i < g.sizex_; ++i) states[i].resize(g.sizey_);

      const State s0(g.GetEntry(), Keys(), 0);
      states[s0.p_.first][s0.p_.second].insert(s0);

      while (true)
      {
        ++g.curSteps_;

        newstates.clear();
        for (auto x = 0; x < g.sizex_; ++x)
        {
          for (auto y = 0; y < g.sizey_; ++y)
          {
            for (const auto& s : states[x][y])
            {
              if (s.IsAlive())
              {
                newstates.append_range(s.Iterate(g));
              }
            }
          }
        }
        for (const auto& s : newstates)
        {
          StateSet& set{ states[s.p_.first][s.p_.second] };
          if (!set.contains(s))
          {
            for (const auto& ss : set)
            {
              if (ss.IsSubsetOf(s))
              {
                ss.Delete();
              }
            }
            // erase all deleted states
            std::erase_if(set, [](const State& s) -> bool { return s.IsDeleted(); });
            set.insert(s);
          }
        }

        if (newstates.size() == 0)
        {
          return g.minSteps_;
        }
      }
    };

  Number n1 = StepsNeeded(g1);
  Number n2 = StepsNeeded(g2);
  Number n3 = StepsNeeded(g3);
  Number n4 = StepsNeeded(g4);

  assert(g1.maxKeys_ + g2.maxKeys_ + g3.maxKeys_ + g4.maxKeys_ == KeyCount);

  return n1 + n2 + n3 + n4;
}
