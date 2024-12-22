//template<> auto InputData<2016, 10, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 10, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  constexpr unsigned int BufSize{ 10 };
  constexpr unsigned int BotSize{ 256 };

  class Bot
  {
  public:
    int chip1{ -1 };
    int chip2{ -1 };
    bool outputh{ false };
    int higher{ -1 };
    bool outputl{ false };
    int lower{ -1 };
  };
  using Bots = std::array<Bot,BotSize>;

  Bots bot{};

  auto GiveTo = [&bot](int botnr, int value) -> bool
    {
      assert(botnr < BotSize);
      if (bot[botnr].chip1 == value || bot[botnr].chip2 == value) return false;
      if (bot[botnr].chip1 == -1)
        {
        bot[botnr].chip1 = value;
      }
      else
      {
        assert(bot[botnr].chip2 == -1);
        bot[botnr].chip2 = value;
      }
      return true;
    };

  for (const auto& line : v)
  {
    int value{};
    int botnr{};
    // value 5 goes to bot 2
    // bot 2 gives low to bot 1 and high to bot 0
    // bot 1 gives low to output 1 and high to bot 0
    int z1 = sscanf_s(line.c_str(), "value %d goes to bot %d", &value, &botnr);
    if (z1 == 2)
    {
      GiveTo(botnr, value);
      continue;
    }

    char target1[BufSize];
    char target2[BufSize];
    int targetnr1{};
    int targetnr2{};
    int z2 = sscanf_s(line.c_str(), "bot %d gives low to %s %d and high to %s %d", &botnr, target1, BufSize, &targetnr1, target2, BufSize, &targetnr2);
    if (z2 == 5)
    {
      assert(botnr < BotSize);
      bot[botnr].outputl = (target1[0] == 'o');
      bot[botnr].lower = targetnr1;
      bot[botnr].outputh = (target2[0] == 'o');
      bot[botnr].higher = targetnr2;
      continue;
    }
    assert(false);
  }

  bool changes{ true };
  while (changes)
  {
    changes = false;
    for (int i = 0; i < BotSize; ++i)
    {
      if (bot[i].chip1 != -1 && bot[i].chip2 != -1)
      {
        if (!bot[i].outputl)
        {
          if (GiveTo(bot[i].lower, bot[i].chip1 < bot[i].chip2 ? bot[i].chip1 : bot[i].chip2))
          {
            changes = true;
          }
        }
        if (!bot[i].outputh)
        {
          if (GiveTo(bot[i].higher, bot[i].chip1 > bot[i].chip2 ? bot[i].chip1 : bot[i].chip2))
          {
            changes = true;
          }
        }
      }
    }
  }

  for (int i = 0; i < BotSize; ++i)
  {
    if ((bot[i].chip1 == 61 && bot[i].chip2 == 17) ||
        (bot[i].chip2 == 61 && bot[i].chip1 == 17)) return i;
  }
  throw "Eror!";
}

//template<> auto InputData<2016, 10, B>() { return "value 5 goes to bot 2\nbot 2 gives low to bot 1 and high to bot 0\nvalue 3 goes to bot 1\nbot 1 gives low to output 1 and high to bot 0\nbot 0 gives low to output 2 and high to output 0\nvalue 2 goes to bot 2\n";}; // Result: ?
template<> Number AoC<2016, 10, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  constexpr unsigned int BufSize{ 10 };
  constexpr unsigned int BotSize{ 256 };

  class Bot
  {
  public:
    int chip1{ -1 };
    int chip2{ -1 };
    bool outputh{ false };
    int higher{ -1 };
    bool outputl{ false };
    int lower{ -1 };
  };
  using Bots = std::array<Bot,BotSize>;

  Bots bot{};
  std::array<int, BotSize> output{};
  for (int i = 0; i < BotSize; ++i)
  {
    output[i] = -1;
  }

  auto GiveTo = [&bot](int botnr, int value) -> bool
    {
      assert(botnr < BotSize);
      if (bot[botnr].chip1 == value || bot[botnr].chip2 == value) return false;
      if (bot[botnr].chip1 == -1)
      {
        bot[botnr].chip1 = value;
      }
      else
      {
        assert(bot[botnr].chip2 == -1);
        bot[botnr].chip2 = value;
      }
      return true;
    };

  for (const auto& line : v)
  {
    int value{};
    int botnr{};
    // value 5 goes to bot 2
    // bot 2 gives low to bot 1 and high to bot 0
    // bot 1 gives low to output 1 and high to bot 0
    int z1 = sscanf_s(line.c_str(), "value %d goes to bot %d", &value, &botnr);
    if (z1 == 2)
    {
      GiveTo(botnr, value);
      continue;
    }

    char target1[BufSize];
    char target2[BufSize];
    int targetnr1{};
    int targetnr2{};
    int z2 = sscanf_s(line.c_str(), "bot %d gives low to %s %d and high to %s %d", &botnr, target1, BufSize, &targetnr1, target2, BufSize, &targetnr2);
    if (z2 == 5)
    {
      assert(botnr < BotSize);
      bot[botnr].outputl = (target1[0] == 'o');
      bot[botnr].lower = targetnr1;
      bot[botnr].outputh = (target2[0] == 'o');
      bot[botnr].higher = targetnr2;
      continue;
    }
    assert(false);
  }

  bool changes{ true };
  while (changes)
  {
    changes = false;
    for (int i = 0; i < BotSize; ++i)
    {
      if (bot[i].chip1 != -1 && bot[i].chip2 != -1)
      {
        if (bot[i].outputl)
        {
          if (output[bot[i].lower] == -1)
          {
            output[bot[i].lower] = bot[i].chip1 < bot[i].chip2 ? bot[i].chip1 : bot[i].chip2;
            changes = true;
          }
          else
          {
            assert(bot[i].lower == bot[i].chip1 < bot[i].chip2 ? bot[i].chip1 : bot[i].chip2);
          }
        }
        else
        {
          if (GiveTo(bot[i].lower, bot[i].chip1 < bot[i].chip2 ? bot[i].chip1 : bot[i].chip2))
          {
            changes = true;
          }
        }
        if (bot[i].outputh)
        {
          if (output[bot[i].higher] == -1)
          {
            output[bot[i].higher] = bot[i].chip1 > bot[i].chip2 ? bot[i].chip1 : bot[i].chip2;
            changes = true;
          }
          else
          {
            assert(output[bot[i].higher] == bot[i].chip1 > bot[i].chip2 ? bot[i].chip1 : bot[i].chip2);
          }
        }
        else
        {
          if (GiveTo(bot[i].higher, bot[i].chip1 > bot[i].chip2 ? bot[i].chip1 : bot[i].chip2))
          {
            changes = true;
          }
        }
      }
    }
  }

  int result = output[0] * output[1] * output[2];

  return result;
}
