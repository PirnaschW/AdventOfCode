//template<> auto InputData<2022, 25, A>() { return "1=-0-2\n12111\n2=0=\n21\n2=01\n111\n20012\n112\n1=-1=\n1-12\n12\n1=\n122"; };
//template<> auto InputData<2022, 25, B>() { return ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>"; };
template<> Number AoC<2022, 25, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  Number z = 0;
  for (auto const& line : v)
  {
    Number n = 0;
    for (int i = 0; i < line.size(); ++i)
    {
      n *= 5;
      switch (line[i])
      {
        case '2': n += 2; break;
        case '1': n += 1; break;
        case '0': n += 0; break;
        case '-': n += -1; break;
        case '=': n += -2; break;
        default:
          assert(false);
      }
    }

    z += n;
  }


  std::string result{};
  while (z > 0)
  {
    int n = (z + 2) % 5;
    char c{};
    switch (n)
    {
      case 0: c = '='; break;
      case 1: c = '-'; break;
      case 2: c = '0'; break;
      case 3: c = '1'; break;
      case 4: c = '2'; break;
    }
    result = c + result;
    z = (z + 2) / 5;
  }
  throw result;
}

template<> Number AoC<2022, 25, B>(std::istream&)
{
  throw "";
}
