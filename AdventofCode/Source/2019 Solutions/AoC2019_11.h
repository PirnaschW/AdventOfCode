//template<> auto InputData<2019, 11, A>() { return "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99"; };

template<> Number AoC<2019, 11, A>(std::istream& input)
{
  class IntCodeComputer
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

  private:
    const Number memsize{ 2ULL << 10ULL };
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

  using Coord = char;
  Coord x{ 0 };
  Coord y{ 0 };
  Coord orientation{ 0 };

  constexpr int asize{ std::numeric_limits<Coord>::max() - std::numeric_limits<Coord>::min() + 1 };
  constexpr Coord xoff{ std::numeric_limits<Coord>::max()-1 };
  constexpr Coord yoff{ std::numeric_limits<Coord>::max()-1 };
  std::array<std::array<bool, asize>, asize> col{ false };
  std::array<std::array<bool, asize>, asize> vis{ false };

  Coord xmax{ 0 };
  Coord xmin{ 0 };
  Coord ymax{ 0 };
  Coord ymin{ 0 };

  c.PushInput(col[x + xoff][y + yoff] ? 1 : 0);
  while (c.ExecuteToOutput() && c.ExecuteToOutput())  // always receive two outputs
  {
    auto color = c.PopOutput();
    auto rotate = c.PopOutput();

    col[x + xoff][y + yoff] = color;
    vis[x + xoff][y + yoff] = true;
    orientation += 4 + (rotate ? -1 : +1);
    orientation %= 4;
    switch (orientation)
    {
      case 0: --y; break;
      case 1: ++x; break;
      case 2: ++y; break;
      case 3: --x; break;
      default: assert(false); break;
    }

    if (x > xmax) xmax = x;
    if (x < xmin) xmin = x;
    if (y > ymax) ymax = y;
    if (y < ymin) ymin = y;
    assert(xmax < std::numeric_limits<Coord>::max() - 1);
    assert(xmin > std::numeric_limits<Coord>::min() + 1);
    assert(ymax < std::numeric_limits<Coord>::max() - 1);
    assert(ymin > std::numeric_limits<Coord>::min() + 1);

    c.PushInput(col[x + xoff][y + yoff] ? 1 : 0);
  }

  Number z{ 0 };
  for (Coord y0 = ymin - 1; y0 <= ymax + 1; ++y0)
  {
    for (Coord x0 = xmax + 1; x0 >= xmin - 1; --x0)
    {
      if (vis[x0 + xoff][y0 + yoff]) ++z;
    }
  }
  return z;
}

template<> Number AoC<2019, 11, B>(std::istream& input)
{
  class IntCodeComputer
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

  private:
    const Number memsize{ 2ULL << 10ULL };
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

  using Coord = char;
  Coord x{ 0 };
  Coord y{ 0 };
  Coord orientation{ 0 };

  constexpr int asize{ std::numeric_limits<Coord>::max() - std::numeric_limits<Coord>::min() + 1 };
  constexpr Coord xoff{ std::numeric_limits<Coord>::max()-1 };
  constexpr Coord yoff{ std::numeric_limits<Coord>::max()-1 };
  std::array<std::array<bool, asize>, asize> col{ false };
  std::array<std::array<bool, asize>, asize> vis{ false };

  Coord xmax{ 0 };
  Coord xmin{ 0 };
  Coord ymax{ 0 };
  Coord ymin{ 0 };

  col[x + xoff][y + yoff] = true;
  c.PushInput(col[x + xoff][y + yoff] ? 1 : 0);
  while (c.ExecuteToOutput() && c.ExecuteToOutput())  // always receive two outputs
  {
    auto color = c.PopOutput();
    auto rotate = c.PopOutput();

    col[x + xoff][y + yoff] = color;
    vis[x + xoff][y + yoff] = true;
    orientation += 4 + (rotate ? -1 : +1);
    orientation %= 4;
    switch (orientation)
    {
      case 0: --y; break;
      case 1: ++x; break;
      case 2: ++y; break;
      case 3: --x; break;
      default: assert(false); break;
    }

    if (x > xmax) xmax = x;
    if (x < xmin) xmin = x;
    if (y > ymax) ymax = y;
    if (y < ymin) ymin = y;
    assert(xmax < std::numeric_limits<Coord>::max() - 1);
    assert(xmin > std::numeric_limits<Coord>::min() + 1);
    assert(ymax < std::numeric_limits<Coord>::max() - 1);
    assert(ymin > std::numeric_limits<Coord>::min() + 1);

    c.PushInput(col[x + xoff][y + yoff] ? 1 : 0);
  }

  std::string res{};
  res += '\n';
  for (Coord y0 = ymin - 1; y0 <= ymax + 1; ++y0)
  {
    for (Coord x0 = xmax + 1; x0 >= xmin - 1; --x0)
    {
      res += col[x0 + xoff][y0 + yoff] ? '#' : ' ';
    }
    res += '\n';
  }
  throw res;
}
