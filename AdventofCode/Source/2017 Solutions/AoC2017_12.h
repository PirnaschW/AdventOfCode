//template<> auto InputData<2017, 12, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2017, 12, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2017, 12, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2017, 12, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
