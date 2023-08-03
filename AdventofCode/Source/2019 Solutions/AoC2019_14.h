//template<> auto InputData<2019, 14, A>() { return "10 ORE => 10 A\n1 ORE => 1 B\n7 A, 1 B => 1 C\n7 A, 1 C => 1 D\n7 A, 1 D => 1 E\n7 A, 1 E => 1 FUEL\n"; };  // 31
//template<> auto InputData<2019, 14, A>() { return "9 ORE => 2 A\n8 ORE => 3 B\n7 ORE => 5 C\n3 A, 4 B => 1 AB\n5 B, 7 C => 1 BC\n4 C, 1 A => 1 CA\n2 AB, 3 BC, 4 CA => 1 FUEL\n"; }; // 165
//template<> auto InputData<2019, 14, A>() { return "157 ORE => 5 NZVS\n165 ORE => 6 DCFZ\n44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL\n12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"
//                                                  "179 ORE => 7 PSHF\n177 ORE => 5 HKGWZ\n7 DCFZ, 7 PSHF => 2 XJWVT\n165 ORE => 2 GPVTF\n3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT\n"; }; // 13312
//template<> auto InputData<2019, 14, A>() { return "2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG\n17 NVRVD, 3 JNWZP => 8 VPVL\n53 STKFG, 6 MNCFX, 46 VJHF, 81 HVMC, 68 CXFTF, 25 GNMV => 1 FUEL\n"
//                                                  "22 VJHF, 37 MNCFX => 5 FWMGM\n139 ORE => 4 NVRVD\n144 ORE => 7 JNWZP\n5 MNCFX, 7 RFSQX, 2 FWMGM, 2 VPVL, 19 CXFTF => 3 HVMC\n5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV\n"
//                                                  "145 ORE => 6 MNCFX\n1 NVRVD => 8 CXFTF\n1 VJHF, 6 MNCFX => 4 RFSQX\n176 ORE => 6 VJHF\n"; }; // 180697
//template<> auto InputData<2019, 14, A>() { return "171 ORE => 8 CNZTR\n7 ZLQW, 3 BMBT, 9 XCVML, 26 XMNCP, 1 WPTQ, 2 MZWV, 1 RJRHP => 4 PLWSL\n114 ORE => 4 BHXH\n14 VRPVC => 6 BMBT\n"
//                                                  "6 BHXH, 18 KTJDG, 12 WPTQ, 7 PLWSL, 31 FHTLT, 37 ZDVW => 1 FUEL\n6 WPTQ, 2 BMBT, 8 ZLQW, 18 KTJDG, 1 XMNCP, 6 MZWV, 1 RJRHP => 6 FHTLT\n"
//                                                  "15 XDBXC, 2 LTCX, 1 VRPVC => 6 ZLQW\n13 WPTQ, 10 LTCX, 3 RJRHP, 14 XMNCP, 2 MZWV, 1 ZLQW => 1 ZDVW\n5 BMBT => 4 WPTQ\n189 ORE => 9 KTJDG\n"
//                                                  "1 MZWV, 17 XDBXC, 3 XCVML => 2 XMNCP\n12 VRPVC, 27 CNZTR => 2 XDBXC\n15 KTJDG, 12 BHXH => 5 XCVML\n3 BHXH, 2 VRPVC => 7 MZWV\n121 ORE => 7 VRPVC\n"
//                                                  "7 XCVML => 6 RJRHP\n5 BHXH, 4 VRPVC => 5 LTCX\n"; }; // 2210736
template<> Number AoC<2019, 14, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  class Ingredient
  {
  public:
    Number z{ 0 };
    std::string n{};
    Number level;
  };

  class Reaction
  {
  public:
    std::vector<Ingredient> in{};
    Ingredient out;
    Number level{ 0 };
  };

  std::unordered_map<std::string,Reaction> list{};

  std::unordered_map<std::string,Reaction> reqs{};

  for (const auto& line : v)
  {
    std::vector<Ingredient> in{};

    std::stringstream s(line);
    bool more{ true };
    while (more)
    {
      Number z;
      std::string n;
      s >> z >> n;

      if (n[n.size() - 1] == ',')  // = more ingredients to come
      {
        n.pop_back();
      }
      else more = false;

      in.push_back(Ingredient(z, n));
    }
    assert(in.size() > 0);

    {
      std::string arrow;
      s >> arrow;
      assert(arrow == "=>");
    }

    Number z;
    std::string n;
    s >> z >> n;

    list.insert({ n,Reaction(in, Ingredient(z, n)) });
  }

  // assign levels to the reactions
  bool more{ true };
  while (more)
  {
    more = false;
    for (auto& r : list)
    {
      if (r.second.level > 0) continue;  // already done
      
      Number maxlevel{ 0 };
      for (auto i : r.second.in)  // for all ingredients
      {
        if (i.n == "ORE") // ORE is level 1
        {
          if (1 > maxlevel) maxlevel = 1;
        }
        else
        {
          const auto& reaction = list.find(i.n)->second;
          if (reaction.level == 0) // not ready yet
          {
            more = true;
            maxlevel = 0;
            break;
          }
          else
          {
            if (reaction.level > maxlevel) maxlevel = reaction.level;
          }
        }
      }

      if (maxlevel > 0) r.second.level = maxlevel + 1;
    }
  }

  std::unordered_map<std::string,Ingredient> needed{};
  for (const auto& r : list)
  {
    needed.insert({ r.second.out.n,Ingredient(0, r.second.out.n, list.find(r.second.out.n)->second.level) });
  }

  needed.insert({ "ORE",Ingredient(0, "ORE", 1) });
  needed["FUEL"].z = 1;

  Number maxlevel{ 0 };
  for (auto const& i : needed)
  {
    if (i.second.z > 0 && i.second.level > maxlevel) maxlevel = i.second.level;
  }
  while (maxlevel > 1)
  {
    for (auto& i : needed)
    {
      if (i.second.z == 0) continue; // not needed, skip
      if (i.second.level < maxlevel) continue; // only build highest level components

      Number realneed = i.second.z;
      auto reaction = list[i.second.n];
      realneed += reaction.out.z - 1;
      realneed /= reaction.out.z;

      for (auto in : reaction.in)  // for all ingredients
      {
        needed[in.n].z += realneed * in.z;  // add our needs to it
      }
      i.second.z = 0;
    }
    --maxlevel;
  }

  Number z = needed["ORE"].z;
  return z;
}


