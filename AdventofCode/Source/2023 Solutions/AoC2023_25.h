//template<> auto InputData<2023, 25, A>() { return
//"jqt: rhn xhk nvd\n"
//"rsh: frs pzl lsr\n"
//"xhk: hfx\n"
//"cmg: qnr nvd lhk bvb\n"
//"rhn: xhk bvb hfx\n"
//"bvb: xhk hfx\n"
//"pzl: lsr hfx nvd\n"
//"qnr: nvd\n"
//"ntq: jqt hfx bvb xhk\n"
//"nvd: lhk\n"
//"lsr: lhk\n"
//"rzs: qnr cmg lsr rsh\n"
//"frs: qnr lhk lsr\n";}; // Result: 54
template<> Number AoC<2023, 25, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Edge = std::pair<int, int>;
  using HistogramMap = std::unordered_map<Edge,int,
    decltype([](const Edge& e) -> size_t { return std::hash<size_t>()((e.first << 16) + e.second); }),
    decltype([](const Edge& e1, const Edge& e2) -> bool { return e1.first == e2.first && e1.second == e2.second; }) >;
  HistogramMap hMap{};
  int hIndex{ 0 };
  using NameMap = std::unordered_map<std::string, int>;
  NameMap nMap{};
  auto GetNameIndex = [&map = nMap](const std::string& s) -> int
    {
      auto [it, found] = map.insert({ s, static_cast<int>(std::ssize(map))});
      return it->second;
    };

  using ConnectionMap = std::unordered_multimap<int, int>;
  ConnectionMap cMap{};

  constexpr unsigned int bufferLength{ 32 };
  for (const auto& line : v)
  {
    char node1[bufferLength]{};
    int p{};
    int z = sscanf_s(line.c_str(), "%[^:]: %n", node1, bufferLength, &p);
    assert(z == 1);
    int n1 = GetNameIndex(node1);
    
    int n{};
    char node2[bufferLength]{};
    while (sscanf_s(line.c_str() + p, " %[^ ] %n", node2, bufferLength, &n) == 1)
    {
      p += n;
      int n2 = GetNameIndex(node2);
      cMap.insert({ n1, n2 });
      cMap.insert({ n2, n1 });
      hMap.insert({ { n1, n2 },hIndex });
      hMap.insert({ { n2, n1 },hIndex });
      ++hIndex;
    }
  }
  using Histogram = std::vector<int>;
  Histogram histogram(hIndex, 0);

  //std::unordered_map < Point, Index,
  //  decltype([](const Point& p) -> size_t { return std::hash<size_t>()((p.x << 16) + p.y); }),
  //  decltype([](const Point& p1, const Point& p2) -> bool { return p1 == p2; }) > junction{};
  //std::unordered_map < Index, Point,
  //  decltype([](const Index& i) -> size_t { return std::hash<size_t>()(i); }),
  //  decltype([](const Index& i1, const Index& i2) -> bool { return i1 == i2; }) > reversejunction{};

  using ConnectionList = std::vector<std::pair<int,int>>;
  class myGlobalInfo
  {
  public:
    const ConnectionMap cMap_{ cMap };
    int target_{};
    mutable ConnectionList hist_{};
    mutable bool done_{ false };
  };
  class myState
  {
  public:
    myState() = delete;
    myState(int node, const ConnectionList& hist) : node_{ node }, hist_{ hist } {}
    size_t Hash() const noexcept {
      if (hash_ == 0) hash_ = std::hash<int>()(node_);
      return hash_;
    }
    bool operator ==(const myState& s) const noexcept { return node_ == s.node_; }
    bool IsAlive() const noexcept { return alive_; }
    void ReplaceWith(const myState& s) const noexcept {}
    std::vector<myState> Iterate([[maybe_unused]] const myGlobalInfo& g) const
    {
      alive_ = false;
      std::vector<myState> v;

      if (g.done_) return v;
      if (node_ == g.target_)
      {
        g.done_ = true;
        g.hist_ = hist_;
        return v;
      }

      auto [itb, ite] = g.cMap_.equal_range(node_);
      for (auto it = itb; it != ite; ++it)
      {
        assert(it->first == node_);
        ConnectionList hist0{ hist_ };
        hist0.emplace_back(Edge{ it->first,it->second });
        v.emplace_back(it->second, hist0);
      }
      return v;
    }

  private:
    const int node_{ 0 };
    const ConnectionList hist_{};
    mutable size_t hash_{ 0 };
    mutable bool alive_{ true };
  };

  auto GetRandomNode = [&nMap]() -> int { return std::rand() % std::ssize(nMap); };
  int count = 100;
  for (int i = 0; i < count; ++i)
  {
    int n1 = GetRandomNode();
    int n2 = GetRandomNode();
    while (n1 == n2) n2 = GetRandomNode(); // make sure they are different

    // now find a connection between the two with BFS
    myGlobalInfo g{};
    g.target_ = n2;
    myState s0(n1, ConnectionList{});
    BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g);
    while (!g.done_)
    {
      size_t z = bfs.NextLevel();
    }

    for (int j = 0; j < std::ssize(g.hist_); ++j)
    {
      auto it = hMap.find(g.hist_[j]);
      assert(it != hMap.cend());
      ++histogram[it->second];
    }
  }

  auto GetMaxConnection = [](Histogram& histogram, HistogramMap& hMap) -> Edge
    {   
      int maxN{ 0 };
      int maxI{ -1 };
      for (int i = 0; i < std::ssize(histogram); ++i)
      {
        if (histogram[i] > maxN)
        {
          maxN = histogram[i];
          maxI = i;
        }
      }
      assert(maxI != -1);
      histogram[maxI] = -1; // remove the value so next time we find the next best

      auto it = std::find_if(hMap.begin(), hMap.end(), [maxI](const auto it) -> bool { return it.second == maxI; });
      assert(it != hMap.end());
      return it->first;
    };

  Edge e1 = GetMaxConnection(histogram, hMap);
  Edge e2 = GetMaxConnection(histogram, hMap);
  Edge e3 = GetMaxConnection(histogram, hMap);

  auto RemoveEdge = [](ConnectionMap& cMap, const Edge& e) -> void
    {
      auto EraseOne = [](ConnectionMap& cMap, int e1, int e2) -> void
        {
          auto [itb, ite] = cMap.equal_range(e1);
          for (auto it = itb; it != ite; ++it)
          {
            if (it->second == e2)
            {
              cMap.erase(it);
              return;
            }
          }
        };
      EraseOne(cMap, e.first, e.second);
      EraseOne(cMap, e.second, e.first);
    };

  RemoveEdge(cMap, e1);
  RemoveEdge(cMap, e2);
  RemoveEdge(cMap, e3);

  int res1{ 0 };
  int res2{ 0 };
  // now try to find a connection between the ends of e1 with BFS - will fail but give the counts
  {
    myGlobalInfo g{};
    g.target_ = e1.second;
    myState s0(e1.first, ConnectionList{});
    BFS::BreadthFirstSearch<myState, myGlobalInfo> bfs(s0, g);
    while (bfs.NextLevel() > 0);
  
    res1 = bfs.GetSet().size();
    res2 = nMap.size() - res1;
  }

  return res1 * res2;
}

//template<> auto InputData<2023, 25, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 25, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
