//template<> auto InputData<2016, 2, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 2, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Map = std::array<int, 10>;

  // 1 2 3
  // 4 5 6
  // 7 8 9
  Map L{ 0,1,1,2,4,4,5,7,7,8 };
  Map R{ 0,2,3,3,5,6,6,8,9,9 };
  Map U{ 0,1,2,3,1,2,3,4,5,6 };
  Map D{ 0,4,5,6,7,8,9,7,8,9 };

  int code{ 0 };
  int n{ 5 };
  for (const auto& line : v)
  {
    for (const auto& c : line)
    {
      switch (c)
      {
        case 'U': n = U[n];  break;
        case 'D': n = D[n];  break;
        case 'L': n = L[n];  break;
        case 'R': n = R[n];  break;
      }
    }

    code *= 10;
    code += n;
  }

  return code;
}

//template<> auto InputData<2016, 2, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 2, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  using Map = std::array<char, 14>;

  //     1 
  //   2 3 4
  // 5 6 7 8 9
  //   A B C
  //     D
  Map L{ 0,1,2,2,3,5,5,6,7,8,10,10,11,13 };
  Map R{ 0,1,3,4,4,6,7,8,9,9,11,12,12,13 };
  Map U{ 0,1,2,1,4,5,2,3,4,9,6,7,8,11 };
  Map D{ 0,3,6,7,8,5,10,11,12,9,10,13,12,13 };

  std::string code{};
  char n{ 5 };
  for (const auto& line : v)
  {
    for (const auto& c : line)
    {
      switch (c)
      {
        case 'U': assert(U[n]!=0); n = U[n];  break;
        case 'D': assert(D[n]!=0); n = D[n];  break;
        case 'L': assert(L[n]!=0); n = L[n];  break;
        case 'R': assert(R[n]!=0); n = R[n];  break;
      }
      assert(n != 0);
    }

    code.push_back(n > 9 ? 'A' + n - 10 : '0' + n);
  }

  throw code;
}
