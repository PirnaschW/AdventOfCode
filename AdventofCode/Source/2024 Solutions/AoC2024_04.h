//template<> auto InputData<2024, 4, A>() { return
//"MMMSXXMASM\n"
//"MSAMXMSMSA\n"
//"AMXSXMAAMM\n"
//"MSAMASMSMX\n"
//"XMASAMXAMM\n"
//"XXAMMXXAMA\n"
//"SMSMSASXSS\n"
//"SAXAMASAAA\n"
//"MAMMMXMMMM\n"
//"MXMXAXMASX\n";}; // Result: 18
template<> Number AoC<2024, 4, A>(std::istream& input)
{
  Input v = ReadLines(input);  // read all lines into vector

  using namespace Coord2D;

  V2D v2d(v);

  constexpr char target[] = "XMAS";
  constexpr Coord tlen = sizeof target - 1;

  auto Match = [&v2d,&target,&tlen](Point p, Direction d) -> bool
    {
      for (int i = 0; i < tlen; ++i)
      {
        if (v2d.GetChar(p + d * i) != target[i]) return false;
      }
      return true;
    };
  auto FindAll = [&v2d,&target,&tlen,&Match](Point p, Direction d) -> Number
    {
      Number count{ 0 };
      while (v2d.IsValid(p) && v2d.IsValid(p + d * (tlen - 1)))
      {
        if (Match(p, d))
          ++count;
        p += d;
      }
      return count;
    };

  Number res{0};
  for (Coord y = 0; y < std::ssize(v); ++y)
  {
    res += FindAll(Point(0, y), GoRight);
    res += FindAll(Point(v2d.SizeX() - 1, y), GoLeft);

    res += FindAll(Point(0, y), GoDownRight);
    res += FindAll(Point(v2d.SizeX() - 1, y), GoUpLeft);

    res += FindAll(Point(v2d.SizeX()-1, y), GoDownLeft);
    res += FindAll(Point(0, y), GoUpRight);
  }
  for (Coord x = 0; x < std::ssize(v[0]); ++x)
  {
    res += FindAll(Point(x, 0), GoDown);
    res += FindAll(Point(x, v2d.SizeY()-1), GoUp);

    res += FindAll(Point(x+1, 0), GoDownRight);
    res += FindAll(Point(x-1, v2d.SizeY()-1), GoUpLeft);

    res += FindAll(Point(x-1, 0), GoDownLeft);
    res += FindAll(Point(x+1, v2d.SizeY()-1), GoUpRight);
  }

  return res;
}

//template<> auto InputData<2024, 4, B>() { return
//"MMMSXXMASM\n"
//"MSAMXMSMSA\n"
//"AMXSXMAAMM\n"
//"MSAMASMSMX\n"
//"XMASAMXAMM\n"
//"XXAMMXXAMA\n"
//"SMSMSASXSS\n"
//"SAXAMASAAA\n"
//"MAMMMXMMMM\n"
//"MXMXAXMASX\n";}; // Result: 9
template<> Number AoC<2024, 4, B>(std::istream& input)
{
  Input v = ReadLines(input);  // read all lines into vector

  using namespace Coord2D;

  V2D v2d(v);

  constexpr char target[] = "XMAS";
  constexpr Coord tlen = sizeof target - 1;

  auto Match = [&v2d,&target,&tlen](Point p, Direction d) -> bool
    {
      for (int i = 0; i < tlen; ++i)
      {
        if (v2d.GetChar(p + d * i) != target[i]) return false;
      }
      return true;
    };
  auto FindAll = [&v2d,&target,&tlen,&Match](Point p, Direction d) -> Number
    {
      Number count{ 0 };
      while (v2d.IsValid(p) && v2d.IsValid(p + d * (tlen - 1)))
      {
        if (Match(p, d))
          ++count;
        p += d;
      }
      return count;
    };

  Number res{0};
  for (Coord x = 0; x < v2d.SizeX(); ++x)
  {
    for (Coord y = 0; y < v2d.SizeY(); ++y)
    {
      const Point p{ x,y };
      if (v2d.GetChar(p) == 'A')
      {
        Point ul{ p + GoUpLeft    };
        Point ur{ p + GoUpRight   };
        Point dl{ p + GoDownLeft  };
        Point dr{ p + GoDownRight };

        if (!v2d.IsValid(ul) || !v2d.IsValid(ur) || !v2d.IsValid(dl) || !v2d.IsValid(dr)) continue;

        char cul = v2d.GetChar(ul);
        char cur = v2d.GetChar(ur);
        char cdl = v2d.GetChar(dl);
        char cdr = v2d.GetChar(dr);

        if ((cul != 'M' || cdr != 'S') && (cul != 'S' || cdr != 'M')) continue;
        if ((cur != 'M' || cdl != 'S') && (cur != 'S' || cdl != 'M')) continue;
        ++res;
      }
    }
  }
  return res;
}
