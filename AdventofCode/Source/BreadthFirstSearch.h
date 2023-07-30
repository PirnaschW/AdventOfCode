
// BreadthFirstSearch was developed from usage patterns but is UNUSED and UNTESTED!

namespace BreadthFirstSearch
{
  template <class State> class StateHash {
  public: size_t operator() (const State& s) const noexcept { return s.Hash(); }
  };
  template <class State> class StateEqual {
  public: bool operator() (const State& s1, const State& s2) const noexcept { return s1 == s2; }
  };

  template <class State, class GlobalInfo>
  class BreadthFirstSearch
  {
  public:
    BreadthFirstSearch(const State& start)
    {
      states_.insert(start);
    }

    void Insert(const State& s)
    {
      if (!newstates_.contains(s))  // avoid duplicates
        newstates_.insert(s);
    }
    size_t NextLevel()
    {
      newstates_.clear();
      for (const auto& s : states_)
      {
        std::vector<State> newstates = s.Iterate();
        for (auto const& ss : newstates) Insert(ss);
      }
      std::swap(newstates_, states_);
      return states_.size();
    }

  private:
    std::unordered_set<State, StateHash<State>, StateEqual<State>> states_{};
    std::unordered_set<State, StateHash<State>, StateEqual<State>> newstates_{};
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
