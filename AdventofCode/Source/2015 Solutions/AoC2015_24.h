//template<> auto InputData<2015, 24, A>() { return "1\n2\n3\n4\n5\n7\n8\n9\n10\n11\n";}; // Result: 99
template<> Number AoC<2015, 24, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  std::vector<int> weights{};
  for (const auto& line : v)
  {
    int w{ 0 };
    sscanf_s(line.c_str(), "%d", &w);
    weights.push_back(w);
  }
  std::sort(weights.begin(), weights.end(),  [](const int& n1, const int& n2) { return n1 > n2; });

  int sum{ 0 };
  for (auto const w : weights)
  {
    sum += w;
  }
  int target = sum / 3;
  assert(target * 3 == sum); /// must be divisible by 3

  // find shortest list to add to target
  using InOut = std::vector<int>;
  InOut inout{};
  inout.resize(weights.size());
  std::vector<InOut> best{};
  int nBest = static_cast<int>(weights.size());

  auto AddMore = [&weights, &target, &best, &nBest](int index, int group, const InOut& inout, int total, int count, auto& AddMore) -> void
    {
      if (count > nBest) return; // can't be an improvement any more!

      if (total == target)
      {
        if (group > 1)
        {
          nBest = 0;  // shortcut all further eval - we only need any solution for group 2
          best.push_back(inout);
          return;
        }
        if (count > nBest) return; // don't care about this one
        if (count < nBest)  // improvement
        {
          nBest = count;
          best.clear();
        }
        best.push_back(inout);
        //for (int i = 0; i < inout.size(); ++i)
        //{
        //  if (inout[i] == group)
        //  {
        //    std::cout << weights[i] << ' ';
        //  }
        //}
        //std::cout << std::endl;
        return;
      }
      if (index >= weights.size()) return;

      if (inout[index] == 0 && total + weights[index] <= target)
      {
        InOut inout0{ inout };
        int total0{ total };
        int count0{ count };
        inout0[index] = group;
        total0 += weights[index];
        ++count0;
        AddMore(index + 1, group, inout0, total0, count0, AddMore);  // try with this one
      }
      AddMore(index + 1, group, inout, total, count, AddMore);  // try also without this one
    };

  AddMore(0, 1, inout, 0, 0, AddMore);

  const std::vector<InOut> savedbest{ best };
  std::vector<InOut> finalbest{};
  for (const auto& io : savedbest)
  {
    best.clear();
    nBest = static_cast<int>(weights.size());
    AddMore(0, 2, io, 0, 0, AddMore); // make sure we can build a second group at all
    if (!best.empty())
    {
      finalbest.push_back(io);
    }
  }

  auto CalcQE = [&weights](const InOut& inout, int group) -> unsigned long long int
    {
      unsigned long long int qe{ 1 };
      int total{ 0 };
      for (int i = 0; i < inout.size(); ++i)
      {
        if (inout[i] == group)
        {
          total += weights[i];
          qe *= weights[i];
          //std::cout << weights[i] << ' ';
        }
      }

      //std::cout << total << ' ' << std::setw(20) << qe << std::endl;
      return qe;
    };
  unsigned long long int minQE{ std::numeric_limits<unsigned long long int>::max() };
  for (const auto& io : finalbest)
  {
    unsigned long long int qe = CalcQE(io,1);
    if (qe < minQE)
    {
      minQE = qe;
    }
  }

  return minQE;
}


//template<> auto InputData<2015, 24, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 24, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  std::vector<int> weights{};
  for (const auto& line : v)
  {
    int w{ 0 };
    sscanf_s(line.c_str(), "%d", &w);
    weights.push_back(w);
  }
  std::sort(weights.begin(), weights.end(),  [](const int& n1, const int& n2) { return n1 > n2; });

  int sum{ 0 };
  for (auto const w : weights)
  {
    sum += w;
  }
  int target = sum / 4;
  assert(target * 4 == sum); /// must be divisible by 3

  // find shortest list to add to target
  using InOut = std::vector<int>;
  InOut inout{};
  inout.resize(weights.size());
  std::vector<InOut> best{};
  int nBest = static_cast<int>(weights.size());

  auto AddMore = [&weights, &target, &best, &nBest](int index, int group, const InOut& inout, int total, int count, auto& AddMore) -> void
    {
      if (count > nBest) return; // can't be an improvement any more!

      if (total == target)
      {
        if (group > 1)
        {
          nBest = 0;  // shortcut all further eval - we only need any solution for group 2
          best.push_back(inout);
          return;
        }
        if (count > nBest) return; // don't care about this one
        if (count < nBest)  // improvement
        {
          nBest = count;
          best.clear();
        }
        best.push_back(inout);
        //for (int i = 0; i < inout.size(); ++i)
        //{
        //  if (inout[i] == group)
        //  {
        //    std::cout << weights[i] << ' ';
        //  }
        //}
        //std::cout << std::endl;
        return;
      }
      if (index >= weights.size()) return;

      if (inout[index] == 0 && total + weights[index] <= target)
      {
        InOut inout0{ inout };
        int total0{ total };
        int count0{ count };
        inout0[index] = group;
        total0 += weights[index];
        ++count0;
        AddMore(index + 1, group, inout0, total0, count0, AddMore);  // try with this one
      }
      AddMore(index + 1, group, inout, total, count, AddMore);  // try also without this one
    };

  AddMore(0, 1, inout, 0, 0, AddMore);

  const std::vector<InOut> savedbest{ best };
  std::vector<InOut> finalbest{};
  for (const auto& io : savedbest)
  {
    best.clear();
    nBest = static_cast<int>(weights.size());
    AddMore(0, 2, io, 0, 0, AddMore); // make sure we can build a second group at all
    if (!best.empty())
    {
      finalbest.push_back(io);
    }
  }

  auto CalcQE = [&weights](const InOut& inout, int group) -> unsigned long long int
    {
      unsigned long long int qe{ 1 };
      int total{ 0 };
      for (int i = 0; i < inout.size(); ++i)
      {
        if (inout[i] == group)
        {
          total += weights[i];
          qe *= weights[i];
          //std::cout << weights[i] << ' ';
        }
      }

      //std::cout << total << ' ' << std::setw(20) << qe << std::endl;
      return qe;
    };
  unsigned long long int minQE{ std::numeric_limits<unsigned long long int>::max() };
  for (const auto& io : finalbest)
  {
    unsigned long long int qe = CalcQE(io,1);
    if (qe < minQE)
    {
      minQE = qe;
    }
  }

  return minQE;
}
