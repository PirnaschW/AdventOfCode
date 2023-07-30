template<> Number AoC<2021, 22, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector< std::vector< std::vector<bool>>> reactor{ false };
  reactor.resize(101);
  for (int x = 0; x <= 100; ++x) reactor[x].resize(101);
  for (int x = 0; x <= 100; ++x)
    for (int y = 0; y <= 100; ++y)
      reactor[x][y].resize(101);


  for (const std::string& line : v)
  {
    char toggle[3];
    int x1;
    int x2;
    int y1;
    int y2;
    int z1;
    int z2;
    //on x=-28..25,y=-34..15,z=-36..13
    int n0 = sscanf_s(line.c_str(), "%3c x=%d..%d,y=%d..%d,z=%d..%d", toggle, 3, &x1, &x2, &y1, &y2, &z1, &z2);
    assert(n0 == 7);

    if (x1 < -50 || y1 < -50 || z1 < -50 || x2 >50 || y2 > 50 || z2 > 50) continue;
    bool setting = toggle[1] == 'n' ? true : false;
    for (int x = x1; x <= x2; ++x)
      for (int y = y1; y <= y2; ++y)
        for (int z = z1; z <= z2; ++z)
          reactor[x+50][y+50][z+50] = setting;

  }

  int n{ 0 };
  for (int x = 0; x <= 100; ++x)
    for (int y = 0; y <= 100; ++y)
      for (int z = 0; z <= 100; ++z)
        if (reactor[x][y][z]) ++n;


  return n;
}

template<> Number AoC<2021, 22, B>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<Number> xCuts{};
  std::vector<Number> yCuts{};
  std::vector<Number> zCuts{};

  struct Toggle
  {
    bool setting{ false };
    Number x1{ 0 };
    Number x2{ 0 };
    Number y1{ 0 };
    Number y2{ 0 };
    Number z1{ 0 };
    Number z2{ 0 };
  };

  std::vector<Toggle> toggles{};

  for (const std::string& line : v)
  {
    char toggle[3];
    Toggle t{};
    //on x=-28..25,y=-34..15,z=-36..13
    int z = sscanf_s(line.c_str(), "%3c x=%lld..%lld,y=%lld..%lld,z=%lld..%lld", toggle, 3, &t.x1, &t.x2, &t.y1, &t.y2, &t.z1, &t.z2);
    assert(z == 7);
    t.setting = toggle[1] == 'n' ? true : false;
    t.x2++;
    t.y2++;
    t.z2++;

    xCuts.push_back(t.x1);
    xCuts.push_back(t.x2);
    yCuts.push_back(t.y1);
    yCuts.push_back(t.y2);
    zCuts.push_back(t.z1);
    zCuts.push_back(t.z2);

    toggles.push_back(t);
  }

  std::sort(xCuts.begin(), xCuts.end());
  std::sort(yCuts.begin(), yCuts.end());
  std::sort(zCuts.begin(), zCuts.end());

  std::vector< std::vector< std::vector<bool>>> reactor{ false };
  reactor.resize(xCuts.size() + 2);
  for (int x = 0; x < reactor.size(); ++x) reactor[x].resize(yCuts.size() + 2);
  for (int x = 0; x < reactor.size(); ++x)
    for (int y = 0; y < reactor[0].size(); ++y)
      reactor[x][y].resize(zCuts.size() + 2);

  size_t maxiz2{ 0 };
  for (Toggle t : toggles)
  {
    size_t ix1 = std::find(xCuts.begin(), xCuts.end(), t.x1) - xCuts.begin();
    size_t ix2 = std::find(xCuts.begin(), xCuts.end(), t.x2) - xCuts.begin();
    size_t iy1 = std::find(yCuts.begin(), yCuts.end(), t.y1) - yCuts.begin();
    size_t iy2 = std::find(yCuts.begin(), yCuts.end(), t.y2) - yCuts.begin();
    size_t iz1 = std::find(zCuts.begin(), zCuts.end(), t.z1) - zCuts.begin();
    size_t iz2 = std::find(zCuts.begin(), zCuts.end(), t.z2) - zCuts.begin();

    if (iz2 > maxiz2) maxiz2 = iz2;

    for (size_t x = ix1; x < ix2; ++x)
      for (size_t y = iy1; y < iy2; ++y)
        for (size_t z = iz1; z < iz2; ++z)
          reactor[x][y][z] = t.setting;
  }


  Number n{ 0 };
  for (int x = 0; x < xCuts.size()-1; ++x)
    for (int y = 0; y < yCuts.size()-1; ++y)
      for (int z = 0; z < zCuts.size()-1; ++z)
        if (reactor[x][y][z])
        {
          n += (xCuts[x + 1] - xCuts[x]) * (yCuts[y + 1] - yCuts[y]) * (zCuts[z + 1] - zCuts[z]);
        }

  return n;
}
