
// BreadthFirstSearch was developed from usage patterns but is UNUSED and UNTESTED!

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
  
  template <class State> using StateMap = std::unordered_set<State, StateHash<State>, StateEqual<State>>;

  template <class State, class GlobalInfo>
  class BreadthFirstSearch
  {
  public:
    BreadthFirstSearch(const State& start)
    {
      states_.insert(start);
    }
    void DoForAll(auto& func) { for (auto s : states_) func(s); }
    StateMap<State>& GetMap() { return states_; }
    size_t NextLevel()
    {
      StateMap<State> oldstates{}; // this will collect the (potentially modified) existing states
      StateMap<State> newstates{}; // this will collect only the really new states
      for (auto s : states_)
      {
        std::vector<State> addedstates = s.Iterate();  // note that this allows 's' to be modified inside Iterate
        oldstates.insert(s); // s might have been modified; insert existing s before adding any new ones
        for (auto const& ss : addedstates)
        {
          if (!states_.contains(ss) && !newstates.contains(ss))  // avoid duplicates
            newstates.insert(ss);
        }
      }

      assert(oldstates.size() == states_.size());
      std::swap(oldstates, states_);

      for (auto const& s : newstates)  // now insert all the really new ones
      {
        assert(!states_.contains(s));  // should not have any duplicates
        states_.insert(s);
      }

      return states_.size();
    }

  private:
    StateMap<State> states_{};
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
