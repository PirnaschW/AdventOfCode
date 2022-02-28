template<> Number AoC<2019, 5, A>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  auto param = [&code](Number n, int pmode) -> Number { return pmode ? n : code[n]; };

  std::queue<Number> in{};
  std::stack<Number> out{};
  in.push(1);
  size_t ptr{ 0 };
  while (true)
  {
    int pmode1 = code[ptr] / 100 % 10;
    int pmode2 = code[ptr] / 1000 % 10;
    switch (code[ptr] % 100)
    {
      case  1: code[code[ptr + 3]] = param(code[ptr + 1], pmode1) + param(code[ptr + 2], pmode2); ptr += 4; break;
      case  2: code[code[ptr + 3]] = param(code[ptr + 1], pmode1) * param(code[ptr + 2], pmode2); ptr += 4; break;
      case  3: code[code[ptr + 1]] = in.front(); in.pop();                                        ptr += 2; break;
      case  4: out.push(param(code[ptr + 1], pmode1));                                            ptr += 2; break;
      case 99: return out.top();                                                                            break;
      default: assert(false);                                                                               break;
    }
    assert(ptr < code.size());
  }
}

template<> Number AoC<2019, 5, B>(std::istream& input)
{
  auto code = ReadNumbers(input, ',');

  auto param = [&code](Number n, int pmode) -> Number { return pmode ? n : code[n]; };

  std::queue<Number> in{};
  std::stack<Number> out{};
  in.push(5);
  size_t ptr{ 0 };
  while (true)
  {
    int pmode1 = code[ptr] / 100 % 10;
    int pmode2 = code[ptr] / 1000 % 10;
    switch (code[ptr] % 100)
    {
      case  1: code[code[ptr + 3]] = param(code[ptr + 1], pmode1) + param(code[ptr + 2], pmode2);  ptr += 4; break;  // add
      case  2: code[code[ptr + 3]] = param(code[ptr + 1], pmode1) * param(code[ptr + 2], pmode2);  ptr += 4; break;  // multiple
      case  3: code[code[ptr + 1]] = in.front(); in.pop();                                         ptr += 2; break;  // input
      case  4: out.push(param(code[ptr + 1], pmode1));                                             ptr += 2; break;  // output
      case  5: if ( param(code[ptr + 1], pmode1)) ptr = param(code[ptr + 2], pmode2); else         ptr += 3; break;  // jump-if-true
      case  6: if (!param(code[ptr + 1], pmode1)) ptr = param(code[ptr + 2], pmode2); else         ptr += 3; break;  // jump-if-false
      case  7: code[code[ptr + 3]] = param(code[ptr + 1], pmode1) <  param(code[ptr + 2], pmode2); ptr += 4; break;  // less-than
      case  8: code[code[ptr + 3]] = param(code[ptr + 1], pmode1) == param(code[ptr + 2], pmode2); ptr += 4; break;  // equal
      case 99: return out.top();                                                                             break;
      default: assert(false);                                                                                break;
    }
    assert(ptr < code.size());
  }
}
