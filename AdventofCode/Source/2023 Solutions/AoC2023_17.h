template<> auto InputData<2023, 17, A>() { return
"2413432311323\n"
"3215453535623\n"
"3255245654254\n"
"3446585845452\n"
"4546657867536\n"
"1438598798454\n"
"4457876987766\n"
"3637877979653\n"
"4654967986887\n"
"4564679986453\n"
"1224686865563\n"
"2546548887735\n"
"4322674655533\n";}; // Result: 102
template<> Number AoC<2023, 17, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 17, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 17, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
