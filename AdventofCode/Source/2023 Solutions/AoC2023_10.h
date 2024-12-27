template<> auto InputData<2023, 10, A>() { return "-L|F7\n7S-7|\nL|7||\n-L-J|\nL|-JF\n"; } // Result: 4
//template<> auto InputData<2023, 10, A>() { return "7-F7-\n.FJ|7\nSJLL7\n|F--J\nLJ.LJ\n"; } // Result: 8
template<> Number AoC<2023, 10, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

template<> auto InputData<2023, 10, B>() { return "-L|F7\n7S-7|\nL|7||\n-L-J|\nL|-JF\n"; } // Result: 4
//template<> auto InputData<2023, 10, B>() { return "7-F7-\n.FJ|7\nSJLL7\n|F--J\nLJ.LJ\n"; } // Result: 8
template<> Number AoC<2023, 10, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
