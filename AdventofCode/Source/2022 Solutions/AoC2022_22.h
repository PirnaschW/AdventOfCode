//template<> auto InputData<2022, 22, A>() { return "        ...#\n        .#..\n        #...\n        ....\n...#.......#\n........#...\n..#....#....\n..........#.\n        ...#....\n        .....#..\n        .#......\n        ......#.\n\n10R5L5R10L4R5L5"; };
template<> Number AoC<2022, 22, A>(std::istream& input)
{
  struct H
  {
    static int nextx(const std::vector<std::string>& v, int x, int y, int dx)
    {
      do
      {
        if (x + dx > (int) v[y].size() - 1)
        {
          x = 0;
        }
        else if (x + dx < 0)
        {
          x = (int) v[y].size() - 1;
        }
        else x += dx;
      }
      while (v[y][x] == ' ');
      return x;
    }
    static int nexty(const std::vector<std::string>& v, int x, int y, int dy)
    {
      do
      {
        if (y + dy > (int) v.size() - 1)
        {
          y = 0;
        }
        else if (y + dy < 0)
        {
          y = (int) v.size() - 1;
        }
        else y += dy;
      }
      while (v[y][x] == ' ');
      return y;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  bool splithere = false;
  std::string instructions{};
  size_t maxlen = 0;
  for (auto const& line : v)
  {
    if (splithere)
    {
      instructions = line;
      break;
    }

    if (line.size() > maxlen) maxlen = line.size();
    if (line != "") continue;
    else splithere = true;
  }
  v.pop_back();
  v.pop_back();
  for (auto& line : v)
  {
    while (line.size() < maxlen) line.push_back(' ');
    assert(line.size() == v[0].size());
  }

  int currx = 0;
  int curry = 0;
  int curro = 0;

  for (currx = 0; v[0][currx] != '.'; ++currx);

  int n = 0;
  bool lastmove{ false };
  for (int i = 0; i < instructions.size(); ++i)
  {
    // read next instruction
    bool rotateleft{};
    switch (instructions[i])
    {
      case 'L': rotateleft = true; break;
      case 'R': rotateleft = false; break;

      default:
        assert(instructions[i] >= '0');
        assert(instructions[i] <= '9');
        n *= 10;
        n += instructions[i] - '0';
        if (i < instructions.size() - 1)
          continue;
        else
        {
          lastmove = true;
          break;
        }
    }

 //   std::cout << n << (rotateleft ? 'L' : 'R') << std::endl;
    // move
    int dx{};
    int dy{};
    switch (curro)
    {
      case 0: dx = 1; dy = 0; break;
      case 1: dx = 0; dy = 1; break;
      case 2: dx = -1; dy = 0; break;
      case 3: dx = 0; dy = -1; break;
      default: assert(false);
    }

    for (int z = 0; z < n; ++z)
    {
      int nextx = H::nextx(v, currx, curry, dx);
      int nexty = H::nexty(v, currx, curry, dy);

      if (v[nexty][nextx] == '.')
      {
        currx = nextx;
        curry = nexty;
      }
      else if (v[nexty][nextx] == '#')
      {
        break;
      }
      else
      {
        assert(v[nexty][nextx] == ' ');
      }
    }
    n = 0;

    // rotate
    if (!lastmove)
    {
      if (rotateleft) curro += 3;
      else ++curro;
      curro %= 4;
    }
    else
    {
      curro %= 4;
    }
//    std::cout << "now at " << currx << ' ' << curry << ' '<< curro << std::endl;
    assert(curro >= 0 && curro <=3);
  }

  int z = 4 * (currx + 1) + 1000 * (curry + 1) + curro;
  return z;
}

//template<> auto InputData<2022, 22, B>() { return "        ...#\n        .#..\n        #...\n        ....\n...#.......#\n........#...\n..#....#....\n..........#.\n        ...#....\n        .....#..\n        .#......\n        ......#.\n\n10R5L5R10L4R5L5"; };
//template<> Number AoC<2022, 22, B>(std::istream& input)
//{
//  return 0;
//  struct Pos
//  {
//    int x{0};
//    int y{0};
//    int o{0};
//  };
//
//  struct H
//  {
//    static Pos delta(int o)
//    {
//      Pos d{};
//      switch (o)
//      {
//        case 0: d.x = 1;  d.y = 0; break;
//        case 1: d.x = 0;  d.y = 1; break;
//        case 2: d.x = -1; d.y = 0; break;
//        case 3: d.x = 0;  d.y = -1; break;
//        default: assert(false);
//      }
//      return d;
//    }
//
//    static Pos nextpos(const std::vector<std::string>& v, Pos curr)
//    {
//      const int N = (int) v.size() / 3;
//      assert(N == (int) v[0].size() / 4);
//
//      Pos d = delta(curr.o);
//      Pos next;
//      next.o = curr.o;
//      assert(check(v, curr));
//
//      // handle cube faces
//      if (curr.y < N && curr.x + d.x < 2 * N) // leave face 1 to the left -> face 3 from top
//      {
//        next.x = curr.y + N + d.y;
//        next.y = curr.x - N - d.x;
//        next.o += 3;
//        assert(check(v, next));
//      }
//      else if (curr.y < N && curr.x + d.x >= 3 * N) // leave face 1 to the right -> face 6 from right
//      {
//        next.x = curr.x + N + 1 - d.x;
//        next.y = 3 * N - 1 - curr.y + d.y;
//        next.o += 2;
//        assert(check(v, next));
//      }
//      else if (curr.y + d.y < 0) // leave face 1 to the top  -> face 2 from top
//      {
//        next.x = 3 * N - 1 - curr.x - d.x;
//        next.y = curr.y + N + 1 + d.y;
//        next.o += 2;
//        assert(check(v, next));
//      }
//
//
//      else if (curr.y + d.y < N && curr.x < N) // leave face 2 to the top -> face 1 from top
//      {
//        next.x = 3 * N - 1 - curr.x + d.x;
//        next.y = curr.y - N - 1 - d.y;
//        next.o += 2;
//        assert(check(v, next));
//      }
//      else if (curr.x + d.x < 0 && curr.y >= N && curr.y < 2 * N) // leave face 2 to the left -> face 6 from bottom
//      {
//        next.x = 3 * N - curr.x + d.x;
//        next.y = curr.y + N - d.y;
//        next.o += 1;
//        assert(check(v, next));
//      }
//      else if (curr.x < N && curr.y < 2 * N && curr.y + d.y >= 2 * N) // leave face 2 to the bottom -> face 5 from bottom
//      {
//        next.x = 3 * N - 1 + curr.x - d.x;
//        next.y = curr.y + N - 1 + d.y;
//        next.o += 2;
//        assert(check(v, next));
//      }
//
//
//      else if (curr.y + d.y < N && curr.x >= N && curr.x < 2 * N) // leave face 3 to the top -> face 1 from left
//      {
//        next.x = curr.y + N + 1 + d.y; // 50 -> 100
//        next.y = curr.x - N - d.x;  // 50...99 -> 0...49
//        next.o += 1;
//        assert(check(v, next));
//      }
//      else if (curr.x >= N && curr.x < 2 * N && curr.y + d.y >= 2 * N) // leave face 3 to the bottom -> face 5 from left
//      {
//        next.x = curr.y + d.y;  // 99 -> 100
//        next.y = 4 * N - 1 - curr.x - d.x;   // 50...99 -> 149...100
//        next.o += 3;
//        assert(check(v, next));
//      }
//
//
//      else if (curr.x + d.x >= 3 * N && curr.y >= N && curr.y < 2 * N) // leave face 4 to the right -> face 6 from top
//      {
//        next.x = 5 * N - 1 - curr.y - d.y;   // 50...99 -> 199...150
//        next.y = curr.x - N + d.x;  // 149 -> 100
//        next.o += 1;
//        assert(check(v, next));
//      }
//
//
//      else if (curr.y >= 2 * N && curr.x + d.x < 2 * N) // leave face 5 to the left -> face 5 3rom bottom
//      {
//        next.x = 4 * N - 1 - curr.y - d.y;  // 100...149 -> 99...50
//        next.y = curr.x + d.x;   // 100 -> 100
//        next.o += 1;
//        assert(check(v, next));
//      }
//      else if (curr.x < 3 * N && curr.y + d.y >= 3 * N) // leave face 5 to the bottom -> face 2 from bottom
//      {
//        next.x = 3 * N - 1 - curr.x + d.x; // 100...149 -> 49...0
//        next.y = 5 * N - 1 - curr.y - d.y; // 149 -> 99
//        next.o += 2;
//        assert(check(v, next));
//      }
//
//
//      else if (curr.x >= 3 * N && curr.y + d.y < 2 * N) // leave face 6 to the top -> face 4 from right
//      {
//        next.x = curr.y + d.y;   // 100 -> 99
//        next.y = 5 * N - 1 - curr.x - d.x;  // 150...199 -> 99...50
//        next.o += 3;
//        assert(check(v, next));
//      }
//      else if (curr.y >= 2 * N && curr.x + d.x >= 4 * N) // leave face 6 to the right -> face 1 from right
//      {
//        next.x = curr.x - 2 * N + 1 - d.x;  // 199 -> 99
//        next.y = 3 * N - 1 - curr.y + d.y; // 100...149 -> 49...0
//        next.o += 2;
//        assert(check(v, next));
//      }
//      else if (curr.x >= 3 * N && curr.y + d.y >= 3 * N) // leave face 6 to the bottom -> face2 from left
//      {
//        next.x = 3 * N - curr.y - d.y; // 149 -> 0
//        next.y = 5 * N - 1 - curr.x + d.x; // 150...199 -> 99...50
//        next.o += 3;
//        assert(check(v, next));
//      }
//
//      else
//      {
//        next.x = curr.x + d.x;
//        next.y = curr.y + d.y;
//        assert(check(v,next));
//      }
//
//      assert(check(v, next));
//
//      next.o %= 4;
//
//      Pos retval{};
//      retval.x = next.x;
//      retval.y = next.y;
//      retval.o = next.o;
//      return retval;
//    }
//
//    static bool check(const std::vector<std::string>& v, Pos curr)
//    {
//      const int N = (int) v.size() / 3;
//      if (curr.x < 0) return false;
//      if (curr.x >= 4 * N) return false;
//      if (curr.y < 0)return false;
//      if (curr.y >= 3 * N)return false;
//      if (v[curr.y][curr.x] == ' ') return false;
//      return true;
//    }
//  };
//
//  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
//
//  bool splithere = false;
//  std::string instructions{};
//  size_t maxlen = 0;
//  for (auto const& line : v)
//  {
//    if (splithere)
//    {
//      instructions = line;
//      break;
//    }
//
//    if (line.size() > maxlen) maxlen = line.size();
//    if (line != "") continue;
//    else splithere = true;
//  }
//  v.pop_back();
//  v.pop_back();
//  for (auto& line : v)
//  {
//    while (line.size() < maxlen) line.push_back(' ');
//    assert(line.size() == v[0].size());
//  }
//
//  const int N = (int) v.size() / 3;
//  assert(N == (int) v[0].size() / 4);
//
//  Pos curr{2*N,0,0};
//
//  int n = 0;
//  bool lastmove{ false };
//  for (int i = 0; i < instructions.size(); ++i)
//  {
//    // read next instruction
//    bool rotateleft{};
//    switch (instructions[i])
//    {
//      case 'L': rotateleft = true; break;
//      case 'R': rotateleft = false; break;
//
//      default:
//        assert(instructions[i] >= '0');
//        assert(instructions[i] <= '9');
//        n *= 10;
//        n += instructions[i] - '0';
//        if (i < instructions.size() - 1)
//          continue;
//        else
//        {
//          lastmove = true;
//          break;
//        }
//    }
//
// //   std::cout << n << (rotateleft ? 'L' : 'R') << std::endl;
//    // move
//
//    for (int z = 0; z < n; ++z)
//    {
//      Pos next = H::nextpos(v, curr);
//
//      if (v[next.y][next.x] == '.')
//      {
//        curr = next;
//      }
//      else if (v[next.y][next.x] == '#')
//      {
//        break;
//      }
//      else
//      {
//        assert(false);
//      }
//    }
//    n = 0;
//
//    // rotate
//    if (!lastmove)
//    {
//      if (rotateleft) curr.o += 3;
//      else ++curr.o;
//      curr.o %= 4;
//    }
//    else
//    {
//      curr.o %= 4;
//    }
////    std::cout << "now at " << currx << ' ' << curry << ' '<< curro << std::endl;
//    assert(curr.o >= 0 && curr.o <= 3);
//  }
//
//  int z = 4 * (curr.x + 1) + 1000 * (curr.y + 1) + curr.o;
//  return z;
//}
//

//template<> auto InputData<2022, 22, B>() { return "        ...#\n        .#..\n        #...\n        ....\n...#.......#\n........#...\n..#....#....\n..........#.\n        ...#....\n        .....#..\n        .#......\n        ......#.\n\n10R5L5R10L4R5L5"; };
template<> Number AoC<2022, 22, B>(std::istream& input)
{
  struct Pos
  {
    int x{ 0 };
    int y{ 0 };
    int o{ 0 };
    bool operator==(const Pos& p) const noexcept { return x == p.x && y == p.y && o == p.o; }
    bool operator!=(const Pos& p) const noexcept { return ! (*this == p); }
  };
  struct LocalPos
  {
    int x{ 0 };
    int y{ 0 };
    int o{ 0 };
    bool operator==(const LocalPos& p) const noexcept { return x == p.x && y == p.y && o == p.o; }
    bool operator!=(const LocalPos& p) const noexcept { return !(*this == p); }
  };

  using FaceID = unsigned char;
  static int N = 0;

  constexpr static const std::array<std::array<FaceID, 4>, 5> id{
     0, 1, 2, 0,
     0, 5, 0, 0,
     3, 4, 0, 0,
     6, 0, 0, 0,
     0, 0, 0, 0,
  };
  constexpr static const std::array<std::array<int,2>,7> FaceOffset{
    -1,-1,
    1, 0,
    2, 0,
    0, 2,
    1, 2,
    1, 1,
    0, 3,
  };

  struct H
  {

    static void SetN(const std::vector<std::string>& v)
    {
      N = (int) v.size() / 4;
      assert(N == (int) v[0].size() / 3);
    }

    static Pos GetDelta(int o) // Get offset depending on given orientation
    {
      constexpr const int dx[4]{ 1,0,-1,0 };
      constexpr const int dy[4]{ 0,1,0,-1 };
      return Pos{ dx[o],dy[o] };
    }

    static FaceID GetFaceID(int x, int y)
    {
      if (y < 0 || x < 0) return 0;
      return id[y/N][x/N];
    }

    static LocalPos ToLocal(const Pos& p)
    {
      return LocalPos{ p.x % N,p.y % N,p.o };
    }

    static Pos ToGlobal(const LocalPos& l, FaceID f)
    {
      return Pos{ l.x + N * FaceOffset[f][0],l.y + N * FaceOffset[f][1],l.o % 4 };
    }

    static void Revert(Pos& p)
    {
      p.o += 2;
      p.o %= 4;
    }

    static Pos GetNaiveNext(const Pos& p)
    {
      Pos d = GetDelta(p.o);
      return Pos{p.x+d.x,p.y+d.y,p.o};
    }

    static Pos GetNextpos(const std::vector<std::string>& v, Pos curr)
    {
      assert(check(v, curr));

      Pos d = GetDelta(curr.o);
      Pos next = GetNaiveNext(curr);

      FaceID f0 = GetFaceID(curr.x, curr.y);
      FaceID f1 = GetFaceID(next.x, next.y);

      assert(f0 != 0);

      if (f0 == f1) // stays on same face
      {
        return next;
      }
      else
      {
        LocalPos l = ToLocal(curr);

        if (l.x + d.x < 0)  // leaving to the left
        {
          switch (f0)
          {
            case 1: return ToGlobal({ 0, N - 1 - l.y,l.o + 2 }, 3);
            case 2: return next;
            case 3: return ToGlobal({ 0, N - 1 - l.y,l.o + 2 }, 1);
            case 4: return next;
            case 5: return ToGlobal({ l.y,0,l.o + 3 }, 3);
            case 6: return ToGlobal({ l.y,0,l.o + 3 }, 1);
          }
        }

        if (l.x + d.x >= N)  // leaving to the right
        {
          switch (f0)
          {
            case 1: return next;
            case 2: return ToGlobal({ N - 1, N - 1 - l.y,l.o + 2 }, 4);
            case 3: return next;
            case 4: return ToGlobal({ N - 1, N - 1 - l.y,l.o + 2 }, 2);
            case 5: return ToGlobal({ l.y, N - 1,l.o + 3 }, 2);
            case 6: return ToGlobal({ l.y, N - 1,l.o + 3 }, 4);
          }
        }

        if (l.y + d.y < 0)  // leaving to the top
        {
          switch (f0)
          {
            case 1: return ToGlobal({ 0,l.x,l.o + 1 }, 6);
            case 2: return ToGlobal({ l.x,N - 1,l.o }, 6);
            case 3: return ToGlobal({ 0,l.x,l.o + 1 }, 5);
            case 4: return next;
            case 5: return next;
            case 6: return next;
          }
        }
        if (l.y + d.y >= N)  // leaving to the bottom
        {
          switch (f0)
          {
            case 1: return next;
            case 2: return ToGlobal({ N - 1,l.x,l.o + 1 }, 5);
            case 3: return next;
            case 4: return ToGlobal({ N - 1,l.x,l.o + 1 }, 6);
            case 5: return next;
            case 6: return ToGlobal({ l.x,0,l.o }, 2);
          }
        }
        assert(false);
        return next;
      }
    }

    static bool check(const std::vector<std::string>& v, Pos curr)
    {
      if (curr.x < 0) return false;
      if (curr.x >= 3 * N) return false;
      if (curr.y < 0)return false;
      if (curr.y >= 4 * N) return false;
      if (v[curr.y][curr.x] == ' ') return false;
      return true;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  bool splithere = false;
  std::string instructions{};
  size_t maxlen = 0;
  for (auto const& line : v)
  {
    if (splithere)
    {
      instructions = line;
      break;
    }

    if (line.size() > maxlen) maxlen = line.size();
    if (line != "") continue;
    else splithere = true;
  }
  v.pop_back();
  v.pop_back();
  for (auto& line : v)
  {
    while (line.size() < maxlen) line.push_back(' ');
    assert(line.size() == v[0].size());
  }

  H::SetN(v);
  int error = 0;
  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[0].size(); ++x)
    {
      if (v[y][x] != ' ')
      {
        Pos p{ x,y,3 };  // verify local - global conversions
        FaceID f = H::GetFaceID(x, y);
        LocalPos l = H::ToLocal(p);
        Pos p0 = H::ToGlobal(l, f);
        assert(p0 == p);
      }
    }
  }

  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[0].size(); ++x)
    {
      if (v[y][x] != ' ')
      {
        for (int o = 0; o < 4; ++o)  // verify back and forth is null move
        {
          const Pos p0{ x,y,o };
          Pos p1 = H::GetNextpos(v, p0);
          H::Revert(p1);
          Pos p2 = H::GetNextpos(v, p1);
          H::Revert(p2);

          if (p0 != p2)
          {
            ++error;
          }
          assert(p0 == p2);
        }
      }
    }
  }

  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[0].size(); ++x)
    {
      if (v[y][x] != ' ')
      {
        for (int o = 0; o < 4; ++o)  // verify back and forth is null move
        {
          const Pos p0{ x,y,o };
          Pos pN = p0;
          for (int n = 0; n < 4 * N; ++n)  // verify 4*N moves is null move
          {
            if ((n % N) == 49)
              ++error;
            pN = H::GetNextpos(v, pN);
            pN.o %= 4;
          }
          if (pN != p0)
          {
            ++error;
          }
          assert(pN == p0);
        }
      }
    }
  }

  Pos curr{ 0,0,0 };
  for (int x = 0; x < v[0].size(); ++x)
  {
    if (v[0][x] == '.')
    {
      curr.x = x;
      break;
    }
  }

  int n = 0;
  bool lastmove{ false };
  for (int i = 0; i < instructions.size(); ++i)
  {
    // read next instruction
    bool rotateleft{};
    switch (instructions[i])
    {
      case 'L': rotateleft = true; break;
      case 'R': rotateleft = false; break;

      default:
        assert(instructions[i] >= '0');
        assert(instructions[i] <= '9');
        n *= 10;
        n += instructions[i] - '0';
        if (i < instructions.size() - 1)
          continue;
        else
        {
          lastmove = true;
          break;
        }
    }

 //   std::cout << n << (rotateleft ? 'L' : 'R') << std::endl;
    // move

    for (int z = 0; z < n; ++z)
    {
      Pos next = H::GetNextpos(v, curr);
      next.o %= 4;
      if (v[next.y][next.x] == '.')
      {
        curr = next;
      }
      else if (v[next.y][next.x] == '#')
      {
        break;
      }
      else
      {
        assert(false);
      }
    }
    n = 0;

    // rotate
    if (!lastmove)
    {
      if (rotateleft) curr.o += 3;
      else ++curr.o;
    }
    curr.o %= 4;

    //    std::cout << "now at " << currx << ' ' << curry << ' '<< curro << std::endl;
    assert(curr.o >= 0 && curr.o <= 3);
  }

  int z = 4 * (curr.x + 1) + 1000 * (curr.y + 1) + curr.o;
  return z;
}
