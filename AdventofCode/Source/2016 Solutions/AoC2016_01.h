//template<> auto InputData<2016, 1, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 1, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  const char* p = v[0].c_str();

  int posx{ 0 };
  int posy{ 0 };
  int direction{ 1 };

  while (true)
  {
    char turn{};
    int dist{ 0 };
    char comma{};
    int off{ 0 };
    int z = sscanf_s(p, " %c%d%c%n", &turn, 1, &dist, &comma, 1, &off);
    assert(z == 3 || z == 2);

    switch(turn)
    {
      case 'R': --direction; break;
      case 'L': ++direction; break;
      default: assert(false);
    }
    direction += 4;
    direction %= 4;

    switch (direction)
    {
      case 0: posx += dist; break;
      case 1: posy += dist; break;
      case 2: posx -= dist; break;
      case 3: posy -= dist; break;
    }
    p += off;
    if (z < 3) break;
  }
  return std::abs(posx) + std::abs(posy);
}

//template<> auto InputData<2016, 1, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 1, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  const char* p = v[0].c_str();

  int posx{ 0 };
  int posy{ 0 };
  int direction{ 1 };

  class Point
  {
  public:
    int x{ 0 };
    int y{ 0 };
  };

  using Visits = std::unordered_set < Point, decltype([](const Point& p)->size_t {return p.x << 16 | p.y; }), decltype([](const Point& p1, const Point& p2)->bool {return p1.x == p2.x && p1.y == p2.y; }) > ;
  Visits visits{};


  auto Visit = [&visits](int x, int y) -> bool
    {
      if (visits.contains({ x,y })) return true;
      visits.insert({ x,y });
      return false;
    };

  while (true)
  {
    char turn{};
    int dist{ 0 };
    char comma{};
    int off{ 0 };
    int z = sscanf_s(p, " %c%d%c%n", &turn, 1, &dist, &comma, 1, &off);
    assert(z == 3 || z == 2);

    switch(turn)
    {
      case 'R': --direction; break;
      case 'L': ++direction; break;
      default: assert(false);
    }
    direction += 4;
    direction %= 4;

    switch (direction)
    {
      case 0: for (int i = 0; i < dist; ++i) { ++posx; if (Visit(posx, posy)) return std::abs(posx) + std::abs(posy); } break;
      case 1: for (int i = 0; i < dist; ++i) { ++posy; if (Visit(posx, posy)) return std::abs(posx) + std::abs(posy); } break;
      case 2: for (int i = 0; i < dist; ++i) { --posx; if (Visit(posx, posy)) return std::abs(posx) + std::abs(posy); } break;
      case 3: for (int i = 0; i < dist; ++i) { --posy; if (Visit(posx, posy)) return std::abs(posx) + std::abs(posy); } break;
    }
    p += off;
    if (z < 3) break;
  }
  throw "Error";
}
