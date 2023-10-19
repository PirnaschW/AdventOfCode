//template<> auto InputData<2016, 17, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 17, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  using Coord = char;

  class GlobalInfo
  {
  public:
    mutable MD5::MD5 md5{};
    mutable std::string solution{};
  };

  class State
  {
  public:
    State() = delete;
    State(const std::string& s, Coord x, Coord y) : s_(s), x_(x), y_(y) {}
    size_t Hash() const noexcept { return std::hash<std::string>()(s_); }
    bool operator ==(const State& s) const noexcept { return s_ == s.s_; }
    bool IsAlive() const noexcept { return alive_; }
    std::vector<State> Iterate(const GlobalInfo& g) const
    {
      std::vector<State> v;
      if (x_ == 3 && y_ == 3)
      {
        g.solution = s_;
        return v;
      }
      alive_ = false;
      auto Try = [&v](const std::string& s, const Coord x, const Coord y) -> void
        {
          if (x < 0 || x >3 || y < 0 || y>3) return;
          v.emplace_back(s, x, y);
        };
      std::string hash = g.md5.digestString(s_.c_str());
      if (hash[0] > 'a') Try(s_ + 'U', x_, y_ - 1);
      if (hash[1] > 'a') Try(s_ + 'D', x_, y_ + 1);
      if (hash[2] > 'a') Try(s_ + 'L', x_ - 1, y_);
      if (hash[3] > 'a') Try(s_ + 'R', x_ + 1, y_);
      return v;
    }
  private:
    const std::string s_{};
    const Coord x_{};
    const Coord y_{};
    mutable bool alive_{ true };
  };

  State s0{ v[0],0,0 };
  GlobalInfo g{};
  BFS::BreadthFirstSearch<State, GlobalInfo> bfs(s0, g);

  while (g.solution.size() == 0)
  {
    bfs.NextLevel();
  }

  throw g.solution.substr(v[0].size());
}

//template<> auto InputData<2016, 17, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 17, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  using Coord = char;

  class GlobalInfo
  {
  public:
    mutable MD5::MD5 md5{};
    mutable size_t solutionsize{0};
  };

  class State
  {
  public:
    State() = delete;
    State(const std::string& s, Coord x, Coord y) : s_(s), x_(x), y_(y) {}
    size_t Hash() const noexcept { return std::hash<std::string>()(s_); }
    bool operator ==(const State& s) const noexcept { return s_ == s.s_; }
    bool IsAlive() const noexcept { return alive_; }
    std::vector<State> Iterate(const GlobalInfo& g) const
    {
      alive_ = false;
      std::vector<State> v;
      if (x_ == 3 && y_ == 3)
      {
        if (s_.size() > g.solutionsize)
        {
          g.solutionsize = static_cast<Number>(s_.size());
        }
        return v;
      }
      auto Try = [&v](const std::string& s, const Coord x, const Coord y) -> void
        {
          if (x < 0 || x >3 || y < 0 || y>3) return;
          v.emplace_back(s, x, y);
        };
      std::string hash = g.md5.digestString(s_.c_str());
      if (hash[0] > 'a') Try(s_+'U',x_,y_-1);
      if (hash[1] > 'a') Try(s_+'D',x_,y_+1);
      if (hash[2] > 'a') Try(s_+'L',x_-1,y_);
      if (hash[3] > 'a') Try(s_+'R',x_+1,y_);
      return v;
    }
  private:
    const std::string s_{};
    const Coord x_{};
    const Coord y_{};
    mutable bool alive_{ true };
  };

  State s0{v[0],0,0};
  GlobalInfo g{};
  BFS::BreadthFirstSearch<State, GlobalInfo> bfs(s0,g);

  while (bfs.NextLevel() > 0);

  return g.solutionsize - v[0].size();
}
