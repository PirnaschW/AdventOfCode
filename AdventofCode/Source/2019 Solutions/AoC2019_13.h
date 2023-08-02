//template<> auto InputData<2019, 13, A>() { return "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99"; };

template<> Number AoC<2019, 13, A>(std::istream& input)
{
  class IntCodeComputer  // 2.0 2023-08-01
  {
  public:
    IntCodeComputer(const std::vector<Number>& code) : code_(code) { code_.resize(memsize); }
    void PushInput(Number n) { in_.push(n); }
    Number PopOutput() { auto f = out_.front(); out_.pop(); return f; }
    bool ExecuteToOutput() { return Execute_(); }
    bool Process(Number& signal)
    {
      PushInput(signal);
      if (!ExecuteToOutput()) return false;
      signal = PopOutput();
      return true;
    }
    const std::queue<Number>& ExecuteToEnd()
    {
      while (Execute_());
      return out_;
    }
    Number Peek(Number n) const { return GetVal(n, 0); }
    void Poke(Number n, Number val) { SetVal(n, 0) = val; }

  private:
    const Number memsize{ 2ULL << 12ULL };
    std::vector<Number> code_;
    Number ptrCode{ 0 };
    Number ptrData{ 0 };
    std::queue<Number> in_{};   // first in, first used input queue
    std::queue<Number> out_{};  // first out, first returned output queue

  private:
    Number GetVal(Number n, int pmode) const
    {
      switch (pmode)
      {
        case 0: assert(n < memsize);           return code_[n];
        case 1:                                return n;
        case 2: assert(ptrData + n < memsize); return code_[ptrData + n];
        default: assert(false);                return 0;
      }
    };
    Number& SetVal(Number n, int pmode)
    {
      switch (pmode)
      {
        case 0: assert(n < memsize);           return code_[n];
        case 2: assert(ptrData + n < memsize); return code_[ptrData + n];
        default: assert(false);                return code_[0];
      }
    };
    bool Execute_()
    {
      while (true)
      {
        int pmode1 = code_[ptrCode] /   100 % 10;
        int pmode2 = code_[ptrCode] /  1000 % 10;
        int pmode3 = code_[ptrCode] / 10000 % 10;
        switch (code_[ptrCode] % 100)
        {
          case  1: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) + GetVal(code_[ptrCode + 2], pmode2);  ptrCode += 4; break;        // add
          case  2: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) * GetVal(code_[ptrCode + 2], pmode2);  ptrCode += 4; break;        // multiple
          case  3: SetVal(code_[ptrCode + 1], pmode1) = in_.front(); in_.pop();                                                   ptrCode += 2; break;        // input
          case  4: out_.push(GetVal(code_[ptrCode + 1], pmode1));                                                                 ptrCode += 2; return true;  // output
          case  5: if ( GetVal(code_[ptrCode + 1], pmode1)) ptrCode = GetVal(code_[ptrCode + 2], pmode2); else                    ptrCode += 3; break;        // jump-if-true
          case  6: if (!GetVal(code_[ptrCode + 1], pmode1)) ptrCode = GetVal(code_[ptrCode + 2], pmode2); else                    ptrCode += 3; break;        // jump-if-false
          case  7: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1)  < GetVal(code_[ptrCode + 2], pmode2); ptrCode += 4; break;        // less-than
          case  8: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) == GetVal(code_[ptrCode + 2], pmode2); ptrCode += 4; break;        // equal
          case  9: ptrData += GetVal(code_[ptrCode + 1], pmode1);                                                                 ptrCode += 2; break;        // add to ptrData
          case 99:                                                                                                                              return false; // end of program                                                                                
          default: assert(false);                                                                                                               break;
        }
        assert(ptrCode < memsize);
      }
    }
  };

  auto code = ReadNumbers(input, ',');
  IntCodeComputer c(code);

  using Coord = unsigned char;
  using Tile = unsigned char;
  Coord xmax{0};
  Coord ymax{0};
  constexpr Coord sx{45};
  constexpr Coord sy{26};
  std::array<std::array<Tile, sy>, sx> screen{0};

  while (c.ExecuteToOutput() && c.ExecuteToOutput() && c.ExecuteToOutput())  // always receive three outputs
  {
    Coord x = (Coord) c.PopOutput();
    Coord y = (Coord) c.PopOutput();
    Tile z = (Tile) c.PopOutput();
    assert(x < sx);
    assert(y < sy);
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;
    screen[x][y] = z;
  }

  Number res{ 0 };
  for (int y = 0; y < ymax; ++y)
  {
    for (int x = 0; x < xmax; ++x)
    {
      if (screen[x][y] == 2) ++res;
    }
  }

  return res;
}

