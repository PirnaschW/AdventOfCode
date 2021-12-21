
void AoC2020_08B(std::istream& input)
{
  using OpCode = int;
  using IPtr = int;
  struct Code
  {
    OpCode opcode{ 0 };
    int param{ 0 };
  };
  const std::unordered_map<std::string, OpCode> compile{
    { "nop", 0 },
    { "jmp", 1 },
    { "acc", 2 },
  };
  std::vector<Code> program{};


  // read and 'compile' program
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  for (const auto& line : v)
  {
    std::istringstream str(line);
    std::string opcode{};
    Code c;
    str >> opcode >> c.param;
    c.opcode = compile.find(opcode)->second;
    program.emplace_back(c);
  }

  // define virtual machine
  class VirtualMachine
  {
  public:
    IPtr Execute(OpCode op, int param)
    {
      Verify(op, param);
      switch (op)
      {
        case 0: return ++ptr;
        case 1: ptr += param; return ptr;
        case 2: acc += param; return ++ptr;
        default: return ptr;
      }
    }
    virtual void Verify(OpCode op, int param) = 0;
  public:
    IPtr ptr{ 0 };
    int acc{ 0 };
  };

  class VM8B : public VirtualMachine
  {
  public:
    void Verify(OpCode op, int param) override
    {
      if (used.contains(ptr)) throw acc;
      used.insert(ptr);
    }
  public:
    std::unordered_set<IPtr> used{};
  };

  for (int i = 0; i < program.size(); ++i) // try all lines
  {
    OpCode changeto{};
    switch (program[i].opcode)
    {
      case 0: changeto = 1; break;
      case 1: changeto = 0; break;
      default: continue; // not allowed to change
    }
    std::vector<Code> program0{ program };
    program0[i].opcode = changeto;

    // run program
    VM8B vm;
    IPtr ptr{ 0 };
    try {
      while (true)
      {
        ptr = vm.Execute(program0[ptr].opcode, program0[ptr].param);
        if (ptr >= program.size())
        {
          std::cout << vm.acc << std::endl;
          return;
        }
      }
    }
    catch (int)
    {
      // keep going with next try
    }
  }
}


void AoC2020_08A(std::istream& input)
{
  using OpCode = int;
  using IPtr = int;
  struct Code
  {
    OpCode opcode{ 0 };
    int param{ 0 };
  };
  const std::unordered_map<std::string, OpCode> compile{
    { "nop", 0 },
    { "jmp", 1 },
    { "acc", 2 },
  };
  std::vector<Code> program{};


  // read and 'compile' program
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  for (const auto& line : v)
  {
    std::istringstream str(line);
    std::string opcode{};
    Code c;
    str >> opcode >> c.param;
    c.opcode = compile.find(opcode)->second;
    program.emplace_back(c);
  }

  // define virtual machine
  class VirtualMachine
  {
  public:
    IPtr Execute(OpCode op, int param)
    {
      Verify(op, param);
      switch (op)
      {
        case 0: return ++ptr;
        case 1: ptr += param; return ptr;
        case 2: acc += param; return ++ptr;
        default: return ptr;
      }
    }
    virtual void Verify(OpCode op, int param) = 0;
  public:
    IPtr ptr{ 0 };
    int acc{ 0 };
  };

  class VM8A : public VirtualMachine
  {
  public:
    void Verify(OpCode op, int param) override
    {
      if (used.contains(ptr)) throw acc;
      used.insert(ptr);
    }
  public:
    std::unordered_set<IPtr> used{};
  };

  // run program
  VM8A vm;
  IPtr ptr{ 0 };
  try {
    while (true) ptr = vm.Execute(program[ptr].opcode, program[ptr].param);
  }
  catch (int z)
  {
    std::cout << z << std::endl;
  }
}
