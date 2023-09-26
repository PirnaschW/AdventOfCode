//template<> auto InputData<2016, 5, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 5, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector
  // ojvtpuvg

  MD5::MD5 md5;

  std::string code{};
  for (int i = 0; i < 1'000'000'000; ++i)
  {
    std::stringstream s{};
    s << v[0] << i;
    std::string hash = md5.digestString(s.str().c_str());
    if (hash.substr(0, 5) == "00000" && hash[5] != '0')
    {
      code.push_back(hash[5]);
      if (code.size() == 8) break;
    }
  }
  assert(code.size() == 8);

  throw code;
}

//template<> auto InputData<2016, 5, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 5, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // ojvtpuvg

  MD5::MD5 md5;

  char code[9]{"\0\0\0\0\0\0\0\0"};
  char done{ 0 };
  auto SetDigit = [&code,&done](char digit, char value) -> bool
    {
      char index = digit - '0';
      if (index < 0 || index > 7) return false;
      if (code[index] != '\0') return false;
      code[index] = value;
      return ++done == 8;
    };


  for (int i = 0; i < 1'000'000'000; ++i)
  {
    //if (i % 100000 == 0) std::cout << i << std::endl;
    std::stringstream s{};
    s << v[0] << i;
    std::string hash = md5.digestString(s.str().c_str());
    if (hash.substr(0, 5) == "00000")
    {
      //std::cout << i << ": " << hash[5] << hash[6] << std::endl;
      if (SetDigit(hash[5], hash[6])) break;
    }
  }

  throw code;
}
