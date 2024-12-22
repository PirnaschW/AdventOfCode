//template<> auto InputData<2015, 13, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 13, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  // Alice would gain 2 happiness units by sitting next to Bob.

  using Pair = std::pair<std::string, std::string>;
  using Names = std::unordered_set<std::string>;
  using Happiness = std::unordered_map < Pair, Number,
    decltype([](const Pair& p) { return std::hash<decltype(p.first)>()(p.first) << 8 | std::hash<decltype(p.second)>()(p.second); }),
    decltype([](const Pair& p1, const Pair& p2) { return p1.first == p2.first && p1.second == p2.second; }) > ;

  Names names{};
  Happiness happiness{};

  constexpr unsigned int BufSize{ 33 };
  for (const auto& line : v)
  {
    char name1[BufSize];
    char verb[BufSize];
    char name2[BufSize];
    Number h;
    int z = sscanf_s(line.c_str(), "%s would %s %lld happiness units by sitting next to %[^.].", name1, BufSize, verb, BufSize, &h, name2, BufSize);
    assert(z == 4);
    if (!names.contains(name1)) names.insert(name1);
    if (!names.contains(name2)) names.insert(name2);
    happiness.insert({ {name1,name2}, verb[0] == 'l' ? -h : h});
  }

  using SeatingOrder = std::vector<std::string>;
  SeatingOrder order{};

  Number maxHappiness{std::numeric_limits<decltype(maxHappiness)>::min()};
  auto TryNext = [&names, &happiness, &maxHappiness](const SeatingOrder& order, const Number& h, auto& TryNext) -> void
    {
      if (order.size() == names.size())
      {
        Number h1{ h };
        h1 += happiness[Pair{ order.back(),order.front() }];
        h1 += happiness[Pair{ order.front(),order.back() }];
        if (h1 > maxHappiness) maxHappiness = h1;
        return;
      }
      for (const auto& name : names)
      {
        if (std::find(order.begin(), order.end(), name) != order.end()) continue;
        SeatingOrder order1{ order };
        order1.push_back(name);
        Number h1{ h };
        if (order.size() > 0)
        {
          h1 += happiness[Pair{ order.back(),name }];
          h1 += happiness[Pair{ name,order.back() }];
        }
        TryNext(order1, h1, TryNext);
      }
    };

  order.push_back(*names.begin());
  TryNext(order, 0, TryNext);

  return maxHappiness;
}

//template<> auto InputData<2015, 13, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 13, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  // Alice would gain 2 happiness units by sitting next to Bob.

  using Pair = std::pair<std::string, std::string>;
  using Names = std::unordered_set<std::string>;
  using Happiness = std::unordered_map < Pair, Number,
    decltype([](const Pair& p) { return std::hash<decltype(p.first)>()(p.first) << 8 | std::hash<decltype(p.second)>()(p.second); }),
    decltype([](const Pair& p1, const Pair& p2) { return p1.first == p2.first && p1.second == p2.second; }) > ;

  Names names{};
  Happiness happiness{};

  constexpr unsigned int BufSize{ 33 };
  for (const auto& line : v)
  {
    char name1[BufSize];
    char verb[BufSize];
    char name2[BufSize];
    Number h;
    int z = sscanf_s(line.c_str(), "%s would %s %lld happiness units by sitting next to %[^.].", name1, BufSize, verb, BufSize, &h, name2, BufSize);
    assert(z == 4);
    if (!names.contains(name1)) names.insert(name1);
    if (!names.contains(name2)) names.insert(name2);
    happiness.insert({ {name1,name2}, verb[0] == 'l' ? -h : h});
  }

  const std::string me{ "Myself" };
  for (const auto& name : names)
  {
    happiness.insert({ {me,name},0 });
    happiness.insert({ {name,me},0 });
  }
  names.insert(me);

  using SeatingOrder = std::vector<std::string>;
  SeatingOrder order{};

  Number maxHappiness{std::numeric_limits<decltype(maxHappiness)>::min()};
  auto TryNext = [&names, &happiness, &maxHappiness](const SeatingOrder& order, const Number& h, auto& TryNext) -> void
    {
      if (order.size() == names.size())
      {
        Number h1{ h };
        h1 += happiness[Pair{ order.back(),order.front() }];
        h1 += happiness[Pair{ order.front(),order.back() }];
        if (h1 > maxHappiness) maxHappiness = h1;
        return;
      }
      for (const auto& name : names)
      {
        if (std::find(order.begin(), order.end(), name) != order.end()) continue;
        SeatingOrder order1{ order };
        order1.push_back(name);
        Number h1{ h };
        if (order.size() > 0)
        {
          h1 += happiness[Pair{ order.back(),name }];
          h1 += happiness[Pair{ name,order.back() }];
        }
        TryNext(order1, h1, TryNext);
      }
    };

  order.push_back(me);
  TryNext(order, 0, TryNext);
  
  return maxHappiness;
}
