void AoC2021_25A(std::istream& input)
{
  using Area = std::vector<std::string>;

  struct H
  {
    static bool MoveEast(Area& v)
    {
      auto v0 = v;
      bool moved = false;
      for (int y = 0; y < v.size(); ++y)
      {
        for (int x = 0; x < v[0].size(); ++x)
        {
          if (v[y][x] != '>') continue;
          int xx = (x == v[0].size() - 1) ? 0 : x + 1;
          if (v[y][xx] != '.') continue;
          std::swap(v0[y][x], v0[y][xx]);
          moved = true;
        }
      }
      std::swap(v0, v);
      return moved;
    }
    static bool MoveSouth(Area& v)
    {
      auto v0 = v;
      bool moved = false;
      for (int y = 0; y < v.size(); ++y)
      {
        for (int x = 0; x < v[0].size(); ++x)
        {
          if (v[y][x] != 'v') continue;
          int yy = (y == v.size() - 1) ? 0 : y + 1;
          if (v[yy][x] != '.') continue;
          std::swap(v0[yy][x], v0[y][x]);
          moved = true;
        }
      }
      std::swap(v0, v);
      return moved;
    }
    static void Print(const Area& v)
    {
      return;
      for (int y = 0; y < v.size(); ++y)
      {
        std::cout << v[y] << std::endl;
      }
      std::cout << std::endl;
    }

  };

  Area v = ReadLines(input);

  bool moved = false;
  int z{ 0 };
  H::Print(v);
  do
  {
    moved = false;
    moved |= H::MoveEast(v);
    moved |= H::MoveSouth(v);
    H::Print(v);
    ++z;
  } while (moved);

  std::cout << z << std::endl;
}

void AoC2021_25B(std::istream& input)
{
}
