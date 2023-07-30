template<> Number AoC<2021, 19, A>(std::istream& input)
{
  constexpr int m{ 2048 };
  constexpr int b{ 16 };

  struct Loc
  {
    Number x{ 0 };
    Number y{ 0 };
    Number z{ 0 };
    bool operator ==(const Loc& l) { return l.x == x && l.y == y && l.z == z; }
  };
  struct Orientation
  {
    Loc xAxis{ 1,0,0 };
    Loc yAxis{ 0,1,0 };
    Loc zAxis{ 0,0,1 };
  };
  struct Source {
    int i1;
    int i2;
  };
  struct Scanner
  {
    int id{ 0 };
    Loc x{ 0,0,0 };
    Loc y{ 0,0,0 };
    Loc z{ 0,0,0 };
    std::vector<Loc> locs{};
    std::array<std::unordered_map<Number, Source>, 24> deltas{};
    bool done{ false };
  };

  using RotList = std::array<struct Orientation, 24>;
  constexpr RotList orientations{
    {
      { {  1, 0, 0 },  { 0, 1, 0 },  {  0, 0, 1 } },
      { {  1, 0, 0 },  { 0, 0, 1 },  {  0,-1, 0 } },
      { {  1, 0, 0 },  { 0,-1, 0 },  {  0, 0,-1 } },
      { {  1, 0, 0 },  { 0, 0,-1 },  {  0, 1, 0 } },

      { { -1, 0, 0 },  { 0, 1, 0 },  {  0, 0,-1 } },
      { { -1, 0, 0 },  { 0, 0, 1 },  {  0, 1, 0 } },
      { { -1, 0, 0 },  { 0,-1, 0 },  {  0, 0, 1 } },
      { { -1, 0, 0 },  { 0, 0,-1 },  {  0,-1, 0 } },

      { {  0, 1, 0 },  {-1, 0, 0 },  {  0, 0, 1 } },
      { {  0, 1, 0 },  { 0, 0, 1 },  {  1, 0, 0 } },
      { {  0, 1, 0 },  { 1, 0, 0 },  {  0, 0,-1 } },
      { {  0, 1, 0 },  { 0, 0,-1 },  { -1, 0, 0 } },

      { {  0,-1, 0 },  {-1, 0, 0 },  {  0, 0,-1 } },
      { {  0,-1, 0 },  { 0, 0, 1 },  { -1, 0, 0 } },
      { {  0,-1, 0 },  { 1, 0, 0 },  {  0, 0, 1 } },
      { {  0,-1, 0 },  { 0, 0,-1 },  {  1, 0, 0 } },

      { {  0, 0, 1 },  {-1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0, 1 },  { 0, 1, 0 },  { -1, 0, 0 } },
      { {  0, 0, 1 },  { 1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0, 1 },  { 0,-1, 0 },  {  1, 0, 0 } },

      { {  0, 0,-1 },  {-1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0,-1 },  { 0, 1, 0 },  {  1, 0, 0 } },
      { {  0, 0,-1 },  { 1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0,-1 },  { 0,-1, 0 },  { -1, 0, 0 } },
    }
  };
  using RevertList = std::array<int, 24>;
  constexpr RevertList revert{ 0, 3, 2, 1,   4, 5, 6, 7,   14, 18, 10, 22,   12, 20, 8, 16,   15, 21, 9, 19,   13, 17, 11, 23 };


  struct H
  {
    static Number Index(Number x, Number y, Number z)
    {
      return ((x + m) << (2LL * b)) + ((y + m) << b) + (z + m);
    }
    static Number Index(const Loc& l)
    {
      return ((l.x + m) << (2LL * b)) + ((l.y + m) << b) + (l.z + m);
    }
    static Number GetX(Number i)
    {
      return (i >> (2LL * b)) - m;
    }
    static Number GetY(Number i)
    {
      return ((i >> b) % (1LL << b)) - m;
    }
    static Number GetZ(Number i)
    {
      return (i % (1LL << b)) - m;
    }
    static Loc GetLoc(Number i)
    {
      return Loc{ GetX(i), GetY(i), GetZ(i) };
    }

    static Loc ReOrient(const RotList& orientations, int ori, const Loc& l)
    {
      Loc res{
        orientations[ori].xAxis.x * l.x + orientations[ori].xAxis.y * l.y + orientations[ori].xAxis.z * l.z,
        orientations[ori].yAxis.x * l.x + orientations[ori].yAxis.y * l.y + orientations[ori].yAxis.z * l.z,
        orientations[ori].zAxis.x * l.x + orientations[ori].zAxis.y * l.y + orientations[ori].zAxis.z * l.z
      };
      return res;
    }
    static Loc Offset(const Loc& offset, const Loc& l)
    {
      Loc res{ l.x + offset.x, l.y + offset.y, l.z + offset.z };
      return res;
    }

    static void CalcDeltas(const RotList& orientations, const RevertList& revert, Scanner& s)
    {
      for (int ori = 0; ori < orientations.size(); ++ori)
      {
        s.deltas[ori].clear();
        s.deltas[ori].reserve(s.locs.size() * s.locs.size() / 2);
      }
      for (int i1 = 0; i1 < s.locs.size(); ++i1)
      {
        const auto& l1 = s.locs[i1];

        for (int ori = 0; ori < orientations.size(); ++ori)
        {
          auto rot = H::ReOrient(orientations, ori, l1);
          auto rotback = H::ReOrient(orientations, revert[ori], rot);
          assert(rotback == l1);
        }

        for (int i2 = i1 + 1; i2 < s.locs.size(); ++i2)
        {
          const auto& l2 = s.locs[i2];

          Source ss(i1, i2);
          Loc d{ l1.x - l2.x, l1.y - l2.y, l1.z - l2.z };
          if (d.x == 0 && d.y == 0 && d.z == 0)
            continue;
          for (int ori = 0; ori < orientations.size(); ++ori)
          {
            s.deltas[ori].insert({ H::Index(H::ReOrient(orientations, ori, d)), ss });
          }
        }
      }
    }

  };


  std::vector<Scanner> scans{};

  std::string line{};
  do
  {
    Scanner s;
    if (!getline(input, line)) break;
    if (line.size() == 0) break;
    int n0 = sscanf_s(line.c_str(), "--- scanner %d", &s.id);
    assert(n0 == 1);
    while (getline(input, line))
    {
      Loc l;
      if (line.size() == 0) break;
      int n = sscanf_s(line.c_str(), "%lld,%lld,%lld", &l.x,&l.y,&l.z);
      assert(n == 3);
      s.locs.push_back(l);
    }
    scans.push_back(s);
  } while (true);

  for (auto& s : scans)
  {
    H::CalcDeltas(orientations,revert,s);
  }

  //for (int i = 0; i < scans.size(); i++)  // for all scanners
  bool more = false;
  do
  {
    more = false;
    for (int j = 1; j < scans.size(); j++)  // for all other scanners
    {
      if (scans[j].done) continue;
      more = true;
      for (int ori = 0; ori < 24 && !scans[j].done; ++ori)  // for all other scanner's orientations
      {
        int matches{ 0 };
        for (auto dj : scans[j].deltas[ori])  // for all beacon locations differences
        {
          Loc dj0 = H::GetLoc(dj.first);
          auto it = scans[0].deltas[0].begin();
          Loc di0 = H::GetLoc(it->first); ++it;
          Loc di1 = H::GetLoc(it->first);
          auto found = scans[0].deltas[0].find(dj.first);
          if (found != scans[0].deltas[0].end())
          {
            ++matches;
            if (matches > 11)
            {
              for (auto& l : scans[j].locs)
              {
                l = H::ReOrient(orientations, ori, l);
              }
              Loc offset{
                scans[0].locs[found->second.i1].x - scans[j].locs[dj.second.i1].x,
                scans[0].locs[found->second.i1].y - scans[j].locs[dj.second.i1].y,
                scans[0].locs[found->second.i1].z - scans[j].locs[dj.second.i1].z
              };
              for (auto& l : scans[j].locs)
              {
                l = H::Offset(offset, l);
              }
              scans[j].done = true;

              int n{ 0 };
              for (auto& l : scans[j].locs)
              {
                if (std::find(scans[0].locs.begin(), scans[0].locs.end(), l) != scans[0].locs.end()) ++n;
              }
              //assert(n > 11);
              for (auto& l : scans[j].locs)
              {
                if (std::find(scans[0].locs.begin(), scans[0].locs.end(), l) == scans[0].locs.end())
                  scans[0].locs.push_back(l);
              }
              H::CalcDeltas(orientations,revert,scans[0]);
              break;
            }
          }
        }
      }
    }
  } while (more);



  size_t z= scans[0].locs.size();
  return z;
}

