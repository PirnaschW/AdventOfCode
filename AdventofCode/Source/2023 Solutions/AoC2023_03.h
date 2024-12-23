//template<> auto InputData<2023, 3, A>()
//  {
//    return
//      "467..114..\n"
//      "...*......\n"
//      "..35..633.\n"
//      "......#...\n"
//      "617*......\n"
//      ".....+.58.\n"
//      "..592.....\n"
//      "......755.\n"
//      "...$.*....\n"
//      ".664.598..\n";
//  }; // Result: 4361
template<> Number AoC<2023, 3, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  auto IsSymbol = [&v](Number x, Number y) -> bool
    {
      if (x < 0) return false;
      if (x >= v[0].size()) return false;
      if (y < 0) return false;
      if (y >= v.size()) return false;

      if (v[y][x] == '.' || isdigit(v[y][x])) return false;
      return true;
    };
  auto HasSymbol = [&v,&IsSymbol](Number x, Number y, Number d) -> bool
    {
      for (Number i = x - d - 1; i <= x; ++i)
        for (Number j = y - 1; j <= y + 1; ++j)
          if (IsSymbol(i, j)) return true;
      return false;
    };

  Number total{0};  // accumulated total
  Number z{0};  // number found
  Number d{0};  // digit count
  for (size_t y = 0; y < v.size(); y++)
  {
    for (size_t x = 0; x < v[y].size(); x++)
    {
      switch (v[y][x])
      {
        case '0': [[fallthrough]];
        case '1': [[fallthrough]];
        case '2': [[fallthrough]];
        case '3': [[fallthrough]];
        case '4': [[fallthrough]];
        case '5': [[fallthrough]];
        case '6': [[fallthrough]];
        case '7': [[fallthrough]];
        case '8': [[fallthrough]];
        case '9':
          z *= 10;
          z += v[y][x] - '0';
          ++d;
          break;
        case '.': [[fallthrough]];
        default:
          if (d > 0)
          {
            if (HasSymbol(x, y, d))
            {
              total += z;
            }
          }
          z = d = 0;
          break;
      }
    }

    // reached end of line, reset
    if (d > 0)
    {
      if (HasSymbol(v[y].size(), y, d))
      {
        total += z;
      }
    }
    z = d = 0;
  }

  return total;
}

//template<> auto InputData<2023, 3, B>()
//  {
//    return
//      "467..114..\n"
//      "...*......\n"
//      "..35..633.\n"
//      "......#...\n"
//      "617*......\n"
//      ".....+.58.\n"
//      "..592.....\n"
//      "......755.\n"
//      "...$.*....\n"
//      ".664.598..\n";
//  }; // Result: 467835
template<> Number AoC<2023, 3, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Gear
  {
  public:
    Number x{ -1 };
    Number y{ -1 };
    int count{ 0 };
    Number ratio{ 1 };
  };
  std::vector<Gear> g{};

  auto IsStarSymbol = [&v](Number x, Number y) -> bool
    {
      if (x < 0) return false;
      if (x >= v[0].size()) return false;
      if (y < 0) return false;
      if (y >= v.size()) return false;

      if (v[y][x] == '*') return true;
      return false;
    };
  auto HasStarSymbol = [&v,&IsStarSymbol](Number& x, Number& y, Number d) -> bool
    {
      for (Number i = x - d - 1; i <= x; ++i)
        for (Number j = y - 1; j <= y + 1; ++j)
          if (IsStarSymbol(i, j))
          {
            x = i;
            y = j;
            return true;
          }
      return false;
    };

  auto LogGear = [&g,&HasStarSymbol](Number& d, Number& z, Number x, Number y) -> void
    {
      if (d > 0)
      {
        if (HasStarSymbol(x, y, d))
        {
          bool notfound{ true };
          for (size_t i = 0; i < g.size(); ++i)
          {
            if (g[i].x == x && g[i].y == y)
            {
              ++g[i].count;
              g[i].ratio *= z;
              notfound = false;
              break;
            }
          }
          if (notfound)
            g.push_back({ x, y, 1, z });
        }
      }
      z = d = 0;

    };

  Number z{0};  // number found
  Number d{0};  // digit count
  for (size_t y = 0; y < v.size(); y++)
  {
    for (size_t x = 0; x < v[y].size(); x++)
    {
      switch (v[y][x])
      {
        case '0': [[fallthrough]];
        case '1': [[fallthrough]];
        case '2': [[fallthrough]];
        case '3': [[fallthrough]];
        case '4': [[fallthrough]];
        case '5': [[fallthrough]];
        case '6': [[fallthrough]];
        case '7': [[fallthrough]];
        case '8': [[fallthrough]];
        case '9':
          z *= 10;
          z += v[y][x] - '0';
          ++d;
          break;
        case '.': [[fallthrough]];
        default:
          LogGear(d, z, x, y);
          break;
      }
    }

    // reached end of line, reset
    LogGear(d, z, v[y].size(), y);
  }

  Number result{0};
  for (size_t i = 0; i < g.size(); ++i)
  {
    if (g[i].count == 2)
    {
      result += g[i].ratio;
    }
  }

  return result;
}
