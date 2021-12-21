void AoC2020_12A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  int x{ 0 };
  int y{ 0 };
  int d{ 0 };
  for (const auto& line : v)
  {
    std::istringstream str(line);

    char icode{ 0 };
    int amount{ 0 };
    str >> icode >> amount;

    switch (icode)
    {
      case 'N': y += amount; break;
      case 'S': y -= amount; break;
      case 'E': x += amount; break;
      case 'W': x -= amount; break;
      case 'L': d += amount; break;
      case 'R': d -= amount; break;
      case 'F':
        while (d < 0) d += 360;
        switch (d % 360)
        {
          case   0: x += amount; break;
          case  90: y += amount; break;
          case 180: x -= amount; break;
          case 270: y -= amount; break;
          default: break;
        }
        break;
      default: break;
    }
  }


  int z = abs(x) + abs(y);
  std::cout << z << std::endl;
}

void AoC2020_12B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  int x{ 0 };
  int y{ 0 };
  int wx{ 10 };
  int wy{ 1 };
  for (const auto& line : v)
  {
    std::istringstream str(line);

    char icode{ 0 };
    int amount{ 0 };
    str >> icode >> amount;

    switch (icode)
    {
      case 'N': wy += amount; break;
      case 'S': wy -= amount; break;
      case 'E': wx += amount; break;
      case 'W': wx -= amount; break;
      case 'R':
        amount = -amount;
        [[fallthrough]];
      case 'L':
        while (amount < 0) amount += 360;
        switch (amount % 360)
        {
          case   0: break;
          case  90: std::swap(wx, wy); wx = -wx; break;
          case 180: wx = -wx; wy = -wy; break;
          case 270: std::swap(wx, wy); wy = -wy; break;
          default: break;
        }
        break;
      case 'F':
        x += amount * wx;
        y += amount * wy;
        break;
      default: break;
    }
  }


  int z = abs(x) + abs(y);
  std::cout << z << std::endl;
}
