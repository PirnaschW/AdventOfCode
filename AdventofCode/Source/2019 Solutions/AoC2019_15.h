//template<> auto InputData<2019, 15, A>() { return "10 ORE => 10 A\n1 ORE => 1 B\n7 A, 1 B => 1 C\n7 A, 1 C => 1 D\n7 A, 1 D => 1 E\n7 A, 1 E => 1 FUEL\n"; };  // 31
template<> Number AoC<2019, 15, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);  // read all lines into vector

  return 0;
}


//template<> auto InputData<2019, 15, B>() { return "157 ORE => 5 NZVS\n165 ORE => 6 DCFZ\n12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"; }; // 
template<> Number AoC<2019, 15, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);  // read all lines into vector

  return 0;
}
