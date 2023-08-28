
namespace BFS
{
  template <class State>
  class StateHash {
  public: size_t operator() (const State& s) const noexcept { return s.Hash(); }
  };
  template <class State>
  class StateEqual {
  public: bool operator() (const State& s1, const State& s2) const noexcept { return s1 == s2; }
  };
  
  template <class State> using StateSet = std::unordered_set<State, StateHash<State>, StateEqual<State>>;
  template <class State> using StateVec = std::vector<State>;

  template <class State, class GlobalInfo>
  class BreadthFirstSearch
  {
  public:
    BreadthFirstSearch(const State& start, const GlobalInfo& g, size_t reserve = 2048) : g_(g)
    {
      states_.reserve(reserve);
      states_.insert(start);
    }
    void DoForAll(auto& func) { for (auto s : states_) func(s); }
    StateSet<State>& GetSet() { return states_; }
    size_t NextLevel()
    {
      StateVec<State> newstates{}; // this will collect the new states
      for (const auto& s : states_)
      {
        if (s.IsAlive())
        {
          const StateVec<State> addedstates = s.Iterate(g_);
          newstates.append_range(addedstates);
        }
      }

      // now insert all the new ones
      for (auto const& s : newstates)
      {
        if (!states_.contains(s)) states_.insert(s);
      }
      return newstates.size();
    }

  private:
    StateSet<State> states_{};
    const GlobalInfo& g_;
  };


  // usage example:
#ifdef NEVER
  class myState
  {
  public:
    size_t Hash() const noexcept { return 0; }
    bool operator ==(const myState& /*s*/) const noexcept { return true; }

    std::vector<myState> Iterate() const
    {
      std::vector<myState> v;

      //...
      myState s;
      //...
      v.push_back(s);
      return v;
    }
  };

  class myGlobalInfo {};
  myState s0;
  BreadthFirstSearch<myState, myGlobalInfo> bfs(s0);

  auto z = bfs.NextLevel();
#endif

};
