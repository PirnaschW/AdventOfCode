//template<> auto InputData<2016, 25, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 25, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2016, 25, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 25, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  return 0;
}
