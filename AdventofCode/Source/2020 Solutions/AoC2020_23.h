void AoC2020_23A(std::istream& input)
{
  using Container = std::list<int>;
  using Iterator = Container::iterator;
  constexpr size_t PickupCount = 3;

  struct H
  {
    static void MakeMove(Container& cups)
    {
      // pick up three cups
      Container pickup{};
      for (int i = 0; i < PickupCount; i++)
      {
        pickup.push_back(cups.front());
        cups.pop_front();
      }

      // save next 'current'
      size_t nextcurr = cups.front();
      
      // find destination
      size_t target = cups.back();
      Iterator it{ cups.end() };
      while (it == cups.end())
      {
        if (target == 1) target = cups.size() + PickupCount + 1;
        it = std::find(cups.begin(), cups.end(), --target);
      }

      // place cups back in circle
      it++;
      if (it == cups.end())
        it = cups.begin();
      while (pickup.size() > 0)
      {
        cups.insert(it,pickup.front());
        pickup.pop_front();
      }

      // find next 'current'
      Iterator itc{ cups.end() };
      while (itc == cups.end())
      {
        itc = std::find(cups.begin(), cups.end(), nextcurr);
      }
      itc++;
      if (itc == cups.end())
        itc = cups.begin();

      // rotate to next 'current'
      std::rotate(cups.begin(), itc, cups.end());
    }
  };

  Container cups{};

  // read the cup sequence
  std::string line{};
  getline(input, line);
  for (const auto& c : line)
    cups.push_back(c - '0');

  // rotate current cup out
  Iterator curr = cups.begin();
  std::rotate(cups.begin(), ++curr, cups.end());

  // play the game
  for (int i = 0; i < 100; ++i)
  {
    H::MakeMove(cups);
  }

  // find cup '1'
  Iterator it = std::find(cups.begin(), cups.end(), 1);

  // rotate to destination
  std::rotate(cups.begin(), it, cups.end());

  // generate result string
  std::string s{};
  cups.pop_front();
  while (cups.size() > 0)
  {
    s += cups.front() + '0';
    cups.pop_front();
  }

  std::cout << s << std::endl;
}

void AoC2020_23B(std::istream& input)
{
  constexpr size_t CupCount = 1'000'000;
  constexpr size_t MoveCount = 10'000'000;
  constexpr size_t PickupCount = 3;

  using Container = std::array<int, CupCount + 1>;
  Container& cups = *(new Container());


  struct H
  {
    static void MakeMove(Container& cups)
    {
      // pick up three cups
      int current = cups[0];
      int takeout1 = cups[current];   assert(ValidCup(takeout1));
      int takeout2 = cups[takeout1];  assert(ValidCup(takeout2));
      int takeout3 = cups[takeout2];  assert(ValidCup(takeout3));
      int remainder = cups[takeout3]; assert(ValidCup(remainder));
      cups[current] = remainder;      assert(ValidCup(cups[current]));

      // find destination cup
      int dest = current - 1;
      while (dest < 1 || dest == takeout1 || dest == takeout2 || dest == takeout3)
      {
        if (--dest < 1) dest = CupCount;
      }

      assert(dest >= 1);
      assert(dest <= CupCount);

      // insert the three cups
      cups[takeout3] = cups[dest]; assert(ValidCup(cups[takeout3]));
      cups[dest] = takeout1;       assert(ValidCup(cups[dest]));

      // select next 'current'
      cups[0] = cups[current];     assert(ValidCup(cups[0]));
    }

    static bool ValidCup(int cup) { return cup >= 1 && cup <= CupCount; }
  };

  // read the cup sequence
  std::string line{};
  getline(input, line);
  int z{ 0 };
  for (const auto& c : line)
    z = cups[z] = c - '0';

  for (int i = static_cast<int>(line.size() + 1); i <= CupCount; ++i)
    z = cups[z] = i;

  cups[z] = cups[0]; // after the last cup comes again the first

  // play the game
  for (int i = 0; i < MoveCount; ++i)
  {
    H::MakeMove(cups);
//    if (!(i % 100'000)) std::cout << i << std::endl;
  }


  // generate result string
  Number z1 = cups[1];
  Number z2 = cups[z1];
  std::cout << z1 * z2 << std::endl;
}
