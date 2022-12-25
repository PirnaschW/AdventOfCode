//template<> auto InputData<2022, 24, A>() { return "#.######\n#>>.<^<#\n#.<..<<#\n#>v.><>#\n#<^v^^>#\n######.#"; };

template<> Number AoC<2022, 24, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Blizzard
  {
    int x;
    int y;
    int d;
  };
  //struct PosHash { size_t operator() (const Pos& p) const noexcept { return std::hash<long long>()((((long long) p.x) << 32) + (long long) p.y); } };
  //struct PosEqual { bool operator() (const Pos& p1, const Pos& p2) const noexcept { return p1.x == p2.x && p1.y == p2.y; } };

  std::vector<Blizzard> blizzards{};

  //const int N = 20;
  std::vector<std::vector<std::vector<bool>>> w{};
  w.resize(1);

  const int xmax = (int) v[0].size();
  const int ymax = (int) v.size();
  w[0].resize(ymax);
  for (int y = 0; y < ymax; ++y)
  {
    w[0][y].resize(xmax);
    for (int x = 0; x < xmax; ++x)
    {
      switch (v[y][x])
      {
        case '>': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,0 }); break;
        case 'v': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,1 }); break;
        case '<': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,2 }); break;
        case '^': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,3 }); break;
        case '.': w[0][y][x] = true;   break;
        case '#': w[0][y][x] = false;  break;
        default: assert(false);
      }
    }
  }

  const int dx[4]{ 1,0,-1,0 };
  const int dy[4]{ 0,1,0,-1 };

  //for (int y = 0; y < ymax; ++y)
  //{
  //  for (int x = 0; x < xmax; ++x)
  //  {
  //    std::cout << (w[0][y][x] ? '.' : '#');
  //  }
  //  std::cout << std::endl;
  //}
  //std::cout << std::endl;


  struct State
  {
    int x{};
    int y{};
  };
  State start{ 1,0 };
  State finish{ xmax - 2,ymax - 1 };
  struct StateHash { size_t operator() (const State& p) const noexcept { return std::hash<long long>()((((long long) p.x) << 32) + (long long) p.y); } };
  struct StateEqual { bool operator() (const State& p1, const State& p2) const noexcept { return p1.x == p2.x && p1.y == p2.y; } };

  std::unordered_set<State, StateHash, StateEqual> list{};
  list.insert(start);
  int z{};

  for (z = 1;; ++z)
  {
    //if (z % 20 == 0) std::cout << z << ' ';

    w.push_back(w[z - 1]);
    for (int y = 1; y < ymax - 1; ++y)
    {
      for (int x = 1; x < xmax - 1; ++x)
      {
        w[z][y][x] = true;  // clean out interior
      }
    }

    for (Blizzard& b : blizzards)
    {
      const int x = b.x + dx[b.d];
      const int y = b.y + dy[b.d];
      if (x < 1 || y < 1 || x >= xmax-1 || y >= ymax-1) // reset blizzard
      {
        switch (b.d)
        {
          case 0: b.x -= xmax - 3; break;
          case 1: b.y -= ymax - 3; break;
          case 2: b.x += xmax - 3; break;
          case 3: b.y += ymax - 3; break;
        }
        assert(b.x >= 1);
        assert(b.y >= 1);
        assert(b.x <= xmax-1);
        assert(b.y <= ymax-1);
      }
      else
      {
        b.x += dx[b.d];
        b.y += dy[b.d];
        assert(b.x >= 1);
        assert(b.y >= 1);
        assert(b.x <= xmax - 1);
        assert(b.y <= ymax - 1);
      }
      w[z][b.y][b.x] = false;
    }

    //for (int y = 0; y < ymax; ++y)
    //{
    //  for (int x = 0; x < xmax; ++x)
    //  {
    //    std::cout << (w[z][y][x] ? '.' : '#');
    //  }
    //  std::cout << std::endl;
    //}
    //std::cout << std::endl;

    std::unordered_set<State, StateHash, StateEqual> newlist{};
    for (auto s : list)
    {
      if (w[z][s.y][s.x])
      {
        State ss = s;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }

      if (s.y < ymax - 1 && w[z][s.y + 1][s.x])
      {
        State ss = s;
        ++ss.y;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
      if (s.y > 0 && w[z][s.y - 1][s.x])
      {
        State ss = s;
        --ss.y;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
      if (s.x < xmax - 1 && w[z][s.y][s.x + 1])
      {
        State ss = s;
        ++ss.x;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
      if (s.x > 0 && w[z][s.y][s.x - 1])
      {
        State ss = s;
        --ss.x;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
    }


    if (newlist.contains(finish)) break;
    std::swap(newlist, list);
  }


  return z;
}

//template<> auto InputData<2022, 24, B>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };

template<> Number AoC<2022, 24, B>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct Blizzard
  {
    int x;
    int y;
    int d;
  };
  //struct PosHash { size_t operator() (const Pos& p) const noexcept { return std::hash<long long>()((((long long) p.x) << 32) + (long long) p.y); } };
  //struct PosEqual { bool operator() (const Pos& p1, const Pos& p2) const noexcept { return p1.x == p2.x && p1.y == p2.y; } };

  std::vector<Blizzard> blizzards{};

  //const int N = 20;
  std::vector<std::vector<std::vector<bool>>> w{};
  w.resize(1);

  const int xmax = (int) v[0].size();
  const int ymax = (int) v.size();
  w[0].resize(ymax);
  for (int y = 0; y < ymax; ++y)
  {
    w[0][y].resize(xmax);
    for (int x = 0; x < xmax; ++x)
    {
      switch (v[y][x])
      {
        case '>': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,0 }); break;
        case 'v': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,1 }); break;
        case '<': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,2 }); break;
        case '^': w[0][y][x] = false;  blizzards.push_back(Blizzard{ x,y,3 }); break;
        case '.': w[0][y][x] = true;   break;
        case '#': w[0][y][x] = false;  break;
        default: assert(false);
      }
    }
  }

  const int dx[4]{ 1,0,-1,0 };
  const int dy[4]{ 0,1,0,-1 };

  //for (int y = 0; y < ymax; ++y)
  //{
  //  for (int x = 0; x < xmax; ++x)
  //  {
  //    std::cout << (w[0][y][x] ? '.' : '#');
  //  }
  //  std::cout << std::endl;
  //}
  //std::cout << std::endl;


  struct State
  {
    int x{};
    int y{};
  };
  State start{ 1,0 };
  State finish{ xmax - 2,ymax - 1 };
  struct StateHash { size_t operator() (const State& p) const noexcept { return std::hash<long long>()((((long long) p.x) << 32) + (long long) p.y); } };
  struct StateEqual { bool operator() (const State& p1, const State& p2) const noexcept { return p1.x == p2.x && p1.y == p2.y; } };

  std::unordered_set<State, StateHash, StateEqual> list{};
  list.insert(start);
  int z{};

  int targetcount = 0;
  for (z = 1;; ++z)
  {
    //if (z % 20 == 0) std::cout << z << ' ';

    w.push_back(w[z - 1]);
    for (int y = 1; y < ymax - 1; ++y)
    {
      for (int x = 1; x < xmax - 1; ++x)
      {
        w[z][y][x] = true;  // clean out interior
      }
    }

    for (Blizzard& b : blizzards)
    {
      const int x = b.x + dx[b.d];
      const int y = b.y + dy[b.d];
      if (x < 1 || y < 1 || x >= xmax - 1 || y >= ymax - 1) // reset blizzard
      {
        switch (b.d)
        {
          case 0: b.x -= xmax - 3; break;
          case 1: b.y -= ymax - 3; break;
          case 2: b.x += xmax - 3; break;
          case 3: b.y += ymax - 3; break;
        }
        assert(b.x >= 1);
        assert(b.y >= 1);
        assert(b.x <= xmax - 1);
        assert(b.y <= ymax - 1);
      }
      else
      {
        b.x += dx[b.d];
        b.y += dy[b.d];
        assert(b.x >= 1);
        assert(b.y >= 1);
        assert(b.x <= xmax - 1);
        assert(b.y <= ymax - 1);
      }
      w[z][b.y][b.x] = false;
    }

    //for (int y = 0; y < ymax; ++y)
    //{
    //  for (int x = 0; x < xmax; ++x)
    //  {
    //    std::cout << (w[z][y][x] ? '.' : '#');
    //  }
    //  std::cout << std::endl;
    //}
    //std::cout << std::endl;

    std::unordered_set<State, StateHash, StateEqual> newlist{};
    for (auto s : list)
    {
      if (w[z][s.y][s.x])
      {
        State ss = s;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }

      if (s.y < ymax - 1 && w[z][s.y + 1][s.x])
      {
        State ss = s;
        ++ss.y;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
      if (s.y > 0 && w[z][s.y - 1][s.x])
      {
        State ss = s;
        --ss.y;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
      if (s.x < xmax - 1 && w[z][s.y][s.x + 1])
      {
        State ss = s;
        ++ss.x;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
      if (s.x > 0 && w[z][s.y][s.x - 1])
      {
        State ss = s;
        --ss.x;
        if (!newlist.contains(ss))
        {
          newlist.insert(ss);
        }
      }
    }

    switch (targetcount)
    {
      case 0:   
        if (newlist.contains(finish))
        {
          newlist.clear();
          newlist.insert(finish);
          ++targetcount;
        }
        break;

      case 1:
        if (newlist.contains(start))
        {
          newlist.clear();
          newlist.insert(start);
          ++targetcount;
        }
        break;
      case 2:
        if (newlist.contains(finish))
        {
          ++targetcount;
        }
        break;
    }
    std::swap(newlist, list);
    if (targetcount == 3) break;
  }

  return z;
}
