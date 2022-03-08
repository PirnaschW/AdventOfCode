
//template<> auto InputData<2019, 9, A>() { return "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99"; };
//template<> auto InputData<2019, 9, A>() { return "1102,34915192,34915192,7,4,7,99,0"; };
//template<> auto InputData<2019, 9, A>() { return "104,1125899906842624,99"; };
//template<> auto InputData<2019, 9, A>() { return "104,1125899906842624,99";};

//template<> auto InputData<2019, 9, A>() { return "109,-1,4,1,99";};//outputs - 1
//template<> auto InputData<2019, 9, A>() { return "109,-1,104,1,99";};//outputs 1
//template<> auto InputData<2019, 9, A>() { return "109,-1,204,1,99";};//outputs 109
//template<> auto InputData<2019, 9, A>() { return "109,1,9,2,204,-6,99";}; // outputs 204
//template<> auto InputData<2019, 9, A>() { return "109,1,109,9,204,-6,99";}; // outputs 204
//template<> auto InputData<2019, 9, A>() { return "109,1,209,-1,204,-106,99"; }; // outputs 204
//template<> auto InputData<2019, 9, A>() { return "109,1,3,3,204,2,99";};// outputs the input
//template<> auto InputData<2019, 9, A>() { return "109,1,203,2,204,2,99";}; // outputs the input

template<> Number AoC<2019, 9, A>(std::istream& input)
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
  c.PushInput(1);
  auto out = c.ExecuteToEnd();

  //while (out.size() > 0)
  //{
  //  std::cout << out.front() << " "; out.pop();
  //}
  //std::cout << '\n';
  assert(out.size() == 1);
  return out.front();
}

template<> Number AoC<2019, 9, B>(std::istream& input)
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
  c.PushInput(2);
  auto out = c.ExecuteToEnd();

  //while (out.size() > 0)
  //{
  //  std::cout << out.front() << " "; out.pop();
  //}
  //std::cout << '\n';
  assert(out.size() == 1);
  return out.front();
}
