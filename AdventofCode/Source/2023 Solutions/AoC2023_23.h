template<> auto InputData<2023, 23, A>() { return
"#.#####################\n"
"#.......#########...###\n"
"#######.#########.#.###\n"
"###.....#.>.>.###.#.###\n"
"###v#####.#v#.###.#.###\n"
"###.>...#.#.#.....#...#\n"
"###v###.#.#.#########.#\n"
"###...#.#.#.......#...#\n"
"#####.#.#.#######.#.###\n"
"#.....#.#.#.......#...#\n"
"#.#####.#.#.#########v#\n"
"#.#...#...#...###...>.#\n"
"#.#.#v#######v###.###v#\n"
"#...#.>.#...>.>.#.###.#\n"
"#####v#.#.###v#.#.###.#\n"
"#.....#...#...#.#.#...#\n"
"#.#########.###.#.#.###\n"
"#...###...#...#...#.###\n"
"###.###.#.###v#####v###\n"
"#...#...#.#.>.>.#.>.###\n"
"#.###.###.#.###.#.#v###\n"
"#.....###...###...#...#\n"
"#####################.#\n";}; // Result: 94
template<> Number AoC<2023, 23, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 23, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 23, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
