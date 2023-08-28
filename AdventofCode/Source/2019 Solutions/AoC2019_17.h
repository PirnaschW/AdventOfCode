//template<> auto InputData<2019, 17, A>() { return "12345678\n4\n"; };  // 01029498
template<> Number AoC<2019, 17, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  using Coord = char;
  
  class Aft
  {
  public:
    Aft(IntCodeComputer_2019_200&& c)
    {
      std::vector<char> line{};
      char prev{ '\0' };
      char out{ '\0' };
      do
      {
        prev = out;
        c.ExecuteToOutput();
        out = static_cast<char>(c.PopOutput());
        line.push_back(out);

        switch (out)
        {
          case '#':  break;
          case '.':  break;
          case '<':  ++robotd; [[fallthrough]];
          case 'v':  ++robotd; [[fallthrough]];
          case '>':  ++robotd; [[fallthrough]];
          case '^':  ++robotd;
            robotx = static_cast<char>(line.size());
            roboty = static_cast<char>(aft.size());
            break;

          case '\n':
            if (prev == out) break; // the end
            line.pop_back();        // remove the trailing '\n'
            aft.push_back(line);    // collect lines
            line.clear();
            break;

          default:
            assert(false);
        }
//        std::cout << out;
      }
      while (out != '\n' || prev != '\n');
    }

    Coord getSizeX() const noexcept { return static_cast<char>(aft[0].size()); }
    Coord getSizeY() const noexcept { return static_cast<char>(aft.size()); }
    bool isCrossing(Coord x, Coord y) const noexcept { return (isScaffold(x, y) && isScaffold(x + 1, y) && isScaffold(x - 1, y) && isScaffold(x, y + 1) && isScaffold(x, y - 1)); }

    Coord getRobotX() const noexcept { return robotx; }
    Coord getRobotY() const noexcept { return roboty; }
    Coord getRobotD() const noexcept { return robotd; }

  private:
    bool isValid(Coord x, Coord y) const noexcept { return (x >= 0) && (x < aft[0].size()) && (y >= 0) && (y < aft.size()); };
    bool isScaffold(Coord x, Coord y) const noexcept { return isValid(x,y) && aft[y][x] == '#'; };

  private:
    std::vector<std::vector<char>> aft{};
    Coord robotx{0};
    Coord roboty{0};
    Coord robotd{-1};
  };

  Aft aft{ IntCodeComputer_2019_200(code) };

  Number sum{ 0 };
  for (Coord x = 0; x < aft.getSizeX(); ++x)
  {
    for (Coord y = 0; y < aft.getSizeY(); ++y)
    {
      if (aft.isCrossing(x,y))
      {
        sum += x * y;
      }
    }

  }

  //c.PushInput(direction);


  return sum;
}


