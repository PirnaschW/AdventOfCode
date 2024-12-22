//template<> auto InputData<2016, 16, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 16, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  auto Iter = [](const std::string& s) -> std::string
    {
      std::string res{s};
      res.resize(s.size() * 2 + 1);

      res[s.size()] = '0';
      for (int i = 0; i < s.size(); ++i)
      {
        res[res.size()-1-i] = s[i] == '0' ? '1' : '0';
      }
      return res;
    };

  assert(Iter("1") == "100");
  assert(Iter("0") == "001");
  assert(Iter("11111") == "11111000000");
  assert(Iter("111100001010") == "1111000010100101011110000");

  // 10010000000110000
  constexpr int req{ 272 };

  std::string s{ v[0] };
  while (s.size() < req)
  {
    s = Iter(s);
  }
  s.resize(req);

  std::string checksum = s;
  do
  {
    std::string next{};
    next.resize(checksum.size() / 2);
    for (int i = 0; i < checksum.size() / 2; ++i)
    {
      next[i] = checksum[2 * i] == checksum[2 * i + 1] ? '1' : '0';
    }
    std::swap(checksum, next);
  }
  while (checksum.size() % 2 == 0);

  throw checksum;
}

//template<> auto InputData<2016, 16, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 16, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  auto Iter = [](const std::string& s) -> std::string
    {
      std::string res{s};
      res.resize(s.size() * 2 + 1);

      res[s.size()] = '0';
      for (int i = 0; i < s.size(); ++i)
      {
        res[res.size()-1-i] = s[i] == '0' ? '1' : '0';
      }
      return res;
    };

  assert(Iter("1") == "100");
  assert(Iter("0") == "001");
  assert(Iter("11111") == "11111000000");
  assert(Iter("111100001010") == "1111000010100101011110000");

  // 10010000000110000
  constexpr int req{ 35651584 };

  std::string s{ v[0] };
  while (s.size() < req)
  {
    s = Iter(s);
  }
  s.resize(req);

  std::string checksum = s;
  do
  {
    std::string next{};
    next.resize(checksum.size() / 2);
    for (int i = 0; i < checksum.size() / 2; ++i)
    {
      next[i] = checksum[2 * i] == checksum[2 * i + 1] ? '1' : '0';
    }
    std::swap(checksum, next);
  }
  while (checksum.size() % 2 == 0);

  throw checksum;
}
