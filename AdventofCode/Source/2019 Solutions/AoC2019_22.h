//template<> auto InputData<2019, 22, A>() { return "deal with increment 7\ndeal into new stack\ndeal into new stack\n10\n";}; // Result: 0 3 6 9 2 5 8 1 4 7
//template<> auto InputData<2019, 22, A>() { return "cut 6\ndeal with increment 7\ndeal into new stack\n10\n";}; // Result: 3 0 7 4 1 8 5 2 9 6
//template<> auto InputData<2019, 22, A>() { return "deal with increment 7\ndeal with increment 9\ncut -2\n10\n";}; // Result: 6 3 0 7 4 1 8 5 2 9
//template<> auto InputData<2019, 22, A>() { return "deal with increment 3\n10\n";}; // Result: 0 7 4 1 8 5 2 9 6 3
//template<> auto InputData<2019, 22, A>() { return "deal with increment 7\n10\n";}; // Result: 0 3 6 9 2 5 8 1 4 7
//template<> auto InputData<2019, 22, A>() { return "deal with increment 9\n10\n";}; // Result: 0 9 8 7 6 5 4 3 2 1
//template<> auto InputData<2019, 22, A>() { return "deal into new stack\ncut -2\ndeal with increment 7\ncut 8\ncut -4\ndeal with increment 7\ncut 3\ndeal with increment 9\ndeal with increment 3\ncut -1\n10\n";}; // Result: 9 2 5 8 1 4 7 0 3 6
template<> Number AoC<2019, 22, A>(std::istream& input)
{
  class SpaceCards
  {
  public:
    SpaceCards(Number count) : count_(count) { list_.resize(count_); }
    void Apply_DealIntoNewStack() noexcept { position_ = count_ - 1 - position_; step_ *= -1; Normalize(); }
    void Apply_CutAt(Number n) noexcept { position_ -= n; Normalize(); }
    void Apply_DealWithIncrement(Number n) noexcept { step_ *= n; position_ = n * position_;  Normalize(); }
    Number GetAt(Number n) const noexcept { FillList(); return list_[n]; }
    Number GetPos(Number n) const noexcept { return (position_ + step_ * n) % count_; }
    void PrintList() const noexcept
    {
      FillList();
      for (auto i = 0; i < count_; ++i)
        std::cout << list_[i] << ' ';
      std::cout << "   pos=" << position_ << "  step=" << step_ << std::endl;
    }

  private:
    void Normalize() noexcept { position_ += count_; position_ %= count_; step_ += count_; step_ %= count_; }
    void FillList() const noexcept { for (auto i = 0; i < count_; ++i) list_[(position_ + i * step_) % count_] = i; }

  private:
    const Number count_{};
    Number position_{ 0 };
    Number step_{ 1 };
    mutable std::vector<Number> list_{};
  };

  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number count{ 10007 };
  bool Testing{ false };
  if (v[v.size() - 1].size() < 4)  // this is a testcase!
  {
    std::stringstream s(v[v.size() - 1]);
    s >> count;
    v.pop_back();
    Testing = true;
  }

  //for (Number n = -10; n <= 10; ++n)
  //{
  //  SpaceCards pack(count);
  //  pack.Apply_CutAt(n);
  //  pack.List();
  //}

  //for (Number n = 3; n <= 13; ++n)
  //{
  //  if (gcd(n, 10) > 1) continue;
  //  SpaceCards pack(count);
  //  pack.Apply_DealWithIncrement(n);
  //  pack.List();
  //  std::cout << std::endl;
  //}

  //for (Number n = 0; n < 10; ++n)
  //{
  //  for (Number n2 = 3; n2 < 10; ++n2)
  //  {
  //    if (gcd(n2, 10) > 1) continue;
  //    std::cout << "Cut " << n << ", Deal Increment " << n2 << std::endl;

  //    SpaceCards pack(count);
  //    pack.Apply_CutAt(n);
  //    pack.List();
  //    pack.Apply_DealWithIncrement(n2);
  //    pack.List();
  //    pack.Apply_DealIntoNewStack();
  //    pack.List();
  //    std::cout << std::endl;
  //  }
  //  std::cout << std::endl;
  //}

  SpaceCards pack(count);

  auto CheckFor = [](const std::string& str, const std::string& test, Number& n) -> bool
    {
      if (str.substr(0, test.size()) == test)
      {
        std::stringstream s(str.substr(test.size()));
        s >> n;
        return true;
      }
      else
        return false;
    };

  if (Testing) pack.PrintList();
  for (auto i = 0; i < v.size(); ++i)
  {
    Number n{};
    if (CheckFor(v[i], "cut ", n))
    {
      pack.Apply_CutAt(n);
    }
    else
    {
      if (CheckFor(v[i], "deal with increment ", n))
      {
        pack.Apply_DealWithIncrement(n);
      }
      else
      {
        if (CheckFor(v[i], "deal into new stack", n))
        {
          pack.Apply_DealIntoNewStack();
        }
        else
        {
          assert(false);
        }
      }
    }
    if (Testing) pack.PrintList();
  }

//  pack.PrintList();
  return pack.GetPos(2019);
}