//template<> auto InputData<2019, 17, B>() { return "167 ORE => 5 NZVS\n165 ORE => 6 DCFZ\n12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"; }; // 
template<> Number AoC<2019, 17, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  using Coord = char;

  class Aft
  {
  public:
    Aft(IntCodeComputer_2019_200& c, bool show)
    {
      if (show) std::cout << std::endl;
      std::vector<char> line{};
      char prev{ '\0' };
      char out{ '\0' };
      do
      {
        prev = out;
        c.ExecuteToOutput();
        out = static_cast<char>(c.PopOutput());
        line.push_back(out);

        switch (out)
        {
          case '#':  break;
          case '.':  break;
          case '<':  ++robotd; [[fallthrough]];
          case 'v':  ++robotd; [[fallthrough]];
          case '>':  ++robotd; [[fallthrough]];
          case '^':  ++robotd;
            robotx = static_cast<char>(line.size()-1);
            roboty = static_cast<char>(aft.size());
            break;

          case '\n':
            if (prev == out) break; // the end
            line.pop_back();        // remove the trailing '\n'
            aft.push_back(line);    // collect lines
            line.clear();
            break;

          default:
            assert(false);
        }
        if (show) std::cout << out;
      }
      while (out != '\n' || prev != '\n');
    }

    Coord getSizeX() const noexcept { return static_cast<char>(aft[0].size()); }
    Coord getSizeY() const noexcept { return static_cast<char>(aft.size()); }
    bool isCrossing(Coord x, Coord y) const noexcept { return (isScaffold(x, y) && isScaffold(x + 1, y) && isScaffold(x - 1, y) && isScaffold(x, y + 1) && isScaffold(x, y - 1)); }
    bool isScaffold(Coord x, Coord y) const noexcept { return isValid(x,y) && aft[y][x] == '#'; };

    Coord getRobotX() const noexcept { return robotx; }
    Coord getRobotY() const noexcept { return roboty; }
    Coord getRobotD() const noexcept { return robotd; }

  private:
    bool isValid(Coord x, Coord y) const noexcept { return (x >= 0) && (x < aft[0].size()) && (y >= 0) && (y < aft.size()); };

  private:
    std::vector<std::vector<char>> aft{};
    Coord robotx{0};
    Coord roboty{0};
    Coord robotd{-1};
  };

  IntCodeComputer_2019_200 c(code);
  assert(c.Peek(0) == 1);
  c.Poke(0, 2);

  Aft aft(c, false);

  // find the necessary movement sequence

  // ...
  Coord robotx = aft.getRobotX();
  Coord roboty = aft.getRobotY();
  Coord robotd = aft.getRobotD();
  std::stringstream sequence{};

  auto dx = [](Coord direction) -> Coord { return direction == 1 ? 1 : (direction == 3 ? -1 : 0); };
  auto dy = [](Coord direction) -> Coord { return direction == 2 ? 1 : (direction == 0 ? -1 : 0); };

  bool more{ true };
  while (more)
  {
    more = false;
    for (Coord dd = 1; dd < 4; dd += 2)  // only try left and right (1 and 3)
    {
      Coord d = (robotd + dd) % 4;
      if (aft.isScaffold(robotx + dx(d), roboty + dy(d)))
      {
        sequence << (dd == 1 ? 'R' : 'L');
        sequence << ',';
        robotd += dd;    // reorient robot for next round
        robotd %= 4;
        robotx += dx(d); // move robot one
        roboty += dy(d);
        Coord z{ 1 };
        while (aft.isScaffold(robotx + dx(d), roboty + dy(d)))
        {
          robotx += dx(d); // move robot one
          roboty += dy(d);
          ++z;
        }
        sequence << (int) z;
        sequence << ',';
        more = true;
        break;
      }
    }
  }

  std::string command{ sequence.str() };

  std::regex reg{ R"--((.{1,21})\1*(.{1,21})(?:\1|\2)*(.{1,21})(?:\1|\2|\3)*)--" };
  std::smatch match{};
  std::regex_match(command, match, reg);
  assert(match.size() == 4);

  std::array<std::string, 3> ABC{};
  for (int i = 0; i < 3; ++i)
  {
    ABC[i] = match[i + 1];
  }

  int pos{ 0 };
  std::string mainroutine{};
  while (pos < command.size())
  {
    for (int i = 0; i < 3; ++i)
    {
      if (command.substr(pos, ABC[i].size()) == ABC[i])
      {
        mainroutine.push_back(static_cast<char>('A' + i));
        mainroutine.push_back(',');
        pos += static_cast<Coord>(ABC[i].size());
        break;
      }
    }
  }

  // remove end commas:
  for (int i = 0; i < 3; ++i)
  {
    ABC[i][ABC[i].size() - 1] = '\n';
  }
  mainroutine[mainroutine.size() - 1] = '\n';

  char out{ 0 };
  for (int i = 0; i < 5; ++i)
  {
    out = '\0';
    while (out != '\n')
    {
      c.ExecuteToOutput();
      out = static_cast<char>(c.PopOutput());
      //std::cout << out;
      if (out == '\n') // feed input now
      {
        for (auto& ch : (i == 0 ? mainroutine : (i == 4 ? "n\n" : ABC[i - 1])))
        {
          c.PushInput(ch);
        }
      }
    }
  }

  Number z{ 0 };
  while (true)
  {
    c.ExecuteToOutput();
    z = c.PopOutput();
    if (z > 255) break;
    //std::cout << (char) z;
  }
  return z;
}
