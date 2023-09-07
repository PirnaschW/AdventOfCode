//template<> auto InputData<2023, 1, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 1, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 1, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 1, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
