//template<> auto InputData<2023, 7, A>() { return "32T3K 765\nT55J5 684\nKK677 28\nKTJJT 220\nQQQJA 483\n";}; // Result: 6440
template<> Number AoC<2023, 7, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  enum Type
  {
    Undefined = 0,
    HighCard,
    OnePair,
    TwoPair,
    ThreeEq,
    FullH,
    FourEq,
    FiveEq,
  };

  class Card
  {
  public:
    char s;
  public:
    constexpr size_t Value() const noexcept
    {
      constexpr char order[]{ "23456789TJQKA" };
      return std::string_view{ order }.find(s);
    }
    constexpr auto operator <=> (const Card& c) const noexcept { return Value() <=> c.Value(); }
    constexpr auto operator == (const Card& c) const noexcept { return Value() == c.Value(); }
  };

  class Hand
  {
  public:
    std::array<Card, 5> c{};
    Number b{};
    Type t{};
  public:
    void SetType()
    {
      std::array<Card, 5> s{ c };
      std::sort(s.begin(), s.end());
      std::array<int, 5> n{ 0 };
      size_t z{ 0 };
      Card prev{ s[0] };
      for (const Card& cc : s)
      {
        if (cc != prev)
        {
          prev = cc;
          ++z;
        }
        ++n[z];
      }
      std::sort(n.begin(), n.end(), [](const int& n1, const int& n2)->bool {return n1 > n2; });
      switch (n[0])
      {
        case 5: t = FiveEq; return;
        case 4: t = FourEq; return;
        case 3: t = (n[1] == 2 ? FullH : ThreeEq); return;
        case 2: t = (n[1] == 2 ? TwoPair : OnePair); return;
        case 1: t = HighCard; return;
        default: assert(false); return;
      }
    }
    constexpr auto operator <=> (const Hand& h) const noexcept
    {
      if (t < h.t) return -1;
      if (t > h.t) return +1;
      for (size_t i = 0; i < 5; ++i)
      {
        if (c[i].Value() < h.c[i].Value()) return -1;
        if (c[i].Value() > h.c[i].Value()) return +1;
      }
      return 0;
    }

  };

  std::vector<Hand> hand{};
  for (const auto& line : v)
  {
    Hand h{};
    int z = sscanf_s(line.c_str(), "%5c %lld", reinterpret_cast<char*>(h.c.data()), sizeof(h.c), &h.b);
    assert(z == 2);
    h.SetType();
    hand.push_back(h);
  }

  std::sort(hand.begin(), hand.end());

  Number result{ 0 };
  for (size_t i = 0; i < hand.size(); ++i)
  {
    result += (i + 1) * hand[i].b;
  }

  return result;
}

//template<> auto InputData<2023, 7, B>() { return "32T3K 765\nT55J5 684\nKK677 28\nKTJJT 220\nQQQJA 483\n";}; // Result: 5905
template<> Number AoC<2023, 7, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  enum Type
  {
    Undefined = 0,
    HighCard,
    OnePair,
    TwoPair,
    ThreeEq,
    FullH,
    FourEq,
    FiveEq,
  };

  class Card
  {
  public:
    char s;
  public:
    constexpr size_t Value() const noexcept
    {
      constexpr char order[]{ "J23456789TQKA" };
      return std::string_view{ order }.find(s);
    }
    constexpr auto operator <=> (const Card& c) const noexcept { return Value() <=> c.Value(); }
    constexpr auto operator == (const Card& c) const noexcept { return Value() == c.Value(); }
  };

  class Hand
  {
  public:
    std::array<Card, 5> c{};
    Number b{};
    Type t{};
  public:
    void SetType()
    {
      std::array<Card, 5> s{ c };
      std::sort(s.begin(), s.end());
      std::vector<int> n(5,0);
      int nj{ 0 };
      size_t z{ 0 };
      Card prev{ s[0] };
      for (const Card& cc : s)
      {
        if (cc == Card{ 'J' })
        {
          ++nj;
          continue;
        }
        if (cc != prev)
        {
          prev = cc;
          ++z;
        }
        ++n[z];
      }
      std::sort(n.begin(), n.end(), [](const int& n1, const int& n2)->bool { return n1 > n2; });
      switch (nj)
      {
        case 5: t = FiveEq; return;
        case 4: t = FiveEq; return;
        case 3: t = (n[0] == 2 ? FiveEq : FourEq); return;
        case 2:
          switch (n[0])
          {
            case 3: t = FiveEq; return;
            case 2: t = FourEq; return;
            case 1: t = ThreeEq; return;
            default: assert(false); return;
          }
        case 1:
          switch (n[0])
          {
            case 4: t = FiveEq; return;
            case 3: t = FourEq; return;
            case 2: t = (n[1] == 2 ? FullH : ThreeEq); return;
            case 1: t = OnePair; return;
            default: assert(false); return;
          }
        case 0:
          switch (n[0])
          {
            case 5: t = FiveEq; return;
            case 4: t = FourEq; return;
            case 3: t = (n[1] == 2 ? FullH : ThreeEq); return;
            case 2: t = (n[1] == 2 ? TwoPair : OnePair); return;
            case 1: t = HighCard; return;
            default: assert(false); return;
          }
      }
    }
    constexpr auto operator <=> (const Hand& h) const noexcept
    {
      if (t < h.t) return -1;
      if (t > h.t) return +1;
      for (size_t i = 0; i < 5; ++i)
      {
        if (c[i].Value() < h.c[i].Value()) return -1;
        if (c[i].Value() > h.c[i].Value()) return +1;
      }
      return 0;
    }

  };

  std::vector<Hand> hand{};
  for (const auto& line : v)
  {
    Hand h{};
    int z = sscanf_s(line.c_str(), "%5c %lld", reinterpret_cast<char*>(h.c.data()), sizeof(h.c), &h.b);
    assert(z == 2);
    h.SetType();
    hand.push_back(h);
  }

  std::sort(hand.begin(), hand.end());

  Number result{ 0 };
  for (size_t i = 0; i < hand.size(); ++i)
  {
    result += (i + 1) * hand[i].b;
  }

  return result;
}
