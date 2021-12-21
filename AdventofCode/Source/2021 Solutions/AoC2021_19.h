void AoC2021_19A(std::istream& input)
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

  constexpr std::array<struct Orientation, 24> orientations{
    {
      { {  1, 0, 0 },  { 0, 1, 0 },  {  0, 0, 1 } },
      { {  1, 0, 0 },  { 0, 1, 0 },  {  0, 0,-1 } },
      { {  1, 0, 0 },  { 0,-1, 0 },  {  0, 0, 1 } },
      { {  1, 0, 0 },  { 0,-1, 0 },  {  0, 0,-1 } },
      { { -1, 0, 0 },  { 0, 1, 0 },  {  0, 0, 1 } },
      { { -1, 0, 0 },  { 0, 1, 0 },  {  0, 0,-1 } },
      { { -1, 0, 0 },  { 0,-1, 0 },  {  0, 0, 1 } },
      { { -1, 0, 0 },  { 0,-1, 0 },  {  0, 0,-1 } },

      { {  0, 1, 0 },  { 0, 0, 1 },  {  1, 0, 0 } },
      { {  0, 1, 0 },  { 0, 0, 1 },  { -1, 0, 0 } },
      { {  0,-1, 0 },  { 0, 0, 1 },  { -1, 0, 0 } },
      { {  0, 1, 0 },  { 0, 0,-1 },  {  1, 0, 0 } },
      { {  0,-1, 0 },  { 0, 0,-1 },  {  1, 0, 0 } },
      { {  0,-1, 0 },  { 0, 0, 1 },  {  1, 0, 0 } },
      { {  0, 1, 0 },  { 0, 0,-1 },  { -1, 0, 0 } },
      { {  0,-1, 0 },  { 0, 0,-1 },  { -1, 0, 0 } },

      { {  0, 0, 1 },  { 1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0, 1 },  {-1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0,-1 },  { 1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0,-1 },  {-1, 0, 0 },  {  0, 1, 0 } },
      { {  0, 0, 1 },  { 1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0, 1 },  {-1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0,-1 },  { 1, 0, 0 },  {  0,-1, 0 } },
      { {  0, 0,-1 },  {-1, 0, 0 },  {  0,-1, 0 } },
    }
  };


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

    static Loc ReOrient(const std::array<struct Orientation, 24>& orientations, int ori, const Loc& l)
    {
      Loc res{
        orientations[ori].xAxis.x * l.x + orientations[ori].xAxis.y * l.y + orientations[ori].xAxis.z * l.z,
        orientations[ori].xAxis.x * l.x + orientations[ori].xAxis.y * l.y + orientations[ori].xAxis.z * l.z,
        orientations[ori].xAxis.x * l.x + orientations[ori].xAxis.y * l.y + orientations[ori].xAxis.z * l.z
      };
      return res;
    }
    static Loc Offset(const Loc& offset, const Loc& l)
    {
      Loc res{ l.x + offset.x, l.y + offset.y, l.z + offset.z };
      return res;
    }

  };


  std::vector<Scanner> scans{};

  std::string line{};
  do
  {
    Scanner s;
    getline(input, line);
    if (line.size() == 0) break;
    int n = sscanf_s(line.c_str(), "--- scanner %d", &s.id);
    assert(n == 1);
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
    for (int i1 = 0; i1 < s.locs.size(); ++i1)
    {
      const auto& l1 = s.locs[i1];
      for (int i2 = 0; i2 < s.locs.size(); ++i2)
      {
        const auto& l2 = s.locs[i2];

        Source ss(i1, i2);
        Loc d{ l1.x - l2.x, l1.y - l2.y, l1.z - l2.z };
        if (d.x == 0 && d.y == 0 && d.z == 0) continue;
        for (int ori = 0; ori < orientations.size(); ++ori)
        {
          s.deltas[ori].insert({ H::Index(H::ReOrient(orientations, ori, d)), ss });
        }
      }
    }
  }

  for (int i = 0; i < scans.size(); i++)  // for all scanners
  {
    for (int j = i + 1; j < scans.size(); j++)  // for all other scanners
    {
      if (scans[j].done) continue;
      for (int ori = 0; ori < 24 && !scans[j].done; ++ori)  // for all other scanner's orientations
      {
        int matches{ 0 };
        for (auto dj : scans[j].deltas[ori])  // for all beacon locations differences
        {
          Loc dj0 = H::GetLoc(dj.first);
          auto it = scans[i].deltas[0].begin();
          Loc di0 = H::GetLoc(it->first); ++it;
          Loc di1 = H::GetLoc(it->first);
          if (scans[i].deltas[0].contains(dj.first))
          {
            ++matches;
            if (matches > 11 * 12 - 1)
            {
              for (auto& l : scans[j].locs)
              {
                l = H::ReOrient(orientations, ori, l);
                l = H::Offset(H::GetLoc(dj.first),l);
              }
              scans[j].done = true;
              break;
            }
          }
        }
      }
    }
  }




  int z{ 19 };
  std::cout << z << std::endl;
}

void AoC2021_19B(std::istream& input)
{
}
