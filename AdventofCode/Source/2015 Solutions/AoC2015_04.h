//template<> auto InputData<2015, 4, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 4, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  MD5::MD5 md5;

  for (int i = 0; i < 1'000'000'000; ++i)
  {
    std::stringstream s{};
    s << v[0] << i;
    std::string hash = md5.digestString(s.str().c_str());
    if (hash.substr(0, 5) == "00000")
      return i;
  }
  throw "Error";
}

//template<> auto InputData<2015, 4, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 4, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  MD5::MD5 md5;

  for (int i = 0; i < 1'000'000'000; ++i)
  {
    std::stringstream s{};
    s << v[0] << i;
    std::string hash = md5.digestString(s.str().c_str());
    if (hash.substr(0, 6) == "000000")
      return i;
  }
  throw "Error";
}
