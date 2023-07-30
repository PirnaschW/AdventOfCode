template<> Number AoC<2022, 11, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };


  //Monkey 0:
  //Starting items : 66, 59, 64, 51
  //  Operation : new = old * 3
  //  Test : divisible by 2
  //  If true : throw to monkey 1
  //  If false : throw to monkey 4

  struct Monkey
  {  
    int id{};
    std::deque<Number> items{};
    Number factor{ 1 };
    Number summand{ 0 };
    Number divisor{ 1 };
    bool square{ false };
    int iftrue{};
    int iffalse{};
    int z{ 0 };
  };


  std::vector<Monkey> monkeys{};
  std::string line{};
  while (getline(input, line))
  {
    Monkey m;
    std::istringstream str1(line.substr(7));
    str1 >> m.id;

    getline(input, line);
    std::istringstream str2(line.substr(16));
    Number worry;
    char sep;
    while (str2 >> sep >> worry)
    {
      m.items.push_back(worry);
    }

    getline(input, line);
    std::istringstream str3(line.substr(23));
    if (line.substr(25, 3) == "old")
      m.square = true;
    else
    {
      char sign;
      Number n;
      str3 >> sign >> n;
      switch (sign)
      {
        case '+': m.summand = n; break;
        case '*': m.factor = n; break;
      }
    }

    getline(input, line);
    std::istringstream str4(line.substr(21));
    str4 >> m.divisor;

    getline(input, line);
    std::istringstream str5(line.substr(28));
    str5 >> m.iftrue;

    getline(input, line);
    std::istringstream str6(line.substr(29));
    str6 >> m.iffalse;

    monkeys.push_back(m);
    getline(input, line);
  }

  for (int i = 0; i < 20; ++i)
  {
    for (int j = 0; j < monkeys.size(); ++j)
    {
      Number nk = monkeys[j].items.size();
      for (Number k = 0; k < nk; ++k)
      {
        auto current = monkeys[j].items.front();
        monkeys[j].items.pop_front();
        ++monkeys[j].z;

        if (monkeys[j].square) current *= current;
        current *= monkeys[j].factor;
        current += monkeys[j].summand;
        current /= 3;
        if (current % monkeys[j].divisor)
          monkeys[monkeys[j].iffalse].items.push_back(current);
        else
          monkeys[monkeys[j].iftrue].items.push_back(current);
      }
    }
  }

  std::vector<int> zz{};
  for (int j = 0; j < monkeys.size(); ++j)
  {
    zz.push_back(monkeys[j].z);
  }

  std::sort(zz.begin(), zz.end(), std::greater<int>());

  return zz[0] * zz[1];
}

template<> Number AoC<2022, 11, B>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };


  //Monkey 0:
  //Starting items : 66, 59, 64, 51
  //  Operation : new = old * 3
  //  Test : divisible by 2
  //  If true : throw to monkey 1
  //  If false : throw to monkey 4

  struct Monkey
  {
    int id{};
    std::deque<Number> items{};
    Number factor{ 1 };
    Number summand{ 0 };
    Number divisor{ 1 };
    bool square{ false };
    int iftrue{};
    int iffalse{};
    Number z{ 0 };
  };


  std::vector<Monkey> monkeys{};
  std::string line{};
  while (getline(input, line))
  {
    Monkey m;
    std::istringstream str1(line.substr(7));
    str1 >> m.id;

    getline(input, line);
    std::istringstream str2(line.substr(16));
    Number worry;
    char sep;
    while (str2 >> sep >> worry)
    {
      m.items.push_back(worry);
    }

    getline(input, line);
    std::istringstream str3(line.substr(23));
    if (line.substr(25, 3) == "old")
      m.square = true;
    else
    {
      char sign;
      Number n;
      str3 >> sign >> n;
      switch (sign)
      {
        case '+': m.summand = n; break;
        case '*': m.factor = n; break;
      }
    }

    getline(input, line);
    std::istringstream str4(line.substr(21));
    str4 >> m.divisor;

    getline(input, line);
    std::istringstream str5(line.substr(28));
    str5 >> m.iftrue;

    getline(input, line);
    std::istringstream str6(line.substr(29));
    str6 >> m.iffalse;

    monkeys.push_back(m);
    getline(input, line);
  }

  Number megadivisor = 1;
  for (int j = 0; j < monkeys.size(); ++j)
  {
    megadivisor *= monkeys[j].divisor;
  }

  for (int i = 0; i < 10000; ++i)
  {
    for (int j = 0; j < monkeys.size(); ++j)
    {
      Number nk = monkeys[j].items.size();
      for (Number k = 0; k < nk; ++k)
      {
        Number current = monkeys[j].items.front();
        monkeys[j].items.pop_front();
        ++monkeys[j].z;

        if (monkeys[j].square)
          current *= current;
        current *= monkeys[j].factor;
        current += monkeys[j].summand;
//        current /= 3;
        current %= megadivisor;
        if (current % monkeys[j].divisor)
          monkeys[monkeys[j].iffalse].items.push_back(current);
        else
          monkeys[monkeys[j].iftrue].items.push_back(current);
      }
    }
  }

  std::vector<Number> zz{};
  for (int j = 0; j < monkeys.size(); ++j)
  {
    zz.push_back(monkeys[j].z);
  }

  std::sort(zz.begin(), zz.end(), std::greater<Number>());

  return zz[0] * zz[1];
}
