template<> Number AoC<2019, 7, A>(std::istream& input)
{
  auto IntCodeComputer = [](std::vector<Number> code, std::queue<Number> in) -> std::stack<Number>
  {
    std::stack<Number> out{};
    auto param = [&code](Number n, int pmode) -> Number { return pmode ? n : code[n]; };

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
        case 99: return out;                                                                                   break;
        default: assert(false);                                                                                break;
      }
      assert(ptr < code.size());
    }
  };

  auto code = ReadNumbers(input, ',');

  auto RunAmp = [&IntCodeComputer, &code](Number phase, Number sig)->Number
  {
    std::queue<Number> in{};
    in.push(phase);
    in.push(sig);
    auto out = IntCodeComputer(code, in);
    return out.top();
  };

  Number maxSig = std::numeric_limits<decltype(maxSig)>::min();
  for (Number pA = 0; pA <= 4; ++pA)
  {
    auto outA = RunAmp(pA, 0);
    for (Number pB = 0; pB <= 4; ++pB)
    {
      if (pB == pA) continue;
      auto outB = RunAmp(pB, outA);
      for (Number pC = 0; pC <= 4; ++pC)
      {
        if (pC == pA) continue;
        if (pC == pB) continue;
        auto outC = RunAmp(pC, outB);
        for (Number pD = 0; pD <= 4; ++pD)
        {
          if (pD == pA) continue;
          if (pD == pB) continue;
          if (pD == pC) continue;
          auto outD = RunAmp(pD, outC);
          for (Number pE = 0; pE <= 4; ++pE)
          {
            if (pE == pA) continue;
            if (pE == pB) continue;
            if (pE == pC) continue;
            if (pE == pD) continue;
            auto outE = RunAmp(pE, outD);

            if (outE > maxSig) maxSig = outE;

          }
        }
      }
    }
  }

  return maxSig;
}

template<> Number AoC<2019, 7, B>(std::istream& input)
{

  class IntCodeComputer
  {
  public:
    IntCodeComputer(const std::vector<Number>& code, Number phase) : code_(code) { PushInput(phase); }
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
    std::vector<Number> code_;
    size_t ptr{ 0 };
    std::queue<Number> in_{};   // first in, first used input queue
    std::queue<Number> out_{};  // first out, first returned output queue

  private:
    Number Param(Number n, int pmode) const { return pmode ? n : code_[n]; }
    bool Execute_()
    {
      while (true)
      {
        int pmode1 = code_[ptr] / 100 % 10;
        int pmode2 = code_[ptr] / 1000 % 10;
        switch (code_[ptr] % 100)
        {
          case  1: code_[code_[ptr + 3]] = Param(code_[ptr + 1], pmode1) + Param(code_[ptr + 2], pmode2);  ptr += 4; break;        // add
          case  2: code_[code_[ptr + 3]] = Param(code_[ptr + 1], pmode1) * Param(code_[ptr + 2], pmode2);  ptr += 4; break;        // multiple
          case  3: code_[code_[ptr + 1]] = in_.front(); in_.pop();                                         ptr += 2; break;        // input
          case  4: out_.push(Param(code_[ptr + 1], pmode1));                                               ptr += 2; return true;  // output
          case  5: if ( Param(code_[ptr + 1], pmode1)) ptr = Param(code_[ptr + 2], pmode2); else           ptr += 3; break;        // jump-if-true
          case  6: if (!Param(code_[ptr + 1], pmode1)) ptr = Param(code_[ptr + 2], pmode2); else           ptr += 3; break;        // jump-if-false
          case  7: code_[code_[ptr + 3]] = Param(code_[ptr + 1], pmode1)  < Param(code_[ptr + 2], pmode2); ptr += 4; break;        // less-than
          case  8: code_[code_[ptr + 3]] = Param(code_[ptr + 1], pmode1) == Param(code_[ptr + 2], pmode2); ptr += 4; break;        // equal
          case 99:                                                                                                   return false; // end of program                                                                                
          default: assert(false);                                                                                    break;
        }
        assert(ptr < code_.size());
      }
    }
  };

  auto code = ReadNumbers(input, ',');

  auto RunAmp = [&code](Number phase, Number sig)->Number
  {
    IntCodeComputer c(code,phase);
    c.PushInput(sig);
    c.ExecuteToOutput();
    return c.PopOutput();
  };

  Number maxSig = std::numeric_limits<decltype(maxSig)>::min();
  constexpr Number minPhase = 5;
  constexpr Number maxPhase = 9;
  for (Number pA = minPhase; pA <= maxPhase; ++pA)
  {
    for (Number pB = minPhase; pB <= maxPhase; ++pB)
    {
      if (pB == pA) continue;
      for (Number pC = minPhase; pC <= maxPhase; ++pC)
      {
        if (pC == pA) continue;
        if (pC == pB) continue;
        for (Number pD = minPhase; pD <= maxPhase; ++pD)
        {
          if (pD == pA) continue;
          if (pD == pB) continue;
          if (pD == pC) continue;
          for (Number pE = minPhase; pE <= maxPhase; ++pE)
          {
            if (pE == pA) continue;
            if (pE == pB) continue;
            if (pE == pC) continue;
            if (pE == pD) continue;

            IntCodeComputer cA(code, pA);
            IntCodeComputer cB(code, pB);
            IntCodeComputer cC(code, pC);
            IntCodeComputer cD(code, pD);
            IntCodeComputer cE(code, pE);

            Number signal{ 0 };
            while (cA.Process(signal) &&
                   cB.Process(signal) &&
                   cC.Process(signal) &&
                   cD.Process(signal) &&
                   cE.Process(signal));

            if (signal > maxSig) maxSig = signal;

          }
        }
      }
    }
  }

  return maxSig;
}
