template<> auto InputData<2023, 24, A>() { return
"19, 13, 30 @ -2,  1, -2\n"
"18, 19, 22 @ -1, -1, -2\n"
"20, 25, 34 @ -2, -2, -4\n"
"12, 31, 28 @ -1, -2, -1\n"
"20, 19, 15 @  1, -5, -3\n"
"Area: 7, 27";}; // Result: 2
template<> Number AoC<2023, 24, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 24, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 24, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
