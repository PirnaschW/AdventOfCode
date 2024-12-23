//template<> auto InputData<2023, 2, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 2, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  // example:
  // Game 1: 2 blue, 3 red; 3 green, 3 blue, 6 red; 4 blue, 6 red; 2 green, 2 blue, 9 red; 2 red, 4 blue
  // Game 2: 4 red, 1 green; 3 red; 13 green, 5 red, 3 blue; 3 green, 2 red; 3 blue, 5 red, 3 green; 2 red, 3 blue, 12 green
  // Game 3: 4 red, 1 green, 1 blue; 1 red, 1 blue; 6 red, 1 green; 6 red, 3 blue, 1 green; 4 red

  const std::array<std::string, 3> colors{ "red", "blue", "green" };

  class Draw
  {
  public:
    std::array<int, 3> counts{ 0,0,0 };
  };

  class Game
  {
  public:
    int id{ 0 };
    std::vector<Draw> draws{};
    Draw maxdraw{};
  };

  std::vector<Game> games{};

  for (const auto& line : v)
  {
    Game g{};
    int off{ 0 };
    const char* pos = line.data();
    int z = sscanf_s(pos, "Game %d: %n", &g.id, &off);
    assert(z == 1);
    pos += off;

    do
    {
      if (*pos == ';') ++pos;
      Draw d;
      do
      {
        if (*pos == ',') ++pos;
        int n{ 0 };
        int z1 = sscanf_s(pos, " %d %n", &n, &off);
        assert(z1 == 1);
        pos += off;

        for (size_t i = 0; i < colors.size(); ++i)
        {
          if (std::strncmp(pos, colors[i].c_str(), colors[i].size()) == 0)
          {
            d.counts[i] = n;
            pos += colors[i].size();
            break;;
          }
        }
      }
      while (*pos == ',');
      g.draws.push_back(d);
    }
    while (*pos == ';');
    games.push_back(g);
  }

  const Draw elf{ 12,14,13 };
  Number result{ 0 };
  for (auto& g : games)
  {
    for (const auto& d : g.draws)
    {
      for (size_t i = 0; i < colors.size(); ++i)
      {
        if (d.counts[i] > g.maxdraw.counts[i])
        {
          g.maxdraw.counts[i] = d.counts[i];
        }
      }
    }

    bool possible{ true };
    for (size_t i = 0; i < colors.size(); ++i)
    {
      if (g.maxdraw.counts[i] > elf.counts[i])
      {
        possible = false;
        break;
      }
    }
    if (possible)
    {
      result += g.id;
    }

  }

  return result;
}

//template<> auto InputData<2023, 2, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 2, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  // example:
  // Game 1: 2 blue, 3 red; 3 green, 3 blue, 6 red; 4 blue, 6 red; 2 green, 2 blue, 9 red; 2 red, 4 blue
  // Game 2: 4 red, 1 green; 3 red; 13 green, 5 red, 3 blue; 3 green, 2 red; 3 blue, 5 red, 3 green; 2 red, 3 blue, 12 green
  // Game 3: 4 red, 1 green, 1 blue; 1 red, 1 blue; 6 red, 1 green; 6 red, 3 blue, 1 green; 4 red

  const std::array<std::string, 3> colors{ "red", "blue", "green" };

  class Draw
  {
  public:
    std::array<int, 3> counts{ 0,0,0 };
  };

  class Game
  {
  public:
    int id{ 0 };
    std::vector<Draw> draws{};
    Draw maxdraw{};
  };

  std::vector<Game> games{};

  for (const auto& line : v)
  {
    Game g{};
    int off{ 0 };
    const char* pos = line.data();
    int z = sscanf_s(pos, "Game %d: %n", &g.id, &off);
    assert(z == 1);
    pos += off;

    do
    {
      if (*pos == ';') ++pos;
      Draw d;
      do
      {
        if (*pos == ',') ++pos;
        int n{ 0 };
        int z1 = sscanf_s(pos, " %d %n", &n, &off);
        assert(z1 == 1);
        pos += off;

        for (size_t i = 0; i < colors.size(); ++i)
        {
          if (std::strncmp(pos, colors[i].c_str(), colors[i].size()) == 0)
          {
            d.counts[i] = n;
            pos += colors[i].size();
            break;;
          }
        }
      }
      while (*pos == ',');
      g.draws.push_back(d);
    }
    while (*pos == ';');
    games.push_back(g);
  }

  const Draw elf{ 12,14,13 };
  Number result{ 0 };
  for (auto& g : games)
  {
    for (const auto& d : g.draws)
    {
      for (size_t i = 0; i < colors.size(); ++i)
      {
        if (d.counts[i] > g.maxdraw.counts[i])
        {
          g.maxdraw.counts[i] = d.counts[i];
        }
      }
    }

    Number product{ 1LL };
    for (size_t i = 0; i < colors.size(); ++i)
    {
      product *= g.maxdraw.counts[i];
    }
    result += product;
  }

  return result;
}
