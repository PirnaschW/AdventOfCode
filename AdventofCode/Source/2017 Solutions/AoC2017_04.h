//template<> auto InputData<2017, 4, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2017, 4, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2017, 4, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2017, 4, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
