//template<> auto InputData<2016, 12, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 12, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  enum class IType
  {
    set,
    cpy,
    inc,
    dec,
    jnz,
    jmp,
  };

  using enum IType;

  class CPU
  {
  public:
    Number p{0};
    std::array<Number,4> r{0};
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
        case set:
          z = sscanf_s(s.c_str(), "%lld %c", &value_, &register2_, 1);
          assert(z == 2);
          break;
        case cpy:
          z = sscanf_s(s.c_str(), "%c %c", &register1_, 1, &register2_, 1);
          assert(z == 2);
          break;
        case inc:
        case dec:
          z = sscanf_s(s.c_str(), "%c", &register1_, 1);
          assert(z == 1);
          break;
        case jnz:
          z = sscanf_s(s.c_str(), "%c %lld", &register1_, 1, &offset_);
          assert(z == 2);
          break;
        case jmp:
          z = sscanf_s(s.c_str(), "%lld %lld", &value_, &offset_);
          assert(z == 2);
          if (value_ == 0) offset_ = 1;
          break;
        default:
          assert(false);
          break;
      }
    };
    void Execute(CPU& cpu) const
    { 
      switch (type_)
      {
        case set: cpu.r[register2_-'a'] = value_;                   ++cpu.p;           break;
        case cpy: cpu.r[register2_-'a'] = cpu.r[register1_-'a'];    ++cpu.p;           break;
        case inc: ++cpu.r[register1_-'a'];                          ++cpu.p;           break;
        case dec: --cpu.r[register1_-'a'];                          ++cpu.p;           break;
        case jnz: cpu.p += (cpu.r[register1_-'a'] == 0 ? 1 : offset_);                 break;
        case jmp: cpu.p += offset_;                                                    break;
        default: assert(false);                                                        break;
      }
    };
  private:
    const IType type_{};
    char register1_{};
    char register2_{};
    Number value_{};
    Number offset_{};
  };

  std::vector<Instruction> code{};

  for (int i = 0; i < v.size(); ++i)
  {
    // cpy x y copies x (either an integer or the value of a register) into register y.
    // inc x increases the value of register x by one.
    // dec x decreases the value of register x by one.
    // jnz x y jumps to an instruction y away (positive means forward; negative means backward), but only if x is not zero.
    if (v[i].substr(0, 3) == "cpy") code.emplace_back(isdigit(v[i][4]) ? set : cpy, v[i].substr(4));
    if (v[i].substr(0, 3) == "inc") code.emplace_back(inc, v[i].substr(4));
    if (v[i].substr(0, 3) == "dec") code.emplace_back(dec, v[i].substr(4));
    if (v[i].substr(0, 3) == "jnz") code.emplace_back(isdigit(v[i][4]) ? jmp : jnz, v[i].substr(4));
  }

  CPU cpu{};
  do
  {
    code[cpu.p].Execute(cpu);
  }
  while (cpu.p < static_cast<Number>(code.size()));

  return cpu.r[0];
}

//template<> auto InputData<2016, 12, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 12, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  enum class IType
  {
    set,
    cpy,
    inc,
    dec,
    jnz,
    jmp,
  };

  using enum IType;

  class CPU
  {
  public:
    Number p{0};
    std::array<Number,4> r{0};
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
        case set:
          z = sscanf_s(s.c_str(), "%lld %c", &value_, &register2_, 1);
          assert(z == 2);
          break;
        case cpy:
          z = sscanf_s(s.c_str(), "%c %c", &register1_, 1, &register2_, 1);
          assert(z == 2);
          break;
        case inc:
        case dec:
          z = sscanf_s(s.c_str(), "%c", &register1_, 1);
          assert(z == 1);
          break;
        case jnz:
          z = sscanf_s(s.c_str(), "%c %lld", &register1_, 1, &offset_);
          assert(z == 2);
          break;
        case jmp:
          z = sscanf_s(s.c_str(), "%lld %lld", &value_, &offset_);
          assert(z == 2);
          if (value_ == 0) offset_ = 1;
          break;
        default:
          assert(false);
          break;
      }
    };
    void Execute(CPU& cpu) const
    { 
      switch (type_)
      {
        case set: cpu.r[register2_-'a'] = value_;                   ++cpu.p;           break;
        case cpy: cpu.r[register2_-'a'] = cpu.r[register1_-'a'];    ++cpu.p;           break;
        case inc: ++cpu.r[register1_-'a'];                          ++cpu.p;           break;
        case dec: --cpu.r[register1_-'a'];                          ++cpu.p;           break;
        case jnz: cpu.p += (cpu.r[register1_-'a'] == 0 ? 1 : offset_);                 break;
        case jmp: cpu.p += offset_;                                                    break;
        default: assert(false);                                                        break;
      }
    };
  private:
    const IType type_{};
    char register1_{};
    char register2_{};
    Number value_{};
    Number offset_{};
  };

  std::vector<Instruction> code{};

  for (int i = 0; i < v.size(); ++i)
  {
    // cpy x y copies x (either an integer or the value of a register) into register y.
    // inc x increases the value of register x by one.
    // dec x decreases the value of register x by one.
    // jnz x y jumps to an instruction y away (positive means forward; negative means backward), but only if x is not zero.
    if (v[i].substr(0, 3) == "cpy") code.emplace_back(isdigit(v[i][4]) ? set : cpy, v[i].substr(4));
    if (v[i].substr(0, 3) == "inc") code.emplace_back(inc, v[i].substr(4));
    if (v[i].substr(0, 3) == "dec") code.emplace_back(dec, v[i].substr(4));
    if (v[i].substr(0, 3) == "jnz") code.emplace_back(isdigit(v[i][4]) ? jmp : jnz, v[i].substr(4));
  }

  CPU cpu{};
  cpu.r['c' - 'a'] = 1;
  do
  {
    code[cpu.p].Execute(cpu);
  }
  while (cpu.p < static_cast<Number>(code.size()));

  return cpu.r[0];
}
