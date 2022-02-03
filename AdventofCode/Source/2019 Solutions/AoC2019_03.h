template<> Number AoC<2019, 3, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');
  code[1] = 12;
  code[2] = 2;
  //std::string teststring1{ "1,9,10,3,2,3,11,0,99,30,40,50" };
  //std::string teststring2{ "1,1,1,4,99,5,6,0,99" };
  //std::istringstream test(teststring2);
  //auto code = ReadNumbers(test, ',');


  size_t ptr{ 0 };
  while (true)
  {
    switch (code[ptr])
    {
      case  1: code[code[ptr + 3]] = code[code[ptr + 1]] + code[code[ptr + 2]]; break;
      case  2: code[code[ptr + 3]] = code[code[ptr + 1]] * code[code[ptr + 2]]; break;
      case 99: return code[0];                                                  break;
      default: assert(false);                                                   break;
    }
    ptr += 4;
    assert(ptr < code.size());
  }
}

template<> Number AoC<2019, 3, B>(std::istream& input)
{
  struct H {
    static Number GetResult(std::vector<Number> code)
    {
      size_t ptr{ 0 };
      while (true)
      {
        switch (code[ptr])
        {
          case  1: code[code[ptr + 3]] = code[code[ptr + 1]] + code[code[ptr + 2]]; break;
          case  2: code[code[ptr + 3]] = code[code[ptr + 1]] * code[code[ptr + 2]]; break;
          case 99: return code[0];                                                  break;
          default: return -1;                                                       break;
        }
        ptr += 4;
        if (ptr >= code.size()) return -2;
      }
    }
  };

  auto code = ReadNumbers(input, ',');
  for (int i = 0; i < 100; ++i)
  {
    for (int j = 0; j < 100; ++j)
    {
      code[1] = i;
      code[2] = j;
      if (H::GetResult(code) == 19690720) return 100 * i + j;
    }
  }
  return 0;
}
