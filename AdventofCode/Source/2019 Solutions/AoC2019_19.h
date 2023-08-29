//template<> auto InputData<2019, 19, A>() { return "Testdata\n"; };  // 01029498
template<> Number AoC<2019, 19, A>(std::istream& input)
{
  using Coord = char;
  auto code = ReadNumbers(input, ',');


  Number n{ 0 };
  for (Coord x = 0; x < 50; ++x)
  {
    for (Coord y = 0; y < 50; ++y)
    {
      IntCodeComputer_2019_200 c(code);
      c.PushInput(x);
      c.PushInput(y);
      c.ExecuteToOutput();
      Number z = c.PopOutput();
      if (z == 1) n++;
      //std::cout << (z == 1 ? '#' : '.');
    }
    //std::cout << std::endl;
  }
  //std::cout << std::endl;
  return n;
}

//template<> auto InputData<2019, 19, B>() { return "Testdata\n"; };  // 01029498
template<> Number AoC<2019, 19, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  constexpr Number ShipSize{ 100 };
  auto TBeam = [&code](Number x, Number y) -> bool
    {
      IntCodeComputer_2019_200 c(code);
      c.PushInput(x);
      c.PushInput(y);
      c.ExecuteToOutput();
      Number z = c.PopOutput();
      return (z == 1);
    };

  Number ystart{ 0 };
  Number xSize{ 0 };
  Number ySize{ 0 };
  for (Number x = 0; ; ++x)
  {
    bool xok{ false };
    for (Number y = ystart; y < 5 * x + 1; ++y)
    {
      if (TBeam(x, y))
      {
        ystart = y;
        break;
      }
    }

    if (ystart == 0) continue;

    Number ybegin{ 0 };
    for (Number y = ystart; TBeam(x, y); ++y)
    {
      for (Number x1 = x; ; ++x1)
      {
        if (!TBeam(x1, y))
        {
          xSize = x1 - x;
          if (xSize >= ShipSize)
          {
            xok = true;
            ybegin = y;
          }
          else
          {
            //if (x % 10 == 0)
            //  std::cout << x << ": " << xend - x + 1 << std::endl;
          }
          break;
        }
      }

      if (xok)
        break;
    }
    //if (x % 10 == 0)
    //  std::cout << x << ' ' << ystart << ": " << xSize << ' ' << ySize << std::endl;

    if (!xok)
    {
      if (xSize < ShipSize - 2) x += ShipSize - xSize;
      continue;
    }
    for (Number y = ybegin + 1; xok && TBeam(x, y); ++y)
    {
      //for (Number x1 = x; ; ++x1)
      //{
      //  if (!TBeam(x1, y))
      //  {
      //    Number xend = x1 - 1;
      //    if (xend - x + 1 < ShipSize)
      //    {
      //      xok = false;
      //    }
      //    break;
      //  }
      //}
      //if (!xok) break;

      ySize = y - ybegin + 1;
      //if (x % 10 == 0)
      //  std::cout << x << ' ' << y << ": " << xSize << ' ' << ySize << std::endl;

      if (ySize >= ShipSize)
      {
        return ShipSize * ShipSize * x + ybegin;
      }
    }
    if (ySize < ShipSize - 2) x += ShipSize - ySize;

  }
  return -1;
}
