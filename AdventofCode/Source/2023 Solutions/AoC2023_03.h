template<> auto InputData<2023, 3, A>()
  {
    return
      "467..114..\n"
      "...*......\n"
      "..35..633.\n"
      "......#...\n"
      "617*......\n"
      ".....+.58.\n"
      "..592.....\n"
      "......755.\n"
      "...$.*....\n"
      ".664.598..\n";
  }; // Result: 4361
template<> Number AoC<2023, 3, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  return 0;
}

//template<> auto InputData<2023, 3, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 3, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