//template<> auto InputData<2019, 14, B>() { return "157 ORE => 5 NZVS\n165 ORE => 6 DCFZ\n44 XJWVT, 5 KHKGT, 1 QDVJ, 29 NZVS, 9 GPVTF, 48 HKGWZ => 1 FUEL\n12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"
//                                                  "179 ORE => 7 PSHF\n177 ORE => 5 HKGWZ\n7 DCFZ, 7 PSHF => 2 XJWVT\n165 ORE => 2 GPVTF\n3 DCFZ, 7 NZVS, 5 HKGWZ, 10 PSHF => 8 KHKGT\n"; }; // 82892753
//template<> auto InputData<2019, 14, B>() { return "2 VPVL, 7 FWMGM, 2 CXFTF, 11 MNCFX => 1 STKFG\n17 NVRVD, 3 JNWZP => 8 VPVL\n53 STKFG, 6 MNCFX, 46 VJHF, 81 HVMC, 68 CXFTF, 25 GNMV => 1 FUEL\n"
//                                                  "22 VJHF, 37 MNCFX => 5 FWMGM\n139 ORE => 4 NVRVD\n144 ORE => 7 JNWZP\n5 MNCFX, 7 RFSQX, 2 FWMGM, 2 VPVL, 19 CXFTF => 3 HVMC\n5 VJHF, 7 MNCFX, 9 VPVL, 37 CXFTF => 6 GNMV\n"
//                                                  "145 ORE => 6 MNCFX\n1 NVRVD => 8 CXFTF\n1 VJHF, 6 MNCFX => 4 RFSQX\n176 ORE => 6 VJHF\n"; }; // 5586022
//template<> auto InputData<2019, 14, B>() { return "171 ORE => 8 CNZTR\n7 ZLQW, 3 BMBT, 9 XCVML, 26 XMNCP, 1 WPTQ, 2 MZWV, 1 RJRHP => 4 PLWSL\n114 ORE => 4 BHXH\n14 VRPVC => 6 BMBT\n"
//                                                  "6 BHXH, 18 KTJDG, 12 WPTQ, 7 PLWSL, 31 FHTLT, 37 ZDVW => 1 FUEL\n6 WPTQ, 2 BMBT, 8 ZLQW, 18 KTJDG, 1 XMNCP, 6 MZWV, 1 RJRHP => 6 FHTLT\n"
//                                                  "15 XDBXC, 2 LTCX, 1 VRPVC => 6 ZLQW\n13 WPTQ, 10 LTCX, 3 RJRHP, 14 XMNCP, 2 MZWV, 1 ZLQW => 1 ZDVW\n5 BMBT => 4 WPTQ\n189 ORE => 9 KTJDG\n"
//                                                  "1 MZWV, 17 XDBXC, 3 XCVML => 2 XMNCP\n12 VRPVC, 27 CNZTR => 2 XDBXC\n15 KTJDG, 12 BHXH => 5 XCVML\n3 BHXH, 2 VRPVC => 7 MZWV\n121 ORE => 7 VRPVC\n"
//                                                  "7 XCVML => 6 RJRHP\n5 BHXH, 4 VRPVC => 5 LTCX\n"; }; // 460664
template<> Number AoC<2019, 14, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);  // read all lines into vector

  class Ingredient
  {
  public:
    Number z{ 0 };
    std::string n{};
    Number level;
  };

  class Reaction
  {
  public:
    std::vector<Ingredient> in{};
    Ingredient out;
    Number level{ 0 };
  };

  std::unordered_map<std::string,Reaction> list{};

  std::unordered_map<std::string,Reaction> reqs{};

  for (const auto& line : v)
  {
    std::vector<Ingredient> in{};

    std::stringstream s(line);
    bool more{ true };
    while (more)
    {
      Number z;
      std::string n;
      s >> z >> n;

      if (n[n.size() - 1] == ',')  // = more ingredients to come
      {
        n.pop_back();
      }
      else more = false;

      in.push_back(Ingredient(z, n));
    }
    assert(in.size() > 0);

    {
      std::string arrow;
      s >> arrow;
      assert(arrow == "=>");
    }

    Number z;
    std::string n;
    s >> z >> n;

    list.insert({ n,Reaction(in, Ingredient(z, n)) });
  }

  // assign levels to the reactions
  bool more{ true };
  while (more)
  {
    more = false;
    for (auto& r : list)
    {
      if (r.second.level > 0) continue;  // already done

      Number maxlevel{ 0 };
      for (auto i : r.second.in)  // for all ingredients
      {
        if (i.n == "ORE") // ORE is level 1
        {
          if (1 > maxlevel) maxlevel = 1;
        }
        else
        {
          const auto& reaction = list.find(i.n)->second;
          if (reaction.level == 0) // not ready yet
          {
            more = true;
            maxlevel = 0;
            break;
          }
          else
          {
            if (reaction.level > maxlevel) maxlevel = reaction.level;
          }
        }
      }

      if (maxlevel > 0) r.second.level = maxlevel + 1;
    }
  }

  std::unordered_map<std::string,Ingredient> needed{};
  for (const auto& r : list)
  {
    needed.insert({ r.second.out.n,Ingredient(0, r.second.out.n, list.find(r.second.out.n)->second.level) });
  }
  needed.insert({ "ORE",Ingredient(0, "ORE", 1) });

  auto neededOre = [&list](std::unordered_map<std::string, Ingredient>& needed) -> Number
    {
      Number maxlevel{ 0 };
      for (auto const& i : needed)
      {
        if (i.second.z > 0 && i.second.level > maxlevel) maxlevel = i.second.level;
      }
      while (maxlevel > 1)
      {
        for (auto& i : needed)
        {
          if (i.second.z == 0) continue; // not needed, skip
          if (i.second.level < maxlevel) continue; // only build highest level components

          Number realneed = i.second.z;
          auto reaction = list[i.second.n];
          realneed += reaction.out.z - 1;
          realneed /= reaction.out.z;

          for (auto in : reaction.in)  // for all ingredients
          {
            needed[in.n].z += realneed * in.z;  // add our needs to it
          }
          i.second.z = 0;
        }
        --maxlevel;
      }

      return needed["ORE"].z;
    };

  needed["FUEL"].z = 1;
  Number ore = neededOre(needed);

  constexpr Number targetore{ 1'000'000'000'000 };

  constexpr Number stepfactor{ 10 };
  Number step = targetore / ore / stepfactor;
  needed["ORE"].z = 0;
  needed["FUEL"].z = step * 15;
  Number ore15 = neededOre(needed);
  needed["ORE"].z = 0;
  needed["FUEL"].z = step * 14;
  Number ore14 = neededOre(needed);

  Number fuel = step * 14 + (step) * (targetore - ore14) / (ore15 - ore14) + stepfactor;

  do
  {
    --fuel;
    needed["ORE"].z = 0;
    needed["FUEL"].z = fuel;
    ore = neededOre(needed);
  }
  while (ore > targetore);

  return fuel;
}
