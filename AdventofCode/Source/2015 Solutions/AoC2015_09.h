//template<> auto InputData<2015, 9, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 9, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  using Pair = std::pair<std::string, std::string>;
  using DistMap = std::unordered_map < Pair, Number,
    decltype([](const Pair& p)->size_t {return std::hash<std::string>()(p.first) ^ std::hash<std::string>()(p.second); }),
    decltype([](const Pair& p1, const Pair& p2)->bool {return p1.first == p2.first && p1.second == p2.second; }) > ;
  using DestList = std::set<std::string>;
  using DestSeq = std::vector<std::string>;

  constexpr int BufSize{ 33 };
  DistMap distmap{};
  DestList destlist{};
  for (const auto& line : v)
  {
    char s1[BufSize]{};
    char s2[BufSize]{};
    Number d{ 0 };
    // "Faerun to Tristram = 65"
    int z = sscanf_s(line.c_str(), "%s to %s = %lld", s1, BufSize, s2, BufSize, &d);
    assert(z == 3);

    distmap.insert({ Pair(s1,s2),d });
    distmap.insert({ Pair(s2,s1),d });

    if (!destlist.contains(s1)) destlist.insert(s1);
    if (!destlist.contains(s2)) destlist.insert(s2);
  }

  Number min{ std::numeric_limits<Number>::max() };
  class H
  {
  public:
    static bool Contains(const DestSeq& seq, const std::string& s)
    {
      for (auto i = 0; i < seq.size(); ++i)
      {
        if (seq[i] == s)
          return true;
      }
      return false;
    };
    static void AddMore(const DestList& destlist, const DistMap& distmap, Number& min, DestSeq& sequence, Number dist)
    {
      for (const auto& next : destlist)
      {
        if (Contains(sequence, next)) continue;
        Number newdist = dist + distmap.at(Pair(sequence[sequence.size() - 1], next));
        DestSeq newsequence{ sequence };
        newsequence.push_back(next);
        if (newsequence.size() < destlist.size())
        {
          H::AddMore(destlist, distmap, min, newsequence, newdist);
        }
        else
        {
          //for (const auto& d : newsequence)
          //{
          //  std::cout << d << ' ';
          //}
          //std::cout << std::endl;
          if (newdist < min) min = newdist;
        }
      }
    }
  };


  for (const auto& start : destlist)
  {
    DestSeq sequence{};
    Number dist{ 0 };
    sequence.push_back(start);
    H::AddMore(destlist, distmap, min, sequence, dist);
  }

  return min;
}

//template<> auto InputData<2015, 9, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 9, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  using Pair = std::pair<std::string, std::string>;
  using DistMap = std::unordered_map < Pair, Number,
    decltype([](const Pair& p)->size_t {return std::hash<std::string>()(p.first) ^ std::hash<std::string>()(p.second); }),
    decltype([](const Pair& p1, const Pair& p2)->bool {return p1.first == p2.first && p1.second == p2.second; }) > ;
  using DestList = std::set<std::string>;
  using DestSeq = std::vector<std::string>;

  constexpr int BufSize{ 33 };
  DistMap distmap{};
  DestList destlist{};
  for (const auto& line : v)
  {
    char s1[BufSize]{};
    char s2[BufSize]{};
    Number d{ 0 };
    // "Faerun to Tristram = 65"
    int z = sscanf_s(line.c_str(), "%s to %s = %lld", s1, BufSize, s2, BufSize, &d);
    assert(z == 3);

    distmap.insert({ Pair(s1,s2),d });
    distmap.insert({ Pair(s2,s1),d });

    if (!destlist.contains(s1)) destlist.insert(s1);
    if (!destlist.contains(s2)) destlist.insert(s2);
  }

  Number max{ 0 };
  class H
  {
  public:
    static bool Contains(const DestSeq& seq, const std::string& s)
    {
      for (auto i = 0; i < seq.size(); ++i)
      {
        if (seq[i] == s)
          return true;
      }
      return false;
    };
    static void AddMore(const DestList& destlist, const DistMap& distmap, Number& max, DestSeq& sequence, Number dist)
    {
      for (const auto& next : destlist)
      {
        if (Contains(sequence, next)) continue;
        Number newdist = dist + distmap.at(Pair(sequence[sequence.size() - 1], next));
        DestSeq newsequence{ sequence };
        newsequence.push_back(next);
        if (newsequence.size() < destlist.size())
        {
          H::AddMore(destlist, distmap, max, newsequence, newdist);
        }
        else
        {
          //for (const auto& d : newsequence)
          //{
          //  std::cout << d << ' ';
          //}
          //std::cout << std::endl;
          if (newdist > max) max = newdist;
        }
      }
    }
  };


  for (const auto& start : destlist)
  {
    DestSeq sequence{};
    Number dist{ 0 };
    sequence.push_back(start);
    H::AddMore(destlist, distmap, max, sequence, dist);
  }

  return max;
}
