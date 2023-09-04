// 2.00 2023-08-01
// 2.01 2023-09-01 added HasOutput
// 2.02 2023-09-04 added HasInput, ExecuteToInput, holdForInput
class IntCodeComputer_2019_200
{
public:
  IntCodeComputer_2019_200(const std::vector<Number>& code) : code_(code) { code_.resize(memsize); }
  void PushInput(Number n) noexcept { in_.push(n); }
  Number PopOutput() { auto f = out_.front(); out_.pop(); return f; }
  bool HasOutput() const noexcept { return !out_.empty(); }
  bool HasInput() const noexcept { return !in_.empty(); }
  bool ExecuteToOutput() { return Execute_(); }
  bool ExecuteToInput() { return Execute_(true); }
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
  bool Execute_(bool holdForInput = false)
  {
    while (true)
    {
      if (holdForInput && (code_[ptrCode] % 100 == 3) && !HasInput()) return true;
      int pmode1 = code_[ptrCode] / 100 % 10;
      int pmode2 = code_[ptrCode] / 1000 % 10;
      int pmode3 = code_[ptrCode] / 10000 % 10;
      switch (code_[ptrCode] % 100)
      {
        case  1: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) + GetVal(code_[ptrCode + 2], pmode2);  ptrCode += 4; break;        // add
        case  2: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) * GetVal(code_[ptrCode + 2], pmode2);  ptrCode += 4; break;        // multiple
        case  3: SetVal(code_[ptrCode + 1], pmode1) = in_.front(); in_.pop();                                                   ptrCode += 2; break;        // input
        case  4: out_.push(GetVal(code_[ptrCode + 1], pmode1));                                                                 ptrCode += 2; return true;  // output
        case  5: if ( GetVal(code_[ptrCode + 1], pmode1)) ptrCode = GetVal(code_[ptrCode + 2], pmode2); else                    ptrCode += 3; break;        // jump-if-true
        case  6: if (!GetVal(code_[ptrCode + 1], pmode1)) ptrCode = GetVal(code_[ptrCode + 2], pmode2); else                    ptrCode += 3; break;        // jump-if-false
        case  7: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) <  GetVal(code_[ptrCode + 2], pmode2); ptrCode += 4; break;        // less-than
        case  8: SetVal(code_[ptrCode + 3], pmode3) = GetVal(code_[ptrCode + 1], pmode1) == GetVal(code_[ptrCode + 2], pmode2); ptrCode += 4; break;        // equal
        case  9: ptrData += GetVal(code_[ptrCode + 1], pmode1);                                                                 ptrCode += 2; break;        // add to ptrData
        case 99:                                                                                                                              return false; // end of program                                                                                
        default: assert(false);                                                                                                               break;
      }
      assert(ptrCode < memsize);
    }
  }
};
