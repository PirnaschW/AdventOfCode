void AoC2021_13A(std::istream& input)
{
  std::vector<std::vector<bool>> sheet{};
  sheet.resize(1400);
  for (auto& s : sheet) s.resize(900);

  std::string line{};
  int y{ 0 };
  int xmax{ 0 };
  int ymax{ 0 };
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    std::istringstream str(line);
    int x{ 0 };
    char dummy{};
    int y{ 0 };
    str >> x >> dummy >> y;
    sheet[x][y] = true;
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;
  }

  while (getline(input, line))
  {
    if (line.size() == 0) break;

    std::istringstream str(line.substr(11, 999));
    char c{};
    char dummy{};
    int fold{ 0 };
    str >> c >> dummy >> fold;

    switch (c)
    {
      case 'x':
        for (int x = 0; x < fold; ++x)
        {
          for (int y = 0; y < sheet[0].size(); ++y)
          {
            sheet[x][y] = sheet[x][y] || sheet[2 * fold - x][y];
            sheet[2 * fold - x][y] = false;
          }
        }
        break;
      case 'y':
        for (int y = 0; y < fold; ++y)
        {
          for (int x = 0; x < sheet.size(); ++x)
          {
            sheet[x][y] = sheet[x][y] || sheet[x][2 * fold - y];
            sheet[x][2 * fold - y] = false;
          }
        }
        break;
      default:
        break;
    }

    break; // only do one fold
  }

  int z{ 0 };
  for (int x = 0; x < sheet.size(); ++x)
  {
    for (int y = 0; y < sheet[0].size(); ++y)
    {
      if (sheet[x][y]) ++z;
    }
  }

  std::cout << z << std::endl;
}

void AoC2021_13B(std::istream& input)
{
  std::vector<std::vector<bool>> sheet{};
  sheet.resize(1400);
  for (auto& s : sheet) s.resize(900);

  std::string line{};
  int y{ 0 };
  int xmax{ 0 };
  int ymax{ 0 };
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    std::istringstream str(line);
    int x{ 0 };
    char dummy{};
    int y{ 0 };
    str >> x >> dummy >> y;
    sheet[x][y] = true;
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;
  }

  while (getline(input, line))
  {
    if (line.size() == 0) break;

    std::istringstream str(line.substr(11, 999));
    char c{};
    char dummy{};
    int fold{ 0 };
    str >> c >> dummy >> fold;

    switch (c)
    {
      case 'x':
        for (int x = 0; x < fold; ++x)
        {
          for (int y = 0; y < sheet[0].size(); ++y)
          {
            sheet[x][y] = sheet[x][y] || sheet[2 * fold - x][y];
            sheet[2 * fold - x][y] = false;
          }
        }
        xmax = fold;
        break;
      case 'y':
        for (int y = 0; y < fold; ++y)
        {
          for (int x = 0; x < sheet.size(); ++x)
          {
            sheet[x][y] = sheet[x][y] || sheet[x][2 * fold - y];
            sheet[x][2 * fold - y] = false;
          }
        }
        ymax = fold;
        break;
      default:
        break;
    }

  }

  for (int x = 0; x < xmax; ++x)
  {
    for (int y = 0; y < ymax; ++y)
    {
      if (sheet[x][y])
      {
        std::cout << 'x';
      }
      else
      {
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }
}