//template<> auto InputData<2019, 22, B>() { return " Testdata\n";}; // 
template<> Number AoC<2019, 22, B>(std::istream& input)
{
  class SpaceCards
  {
  public:
    SpaceCards(Number count) : count_(count) { }
    void Apply_DealIntoNewStack() noexcept { position_ = count_ - 1 - position_; step_ *= -1; Normalize(); }
    void Apply_CutAt(Number n) noexcept { position_ -= n; Normalize(); }
    void Apply_DealWithIncrement(Number n) noexcept { step_ *= n; position_ = n * position_;  Normalize(); }
    Number GetPos(Number n) const noexcept { return (position_ + step_ * n) % count_; }

  private:
    void Normalize() noexcept { position_ += count_; position_ %= count_; step_ += count_; step_ %= count_; }

  private:
    const Number count_{};
    Number position_{ 0 };
    Number step_{ 1 };
  };

  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr Number PackSize{ 119315717514047 };
  constexpr Number RepeatCount{ 101741582076661 };

  SpaceCards pack(PackSize);

  auto CheckFor = [](const std::string& str, const std::string& test, Number& n) -> bool
    {
      if (str.substr(0, test.size()) == test)
      {
        std::stringstream s(str.substr(test.size()));
        s >> n;
        return true;
      }
      else
        return false;
    };

  // run once to get effect
  for (auto i = 0; i < v.size(); ++i)
  {
    Number n{};
    if (CheckFor(v[i], "cut ", n))
    {
      pack.Apply_CutAt(n);
    }
    else
    {
      if (CheckFor(v[i], "deal with increment ", n))
      {
        pack.Apply_DealWithIncrement(n);
      }
      else
      {
        if (CheckFor(v[i], "deal into new stack", n))
        {
          pack.Apply_DealIntoNewStack();
        }
        else
        {
          assert(false);
        }
      }
    }
  }
  const Number position = pack.GetPos(0);
  const Number step = pack.GetPos(1) - position;

  // pos(1)(i) = pos + step * i
  // pos(2)(i) = pos + step * pos(1)(i)
  //           = pos + step * pos + step * step * i
  //
  // pos(n)(i) = pos * (step^0 +step^1 + step^2... + step^(n-1)) + step^n*i
  //           = pos * (step^n - 1)/(step - 1) + step^n * i
  //           = pos * Quotient + StepN * i
  //

  const Number StepN = ModuloPower(step, RepeatCount, PackSize);
  const Number invStep1 = ModularInverse(step - 1, PackSize);
  const Number Quotient = ModuloMultiply(StepN - 1,invStep1,PackSize);

  const Number invStepN = ModularInverse(StepN, PackSize);
  const Number Left = (PackSize + 2020 - ModuloMultiply(Quotient, position, PackSize)) % PackSize;
  const Number res = ModuloMultiply(Left,invStepN,PackSize);

  return res; // pack.GetAt(2020);
}