template<> Number AoC<2021, 19, B>(std::istream& input)
{
  constexpr int m{ 2048 };
  constexpr int b{ 16 };

  struct Loc
  {
    Number x{ 0 };
    Number y{ 0 };
    Number z{ 0 };
    bool operator ==(const Loc& l) { return l.x == x && l.y == y && l.z == z; }
  };
  struct Orientation
  {
    Loc xAxis{ 1,0,0 };
    Loc yAxis{ 0,1,0 };
    Loc zAxis{ 0,0,1 };
  };
  struct Source {
    int i1;
    int i2;
  };
  struct Scanner
  {
    int id{ 0 };
    Loc x{ 0,0,0 };
    Loc y{ 0,0,0 };
    Loc z{ 0,0,0 };
    std::vector<Loc> locs{};
    std::array<std::unordered_map<Number, Source>, 24> deltas{};
    bool done{ false };
  };

  std::vector<Loc> foundScannerLocations{};
  foundScannerLocations.push_back({ 0, 0, 0 });  // Scanner 0

  using RotList = std::array<struct Orientation, 24>;
  constexpr RotList orientations{
    {
      { {  1, 0, 0 },  { 0, 1, 0 },  {  0, 0, 1 } },
      { {  1, 0, 0 },  { 0, 0, 1 },  {  0,-1, 0 } },
      { {  1, 0, 0 },  { 0,-1, 0 },  {  0, 0,-1 } },
      { {  1, 0, 0 },  { 0, 0,-1 },  {  0, 1, 0 } },

      { { -1, 0, 0 },  { 0, 1, 0 },  {  0, 0,-1 } },
      { { -1, 0, 0 },  { 0, 0, 1 },  {  0, 1, 0 } },
      { { -1, 0, 0 },  { 0,-1, 0 },  {  0, 0, 1 } },
      { { -1, 0, 0 },  { 0, 0,-1 },  {  0,-1, 0 } },

      { {  0, 1, 0 },  {-1, 0, 0 },  {  0, 0, 1 } },
      { {  0, 1, 0 },  { 0, 0, 1 },  {  1, 0, 0 } },
      { {  0, 1, 0 },  { 1, 0, 0 },  {  0, 0,-1 } },
      { {  0, 1, 0 },  { 0, 0,-1 },  { -1, 0, 0 } },

      { {  0,-1, 0 },  {-1, 0, 0 },  {  0, 0,-1 } },
      { {  0,-1, 0 },  { 0, 0, 1 },  { -1, 0, 0 } },
      { {  0,-1, 0 },  { 1, 0, 0 },  {  0, 0, 1 } },
      { {  0,-1, 0 },  { 0, 0,-1 },  {  1, 0, 0 } },

      { {  0, 0, 1 },  {-1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0, 1 },  { 0, 1, 0 },  { -1, 0, 0 } },
      { {  0, 0, 1 },  { 1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0, 1 },  { 0,-1, 0 },  {  1, 0, 0 } },

      { {  0, 0,-1 },  {-1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0,-1 },  { 0, 1, 0 },  {  1, 0, 0 } },
      { {  0, 0,-1 },  { 1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0,-1 },  { 0,-1, 0 },  { -1, 0, 0 } },
    }
  };
  using RevertList = std::array<int, 24>;
  constexpr RevertList revert{ 0, 3, 2, 1,   4, 5, 6, 7,   14, 18, 10, 22,   12, 20, 8, 16,   15, 21, 9, 19,   13, 17, 11, 23 };


  struct H
  {
    static Number Index(Number x, Number y, Number z)
    {
      return ((x + m) << (2LL * b)) + ((y + m) << b) + (z + m);
    }
    static Number Index(const Loc& l)
    {
      return ((l.x + m) << (2LL * b)) + ((l.y + m) << b) + (l.z + m);
    }
    static Number GetX(Number i)
    {
      return (i >> (2LL * b)) - m;
    }
    static Number GetY(Number i)
    {
      return ((i >> b) % (1LL << b)) - m;
    }
    static Number GetZ(Number i)
    {
      return (i % (1LL << b)) - m;
    }
    static Loc GetLoc(Number i)
    {
      return Loc{ GetX(i), GetY(i), GetZ(i) };
    }

    static Loc ReOrient(const RotList& orientations, int ori, const Loc& l)
    {
      Loc res{
        orientations[ori].xAxis.x * l.x + orientations[ori].xAxis.y * l.y + orientations[ori].xAxis.z * l.z,
        orientations[ori].yAxis.x * l.x + orientations[ori].yAxis.y * l.y + orientations[ori].yAxis.z * l.z,
        orientations[ori].zAxis.x * l.x + orientations[ori].zAxis.y * l.y + orientations[ori].zAxis.z * l.z
      };
      return res;
    }
    static Loc Offset(const Loc& offset, const Loc& l)
    {
      Loc res{ l.x + offset.x, l.y + offset.y, l.z + offset.z };
      return res;
    }

    static void CalcDeltas(const RotList& orientations, const RevertList& /*revert*/, Scanner& s)
    {
      for (int ori = 0; ori < orientations.size(); ++ori)
      {
        s.deltas[ori].clear();
        s.deltas[ori].reserve(s.locs.size() * s.locs.size() / 2);
      }
      for (int i1 = 0; i1 < s.locs.size(); ++i1)
      {
        const auto& l1 = s.locs[i1];

        //for (int ori = 0; ori < orientations.size(); ++ori)
        //{
        //  auto rot = H::ReOrient(orientations, ori, l1);
        //  auto rotback = H::ReOrient(orientations, revert[ori], rot);
        //  assert(rotback == l1);
        //}

        for (int i2 = i1 + 1; i2 < s.locs.size(); ++i2)
        {
          const auto& l2 = s.locs[i2];

          Source ss(i1, i2);
          Loc d{ l1.x - l2.x, l1.y - l2.y, l1.z - l2.z };
          if (d.x == 0 && d.y == 0 && d.z == 0)
            continue;
          for (int ori = 0; ori < orientations.size(); ++ori)
          {
            s.deltas[ori].insert({ H::Index(H::ReOrient(orientations, ori, d)), ss });
          }
        }
      }
    }

    static Number GetManhattan(const Loc& floc1, const Loc& floc2)
    {
      return std::abs(floc1.x - floc2.x) + std::abs(floc1.y - floc2.y) + std::abs(floc1.z - floc2.z);
    }

  };


  std::vector<Scanner> scans{};

  std::string line{};
  do
  {
    Scanner s;
    if (!getline(input, line)) break;
    if (line.size() == 0) break;
    int n = sscanf_s(line.c_str(), "--- scanner %d", &s.id);
    assert(n == 1);
    while (getline(input, line))
    {
      Loc l;
      if (line.size() == 0) break;
      int n1 = sscanf_s(line.c_str(), "%lld,%lld,%lld", &l.x, &l.y, &l.z);
      assert(n1 == 3);
      s.locs.push_back(l);
    }
    scans.push_back(s);
  } while (true);

  for (auto& s : scans)
  {
    H::CalcDeltas(orientations, revert, s);
  }

  //for (int i = 0; i < scans.size(); i++)  // for all scanners
  bool more = false;
  do
  {
    more = false;
    for (int j = 1; j < scans.size(); j++)  // for all other scanners
    {
      if (scans[j].done) continue;
      more = true;
      for (int ori = 0; ori < 24 && !scans[j].done; ++ori)  // for all other scanner's orientations
      {
        int matches{ 0 };
        for (auto dj : scans[j].deltas[ori])  // for all beacon locations differences
        {
          Loc dj0 = H::GetLoc(dj.first);
          auto it = scans[0].deltas[0].begin();
          Loc di0 = H::GetLoc(it->first); ++it;
          Loc di1 = H::GetLoc(it->first);
          auto found = scans[0].deltas[0].find(dj.first);
          if (found != scans[0].deltas[0].end())
          {
            ++matches;
            if (matches > 11)
            {
              for (auto& l : scans[j].locs)
              {
                l = H::ReOrient(orientations, ori, l);
              }
              Loc offset{
                scans[0].locs[found->second.i1].x - scans[j].locs[dj.second.i1].x,
                scans[0].locs[found->second.i1].y - scans[j].locs[dj.second.i1].y,
                scans[0].locs[found->second.i1].z - scans[j].locs[dj.second.i1].z
              };
              foundScannerLocations.push_back(offset);
              for (auto& l : scans[j].locs)
              {
                l = H::Offset(offset, l);
              }
              scans[j].done = true;

              int n{ 0 };
              for (auto& l : scans[j].locs)
              {
                if (std::find(scans[0].locs.begin(), scans[0].locs.end(), l) != scans[0].locs.end()) ++n;
              }
              //assert(n > 11);
              for (auto& l : scans[j].locs)
              {
                if (std::find(scans[0].locs.begin(), scans[0].locs.end(), l) == scans[0].locs.end())
                  scans[0].locs.push_back(l);
              }
              H::CalcDeltas(orientations, revert, scans[0]);
              break;
            }
          }
        }
      }
    }
  } while (more);

  Number maxd{ 0 };
  for (const auto& floc1 : foundScannerLocations)
    for (const auto& floc2 : foundScannerLocations)
    {
      Number d = H::GetManhattan(floc1, floc2);
      if (d > maxd) maxd = d;
    }

  return maxd;
}
