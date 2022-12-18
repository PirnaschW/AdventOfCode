
//template<> auto InputData<2022, 17, A>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };
//template<> auto InputData<2022, 17, B>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };

template<> Number AoC<2022, 17, A>(std::istream& input)
{
  std::string line{};
  std::string line2{};

  getline(input, line);
  getline(input, line2);
  assert(line2 == "");

  std::vector<std::array<bool, 7>> rows{};
  rows.resize(2022 * 13 / 5 + 10);

  struct pos
  {
    int x{ 0 };
    int y{ 0 };
  };
  struct Block
  {
    int dx{};
    int dy{};
    std::vector<pos> r{};
  };

  Block b1{ 4, 1, {{0,0},{1,0},{2,0},{3,0} } };
  Block b2{ 3, 3, {{1,0},{0,1},{1,1},{2,1},{1,2} } };
  Block b3{ 3, 3, {{0,0},{1,0},{2,0},{2,1},{2,2} } };
  Block b4{ 1, 4, {{0,0},{0,1},{0,2},{0,3} } };
  Block b5{ 2, 2, {{0,0},{1,0},{0,1},{1,1} } };
  std::vector<Block> b{ b1,b2,b3,b4,b5 };

  int currB{};
  int currL{};
  int maxY{ 0 };
  int currBlock{ -1 };
  int currJet{ -1 };
  int n = 0;
  while (++n <= 2022)
  {
    currB = maxY + 4;
    currL = 2;
    ++currBlock;
    currBlock %= b.size();
    while (true)
    {
      //{
      //  auto temp = rows;
      //  for (auto i = 0; i < b[currBlock].r.size(); ++i)
      //  {
      //    temp[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x] = true;
      //  }
      //  std::cout << std::endl;
      //  for (auto y = maxY + 8; y >= 0; --y)
      //  {
      //    for (auto x = 0; x < 7; ++x)
      //    {
      //      std::cout << (temp[y][x] ? '#' : '.');
      //    }
      //    std::cout << std::endl;
      //  }
      //}

      // apply Jet
      ++currJet;
      switch (line[currJet % line.size()])
      {
        case '>':
          if (currL + 1 + b[currBlock].dx <= 7)
          {
            bool shift = true;
            for (auto i = 0; i < b[currBlock].r.size(); ++i)
            {
              if (rows[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x + 1])
              {
                shift = false;
                break;
              }
            }
            if (shift)
              ++currL;
          }
          break;
        case '<':
          if (currL - 1 >= 0)
          {
            bool shift = true;
            for (auto i = 0; i < b[currBlock].r.size(); ++i)
            {
              if (rows[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x - 1])
              {
                shift = false;
                break;
              }
            }
            if (shift)
              --currL;
          }
          break;
        default:
          break;
      }

      // falling?
      bool fall = currB > 1;
      if (fall)
        for (auto i = 0; i < b[currBlock].r.size(); ++i)
        {
          if (rows[currB - 1 + b[currBlock].r[i].y][currL + b[currBlock].r[i].x])
          {
            fall = false;
            break;
          }
        }
      if (fall)
        currB--; // falling
      else  // settle
      {
        for (auto i = 0; i < b[currBlock].r.size(); ++i)
        {
          rows[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x] = true;
          if (currB + b[currBlock].r[i].y > maxY) maxY = currB + b[currBlock].r[i].y;
        }

        //std::cout << std::endl;
        //for (auto y = maxY+2; y >= 0; --y)
        //{
        //  for (auto x = 0; x < 7; ++x)
        //  {
        //    std::cout << (rows[y][x] ? '#' : '.');
        //  }
        //  std::cout << std::endl;
        //}

        break;
      }
    }
  }

  return maxY;
}

