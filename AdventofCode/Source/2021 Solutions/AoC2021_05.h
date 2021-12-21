void AoC2021_05B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  char board[1000][1000]{ 0 };

  for (const auto& line : v)
  {
    std::istringstream str(line);
    int x1, x2, y1, y2;
    char comma;
    std::string arrow;
    str >> x1 >> comma >> y1 >> arrow >> x2 >> comma >> y2;

    if (x1 != x2 && y1 != y2)
    {
      if (x1 > x2) { std::swap(x1, x2); std::swap(y1, y2); }
      for (int x = x1; x <= x2; ++x)
      {
        if (y1 > y2) ++board[x][y1 + x1 - x];
        else ++board[x][y1 + x - x1];
      }
    }
    else
    {
      if (x1 > x2) { std::swap(x1, x2); }
      if (y1 > y2) { std::swap(y1, y2); }
      for (int x = x1; x <= x2; ++x)
        for (int y = y1; y <= y2; ++y)
          ++board[x][y];
    }
  }

  int z{ 0 };
  for (int x = 0; x < 1000; ++x)
    for (int y = 0; y < 1000; ++y)
    {
      if (board[x][y] > 1)++z;
    }

  std::cout << z << std::endl;

}



void AoC2021_05A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  char board[1000][1000]{ 0 };

  for (const auto& line : v)
  {
    std::istringstream str(line);
    int x1, x2, y1, y2;
    char comma;
    std::string arrow;
    str >> x1 >> comma >> y1 >> arrow >> x2 >> comma >> y2;
    if (x1 > x2) { std::swap(x1, x2); }
    if (y1 > y2) { std::swap(y1, y2); }

    if (x1 != x2 && y1 != y2) continue;

    for (int x = x1; x <= x2; ++x)
      for (int y = y1; y <= y2; ++y)
        ++board[x][y];
  }

  int z{ 0 };
  for (int x = 0; x < 1000; ++x)
    for (int y = 0; y < 1000; ++y)
    {
      if (board[x][y] > 1)++z;
    }

  std::cout << z << std::endl;
}
