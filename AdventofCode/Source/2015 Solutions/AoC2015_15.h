//template<> auto InputData<2015, 15, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 15, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  class Ingredient
  {
  public:
    Ingredient() = delete;
    Ingredient(const std::string& name, Number capacity, Number durability, Number flavor, Number texture, Number calories) noexcept :
      name_      (name),
      capacity_  (capacity),
      durability_(durability),
      flavor_    (flavor),
      texture_   (texture),
      calories_  (calories)
    {}

  public:
    const std::string name_;
    const Number capacity_;
    const Number durability_;
    const Number flavor_;
    const Number texture_;
    const Number calories_;
  };

  using Ingredients = std::vector<Ingredient>;
  Ingredients ingredients{};
  constexpr unsigned int BufSize{ 33 };

  for (const auto& line : v)
  {
    char name[BufSize]{};
    Number capacity{};
    Number durability{};
    Number flavor{};
    Number texture{};
    Number calories{};
    // Sprinkles: capacity 5, durability -1, flavor 0, texture 0, calories 5
    int z = sscanf_s(line.c_str(), "%[^:]: capacity %lld, durability %lld, flavor %lld, texture %lld, calories %lld", name, BufSize, &capacity, &durability, &flavor, &texture, &calories);
    assert(z == 6);
    ingredients.emplace_back(name, capacity, durability, flavor, texture, calories);
  }

  using Amounts = std::vector<Number>;
  Amounts amounts{};
  amounts.resize(ingredients.size());
  for (int i = 0; i < amounts.size(); ++i)
  {
    amounts[i] = 0;
  }
  Number score{ 0 };

  auto GetScore = [&ingredients](const Amounts& amounts) -> Number
    {
      Number capacity{};
      Number durability{};
      Number flavor{};
      Number texture{};
      Number calories{};
      for (int i = 0; i < amounts.size(); ++i)
      {
        capacity   += ingredients[i].capacity_   * amounts[i];
        durability += ingredients[i].durability_ * amounts[i];
        flavor     += ingredients[i].flavor_     * amounts[i];
        texture    += ingredients[i].texture_    * amounts[i];
        calories   += ingredients[i].calories_   * amounts[i];
      }
      if (capacity   < 0) capacity   = 0;
      if (durability < 0) durability = 0;
      if (flavor     < 0) flavor     = 0;
      if (texture    < 0) texture    = 0;
      if (calories   < 0) calories   = 0;
      return capacity * durability * flavor * texture;
    };

  auto TryMix = [&ingredients, &score, &GetScore](const Amounts& amounts, const size_t index, auto& TryMix) -> void
    {
      Number usedup{ 0 };
      for (int i = 0; i < index; ++i)
      {
        usedup += amounts[i];
      }
      if (index + 1 == amounts.size())
      {
        Amounts amounts0{ amounts };
        amounts0[index] = 100 - usedup;
        Number s = GetScore(amounts0);
        if (s > score) score = s;
        return;
      }
      for (auto i = 0; i + usedup < 100; ++i)
      {
        Amounts amounts0{ amounts };
        amounts0[index] = i;
        TryMix(amounts0, index + 1, TryMix);
      }
    };

  TryMix(amounts,0,TryMix);

  return score;
}

//template<> auto InputData<2015, 15, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 15, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector


  class Ingredient
  {
  public:
    Ingredient() = delete;
    Ingredient(const std::string& name, Number capacity, Number durability, Number flavor, Number texture, Number calories) noexcept :
      name_      (name),
      capacity_  (capacity),
      durability_(durability),
      flavor_    (flavor),
      texture_   (texture),
      calories_  (calories)
    {}

  public:
    const std::string name_;
    const Number capacity_;
    const Number durability_;
    const Number flavor_;
    const Number texture_;
    const Number calories_;
  };

  using Ingredients = std::vector<Ingredient>;
  Ingredients ingredients{};
  constexpr unsigned int BufSize{ 33 };

  for (const auto& line : v)
  {
    char name[BufSize]{};
    Number capacity{};
    Number durability{};
    Number flavor{};
    Number texture{};
    Number calories{};
    // Sprinkles: capacity 5, durability -1, flavor 0, texture 0, calories 5
    int z = sscanf_s(line.c_str(), "%[^:]: capacity %lld, durability %lld, flavor %lld, texture %lld, calories %lld", name, BufSize, &capacity, &durability, &flavor, &texture, &calories);
    assert(z == 6);
    ingredients.emplace_back(name, capacity, durability, flavor, texture, calories);
  }

  using Amounts = std::vector<Number>;
  Amounts amounts{};
  amounts.resize(ingredients.size());
  for (int i = 0; i < amounts.size(); ++i)
  {
    amounts[i] = 0;
  }
  Number score{ 0 };

  auto GetScore = [&ingredients](const Amounts& amounts) -> Number
    {
      Number capacity{};
      Number durability{};
      Number flavor{};
      Number texture{};
      Number calories{};
      for (int i = 0; i < amounts.size(); ++i)
      {
        capacity   += ingredients[i].capacity_   * amounts[i];
        durability += ingredients[i].durability_ * amounts[i];
        flavor     += ingredients[i].flavor_     * amounts[i];
        texture    += ingredients[i].texture_    * amounts[i];
        calories   += ingredients[i].calories_   * amounts[i];
      }
      if (calories != 500) return 0;
      if (capacity   < 0) capacity   = 0;
      if (durability < 0) durability = 0;
      if (flavor     < 0) flavor     = 0;
      if (texture    < 0) texture    = 0;
      if (calories   < 0) calories   = 0;
      return capacity * durability * flavor * texture;
    };

  auto TryMix = [&ingredients, &score, &GetScore](const Amounts& amounts, const size_t index, auto& TryMix) -> void
    {
      Number usedup{ 0 };
      for (int i = 0; i < index; ++i)
      {
        usedup += amounts[i];
      }
      if (index + 1 == amounts.size())
      {
        Amounts amounts0{ amounts };
        amounts0[index] = 100 - usedup;
        Number s = GetScore(amounts0);
        if (s > score) score = s;
        return;
      }
      for (auto i = 0; i + usedup < 100; ++i)
      {
        Amounts amounts0{ amounts };
        amounts0[index] = i;
        TryMix(amounts0, index + 1, TryMix);
      }
    };

  TryMix(amounts,0,TryMix);

  return score;
}
