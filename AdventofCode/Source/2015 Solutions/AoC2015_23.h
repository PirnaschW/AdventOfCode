//template<> auto InputData<2015, 23, A>() { return "inc a\njio a, +2\ntpl a\ninc a\n";}; // Result: a = 2
template<> Number AoC<2015, 23, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector
  // inc a
  // jio a, +2
  // tpl a
  // inc a


  enum class IType
  {
    hlf,
    tpl,
    inc,
    jmp,
    jie,
    jio,
  };

  using enum IType;

  class CPU
  {
  public:
    unsigned int p{0};
    unsigned long long a{0};
    unsigned long long b{0};
  };

  class Instruction
  {
//    using enum IType;
  public:
    Instruction() = delete;
    Instruction(IType type, const std::string& s) : type_(type)
    { 
      int z{ 0 };
      switch (type_)
      {
        case hlf:
        case tpl:
        case inc:
          z = sscanf_s(s.c_str(), "%c", &register_, 1);
          assert(z == 1);
          break;
        case jmp:
          z = sscanf_s(s.c_str(), "%d", &offset_);
          assert(z == 1);
          break;
        case jie:
        case jio:
          z = sscanf_s(s.c_str(), "%c, %d", &register_, 1, &offset_);
          assert(z == 2);
          break;
        default:
          assert(false);
          break;
      }
    };
    void Execute(CPU& cpu)
    { 
      switch (type_)
      {
        case hlf: (register_ == 'a' ? cpu.a : cpu.b) /= 2;    ++cpu.p;                      break;
        case tpl: (register_ == 'a' ? cpu.a : cpu.b) *= 3;    ++cpu.p;                      break;
        case inc: ++(register_ == 'a' ? cpu.a : cpu.b);       ++cpu.p;                      break;
        case jmp:                                               cpu.p += offset_;           break;
        case jie: ((register_ == 'a' ? cpu.a : cpu.b) %  2) ? ++cpu.p : cpu.p += offset_;   break;
        case jio: ((register_ == 'a' ? cpu.a : cpu.b) == 1) ?   cpu.p += offset_ : ++cpu.p; break;
        default: assert(false);                                                            break;
      }
    };
  private:
    const IType type_{};
    char register_{};
    int offset_{};
  };

  std::vector<Instruction> code{};

  for (int i=0; i<v.size(); ++i)
  {
     // hlf r      // sets register r to half its current value, then continues with the next instruction.
     // tpl r      // sets register r to triple its current value, then continues with the next instruction.
     // inc r      // increments register r, adding 1 to it, then continues with the next instruction.
     // jmp offset // is a jump; it continues with the instruction offset away relative to itself.
     // jie r      // offset is like jmp, but only jumps if register r is even ("jump if even").
     // jio r      // offset is like jmp, but only jumps if register r is 1 ("jump if one", not odd).
    if (v[i].substr(0, 3) == "hlf") code.emplace_back(hlf, v[i].substr(4));
    if (v[i].substr(0, 3) == "tpl") code.emplace_back(tpl, v[i].substr(4));
    if (v[i].substr(0, 3) == "inc") code.emplace_back(inc, v[i].substr(4));
    if (v[i].substr(0, 3) == "jmp") code.emplace_back(jmp, v[i].substr(4));
    if (v[i].substr(0, 3) == "jie") code.emplace_back(jie, v[i].substr(4));
    if (v[i].substr(0, 3) == "jio") code.emplace_back(jio, v[i].substr(4));
  }

  CPU cpu{};
  do
  {
    code[cpu.p].Execute(cpu);
  }
  while (cpu.p < code.size());

  return cpu.b;
}

//template<> auto InputData<2015, 23, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 23, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector
  // inc a
  // jio a, +2
  // tpl a
  // inc a


  enum class IType
  {
    hlf,
    tpl,
    inc,
    jmp,
    jie,
    jio,
  };

  using enum IType;

  class CPU
  {
  public:
    unsigned int p{0};
    unsigned long long a{0};
    unsigned long long b{0};
  };

  class Instruction
  {
    //    using enum IType;
  public:
    Instruction() = delete;
    Instruction(IType type, const std::string& s) : type_(type)
    { 
      int z{ 0 };
      switch (type_)
      {
        case hlf:
        case tpl:
        case inc:
          z = sscanf_s(s.c_str(), "%c", &register_, 1);
          assert(z == 1);
          break;
        case jmp:
          z = sscanf_s(s.c_str(), "%d", &offset_);
          assert(z == 1);
          break;
        case jie:
        case jio:
          z = sscanf_s(s.c_str(), "%c, %d", &register_, 1, &offset_);
          assert(z == 2);
          break;
        default:
          assert(false);
          break;
      }
    };
    void Execute(CPU& cpu)
    { 
      switch (type_)
      {
        case hlf: (register_ == 'a' ? cpu.a : cpu.b) /= 2;    ++cpu.p;                      break;
        case tpl: (register_ == 'a' ? cpu.a : cpu.b) *= 3;    ++cpu.p;                      break;
        case inc: ++(register_ == 'a' ? cpu.a : cpu.b);       ++cpu.p;                      break;
        case jmp:                                               cpu.p += offset_;           break;
        case jie: ((register_ == 'a' ? cpu.a : cpu.b) %  2) ? ++cpu.p : cpu.p += offset_;   break;
        case jio: ((register_ == 'a' ? cpu.a : cpu.b) == 1) ?   cpu.p += offset_ : ++cpu.p; break;
        default: assert(false);                                                            break;
      }
    };
  private:
    const IType type_{};
    char register_{};
    int offset_{};
  };

  std::vector<Instruction> code{};

  for (int i=0; i<v.size(); ++i)
  {
    // hlf r      // sets register r to half its current value, then continues with the next instruction.
    // tpl r      // sets register r to triple its current value, then continues with the next instruction.
    // inc r      // increments register r, adding 1 to it, then continues with the next instruction.
    // jmp offset // is a jump; it continues with the instruction offset away relative to itself.
    // jie r      // offset is like jmp, but only jumps if register r is even ("jump if even").
    // jio r      // offset is like jmp, but only jumps if register r is 1 ("jump if one", not odd).
    if (v[i].substr(0, 3) == "hlf") code.emplace_back(hlf, v[i].substr(4));
    if (v[i].substr(0, 3) == "tpl") code.emplace_back(tpl, v[i].substr(4));
    if (v[i].substr(0, 3) == "inc") code.emplace_back(inc, v[i].substr(4));
    if (v[i].substr(0, 3) == "jmp") code.emplace_back(jmp, v[i].substr(4));
    if (v[i].substr(0, 3) == "jie") code.emplace_back(jie, v[i].substr(4));
    if (v[i].substr(0, 3) == "jio") code.emplace_back(jio, v[i].substr(4));
  }

  CPU cpu{};
  cpu.a = 1;
  do
  {
    code[cpu.p].Execute(cpu);
  }
  while (cpu.p < code.size());

  return cpu.b;
}
