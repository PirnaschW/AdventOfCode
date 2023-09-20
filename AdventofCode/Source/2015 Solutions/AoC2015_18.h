//template<> auto InputData<2015, 18, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 18, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  constexpr int xSize{ 100 };
  constexpr int ySize{ 100 };
  using Lights = std::array<std::array<bool, xSize>, ySize>;
  Lights light{};

  auto Set = [&light, &v]() -> void
    {
      for (int x = 0; x < light.size(); ++x)
      {
        for (int y = 0; y < light[0].size(); ++y)
        {
          light[x][y] = v[y][x] == '#';
        }
      }
    };

  auto GetAt = [&light](int x, int y) -> int
    {
      if (x < 0 || x >= light.size()) return 0;
      if (y < 0 || y >= light[0].size()) return 0;
      return light[x][y] ? 1 : 0;
    };
  auto GetAround = [&light, &GetAt](int x, int y) -> int
    {
      return
        GetAt(x + 1, y + 0) +
        GetAt(x + 1, y + 1) +
        GetAt(x + 0, y + 1) +
        GetAt(x - 1, y + 1) +
        GetAt(x - 1, y + 0) +
        GetAt(x - 1, y - 1) +
        GetAt(x + 0, y - 1) +
        GetAt(x + 1, y - 1);
    };

  auto Iterate = [&light, &GetAround]() -> void
    {
      Lights light0{ false };
      for (int x = 0; x < light.size(); ++x)
      {
        for (int y = 0; y < light[0].size(); ++y)
        {
          int z = GetAround(x, y);
          if (light[x][y])
          {
            switch (z)
            {
              case 2:
              case 3:
                light0[x][y] = true;
                break;
              default: 
                light0[x][y] = false;
                break;
            }
          }
          else
          {
            switch (z)
            {
              case 3:
                light0[x][y] = true;
                break;
              default: 
                light0[x][y] = false;
                break;
            }
          }
        }
      }
      std::swap(light, light0);
    };

  auto Count = [&light, &GetAt]() -> int
    {
      int z{ 0 };
      for (int x = 0; x < light.size(); ++x)
      {
        for (int y = 0; y < light[0].size(); ++y)
        {
          z += GetAt(x, y);
        }
      }
      return z;
    };


  Set();
  for (int i = 0; i < 100; ++i)
  {
    Iterate();
  }
  int res = Count();

  return res;
}

//template<> auto InputData<2015, 18, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 18, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  constexpr int xSize{ 100 };
  constexpr int ySize{ 100 };
  using Lights = std::array<std::array<bool, xSize>, ySize>;
  Lights light{};

  auto Set = [&light, &v]() -> void
    {
      for (int x = 0; x < light.size(); ++x)
      {
        for (int y = 0; y < light[0].size(); ++y)
        {
          light[x][y] = v[y][x] == '#';
        }
      }
    };

  auto GetAt = [&light](int x, int y) -> int
    {
      if (x < 0 || x >= light.size()) return 0;
      if (y < 0 || y >= light[0].size()) return 0;
      return light[x][y] ? 1 : 0;
    };
  auto GetAround = [&light, &GetAt](int x, int y) -> int
    {
      return
        GetAt(x + 1, y + 0) +
        GetAt(x + 1, y + 1) +
        GetAt(x + 0, y + 1) +
        GetAt(x - 1, y + 1) +
        GetAt(x - 1, y + 0) +
        GetAt(x - 1, y - 1) +
        GetAt(x + 0, y - 1) +
        GetAt(x + 1, y - 1);
    };

  auto Iterate = [&light, &GetAround]() -> void
    {
      Lights light0{ false };
      for (int x = 0; x < light.size(); ++x)
      {
        for (int y = 0; y < light[0].size(); ++y)
        {
          int z = GetAround(x, y);
          if (light[x][y])
          {
            switch (z)
            {
              case 2:
              case 3:
                light0[x][y] = true;
                break;
              default: 
                light0[x][y] = false;
                break;
            }
          }
          else
          {
            switch (z)
            {
              case 3:
                light0[x][y] = true;
                break;
              default: 
                light0[x][y] = false;
                break;
            }
          }
        }
      }
      std::swap(light, light0);
    };

  auto Count = [&light, &GetAt]() -> int
    {
      int z{ 0 };
      for (int x = 0; x < light.size(); ++x)
      {
        for (int y = 0; y < light[0].size(); ++y)
        {
          z += GetAt(x, y);
        }
      }
      return z;
    };

  auto Stuck = [&light]() -> void
    {
      light[0]             [0]                 = true;
      light[light.size()-1][0]                 = true;
      light[0]             [light[0].size()-1] = true;
      light[light.size()-1][light[0].size()-1] = true;
    };


  Set();
  for (int i = 0; i < 100; ++i)
  {
    Iterate();
    Stuck();
  }
  int res = Count();

  return res;
}
