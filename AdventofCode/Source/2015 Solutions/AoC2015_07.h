//template<> auto InputData<2015, 7, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 7, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Wire
  {
  public:
    Wire() = delete;
    constexpr Wire(char c1, char c2) : c1_{ c1 }, c2_{ c2 } {}
    constexpr size_t Hash() const noexcept { return c1_ << 8 | c2_; }
    constexpr bool operator==(const Wire& w) const noexcept { return c1_ == w.c1_ && c2_ == w.c2_; }
  private:
    char c1_{};
    char c2_{};
  };

  enum class OpType
  {
    Set,
    Not,
    And,
    Or,
    LShift,
    RShift,
  };

  class Value
  {
  public:
    static Value CreateValue(const char* s)
    {
      if (!isdigit(s[0])) return Value(Wire(s[0], s[1]));
      Number z;
      int n = sscanf_s(s, "%lld", &z);
      assert(n == 1);
      return Value(z);
    }
    constexpr Value(Number z) : isNumber_(true), w_{ Wire('\0','\0') }, z_(z) {}
    constexpr Value(const Wire& w) : isNumber_(false), w_(w), z_(0LL) {}
    constexpr bool IsNumber() const noexcept { return calculated_ || isNumber_; }
    constexpr Wire GetWire() const { assert(!isNumber_);  return w_; }
    constexpr Number GetNumber() const { assert(calculated_ || isNumber_);  return calculated_ ? z0_ : z_; }
    constexpr void SetNumber(Number z) const noexcept { calculated_ = true; z0_ = z; }
  private:
    mutable bool calculated_{ false };
    const bool isNumber_;
    const Wire w_;
    const Number z_;
    mutable Number z0_;
  };


  class SourceOp
  {
  public:
    SourceOp(OpType ot, const Value& source1, const Value& source2, const Value& dest) : ot_{ ot }, v1_{ source1 }, v2_{ source2 }, d_{ dest.GetWire() } {}
  public:
    const OpType ot_;
    const Value v1_;
    const Value v2_;
    const Wire d_;
  };

  using OpMap = std::unordered_map < Wire, SourceOp, decltype([](const Wire& w)->size_t {return w.Hash(); }), decltype([](const Wire& w1, const Wire& w2)->bool {return w1 == w2; }) > ;
  OpMap opmap{};

  for (const auto& line : v)
  {
    constexpr unsigned int BufferSize{ 33 };
    OpType ot{};
    char p1[BufferSize]{};
    char p2[BufferSize]{};
    char p3[BufferSize]{};

    // 1 -> x
    // NOT a -> x
    // a AND b -> x
    // a OR b -> x
    // a LSHIFT 1 -> x
    // a RSHIFT 1 -> x
    if      (2 == sscanf_s(line.c_str(), "          %s -> %s", p1, BufferSize,                 p3, BufferSize)) ot = OpType::Set;
    else if (2 == sscanf_s(line.c_str(), "   NOT    %s -> %s", p1, BufferSize,                 p3, BufferSize)) ot = OpType::Not;
    else if (3 == sscanf_s(line.c_str(), "%s AND    %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::And;
    else if (3 == sscanf_s(line.c_str(), "%s  OR    %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::Or;
    else if (3 == sscanf_s(line.c_str(), "%s LSHIFT %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::LShift;
    else if (3 == sscanf_s(line.c_str(), "%s RSHIFT %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::RShift;
    else assert(false);

    SourceOp op(ot, Value::CreateValue(p1), Value::CreateValue(p2), Value::CreateValue(p3));
    opmap.insert({ Wire(p3[0],p3[1]), op });
  }

  class H
  {
  public:
    static Number GetValue(const OpMap& opmap, const Value& v)
    {
      if (v.IsNumber()) return v.GetNumber();
      const SourceOp& op = opmap.at(v.GetWire());
      Number z = GetValue_(opmap, op);
      v.SetNumber(z);
      return z;
    }  
    static Number GetValue_(const OpMap& opmap, const SourceOp& op)
    {
      switch (op.ot_)
      {
        case OpType::Set:    return  GetValue(opmap, op.v1_);
        case OpType::Not:    return ~GetValue(opmap, op.v1_);
        case OpType::And:    return  GetValue(opmap, op.v1_) &  GetValue(opmap, op.v2_);
        case OpType::Or:     return  GetValue(opmap, op.v1_) |  GetValue(opmap, op.v2_);
        case OpType::LShift: return  GetValue(opmap, op.v1_) << GetValue(opmap, op.v2_);
        case OpType::RShift: return  GetValue(opmap, op.v1_) >> GetValue(opmap, op.v2_);
        default: assert(false); return 0;
      }
    }  
  };


  Number res = H::GetValue(opmap,Value::CreateValue("a"));

  return res;
}

//template<> auto InputData<2015, 7, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 7, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Wire
  {
  public:
    Wire() = delete;
    constexpr Wire(char c1, char c2) : c1_{ c1 }, c2_{ c2 } {}
    constexpr size_t Hash() const noexcept { return c1_ << 8 | c2_; }
    constexpr bool operator==(const Wire& w) const noexcept { return c1_ == w.c1_ && c2_ == w.c2_; }
  private:
    char c1_{};
    char c2_{};
  };

  enum class OpType
  {
    Set,
    Not,
    And,
    Or,
    LShift,
    RShift,
  };

  class Value
  {
  public:
    static Value CreateValue(const char* s)
    {
      if (!isdigit(s[0])) return Value(Wire(s[0], s[1]));
      Number z;
      int n = sscanf_s(s, "%lld", &z);
      assert(n == 1);
      return Value(z);
    }
    constexpr Value(Number z) : isNumber_(true), w_{ Wire('\0','\0') }, z_(z) {}
    constexpr Value(const Wire& w) : isNumber_(false), w_(w), z_(0LL) {}
    constexpr bool IsNumber() const noexcept { return calculated_ || isNumber_; }
    constexpr Wire GetWire() const { assert(!isNumber_);  return w_; }
    constexpr Number GetNumber() const { assert(calculated_ || isNumber_);  return calculated_ ? z0_ : z_; }
    constexpr void SetNumber(Number z) const noexcept { calculated_ = true; z0_ = z; }
  private:
    mutable bool calculated_{ false };
    const bool isNumber_;
    const Wire w_;
    const Number z_;
    mutable Number z0_;
  };


  class SourceOp
  {
  public:
    SourceOp(OpType ot, const Value& source1, const Value& source2, const Value& dest) : ot_{ ot }, v1_{ source1 }, v2_{ source2 }, d_{ dest.GetWire() } {}
  public:
    const OpType ot_;
    const Value v1_;
    const Value v2_;
    const Wire d_;
  };

  using OpMap = std::unordered_map < Wire, SourceOp, decltype([](const Wire& w)->size_t {return w.Hash(); }), decltype([](const Wire& w1, const Wire& w2)->bool {return w1 == w2; }) > ;
  OpMap opmap{};

  for (const auto& line : v)
  {
    constexpr unsigned int BufferSize{ 33 };
    OpType ot{};
    char p1[BufferSize]{};
    char p2[BufferSize]{};
    char p3[BufferSize]{};

    // 1 -> x
    // NOT a -> x
    // a AND b -> x
    // a OR b -> x
    // a LSHIFT 1 -> x
    // a RSHIFT 1 -> x
    if      (2 == sscanf_s(line.c_str(), "          %s -> %s", p1, BufferSize,                 p3, BufferSize)) ot = OpType::Set;
    else if (2 == sscanf_s(line.c_str(), "   NOT    %s -> %s", p1, BufferSize,                 p3, BufferSize)) ot = OpType::Not;
    else if (3 == sscanf_s(line.c_str(), "%s AND    %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::And;
    else if (3 == sscanf_s(line.c_str(), "%s  OR    %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::Or;
    else if (3 == sscanf_s(line.c_str(), "%s LSHIFT %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::LShift;
    else if (3 == sscanf_s(line.c_str(), "%s RSHIFT %s -> %s", p1, BufferSize, p2, BufferSize, p3, BufferSize)) ot = OpType::RShift;
    else assert(false);

    SourceOp op(ot, Value::CreateValue(p1), Value::CreateValue(p2), Value::CreateValue(p3));
    opmap.insert({ Wire(p3[0],p3[1]), op });
  }

  class H
  {
  public:
    static Number GetValue(const OpMap& opmap, const Value& v)
    {
      if (v.IsNumber()) return v.GetNumber();
      const SourceOp& op = opmap.at(v.GetWire());
      Number z = GetValue_(opmap, op);
      v.SetNumber(z);
      return z;
    }  
    static Number GetValue_(const OpMap& opmap, const SourceOp& op)
    {
      switch (op.ot_)
      {
        case OpType::Set:    return  GetValue(opmap, op.v1_);
        case OpType::Not:    return ~GetValue(opmap, op.v1_);
        case OpType::And:    return  GetValue(opmap, op.v1_) &  GetValue(opmap, op.v2_);
        case OpType::Or:     return  GetValue(opmap, op.v1_) |  GetValue(opmap, op.v2_);
        case OpType::LShift: return  GetValue(opmap, op.v1_) << GetValue(opmap, op.v2_);
        case OpType::RShift: return  GetValue(opmap, op.v1_) >> GetValue(opmap, op.v2_);
        default: assert(false); return 0;
      }
    }  
  };

  OpMap opmap0{ opmap };
  Number a = H::GetValue(opmap0,Value::CreateValue("a"));

  Wire b('b', '\0');
  opmap.erase(b);
  opmap.insert({ b, SourceOp(OpType::Set, Value(a), Value(a), Value(b)) });
  Number a1 = H::GetValue(opmap,Value::CreateValue("a"));

  return a1;
}
