//template<> auto InputData<2016, 19, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 19, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2016, 19, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 19, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector
  return 0;
}