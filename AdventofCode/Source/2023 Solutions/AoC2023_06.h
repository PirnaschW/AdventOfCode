template<> auto InputData<2023, 6, A>() { return "Time:      7  15   30\nDistance:  9  40  200\n";}; // Result: 288
template<> Number AoC<2023, 6, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 6, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 6, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
