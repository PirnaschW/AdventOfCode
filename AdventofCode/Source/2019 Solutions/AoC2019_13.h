//template<> auto InputData<2019, 13, A>() { return "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99"; };

template<> Number AoC<2019, 13, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');
  IntCodeComputer_2019_200 c(code);

  using Coord = unsigned char;
  using Tile = unsigned char;
  Coord xmax{0};
  Coord ymax{0};
  constexpr Coord sx{45};
  constexpr Coord sy{26};
  std::array<std::array<Tile, sy>, sx> screen{0};

  while (c.ExecuteToOutput() && c.ExecuteToOutput() && c.ExecuteToOutput())  // always receive three outputs
  {
    Coord x = (Coord) c.PopOutput();
    Coord y = (Coord) c.PopOutput();
    Tile z = (Tile) c.PopOutput();
    assert(x < sx);
    assert(y < sy);
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;
    screen[x][y] = z;
  }

  Number res{ 0 };
  for (int y = 0; y < ymax; ++y)
  {
    for (int x = 0; x < xmax; ++x)
    {
      if (screen[x][y] == 2) ++res;
    }
  }

  return res;
}

template<> Number AoC<2019, 13, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');
  IntCodeComputer_2019_200 c(code);
  c.Poke(0, 2);
  c.PushInput(0);

  using Coord = char;
  using Tile = unsigned char;
  Coord xmax{ 0 };
  Coord ymax{ 0 };
  constexpr Coord sx{ 45 };
  constexpr Coord sy{ 26 };
  std::array<std::array<Tile, sy>, sx> screen{ 0 };

  Number score{ 0 };
  Coord xBall{ -1 };
  Coord xPaddle{ -1 };
  while (c.ExecuteToOutput() && c.ExecuteToOutput() && c.ExecuteToOutput())  // always receive three outputs
  {
    Coord x = (Coord) c.PopOutput();
    Coord y = (Coord) c.PopOutput();
    assert(x < sx);
    assert(y < sy);
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;

    Tile z{0};
    if (x == -1 and y == 0)
    {
      score = c.PopOutput();
    }
    else
    {
      z = (Tile) c.PopOutput();
      screen[x][y] = z;

      switch (z)
      {
        case 4: xBall = x; break;
        case 3: xPaddle = x; break;
        default: break;
      }

      if (z == 4 && xPaddle != -1 && xBall != -1) // after setup, when the new ball position is delivered, compare to ball and move paddle accordingly
      {
        c.PushInput(xBall > xPaddle ? 1 : (xBall < xPaddle ? -1 : 0));
      }
    }
  }

  return score;
}
