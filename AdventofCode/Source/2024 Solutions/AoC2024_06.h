//template<> auto InputData<2024, 6, A>() { return 
//"....#.....\n"
//".........#\n"
//"..........\n"
//"..#.......\n"
//".......#..\n"
//"..........\n"
//".#..^.....\n"
//"........#.\n"
//"#.........\n"
//"......#...\n";}; // Result: 41
template<> Number AoC<2024, 6, A>(std::istream& input)
{
  Input v = ReadLines(input);  // read all lines into vector

  using namespace Coord2D;
  V2D v2d(v);

  Point p = v2d.Find('^');
  Direction d = GoUp;

  PointSet set{p};
  while (v2d.IsValid(p+d))
  {
    if (v2d.GetChar(p + d) == '#')
      d = d.TurnRight();
    else p += d;
    set.insert(p);
  }

  return set.size();
}

//template<> auto InputData<2024, 6, B>() { return 
//"....#.....\n"
//".........#\n"
//"..........\n"
//"..#.......\n"
//".......#..\n"
//"..........\n"
//".#..^.....\n"
//"........#.\n"
//"#.........\n"
//"......#...\n";}; // Result: 6
template<> Number AoC<2024, 6, B>(std::istream& input)
{
  Input v = ReadLines(input);  // read all lines into vector

  using namespace Coord2D;
  V2D v2d(v);

  auto IsLoop = [&v2d](Point p, Direction d) -> bool
    {
      PointDirectionSet set{ {p,d} };
      while (v2d.IsValid(p+d))
      {
        if (v2d.GetChar(p + d) == '#')
          d = d.TurnRight();
        else p += d;
        if (set.contains({p,d}))
          return true;
        else set.insert({ p,d });
      }
      return false;
    };



  Point p0 = v2d.Find('^');
  Direction d0 = GoUp;
  
  // collect the guard's path
  PointSet set{p0};
  Point p{ p0 };
  Direction d{ d0 };
  while (v2d.IsValid(p+d))
  {
    if (v2d.GetChar(p + d) == '#')
      d = d.TurnRight();
    else p += d;
    set.insert(p);
  }

  Number count{ 0 };
  for (Coord y = 0; y < v2d.SizeY(); ++y)
  {
    for (Coord x = 0; x < v2d.SizeX(); ++x)
    {
      const Point pp{ x,y };
      if (v2d.GetChar(pp) != '.') continue;
      if (!set.contains(pp)) continue;  // guard would never get here

      // test with an obstacle there:
      v[y][x] = '#';
      if (IsLoop(p0, d0))
        ++count;
      v[y][x] = '.';
    }
  }

  return count;
}
