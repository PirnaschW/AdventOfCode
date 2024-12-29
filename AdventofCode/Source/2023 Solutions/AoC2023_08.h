//template<> auto InputData<2023, 8, A>() { return "RL\n\n"
//"AAA = (BBB, CCC)\n"
//"BBB = (DDD, EEE)\n"
//"CCC = (ZZZ, GGG)\n"
//"DDD = (DDD, DDD)\n"
//"EEE = (EEE, EEE)\n"
//"GGG = (GGG, GGG)\n"
//"ZZZ = (ZZZ, ZZZ)\n";}; // Result: 2
//template<> auto InputData<2023, 8, A>() { return "LLR\n\n"
//"AAA = (BBB, BBB)\n"
//"BBB = (AAA, ZZZ)\n"
//"ZZZ = (ZZZ, ZZZ)\n";}; // Result: 6
template<> Number AoC<2023, 8, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  std::string direction{ v[0] };
  size_t pos{ direction.size() };
  auto GetNextDirection = [&direction, &pos]()->char { if (++pos >= direction.size()) pos = 0; return direction[pos]; };

  std::unordered_map<std::string, int> name{};
  auto MapName = [&name](const std::string& n)->int
    {
      if (const auto& it = name.find(n); it != name.cend())
      {
        return it->second;
      }
      else
      {
        int next = static_cast<int>(std::ssize(name));
        name.insert({ n, next });
        return next;
      }
    };

  class Node
  {
  public:
    int id{ -1 };
    int left{ -1 };
    int right{ -1 };
  };
  std::vector<Node> node(v.size()-2);
  for (size_t i = 2; i < v.size(); ++i)
  {
    constexpr unsigned int NameLen{ 4 };
    char n[NameLen]{};
    char l[NameLen]{};
    char r[NameLen]{};
    int z = sscanf_s(v[i].c_str(), "%3c = (%3c, %3c)", n, NameLen, l, NameLen, r, NameLen);
    assert(z == 3);


    Node nn{ MapName(n),MapName(l),MapName(r) };
    assert(node[nn.id].id == -1);
    node[nn.id] = nn;
  }

  int current = MapName("AAA");
  int target = MapName("ZZZ");
  Number steps{ 0 };
  while (current != target)
  {
    current = (GetNextDirection() == 'L' ? node[current].left : node[current].right);
    ++steps;
  }

  return steps;
}


//template<> auto InputData<2023, 8, B>() { return "LR\n\n"
//"11A = (11B, XXX)\n"
//"11B = (XXX, 11Z)\n"
//"11Z = (11B, XXX)\n"
//"22A = (22B, XXX)\n"
//"22B = (22C, 22C)\n"
//"22C = (22Z, 22Z)\n"
//"22Z = (22B, 22B)\n"
//"XXX = (XXX, XXX)\n";}; // Result: 6
template<> Number AoC<2023, 8, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  std::string direction{ v[0] };
  size_t pos{ direction.size() };
  auto GetNextDirection = [&direction, &pos]()->char { if (++pos >= direction.size()) pos = 0; return direction[pos]; };
  auto ResetDirection = [&direction, &pos]()->void { pos = direction.size(); };

  std::unordered_map<std::string, int> name{};
  auto MapName = [&name](const std::string& n)->int
    {
      if (const auto& it = name.find(n); it != name.cend())
      {
        return it->second;
      }
      else
      {
        int next = static_cast<int>(std::ssize(name));
        name.insert({ n, next });
        return next;
      }
    };

  class Node
  {
  public:
    int id{ -1 };
    int left{ -1 };
    int right{ -1 };
  };
  std::vector<Node> node(v.size() - 2);
  for (size_t i = 2; i < v.size(); ++i)
  {
    constexpr unsigned int NameLen{ 4 };
    char n[NameLen]{};
    char l[NameLen]{};
    char r[NameLen]{};
    int z = sscanf_s(v[i].c_str(), "%3c = (%3c, %3c)", n, NameLen, l, NameLen, r, NameLen);
    assert(z == 3);


    Node nn{ MapName(n),MapName(l),MapName(r) };
    assert(node[nn.id].id == -1);
    node[nn.id] = nn;
  }

  std::vector<int> start{};
  std::unordered_set<int> target{};
  for (const auto& n : name)
  {
    switch (n.first[2])
    {
      case 'A': start.push_back(n.second); break;
      case 'Z': target.insert(n.second);     break;
      default: break;
    }
  }

  auto GetCycle = [&target, &node, &GetNextDirection](int n)->std::vector<Number>
    {
      std::vector<Number> cycle{};
      Number steps{ 0 };
      while (cycle.size() < 3)
      {
        bool left = GetNextDirection() == 'L';
        n = (left ? node[n].left : node[n].right);
        ++steps;

        if (target.contains(n))
        {
          cycle.push_back(steps);
        }
      }
      return cycle;
    };

  // get cycle length for each entry in start and multiply together
  Number result{ 1 };
  for (int n : start)
  {
    ResetDirection();
    std::vector<Number> cycle = GetCycle(n);
    assert(2 * cycle[0] == cycle[1]);
    assert(3 * cycle[0] == cycle[2]);
    result = std::lcm(result,cycle[0]);
  }

  return result;
}
