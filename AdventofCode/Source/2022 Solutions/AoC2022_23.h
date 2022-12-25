//template<> auto InputData<2022, 23, A>() { return ".....\n..##.\n..#..\n.....\n..##.\n....."; };
//template<> auto InputData<2022, 23, A>() { return "..............\n..............\n.......#......\n.....###.#....\n...#...#.#....\n....#...##....\n...#.###......\n...##.#.##....\n....#..#......\n..............\n..............\n.............."; };
template<> Number AoC<2022, 23, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  const int N = 10;

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Elf
  {
    int x{};
    int y{};
  };
  struct Pos
  {
    int x{};
    int y{};
  };

  struct PosHash { size_t operator() (const Pos& p) const noexcept { return std::hash<long long>()((((long long) p.x) << 32) + (long long) p.y); } };
  struct PosEqual { bool operator() (const Pos& p1, const Pos& p2) const noexcept { return p1.x == p2.x && p1.y == p2.y; } };

  std::unordered_map<Pos, Elf, PosHash, PosEqual> elves{};

  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[y].size(); ++x)
    {
      if (v[y][x] == '#')
      {
        elves.insert(std::pair<Pos, Elf>(Pos{ x,y }, Elf{ x,y }));
      }
    }
  }

  const int dx[4]{ 0,0,-1,1 };
  const int dy[4]{ -1,1,0,0 };

  for (int i = 0; i < N; ++i)
  {
    std::unordered_multimap<Pos, Elf, PosHash, PosEqual> proposed{};
    std::unordered_map<Pos, Elf, PosHash, PosEqual> decided{};

    for (auto& e : elves)
    {
      int x = e.first.x;
      int y = e.first.y;

      bool occN = elves.contains(Pos{ x - 1,y - 1 }) || elves.contains(Pos{ x,y - 1 }) || elves.contains(Pos{ x + 1,y - 1 });
      bool occS = elves.contains(Pos{ x - 1,y + 1 }) || elves.contains(Pos{ x,y + 1 }) || elves.contains(Pos{ x + 1,y + 1 });
      bool occW = elves.contains(Pos{ x - 1,y + 1 }) || elves.contains(Pos{ x - 1,y }) || elves.contains(Pos{ x - 1,y - 1 });
      bool occE = elves.contains(Pos{ x + 1,y + 1 }) || elves.contains(Pos{ x + 1,y }) || elves.contains(Pos{ x + 1,y - 1 });
      bool occA = occN || occS || occW || occE;

      if (!occA)
      {
        decided.insert(std::pair<Pos, Elf>(Pos{ x ,y }, Elf{ x,y }));
        continue;
      }

      bool occ[4]{ occN,occS,occW,occE };

      bool notproposed = true;
      for (int j = 0; j < 4; ++j)
      {
        const int d = (i + j) % 4;
        if (!occ[d])
        {
          proposed.insert(std::pair<Pos, Elf>(Pos{ x + dx[d],y + dy[d] }, Elf{ x,y }));
          notproposed = false;
          break;
        }
      }
      if (notproposed)
      {
        decided.insert(std::pair<Pos, Elf>(Pos{ x ,y }, Elf{ x,y }));
      }
    }

    for (auto e : proposed)
    {
      if (proposed.count(e.first) == 1)
      {
        decided.insert(std::pair<Pos, Elf>(e.first, Elf{ e.first.x, e.first.y }));
      }
      else
      {
        decided.insert(std::pair<Pos, Elf>(Pos{ e.second.x ,e.second.y }, e.second));
      }
    }

    std::swap(decided, elves);
  }


  int minx = 1'000'000;
  int miny = 1'000'000;
  int maxx = -1'000'000;
  int maxy = -1'000'000;
  for (auto& e : elves)
  {
    if (e.first.x > maxx) maxx = e.first.x;
    if (e.first.x < minx) minx = e.first.x;
    if (e.first.y > maxy) maxy = e.first.y;
    if (e.first.y < miny) miny = e.first.y;
  }

  Number z = (maxx - minx + 1) * (maxy - miny + 1) - elves.size();
  return z;
}

//template<> auto InputData<2022, 23, B>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };
template<> Number AoC<2022, 23, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Elf
  {
    int x{};
    int y{};
  };
  struct Pos
  {
    int x{};
    int y{};
  };

  struct PosHash { size_t operator() (const Pos& p) const noexcept { return std::hash<long long>()((((long long) p.x) << 32) + (long long) p.y); } };
  struct PosEqual { bool operator() (const Pos& p1, const Pos& p2) const noexcept { return p1.x == p2.x && p1.y == p2.y; } };

  std::unordered_map<Pos, Elf, PosHash, PosEqual> elves{};

  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[y].size(); ++x)
    {
      if (v[y][x] == '#')
      {
        elves.insert(std::pair<Pos, Elf>(Pos{ x,y }, Elf{ x,y }));
      }
    }
  }

  const int dx[4]{ 0,0,-1,1 };
  const int dy[4]{ -1,1,0,0 };

  Number i = 0;
  bool more = true;
  while (more)
  {
    std::unordered_multimap<Pos, Elf, PosHash, PosEqual> proposed{};
    std::unordered_map<Pos, Elf, PosHash, PosEqual> decided{};

    more = false;
    for (auto& e : elves)
    {
      int x = e.first.x;
      int y = e.first.y;

      bool occN = elves.contains(Pos{ x - 1,y - 1 }) || elves.contains(Pos{ x,y - 1 }) || elves.contains(Pos{ x + 1,y - 1 });
      bool occS = elves.contains(Pos{ x - 1,y + 1 }) || elves.contains(Pos{ x,y + 1 }) || elves.contains(Pos{ x + 1,y + 1 });
      bool occW = elves.contains(Pos{ x - 1,y + 1 }) || elves.contains(Pos{ x - 1,y }) || elves.contains(Pos{ x - 1,y - 1 });
      bool occE = elves.contains(Pos{ x + 1,y + 1 }) || elves.contains(Pos{ x + 1,y }) || elves.contains(Pos{ x + 1,y - 1 });
      bool occA = occN || occS || occW || occE;

      if (!occA)
      {
        decided.insert(std::pair<Pos, Elf>(Pos{ x ,y }, Elf{ x,y }));
        continue;
      }

      bool occ[4]{ occN,occS,occW,occE };

      bool notproposed = true;
      for (int j = 0; j < 4; ++j)
      {
        const int d = (i + j) % 4;
        if (!occ[d])
        {
          proposed.insert(std::pair<Pos, Elf>(Pos{ x + dx[d],y + dy[d] }, Elf{ x,y }));
          notproposed = false;
          break;
        }
      }
      if (notproposed)
      {
        decided.insert(std::pair<Pos, Elf>(Pos{ x ,y }, Elf{ x,y }));
      }
    }

    for (auto e : proposed)
    {
      if (proposed.count(e.first) == 1)
      {
        decided.insert(std::pair<Pos, Elf>(e.first, Elf{ e.first.x, e.first.y }));
        more = true;
      }
      else
      {
        decided.insert(std::pair<Pos, Elf>(Pos{ e.second.x ,e.second.y }, e.second));
      }
    }

    std::swap(decided, elves);
    ++i;
  }


  return i;
}
