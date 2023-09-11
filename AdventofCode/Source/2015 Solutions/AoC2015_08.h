//template<> auto InputData<2015, 8, A>() { return R"--("")--" "\n";}; // Result: 2 - 0 = 2
//template<> auto InputData<2015, 8, A>() { return R"--("abc")--" "\n";}; // Result: 5 - 3 = 2
//template<> auto InputData<2015, 8, A>() { return R"--("aaa\"aaa")--" "\n";}; // Result: 10 - 7 = 3
//template<> auto InputData<2015, 8, A>() { return R"--("\x27")--" "\n";}; // Result: 6 - 1 = 5
//template<> auto InputData<2015, 8, A>() { return R"--("\xyz")--" "\n";}; // Result: 6 - 4 = 2
//template<> auto InputData<2015, 8, A>() { return R"--("")--" "\n" R"--("abc")--" "\n"  R"--("aaa\"aaa")--" "\n" R"--("\x27")--" "\n"; }; // Result: 2+5+10+6 - (0+3+7+1) = 12
//template<> auto InputData<2015, 8, A>() { return R"--("v\xfb\"lgs\"kvjfywmut\x9cr")--" "\n";}; // Result: 28 - 18 = 10
//template<> auto InputData<2015, 8, A>() { return R"--("\"\xe8\"ec\xeah\"qo\\g\"iuqxy\"e\"y\xe7xk\xc6d")--" "\n"; }; // Result: 48 - 27 = 21
//template<> auto InputData<2015, 8, A>() { return R"--("x\"\xcaj\\xwwvpdldz")--" "\n"; }; // Result: 21 - 14 = 7
template<> Number AoC<2015, 8, A>(std::istream& input)
{
  Number zCode{ 0 };
  Number zMem { 0 };
  while (true)
  {
    int c = input.get();
    if (c == std::char_traits<char>::eof()) break;
    if (c == '\n')
    {
      zMem -= 2; // for beginning and end "
      continue;
    }
    char cc = static_cast<char>(c);

    zCode += 1;
    zMem += 1;
    if (c == '\\')
    {
      if (input.peek() == '\"')
      {
        int cb = input.get();  // '"'
        assert(cb == '\"');
        zCode += 1;
      }
      else if (input.peek() == '\\')
      {
        int cb = input.get();  // '\'
        assert(cb == '\\');
        zCode += 1;
      }
      else if (input.peek() == 'x')
      {
        int cx = input.get();  // x
        int ch1 = input.get();  // first hex code 0-f
        int ch2 = input.get();  // second hex code 0-f
        assert(cx == 'x');
        zCode += 3;
        if (!isxdigit(ch1) || !isxdigit(ch2)) // wasn't a valid hex code!
        {
          zMem += 3;
        }
      }
    }
  }

  return zCode - zMem;
}

//template<> auto InputData<2015, 8, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 8, B>(std::istream& input)
{
  Number zCode{ 0 };
  Number zEncode { 0 };
  while (true)
  {
    int c = input.get();
    if (c == std::char_traits<char>::eof()) break;
    if (c == '\n')
    {
      zEncode += 2; // for beginning and end "
      continue;
    }
    char cc = static_cast<char>(c);

    ++zCode;
    ++zEncode;
    switch (c)
    {
      case '\\': ++zEncode; break;
      case '\"': ++zEncode; break;
    }
  }

  return zEncode - zCode;
}
