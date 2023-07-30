template<> Number AoC<2022, 16, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Valve
  {
    std::string name{};
    Number flow{};
    std::vector<std::string> tunnelname{};
    std::vector<int> tunnels{};
  };

  std::vector<Valve> valves{};

  for (const auto& line : v)
  {
    Valve valve;
    char n[4];
    char w1[9];
    char w2[9];
    char w3[9];
    char n1[4], n2[4], n3[4], n4[4], n5[4], n6[4];
    int z = sscanf_s(line.c_str(), "Valve %s has flow rate=%lld; %s %s to %s %[^,], %[^,], %[^,], %[^,], %[^,], %[^,]", n, 3, &valve.flow, w1, 8, w2, 8, w3, 8, n1, 3, n2, 3, n3, 3, n4, 3, n5, 3, n6, 3);
    switch (z)
    {
      default:
        break;
      case 10:valve.tunnelname.push_back(n5);
      case 9: valve.tunnelname.push_back(n4);
      case 8: valve.tunnelname.push_back(n3);
      case 7: valve.tunnelname.push_back(n2);
      case 6: valve.tunnelname.push_back(n1);
        break;
    }
    valve.name = n;
    valves.push_back(valve);
  }

  std::map<std::string, int> valvemap{};
  for (int i=0; i<valves.size(); ++i)
  {
    valvemap.insert(std::pair<std::string,int>(valves[i].name,i));
  }

  for (int i = 0; i < valves.size(); ++i)
  {
    for (auto j = 0; j < valves[i].tunnelname.size(); ++j)
    {
      int index = valvemap[valves[i].tunnelname[j]];
      valves[i].tunnels.push_back(index);
    }
  }


  struct State
  {
    Number Open{};
    Number Released{};
    Number current{-1};
    std::vector<bool>opened{};
  };
  State root{ 0,0,-1,std::vector<bool>(valves.size(), false) };
  root.current = valvemap["AA"];



  struct shash
  {
    size_t operator() (const State& s) const noexcept
    {
      return std::hash<Number>()(s.current) + std::hash<std::vector<bool>>()(s.opened) * 113 * 37;
    }
  };
  struct sequal
  {
    bool operator() (const State& s1, const State& s2) const noexcept
    {
      return s1.current == s2.current && s1.opened == s2.opened;
    }
  };

  std::unordered_set<State,shash, sequal> states{};
  states.insert(root);

  int z = 30;
  while (z-- > 0)
  {
    std::unordered_set<State, shash, sequal> newstates{};
    for (auto& s : states)
    {
      if (!s.opened[s.current] && valves[s.current].flow > 0)  // option: open this one
      {
        State ss = s;
        ss.opened[ss.current] = true;
        ss.Released += ss.Open;
        ss.Open += valves[ss.current].flow;
        auto it = newstates.find(ss);
        if (it == newstates.end()) newstates.insert(ss);
        else
        {
          if (it->Released + z * it->Open < ss.Released + z * ss.Open)
          {
            newstates.erase(it);
            newstates.insert(ss);
          }
        }
      }
      for (int t : valves[s.current].tunnels)  // options walk in each tunnel
      {
        State ss = s;
        ss.current = t;
        ss.Released += ss.Open;
        auto it = newstates.find(ss);
        if (it == newstates.end()) newstates.insert(ss);
        else
        {
          if (it->Released + z * it->Open < ss.Released + z * ss.Open)
          {
            newstates.erase(it);
            newstates.insert(ss);
          }
        }
      }
    }

    std::swap(states,newstates);
//    std::cout << z << ' ' << states.size() << '\n';
  }

  Number zmax = 0;
  for (auto& s : states)
  {
    if (s.Released > zmax) zmax = s.Released;
  }
  return zmax;
}


