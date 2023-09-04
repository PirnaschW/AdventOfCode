//template<> auto InputData<2019, 23, A>() { return "Testdata\n"; };  // 
template<> Number AoC<2019, 23, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  constexpr Number count = 50;
  std::vector<IntCodeComputer_2019_200> icc(count, code);

  for (auto i = 0; i < count; ++i)
  {
    icc[i].PushInput(i);
    icc[i].ExecuteToInput();
  }


  auto Send = [&icc](Number d, Number x, Number y) -> bool
    {
      if (d == 255) return true;
      icc[d].PushInput(x);
      icc[d].PushInput(y);
      return false;
    };

  while (true)
  {
    for (auto i = 0; i < count; ++i)
    {
      if (!icc[i].HasInput()) icc[i].PushInput(-1);
      icc[i].ExecuteToInput();
      while (icc[i].HasOutput())
      {
        Number d = icc[i].PopOutput();  // destination
        icc[i].ExecuteToOutput();
        Number x = icc[i].PopOutput();  // x
        icc[i].ExecuteToOutput();
        Number y = icc[i].PopOutput();  // y
        //std::cout << i << ": " << d << ' ' << x << ' ' << y << ' ' << std::endl;

        if (Send(d, x, y)) return y;
        icc[i].ExecuteToInput();
      }
    }
  }
  throw "Error";
}


//template<> auto InputData<2019, 23, B>() { return "Testdata\n"; };  // 
template<> Number AoC<2019, 23, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  constexpr Number count = 50;
  std::vector<IntCodeComputer_2019_200> icc(count, code);
  class NAT
  {
  public:
    Number x{ -1 };
    Number y{ -1 };
    Number LastYSent{ -1 };
  };
  NAT nat{};

  for (auto i = 0; i < count; ++i)
  {
    icc[i].PushInput(i);
    icc[i].ExecuteToInput();
  }


  auto Send = [&icc,&nat](Number d, Number x, Number y) -> bool
    {
      if (d == 255)
      {
        nat.x = x;
        nat.y = y;
        return true;
      }
      icc[d].PushInput(x);
      icc[d].PushInput(y);
      return false;
    };

  while (true)
  {
    bool idle{ true };
    for (auto i = 0; i < count; ++i)
    {
      if (!icc[i].HasInput()) icc[i].PushInput(-1);
      icc[i].ExecuteToInput();
      while (icc[i].HasOutput())
      {
        idle = false;
        Number d = icc[i].PopOutput();  // destination
        icc[i].ExecuteToOutput();
        Number x = icc[i].PopOutput();  // x
        icc[i].ExecuteToOutput();
        Number y = icc[i].PopOutput();  // y
        //std::cout << i << ": " << d << ' ' << x << ' ' << y << ' ' << std::endl;

        Send(d, x, y);
        icc[i].ExecuteToInput();
      }
    }

    if (idle)
    {
      if (nat.LastYSent == nat.y) return nat.y;
      nat.LastYSent = nat.y;
      Send(0, nat.x, nat.y);
    }
  }
  throw "Error";
}
