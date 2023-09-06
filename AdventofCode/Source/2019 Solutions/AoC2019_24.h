//template<> auto InputData<2019, 24, A>() { return "....#\n#..#.\n#..##\n..#..\n#....\n";}; // Result: 2129920
template<> Number AoC<2019, 24, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Coord = int;
  constexpr Coord sx{ 5 };
  constexpr Coord sy{ 5 };
  using Area = std::array<std::array<bool, sx>, sy>;


  class Eris
  {
  public:
    Eris() = delete;
    Eris(const Input& v)
    {
      for (auto y = 0; y < sy; ++y)
      {
        for (auto x = 0; x < sx; ++x)
        {
          area_[y][x] = (v[y][x] == '#');
        }
      }
    }
    Number GetValue() const noexcept
    {
      Number res{ 0 };
      Number add{ 1 };
      for (auto y = 0; y < sy; ++y)
      {
        for (auto x = 0; x < sx; ++x)
        {
          if (area_[y][x]) res += add;
          add <<= 1;
        }
      }
      return res;
    }
    void Iterate() noexcept
    {
      Area newarea{};
      for (auto y = 0; y < sy; ++y)
      {
        for (auto x = 0; x < sx; ++x)
        {
          char s{ 0 };
          if (GetAt(x - 1, y + 0)) ++s;
          if (GetAt(x + 1, y + 0)) ++s;
          if (GetAt(x + 0, y + 1)) ++s;
          if (GetAt(x + 0, y - 1)) ++s;

          if (GetAt(x, y)) newarea[y][x] = s == 1;
          else newarea[y][x] = (s == 1 || s == 2);
        }
      }
      std::swap(newarea, area_);
    }
  private:
    bool GetAt(Coord x, Coord y)
    {
      if (x < 0 || x >= sx || y < 0 || y >= sy) return false;
      return area_[y][x];
    }
  private:
    Area area_{true};
  };

  std::unordered_set<Number> states{};
  Eris e(v);

  while (true)
  {
    Number biodiversity = e.GetValue();
    if (states.contains(biodiversity))
      return biodiversity;
    states.insert(biodiversity);
    e.Iterate();
  }

  throw "Error";
}

//template<> auto InputData<2019, 24, B>() { return "....#\n#..#.\n#..##\n..#..\n#....\n10\n";}; // Result: 99
template<> Number AoC<2019, 24, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  int MinuteCount = 200;
  if (v.size() > 5)
  { // it's a testcase
    std::stringstream s(v[v.size() - 1]);
    s >> MinuteCount;
    v.pop_back();
  }

  using Coord = int;
  constexpr Coord sx{ 5 };            // size x
  constexpr Coord sy{ 5 };            // size y
  const Coord sz{ MinuteCount + 5 };  // size z
  constexpr Coord cx{ sx / 2 };       // center x
  constexpr Coord cy{ sy / 2 };       // center y
  const Coord cz{ sz / 2 };           // center z
  using Area = std::array<std::array<int, sx>, sy>;
  using Areas = std::vector<Area>;

  enum class Direction
  {
    N,
    S,
    E,
    W,
  };
  class Eris
  {
  public:
    Eris() = delete;
    Eris(const Input& v, Number minutes, Coord sz, Coord cz) : minutes_(minutes), sz_(sz), cz_(cz)
    {
      areas_.resize(sz_);
      for (int i = 0; i < sz_; ++i)
      {
        areas_[i] = Area();
      }

      // seed input data to center level
      for (auto y = 0; y < sy; ++y)
      {
        for (auto x = 0; x < sx; ++x)
        {
          areas_[cz_][y][x] = (v[y][x] == '#');
        }
      }
    }
    Number GetBugCount() const noexcept
    {
      Number count{ 0 };
      for (auto z = 0; z < sz_; ++z)
      {
        for (auto y = 0; y < sy; ++y)
        {
          for (auto x = 0; x < sx; ++x)
          {
            if (x == cx && y == cy) continue;  // ignore center fields
            if (areas_[z][y][x]) ++count;
          }
        }
      }
      return count;
    }
    void Iterate() noexcept
    {
      Areas newareas{ areas_ };
      for (auto z = 1; z < sz_ - 1; ++z)
      {
        for (auto y = 0; y < sy; ++y)
        {
          for (auto x = 0; x < sx; ++x)
          {
            int s{ 0 };
            s += GetAt(x - 1, y + 0, z, Direction::W);
            s += GetAt(x + 1, y + 0, z, Direction::E);
            s += GetAt(x + 0, y + 1, z, Direction::S);
            s += GetAt(x + 0, y - 1, z, Direction::N);

            if (s > 0)
            {
              int b = 0;
            }
            if (areas_[z][y][x])
            {
              newareas[z][y][x] = s == 1 ? 1 : 0;
            }
            else
            {
              newareas[z][y][x] = (s == 1 || s == 2) ? 1 : 0;
            }
          }
        }
      }
      std::swap(newareas, areas_);
    }

  private:
    int GetAt(Coord x, Coord y, Coord z, Direction d)
    {
      assert(x >= -1 && x <= sx);
      assert(y >= -1 && y <= sy);
      assert(z > 0 && z < sz_-1);

      if (x == -1)
      {
        assert(d == Direction::W);
        assert(y >= 0 && y < sy);
        return areas_[z + 1][cy][cx-1];
      }
      if (x == sx)
      {
        assert(d == Direction::E);
        assert(y >= 0 && y < sy);
        return areas_[z + 1][cy][cx+1];
      }

      if (y == -1)
      {
        assert(d == Direction::N);
        assert(x >= 0 && x < sx);
        return areas_[z + 1][cy-1][cx];
      }
      if (y == sy)
      {
        assert(d == Direction::S);
        assert(x >= 0 && x < sx);
        return areas_[z + 1][cy+1][cx];
      }

      if (x == cx && y == cy)
      {
        int s{ 0 };
        switch (d)
        {
          case Direction::E:
          case Direction::W:
            for (auto y0 = 0; y0 < sy; ++y0)
            {
              s += areas_[z - 1][y0][d == Direction::W ? sx - 1 : 0];
            }
            return s;
          case Direction::N:
          case Direction::S:
            for (auto x0 = 0; x0 < sx; ++x0)
            {
              s += areas_[z - 1][d == Direction::S ? 0 : sy - 1][x0];
            }
            return s;
          default:
            assert(false);
        }
      }

      return areas_[z][y][x];
    }

  private:
    const Number minutes_{};
    const Number sz_{};
    const Number cz_{};
    Areas areas_{};
  };

  Eris e(v, MinuteCount, sz, cz);

  for (auto i = 0; i < MinuteCount; ++i)
  {
    e.Iterate();
  }
  Number res = e.GetBugCount();

  return res;
}
