//template<> auto InputData<2019, 21, A>() { return "Testdata\n"; };  // 
template<> Number AoC<2019, 21, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  using Coord = char;

  IntCodeComputer_2019_200 icc(code);

  bool testing{ false };

  while (true)
  {
    icc.ExecuteToOutput();
    char c = static_cast<char>(icc.PopOutput());
    if(testing) std::cout << c;
    if (c == '\n') break;
  }


  // #####.#..########

  // ABCD -> J
  // 0000 -> x = dead
  // 0001 -> 1
  // 0010 -> x = dead
  // 0011 -> 1
  // 0100 -> x = dead
  // 0101 -> 1
  // 0110 -> x = dead
  // 0111 -> 1
  // 1000 -> 0
  // 1001 -> 1?
  // 1010 -> 0
  // 1011 -> 1?
  // 1100 -> 0
  // 1101 -> 1
  // 1110 -> 0
  // 1111 -> 0


  // XABC -> J
  // 0000 -> x = dead
  // 0001 -> 1
  // 0010 -> x = dead
  // 0011 -> 1
  // 0100 -> x = dead
  // 0101 -> 1
  // 0110 -> x = dead
  // 0111 -> 1
  // 1000 -> 0
  // 1001 -> 1
  // 1010 -> 0
  // 1011 -> 1
  // 1100 -> 0
  // 1101 -> 1
  // 1110 -> 0
  // 1111 -> 1

  // NOT A J
  // NOT B T
  // OR T J
  // AND D J

  //NOT D T
  //NOT T J

// A = 1, B = 1 -> ^J
// C = 0, D = 1 -> J

//  std::string command{ "NOT A J\nWALK\n" };
//  std::string command{ "OR D J\nWALK\n" };
  std::string command{ "NOT A J\nNOT C T\nOR T J\nAND D J\nWALK\n" };

  // NOT, AND, OR: 3
  // A, B, C, D, T, J: 6
  // T, J: 2
  // 3 * 6 * 2 = 36




  for (auto& c : command)
  {
    icc.PushInput(c);
  }

  Number res{ 0 };
  while (true)
  {
    icc.ExecuteToOutput();
    assert(icc.HasOutput());
    res = icc.PopOutput();
    if (res > std::numeric_limits<char>::max()) break;
    char c = static_cast<char>(res);
    if(testing) std::cout << c;
  }

  return res;
}


//template<> auto InputData<2019, 21, B>() { return "Testdata\n"; };  // 
template<> Number AoC<2019, 21, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  using Coord = char;

  IntCodeComputer_2019_200 icc(code);

  bool testing{ false };

  while (true)
  {
    icc.ExecuteToOutput();
    char c = static_cast<char>(icc.PopOutput());
    if(testing) std::cout << c;
    if (c == '\n') break;
  }

  std::string command{ "NOT A J\nNOT B T\nOR T J\nNOT C T\nOR T J\nAND D J\nNOT D T\nOR E T\nOR H T\nAND T J\nRUN\n" };
  for (auto& c : command)
  {
    icc.PushInput(c);
  }

  Number res{ 0 };
  while (true)
  {
    icc.ExecuteToOutput();
    assert(icc.HasOutput());
    res = icc.PopOutput();
    if (res > std::numeric_limits<char>::max()) break;
    char c = static_cast<char>(res);
    if(testing) std::cout << c;
  }

  return res;
}
