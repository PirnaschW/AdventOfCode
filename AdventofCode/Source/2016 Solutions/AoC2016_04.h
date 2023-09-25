//template<> auto InputData<2016, 4, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 4, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Pair = std::pair<char, int>;
  std::array<Pair, 26> charcount0{};
  for (char i = 0; i < charcount0.size(); ++i)
  {
    charcount0[i].first = 'a' + i;
    charcount0[i].second = 0;
  }

  constexpr unsigned int BufSize{ 64 };
  int sum{ 0 };
  for (const auto& line : v)
  {
    char name[BufSize]{};
    char checksum[5]{};
    int sector{ 0 };
    int count{ 0 };
    // aaaaa-bbb-z-y-x-123[abxyz]
    int z = sscanf_s(line.c_str(), "%[^1234567890]%d[%5c]%n", name, BufSize, &sector, checksum, 5, &count);
    assert(z == 3);
    assert(count == line.size());

    std::array<Pair, 26> charcount{ charcount0 };
    for (const auto& c : name)
    {
      if (c == '-') continue;
      if (c == '\0') break;
      ++(charcount[c - 'a'].second);
    }
    std::sort(charcount.begin(), charcount.end(), [](const Pair& p1, const Pair& p2) -> bool { return (p1.second == p2.second) ? (p1.first < p2.first) : (p1.second > p2.second); });

    bool valid{ true };
    for (int i = 0; i < 5; ++i)
    {
      if (checksum[i] != charcount[i].first)
      {
        valid = false;
      }
    }
    if (valid) sum += sector;
  }

  return sum;
}

//template<> auto InputData<2016, 4, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 4, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Pair = std::pair<char, int>;
  std::array<Pair, 26> charcount0{};
  for (char i = 0; i < charcount0.size(); ++i)
  {
    charcount0[i].first = 'a' + i;
    charcount0[i].second = 0;
  }

  constexpr unsigned int BufSize{ 64 };
  int sector{ 0 };
  for (const auto& line : v)
  {
    char name[BufSize]{};
    char checksum[5]{};
    sector = 0;
    int count{ 0 };
    // aaaaa-bbb-z-y-x-123[abxyz]
    int z = sscanf_s(line.c_str(), "%[^1234567890]%d[%5c]%n", name, BufSize, &sector, checksum, 5, &count);
    assert(z == 3);
    assert(count == line.size());

    std::array<Pair, 26> charcount{ charcount0 };
    for (const auto& c : name)
    {
      if (c == '-') continue;
      if (c == '\0') break;
      ++(charcount[c - 'a'].second);
    }
    std::sort(charcount.begin(), charcount.end(), [](const Pair& p1, const Pair& p2) -> bool { return (p1.second == p2.second) ? (p1.first < p2.first) : (p1.second > p2.second); });

    bool valid{ true };
    for (int i = 0; i < 5; ++i)
    {
      if (checksum[i] != charcount[i].first)
      {
        valid = false;
      }
    }
    if (valid)
    {
      for (int i = 0; name[i] != '\0'; ++i)
      {
        if (name[i] == '-') continue;
        name[i] = ((name[i] - 'a') + sector) % 26 + 'a';
      }
      if (std::string(name) == std::string("northpole-object-storage-")) break;
    }
  }

  return sector;
}
