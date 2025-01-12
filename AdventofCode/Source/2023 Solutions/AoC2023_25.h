template<> auto InputData<2023, 25, A>() { return
"jqt: rhn xhk nvd\n"
"rsh: frs pzl lsr\n"
"xhk: hfx\n"
"cmg: qnr nvd lhk bvb\n"
"rhn: xhk bvb hfx\n"
"bvb: xhk hfx\n"
"pzl: lsr hfx nvd\n"
"qnr: nvd\n"
"ntq: jqt hfx bvb xhk\n"
"nvd: lhk\n"
"lsr: lhk\n"
"rzs: qnr cmg lsr rsh\n"
"frs: qnr lhk lsr\n";}; // Result: 54
template<> Number AoC<2023, 25, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 25, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 25, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