template<> Number AoC<2019, 13, B>(std::istream& input)
{
  class IntCodeComputer  // 2.0 2023-08-01
  {
  public:
    IntCodeComputer(const std::vector<Number>& code) : code_(code) { code_.resize(memsize); }
    void PushInput(Number n) { in_.push(n); }
    Number PopOutput() { auto f = out_.front(); out_.pop(); return f; }
    bool ExecuteToOutput() { return Execute_(); }
    bool Process(Number& signal)
    {
      PushInput(signal);
      if (!ExecuteToOutput()) return false;
      signal = PopOutput();
      return true;
    }
    const std::queue<Number>& ExecuteToEnd()
    {
      while (Execute_());
      return out_;
    }
    Number Peek(Number n) const { return GetVal(n, 0); }
    void Poke(Number n, Number val) { SetVal(n, 0) = val; }

  private:
    const Number memsize{ 2ULL << 12ULL };
    std::vector<Number> code_;
    Number ptrCode{ 0 };
    Number ptrData{ 0 };
    std::queue<Number> in_{};   // first in, first used input queue
    std::queue<Number> out_{};  // first out, first returned output queue

  private:
    Number GetVal(Number n, int pmode) const
    {
      switch (pmode)
      {
        case 0: assert(n < memsize);           return code_[n];
        case 1:                                return n;
        case 2: assert(ptrData + n < memsize); return code_[ptrData + n];
        default: assert(false);                return 0;
      }
    };
    Number& SetVal(Number n, int pmode)
    {
      switch (pmode)
      {
        case 0: assert(n < memsize);           return code_[n];
        case 2: assert(ptrData + n < memsize); return code_[ptrData + n];
        default: assert(false);                return code_[0];
      }
    };
    bool Execute_()
    {
      while (true)
      {
        int pmode1 = code_[ptrCode] / 100 % 10;
        int pmode2 = code_[ptrCode] / 1000 % 10;
        int pmode3 = code_[ptrCode] / 10000 % 10;
        switch (code_[ptrCode] % 100)
        {
          case  1: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) + GetVal(code_[ptrCode + 2], pmode2);  ptrCode += 4; break;        // add
          case  2: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) * GetVal(code_[ptrCode + 2], pmode2);  ptrCode += 4; break;        // multiple
          case  3: SetVal(code_[ptrCode + 1], pmode1) = in_.front(); in_.pop();                                                   ptrCode += 2; break;        // input
          case  4: out_.push(GetVal(code_[ptrCode + 1], pmode1));                                                                 ptrCode += 2; return true;  // output
          case  5: if (GetVal(code_[ptrCode + 1], pmode1)) ptrCode = GetVal(code_[ptrCode + 2], pmode2); else                    ptrCode += 3; break;        // jump-if-true
          case  6: if (!GetVal(code_[ptrCode + 1], pmode1)) ptrCode = GetVal(code_[ptrCode + 2], pmode2); else                    ptrCode += 3; break;        // jump-if-false
          case  7: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) < GetVal(code_[ptrCode + 2], pmode2); ptrCode += 4; break;        // less-than
          case  8: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) == GetVal(code_[ptrCode + 2], pmode2); ptrCode += 4; break;        // equal
          case  9: ptrData += GetVal(code_[ptrCode + 1], pmode1);                                                                 ptrCode += 2; break;        // add to ptrData
          case 99:                                                                                                                              return false; // end of program                                                                                
          default: assert(false);                                                                                                               break;
        }
        assert(ptrCode < memsize);
      }
    }
  };

  auto code = ReadNumbers(input, ',');
  IntCodeComputer c(code);
  c.Poke(0, 2);
  c.PushInput(0);

  using Coord = char;
  using Tile = unsigned char;
  Coord xmax{ 0 };
  Coord ymax{ 0 };
  constexpr Coord sx{ 45 };
  constexpr Coord sy{ 26 };
  std::array<std::array<Tile, sy>, sx> screen{ 0 };

  Number score{ 0 };
  Coord xBall{ -1 };
  Coord xPaddle{ -1 };
  while (c.ExecuteToOutput() && c.ExecuteToOutput() && c.ExecuteToOutput())  // always receive three outputs
  {
    Coord x = (Coord) c.PopOutput();
    Coord y = (Coord) c.PopOutput();
    assert(x < sx);
    assert(y < sy);
    if (x > xmax) xmax = x;
    if (y > ymax) ymax = y;

    Tile z{0};
    if (x == -1 and y == 0)
    {
      score = c.PopOutput();
    }
    else
    {
      z = (Tile) c.PopOutput();
      screen[x][y] = z;

      switch (z)
      {
        case 4: xBall = x; break;
        case 3: xPaddle = x; break;
        default: break;
      }

      if (z == 4 && xPaddle != -1 && xBall != -1) // after setup, when the new ball position is delivered, compare to ball and move paddle accordingly
      {
        c.PushInput(xBall > xPaddle ? 1 : (xBall < xPaddle ? -1 : 0));
      }
    }
  }

  return score;
}
