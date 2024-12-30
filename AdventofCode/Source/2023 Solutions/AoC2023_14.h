//template<> auto InputData<2023, 14, A>() { return
//"O....#....\n"
//"O.OO#....#\n"
//".....##...\n"
//"OO.#O....O\n"
//".O.....O#.\n"
//"O.#..O.#.#\n"
//"..O..#O..O\n"
//".......O..\n"
//"#....###..\n"
//"#OO..#....\n";}; // Result: 136
template<> Number AoC<2023, 14, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  for (int x = 0; x < std::ssize(v[0]); ++x)
  {
    int rollto = { 0 };
    for (int y = 0; y < std::ssize(v); ++y)
    {
      switch (v[y][x])
      {
        case '#':
          rollto = y + 1;
          break;
        case '.':
          break;
        case 'O':
          if (rollto < y)
          {
            std::swap(v[rollto][x], v[y][x]);
          }
          ++rollto;
          break;
      }
    }
  }

  Number res{ 0 };
  for (int x = 0; x < std::ssize(v[0]); ++x)
  {
    for (int y = 0; y < std::ssize(v); ++y)
    {
      if (v[y][x] == 'O')
        res += std::ssize(v) - y;
    }
  }
  return res;
}

//template<> auto InputData<2023, 14, B>() { return
//"O....#....\n"
//"O.OO#....#\n"
//".....##...\n"
//"OO.#O....O\n"
//".O.....O#.\n"
//"O.#..O.#.#\n"
//"..O..#O..O\n"
//".......O..\n"
//"#....###..\n"
//"#OO..#....\n";}; // Result: 64
template<> Number AoC<2023, 14, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto RollN = [](Input v) -> Input
    {
      for (int x = 0; x < std::ssize(v[0]); ++x)
      {
        for (int y = 0, rollto = y; y < std::ssize(v); ++y)
        {
          switch (v[y][x])
          {
            case '#':
              rollto = y + 1;
              break;
            case '.':
              break;
            case 'O':
              if (rollto < y)
              {
                std::swap(v[rollto][x], v[y][x]);
              }
              ++rollto;
              break;
          }
        }
      }
      return v;
    };
  auto RollS = [](Input v) -> Input
    {
      for (int x = 0; x < std::ssize(v[0]); ++x)
      {
        for (int y = std::ssize(v) - 1, rollto = y; y >= 0; --y)
        {
          switch (v[y][x])
          {
            case '#':
              rollto = y - 1;
              break;
            case '.':
              break;
            case 'O':
              if (rollto > y)
              {
                std::swap(v[rollto][x], v[y][x]);
              }
              --rollto;
              break;
          }
        }
      }
      return v;
    };
  auto RollW = [](Input v) -> Input
    {
      for (int y = 0; y < std::ssize(v); ++y)
      {
        for (int x = 0, rollto = x; x < std::ssize(v[0]); ++x)
        {
          switch (v[y][x])
          {
            case '#':
              rollto = x + 1;
              break;
            case '.':
              break;
            case 'O':
              if (rollto < x)
              {
                std::swap(v[y][rollto], v[y][x]);
              }
              ++rollto;
              break;
          }
        }
      }
      return v;
    };
  auto RollE = [](Input v) -> Input
    {
      for (int y = 0; y < std::ssize(v); ++y)
      {
        for (int x = std::ssize(v[0]) - 1, rollto = x; x >= 0; --x)
        {
          switch (v[y][x])
          {
            case '#':
              rollto = x - 1;
              break;
            case '.':
              break;
            case 'O':
              if (rollto > x)
              {
                std::swap(v[y][rollto], v[y][x]);
              }
              --rollto;
              break;
          }
        }
      }
      return v;
    };
  auto GetLoad = [](const Input& v) -> Number
    {
      Number load{ 0 };
      for (int x = 0; x < std::ssize(v[0]); ++x)
      {
        for (int y = 0; y < std::ssize(v); ++y)
        {
          if (v[y][x] == 'O')
            load += std::ssize(v) - y;
        }
      }
      return load;
    };
  auto GetOneString = [](const Input& v) -> std::string
    {
      std::string s{};
      for (const auto& line : v)
        s.append(line);
      return s;
    };
  std::vector<std::string> vHistory{};
  std::vector<Number> lHistory{};
  int Count{ 1'000'000'000 };
  for (int z = 0; z < Count; ++z)
  {
    v = RollN(v);
    v = RollW(v);
    v = RollS(v);
    v = RollE(v);

    std::string s = GetOneString(v);
    for (int i = 0; i < std::ssize(vHistory); ++i)
    {
      if (s == vHistory[i]) // found period!
      {
        int final = i + (Count - z - 1) % (z - i);
        return lHistory[final];
      }
    }
    lHistory.push_back(GetLoad(v));
    vHistory.push_back(s);
  }
  assert(false);
  return 0;
}
