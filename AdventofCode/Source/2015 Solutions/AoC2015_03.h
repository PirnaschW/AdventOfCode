//template<> auto InputData<2015, 3, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 3, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Point
  {
  public:
    char x{ 0 };
    char y{ 0 };
  };
  std::unordered_set<int> houses{};
  Point p{};
  auto makeint = [](const Point& p) -> int {return (p.x << 8) + p.y; };
  houses.insert(makeint(p));
  for (const char c : v[0])
  {
    switch (c)
    {
      case '>': ++p.x; break;
      case '<': --p.x; break;
      case 'v': ++p.y; break;
      case '^': --p.y; break;
      default: assert(false);
    }
    if (!houses.contains(makeint(p))) houses.insert(makeint(p));
  }

  return houses.size();
}

//template<> auto InputData<2015, 3, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 3, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Point
  {
  public:
    char x{ 0 };
    char y{ 0 };
  };
  std::unordered_set<int> houses{};
  Point p1{};
  Point p2{};
  auto makeint = [](const Point& p) -> int {return (p.x << 8) + p.y; };
  houses.insert(makeint(p1));
  for (auto i=0; i<v[0].size(); i+=2)
  {
    switch (v[0][i])
    {
      case '>': ++p1.x; break;
      case '<': --p1.x; break;
      case 'v': ++p1.y; break;
      case '^': --p1.y; break;
      default: assert(false);
    }
    if (!houses.contains(makeint(p1))) houses.insert(makeint(p1));
    switch (v[0][i+1])
    {
      case '>': ++p2.x; break;
      case '<': --p2.x; break;
      case 'v': ++p2.y; break;
      case '^': --p2.y; break;
      default: assert(false);
    }
    if (!houses.contains(makeint(p2))) houses.insert(makeint(p2));
  }

  return houses.size();
}
