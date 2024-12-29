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


  auto IsSymbol = [&v](int x, int y) -> bool
    {
      if (x < 0) return false;
      if (x >= static_cast<int>(v[0].size())) return false;
      if (y < 0) return false;
      if (y >= static_cast<int>(v.size())) return false;

      if (v[y][x] == '.' || isdigit(v[y][x])) return false;
      return true;
    };
  auto HasSymbol = [&v,&IsSymbol](int x, int y, int d) -> bool
    {
      for (int i = x - d - 1; i <= x; ++i)
        for (int j = y - 1; j <= y + 1; ++j)
          if (IsSymbol(i, j)) return true;
      return false;
    };

  Number total{0};  // accumulated total
  Number z{0};  // number found
  int d{0};  // digit count
  for (int y = 0; y < std::ssize(v); y++)
  {
    for (int x = 0; x < std::ssize(v[y]); x++)
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
      if (HasSymbol(static_cast<int>(std::ssize(v[y])), y, d))
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

  auto IsStarSymbol = [&v](int x, int y) -> bool
    {
      if (x < 0) return false;
      if (x >= static_cast<int>(v[0].size())) return false;
      if (y < 0) return false;
      if (y >= static_cast<int>(v.size())) return false;

      if (v[y][x] == '*') return true;
      return false;
    };
  auto HasStarSymbol = [&v,&IsStarSymbol](int& x, int& y, int d) -> bool
    {
      for (int i = x - d - 1; i <= x; ++i)
        for (int j = y - 1; j <= y + 1; ++j)
          if (IsStarSymbol(i, j))
          {
            x = i;
            y = j;
            return true;
          }
      return false;
    };

  auto LogGear = [&g,&HasStarSymbol](int& d, Number& z, int x, int y) -> void
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
  int d{0};  // digit count
  for (int y = 0; y < std::ssize(v); y++)
  {
    for (int x = 0; x < std::ssize(v[y]); x++)
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
    LogGear(d, z, static_cast<int>(std::ssize(v[y])), y);
  }

  Number result{0};
  for (int i = 0; i < std::ssize(g); ++i)
  {
    if (g[i].count == 2)
    {
      result += g[i].ratio;
    }
  }

  return result;
}
