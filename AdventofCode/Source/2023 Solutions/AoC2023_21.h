template<> auto InputData<2023, 21, A>() { return
"...........\n"
".....###.#.\n"
".###.##..#.\n"
"..#.#...#..\n"
"....#.#....\n"
".##..S####.\n"
".##..#...#.\n"
".......##..\n"
".##.#.####.\n"
".##..##.##.\n"
"...........\n"
"6\n"; }; // Result: 16
template<> Number AoC<2023, 21, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 21, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 21, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
