//template<> auto InputData<2022, 21, A>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };
//template<> auto InputData<2022, 21, B>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };
template<> Number AoC<2022, 21, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Node
  {
    std::string name{};
    bool isNumber{ false };
    bool isCalculated{ false };
    Number z;
    char op{0};
    std::string op1{};
    std::string op2{};
  };

  std::unordered_map<std::string, Node> map{};

  struct H
  {
    static Number GetValue(std::unordered_map<std::string, Node>& map, std::string name)
    {
      Node& node = map.find(name)->second;
      if (node.isNumber || node.isCalculated) return node.z;
      switch (node.op)
      {
        case '*': return GetValue(map, node.op1) * GetValue(map, node.op2);
        case '/': return GetValue(map, node.op1) / GetValue(map, node.op2);
        case '+': return GetValue(map, node.op1) + GetValue(map, node.op2);
        case '-': return GetValue(map, node.op1) - GetValue(map, node.op2);
        default:
          return 0;
      }
    }
  };

  for (auto const& line : v)
  {
    Node node;
    char name[5];
    int z1 = sscanf_s(line.c_str(), "%4c: %lld", name, 4, &node.z);
    name[4] = '\0';
    node.name = name;
    if (z1 == 2)
    {
      node.isNumber = true;
    }
    else {
      char op1[5];
      char op2[5];
      int z2 = sscanf_s(line.c_str(), "%4c: %4c %1c %4c", name, 4, op1, 4, &node.op, 1, op2, 4);
      assert(z2 == 4);
      op1[4] = '\0';
      node.op1 = op1;
      op2[4] = '\0';
      node.op2 = op2;
    }
    map.insert(std::pair<std::string, Node>(node.name, node));
  }

  Number z = H::GetValue(map,"root");
  return z;
}

template<> Number AoC<2022, 21, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Node
  {
    std::string name{};
    bool isNumber{ false };
    bool isCalculated{ false };
    bool useshuman{ false };
    Number z;
    char op{ 0 };
    std::string op1{};
    std::string op2{};
  };

  std::unordered_map<std::string, Node> map{};

  struct H
  {
    static Number GetValue(std::unordered_map<std::string, Node>& map, const std::string& name)
    {
      Node& node = map.find(name)->second;
      if (name == "humn")
      {
        node.useshuman = true;
        throw 1;
      }

      try
      {
        if (node.isNumber || node.isCalculated) return node.z;
        switch (node.op)
        {
          case '*': return GetValue(map, node.op1) * GetValue(map, node.op2);
          case '/': return GetValue(map, node.op1) / GetValue(map, node.op2);
          case '+': return GetValue(map, node.op1) + GetValue(map, node.op2);
          case '-': return GetValue(map, node.op1) - GetValue(map, node.op2);
          default:
            return 0;
        }
      }
      catch (int)
      {
        node.useshuman = true;
        throw;
      }
    }
    static Number GetNeeded(std::unordered_map<std::string, Node>& map, const Number& value, std::string& name)
    {
      if (name == "humn")
      {
        return value;
      }

      Node& node = map.find(name)->second;

      Node& node1 = map.find(node.op1)->second;
      Node& node2 = map.find(node.op2)->second;
      switch (node.op)
      {
        case '*':
          if (node1.useshuman) return GetNeeded(map, value / GetValue(map, node.op2), node.op1);
          if (node2.useshuman) return GetNeeded(map, value / GetValue(map, node.op1), node.op2);
          assert(false);
        case '/':
          if (node1.useshuman) return GetNeeded(map, value * GetValue(map, node.op2), node.op1);
          if (node2.useshuman) return GetNeeded(map, GetValue(map, node.op1) / value, node.op2);
          assert(false);
        case '+':
          if (node1.useshuman) return GetNeeded(map, value - GetValue(map, node.op2), node.op1);
          if (node2.useshuman) return GetNeeded(map, value - GetValue(map, node.op1), node.op2);
          assert(false);
        case '-':
          if (node1.useshuman) return GetNeeded(map, value + GetValue(map, node.op2), node.op1);
          if (node2.useshuman) return GetNeeded(map, GetValue(map, node.op1) - value, node.op2);
          assert(false);
        default:
          assert(false);
          return 0;
      }
    }
  };

  for (auto const& line : v)
  {
    Node node;
    char name[5];
    int z1 = sscanf_s(line.c_str(), "%4c: %lld", name, 4, &node.z);
    name[4] = '\0';
    node.name = name;
    if (z1 == 2)
    {
      node.isNumber = true;
    }
    else {
      char op1[5];
      char op2[5];
      int z2 = sscanf_s(line.c_str(), "%4c: %4c %1c %4c", name, 4, op1, 4, &node.op, 1, op2, 4);
      assert(z2 == 4);
      op1[4] = '\0';
      node.op1 = op1;
      op2[4] = '\0';
      node.op2 = op2;
    }
    map.insert(std::pair<std::string, Node>(node.name, node));
  }

  Node root = map.find("root")->second;

  bool gotleft{ true };
  bool gotright{ true };
  Number left{};
  Number right{};
  try
  {
    left = H::GetValue(map, root.op1);
  }
  catch (int)
  {
    gotleft = false;
  }

  try
  {
    right = H::GetValue(map, root.op2);
  }
  catch (int)
  {
    gotright = false;
  }
  assert(gotright ^ gotleft);

  Number z = H::GetNeeded(map, gotright ? right : left, gotright ? root.op1 : root.op2);
  return z;
}



template <class State> class StateHash { public: size_t operator() (const State& s) const noexcept { return s.Hash(); } };
template <class State> class StateEqual { public: bool operator() (const State& s1, const State& s2) const noexcept { return s1 == s2; } };
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
