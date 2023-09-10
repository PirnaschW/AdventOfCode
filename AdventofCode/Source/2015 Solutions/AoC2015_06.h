//template<> auto InputData<2015, 6, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 6, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr Number xmax{ 1000 };
  constexpr Number ymax{ 1000 };
  std::array<std::array<bool, xmax>, ymax> light{};

  for (const auto& line : v)
  {
    int x1{ 0 };
    int x2{ 0 };
    int y1{ 0 };
    int y2{ 0 };
    // turn on 0,0 through 999,999
    // toggle 0,0 through 999,0
    // turn off 499,499 through 500,500
    if (sscanf_s(line.c_str(), "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2) == 4)
    {
      for (auto x = x1; x <= x2; ++x)
      {
        for (auto y = y1; y <= y2; ++y)
        {
          light[y][x] = true;
        }
      }
    }
    else if (sscanf_s(line.c_str(), "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2) == 4)
    {
      for (auto x = x1; x <= x2; ++x)
      {
        for (auto y = y1; y <= y2; ++y)
        {
          light[y][x] = false;
        }
      }
    }
    else if (sscanf_s(line.c_str(), "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2) == 4)
    {
      for (auto x = x1; x <= x2; ++x)
      {
        for (auto y = y1; y <= y2; ++y)
        {
          light[y][x] = !light[y][x];
        }
      }
    }
    else
      assert(false);
  }

  Number z{ 0 };
  for (auto x = 0; x < xmax; ++x)
  {
    for (auto y = 0; y < ymax; ++y)
    {
      if (light[y][x]) ++z;
    }
  }
  return z;
}

//template<> auto InputData<2015, 6, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 6, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr Number xmax{ 1000 };
  constexpr Number ymax{ 1000 };
  using Brightness = unsigned char;

  using LightArray = std::array<std::array<Brightness, xmax>, ymax>;
  LightArray& light = *(new LightArray());

  constexpr Brightness max = std::numeric_limits<Brightness>::max();
  for (const auto& line : v)
  {
    int x1{ 0 };
    int x2{ 0 };
    int y1{ 0 };
    int y2{ 0 };
    // turn on 0,0 through 999,999
    // toggle 0,0 through 999,0
    // turn off 499,499 through 500,500
    if (sscanf_s(line.c_str(), "turn on %d,%d through %d,%d", &x1, &y1, &x2, &y2) == 4)
    {
      for (auto x = x1; x <= x2; ++x)
      {
        for (auto y = y1; y <= y2; ++y)
        {
          ++light[y][x];
          assert(light[y][x] < max);
        }
      }
    }
    else if (sscanf_s(line.c_str(), "turn off %d,%d through %d,%d", &x1, &y1, &x2, &y2) == 4)
    {
      for (auto x = x1; x <= x2; ++x)
      {
        for (auto y = y1; y <= y2; ++y)
        {
          if (light[y][x] > 0) --light[y][x];
        }
      }
    }
    else if (sscanf_s(line.c_str(), "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2) == 4)
    {
      for (auto x = x1; x <= x2; ++x)
      {
        for (auto y = y1; y <= y2; ++y)
        {
          light[y][x] += 2;
        }
      }
    }
    else
      assert(false);
  }

  Number z{ 0 };
  for (auto x = 0; x < xmax; ++x)
  {
    for (auto y = 0; y < ymax; ++y)
    {
      z += light[y][x];
    }
  }

  delete &light;
  return z;
}
