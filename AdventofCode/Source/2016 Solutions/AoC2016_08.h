//template<> auto InputData<2016, 8, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 8, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  constexpr int xSize{ 50 };
  constexpr int ySize{ 6 };
  using Row = std::array<bool, xSize>;
  using Col = std::array<bool, ySize>;
  using Display = std::array<std::array<bool, ySize>, xSize>;  // use Display[x][y]

  Display display{ false };
  auto ShiftRow = [&display](int y, int count) -> void
    {
      Row row{};
      for (int i = 0; i < xSize; ++i)
      {
        row[(i + count) % xSize] = display[i][y];
      }
      for (int i = 0; i < xSize; ++i)
      {
        display[i][y] = row[i];
      }
    };
  auto ShiftCol = [&display](int x, int count) -> void
    {
      Col col{};
      for (int i = 0; i < ySize; ++i)
      {
        col[(i + count) % ySize] = display[x][i];
      }
      std::swap(display[x], col);
    };
  auto Set = [&display](int x, int y) -> void
    {
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; ++j)
        {
          display[i][j] = true;
        }
      }
    };
  auto Count = [&display]() -> int
    {
      int n{ 0 };
      for (int i = 0; i < xSize; ++i)
      {
        for (int j = 0; j < ySize; ++j)
        {
          if (display[i][j]) ++n;
        }
      }
      return n;
    };

  for (const auto& line : v)
  {
    // rect AxB
    // rotate row y=A by B
    // rotate column x=A by B
    int x{ 0 };
    int y{ 0 };
    int z1 = sscanf_s(line.c_str(), "rect %dx%d", &x, &y);
    if (z1 == 2)
    {
      Set(x, y);
      continue;
    }

    int z2 = sscanf_s(line.c_str(), "rotate row y=%d by %d", &y, &x);
    if (z2 == 2)
    {
      ShiftRow(y, x);
      continue;
    }

    int z3 = sscanf_s(line.c_str(), "rotate column x=%d by %d", &x, &y);
    if (z3 == 2)
    {
      ShiftCol(x, y);
      continue;
    }
    assert(false);
  }

  int n = Count();
  return n;
}

//template<> auto InputData<2016, 8, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 8, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  constexpr int xSize{ 50 };
  constexpr int ySize{ 6 };
  using Row = std::array<bool, xSize>;
  using Col = std::array<bool, ySize>;
  using Display = std::array<std::array<bool, ySize>, xSize>;  // use Display[x][y]

  Display display{ false };
  auto ShiftRow = [&display](int y, int count) -> void
    {
      Row row{};
      for (int i = 0; i < xSize; ++i)
      {
        row[(i + count) % xSize] = display[i][y];
      }
      for (int i = 0; i < xSize; ++i)
      {
        display[i][y] = row[i];
      }
    };
  auto ShiftCol = [&display](int x, int count) -> void
    {
      Col col{};
      for (int i = 0; i < ySize; ++i)
      {
        col[(i + count) % ySize] = display[x][i];
      }
      std::swap(display[x], col);
    };
  auto Set = [&display](int x, int y) -> void
    {
      for (int i = 0; i < x; ++i)
      {
        for (int j = 0; j < y; ++j)
        {
          display[i][j] = true;
        }
      }
    };
  auto Count = [&display]() -> int
    {
      int n{ 0 };
      for (int i = 0; i < xSize; ++i)
      {
        for (int j = 0; j < ySize; ++j)
        {
          if (display[i][j]) ++n;
        }
      }
      return n;
    };
  auto Print = [&display]() -> void
    {
      std::cout << std::endl;
      for (int j = 0; j < ySize; ++j)
      {
        for (int i = 0; i < xSize; ++i)
        {
          std::cout << (display[i][j] ? '#' : '.');
        }
        std::cout << std::endl;
      }
    };

  for (const auto& line : v)
  {
    // rect AxB
    // rotate row y=A by B
    // rotate column x=A by B
    int x{ 0 };
    int y{ 0 };
    int z1 = sscanf_s(line.c_str(), "rect %dx%d", &x, &y);
    if (z1 == 2)
    {
      Set(x, y);
      continue;
    }

    int z2 = sscanf_s(line.c_str(), "rotate row y=%d by %d", &y, &x);
    if (z2 == 2)
    {
      ShiftRow(y, x);
      continue;
    }

    int z3 = sscanf_s(line.c_str(), "rotate column x=%d by %d", &x, &y);
    if (z3 == 2)
    {
      ShiftCol(x, y);
      continue;
    }
    assert(false);
  }

  Print();
  throw "?";
}