template<> Number AoC<2022, 17, B>(std::istream& input)
{
  std::string line{};
  getline(input, line);

  struct pos
  {
    int x{ 0 };
    int y{ 0 };
  };
  struct Block
  {
    int dx{};
    int dy{};
    std::vector<pos> r{};
  };

  const Block b1{ 4, 1, {{0,0},{1,0},{2,0},{3,0} } };
  const Block b2{ 3, 3, {{1,0},{0,1},{1,1},{2,1},{1,2} } };
  const Block b3{ 3, 3, {{0,0},{1,0},{2,0},{2,1},{2,2} } };
  const Block b4{ 1, 4, {{0,0},{0,1},{0,2},{0,3} } };
  const Block b5{ 2, 2, {{0,0},{1,0},{0,1},{1,1} } };
  const std::array b{ b1,b2,b3,b4,b5 };

  int currB{};
  int currL{};
  int maxY{ 0 };
  int currBlock{ -1 };
  int currJet{ -1 };

  // Periodicity
  const int PeriodicityTakeBaseline = 500;
  const int PeriodicityCompareRows = 20;
  const int PeriodicityMaxIntroRows = 3000;
  Number PeriodicityBaselineHeight{};
  Number PeriodicityBlocks{};  // to be calculated
  Number PeriodicityHeight{};  // to be calculated
  std::array<std::array<bool, 7>, PeriodicityCompareRows> PeriodicityBaseline{};
  Number PeriodocityExtraHeight{};
  bool PeriodicityFound = false;

  //std::vector<std::array<bool, 7>> rows{};
  //rows.resize(3 * PeriodicityMaxIntroRows + 2 * PeriodicityTakeBaseline);

  std::array<std::array<bool, 7>, 3 * PeriodicityMaxIntroRows + 2 * PeriodicityTakeBaseline> rows{};

  Number nMax = 1'000'000'000'000;
  Number n = 0;
  while (++n <= nMax)
  {
    // Periodicity
    if (n == PeriodicityTakeBaseline)
    { // save baseline
      PeriodicityBaselineHeight = maxY;
      for (auto i = 0; i < PeriodicityCompareRows; i++)
        PeriodicityBaseline[i] = rows[maxY - PeriodicityCompareRows + i];
    }
    if (!PeriodicityFound && n > PeriodicityTakeBaseline)
    {
      bool found = true;
      for (auto i = 0; i < PeriodicityCompareRows; i++)
      {
        if (PeriodicityBaseline[i] != rows[maxY - PeriodicityCompareRows + i])
        {
          found = false;
          break;
        }
      }
      if (found)
      {
        PeriodicityFound = true;
        PeriodicityBlocks = n - PeriodicityTakeBaseline;
        PeriodicityHeight = maxY - PeriodicityBaselineHeight;
        Number PeriodicityCount = (nMax - PeriodicityMaxIntroRows) / PeriodicityBlocks;

        n += PeriodicityCount * PeriodicityBlocks;                       // skip that many periods
        PeriodocityExtraHeight = PeriodicityCount * PeriodicityHeight;   // add the skipped elevation
      }
    }

    currB = maxY + 4;
    currL = 2;
    ++currBlock;
    currBlock %= b.size();
    while (true)
    {
      // Visualize while falling
      //{
      //  auto temp = rows;
      //  for (auto i = 0; i < b[currBlock].r.size(); ++i)
      //  {
      //    temp[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x] = true;
      //  }
      //  std::cout << std::endl;
      //  for (auto y = maxY + 8; y >= 0; --y)
      //  {
      //    for (auto x = 0; x < 7; ++x)
      //    {
      //      std::cout << (temp[y][x] ? '#' : '.');
      //    }
      //    std::cout << std::endl;
      //  }
      //}

      // apply Jet
      ++currJet;
      switch (line[currJet % line.size()])
      {
        case '>':
          if (currL + 1 + b[currBlock].dx <= 7)
          {
            bool shift = true;
            for (auto i = 0; i < b[currBlock].r.size(); ++i)
            {
              if (rows[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x + 1])
              {
                shift = false;
                break;
              }
            }
            if (shift)
              ++currL;
          }
          break;
        case '<':
          if (currL - 1 >= 0)
          {
            bool shift = true;
            for (auto i = 0; i < b[currBlock].r.size(); ++i)
            {
              if (rows[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x - 1])
              {
                shift = false;
                break;
              }
            }
            if (shift)
              --currL;
          }
          break;
        default:
          break;
      }

      // falling?
      bool fall = currB > 1;
      if (fall)
        for (auto i = 0; i < b[currBlock].r.size(); ++i)
        {
          if (rows[currB - 1 + b[currBlock].r[i].y][currL + b[currBlock].r[i].x])
          {
            fall = false;
            break;
          }
        }
      if (fall)
        currB--; // falling
      else  // settle
      {
        for (auto i = 0; i < b[currBlock].r.size(); ++i)
        {
          rows[currB + b[currBlock].r[i].y][currL + b[currBlock].r[i].x] = true;
          if (currB + b[currBlock].r[i].y > maxY) maxY = currB + b[currBlock].r[i].y;
        }

        // Visualize when settled
        //std::cout << std::endl;
        //for (auto y = maxY+2; y >= 0; --y)
        //{
        //  for (auto x = 0; x < 7; ++x)
        //  {
        //    std::cout << (rows[y][x] ? '#' : '.');
        //  }
        //  std::cout << std::endl;
        //}

        break;
      }
    }
  }

  return PeriodocityExtraHeight + maxY;
}