template<> Number AoC<2022, 16, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Valve
  {
    std::string name{};
    Number flow{};
    std::vector<std::string> tunnelname{};
    std::vector<int> tunnels{};
  };

  std::vector<Valve> valves{};

  for (const auto& line : v)
  {
    Valve valve;
    char n[4];
    char w1[9];
    char w2[9];
    char w3[9];
    char n1[4], n2[4], n3[4], n4[4], n5[4], n6[4];
    int z = sscanf_s(line.c_str(), "Valve %s has flow rate=%lld; %s %s to %s %[^,], %[^,], %[^,], %[^,], %[^,], %[^,]", n, 3, &valve.flow, w1, 8, w2, 8, w3, 8, n1, 3, n2, 3, n3, 3, n4, 3, n5, 3, n6, 3);
    switch (z)
    {
      default:
        break;
      case 10:valve.tunnelname.push_back(n5);
      case 9: valve.tunnelname.push_back(n4);
      case 8: valve.tunnelname.push_back(n3);
      case 7: valve.tunnelname.push_back(n2);
      case 6: valve.tunnelname.push_back(n1);
        break;
    }
    valve.name = n;
    valves.push_back(valve);
  }

  std::map<std::string, int> valvemap{};
  for (int i = 0; i < valves.size(); ++i)
  {
    valvemap.insert(std::pair<std::string, int>(valves[i].name, i));
  }

  for (int i = 0; i < valves.size(); ++i)
  {
    for (auto j = 0; j < valves[i].tunnelname.size(); ++j)
    {
      int index = valvemap[valves[i].tunnelname[j]];
      valves[i].tunnels.push_back(index);
    }
  }


  struct State
  {
    Number Open{};
    Number Released{};
    Number current{ -1 };
    std::vector<bool>opened{};
  };
  State root{ 0,0,-1,std::vector<bool>(valves.size(), false) };
  root.current = valvemap["AA"];

  struct shash
  {
    size_t operator() (const State& s) const noexcept
    {
      return std::hash<Number>()(s.current) + std::hash<std::vector<bool>>()(s.opened) * 113 * 37;
    }
  };
  struct sequal
  {
    bool operator() (const State& s1, const State& s2) const noexcept
    {
      return s1.current == s2.current && s1.opened == s2.opened;
    }
  };

  struct H
  {
    static void Update(std::unordered_set<State, shash, sequal>& states, State& ss, int z)
    {
      auto it = states.find(ss);
      if (it == states.end()) states.insert(ss);
      else
      {
        if (it->Released + z * it->Open < ss.Released + z * ss.Open)
        {
          states.erase(it);
          states.insert(ss);
        }
      }
    }
  };

  std::unordered_set<State, shash, sequal> states{};
  states.insert(root);

  int z = 26;
  while (z-- > 0)
  {
    std::unordered_set<State, shash, sequal> newstates{};
    for (auto& s : states)
    {
      if (!s.opened[s.current] && valves[s.current].flow > 0)  // option: open this one
      {
        State ss = s;
        ss.opened[ss.current] = true;
        ss.Released += ss.Open;
        ss.Open += valves[ss.current].flow;
        auto it = newstates.find(ss);
        if (it == newstates.end()) newstates.insert(ss);
        else
        {
          if (it->Released + z * it->Open < ss.Released + z * ss.Open)
          {
            newstates.erase(it);
            newstates.insert(ss);
          }
        }
      }
      for (int t : valves[s.current].tunnels)  // options walk in each tunnel
      {
        State ss = s;
        ss.current = t;
        ss.Released += ss.Open;
        auto it = newstates.find(ss);
        if (it == newstates.end()) newstates.insert(ss);
        else
        {
          if (it->Released + z * it->Open < ss.Released + z * ss.Open)
          {
            newstates.erase(it);
            newstates.insert(ss);
          }
        }
      }
    }

    std::swap(states, newstates);
//    std::cout << z << ' ' << states.size() << '\n';
  }


  std::unordered_set<State, shash, sequal> newstates{};
  for (auto& s : states)
  {
    State ss = s;
    ss.current = root.current;
    ss.Open = 0;
    H::Update(newstates, ss, 0);
  }
  std::swap(states, newstates);

  z = 26;  // now the elephant
  while (z-- > 0)
  {
    std::unordered_set<State, shash, sequal> newstatesE{};
    for (auto& s : states)
    {
      if (!s.opened[s.current] && valves[s.current].flow > 0)  // option: open this one
      {
        State ss = s;
        ss.opened[ss.current] = true;
        ss.Released += ss.Open;
        ss.Open += valves[ss.current].flow;
        auto it = newstatesE.find(ss);
        if (it == newstatesE.end()) newstatesE.insert(ss);
        else
        {
          if (it->Released + z * it->Open < ss.Released + z * ss.Open)
          {
            newstatesE.erase(it);
            newstatesE.insert(ss);
          }
        }
      }
      for (int t : valves[s.current].tunnels)  // options walk in each tunnel
      {
        State ss = s;
        ss.current = t;
        ss.Released += ss.Open;
        auto it = newstatesE.find(ss);
        if (it == newstatesE.end()) newstatesE.insert(ss);
        else
        {
          if (it->Released + z * it->Open < ss.Released + z * ss.Open)
          {
            newstatesE.erase(it);
            newstatesE.insert(ss);
          }
        }
      }
    }

    std::swap(states, newstatesE);
//    std::cout << z << ' ' << states.size() << '\n';
  }

  Number zmax = 0;
  for (auto& s : states)
  {
    if (s.Released > zmax) zmax = s.Released;
  }
  return zmax;
}
