//template<> auto InputData<2023, 19, A>() { return
//"px{a<2006:qkq,m>2090:A,rfg}\n"
//"pv{a>1716:R,A}\n"
//"lnx{m>1548:A,A}\n"
//"rfg{s<537:gd,x>2440:R,A}\n"
//"qs{s>3448:A,lnx}\n"
//"qkq{x<1416:A,crn}\n"
//"crn{x>2662:A,R}\n"
//"in{s<1351:px,qqz}\n"
//"qqz{s>2770:qs,m<1801:hdj,R}\n"
//"gd{a>3333:R,R}\n"
//"hdj{m>838:A,pv}\n"
//"\n"
//"{x=787,m=2655,a=1222,s=2876}\n"
//"{x=1679,m=44,a=2067,s=496}\n"
//"{x=2036,m=264,a=79,s=2244}\n"
//"{x=2461,m=1339,a=466,s=291}\n"
//"{x=2127,m=1623,a=2188,s=1013}\n";}; // Result: 19114
template<> Number AoC<2023, 19, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr unsigned int bufferLength{ 100 };

  class Condition
  {
  public:
    int var{};
    char oper{};
    Number limit{};
    int target{};
  };
  using Conditions = std::vector<Condition>;
  class Workflow
  {
  public:
    Conditions cond{};
    int target{};
  };
  std::vector<Workflow> workflow{};
  workflow.resize(std::ssize(v)); // overkill, but sure

  using NameMap = std::unordered_map<std::string, int>;
  NameMap wName{};
  NameMap vName{};
  auto GetNameIndex = [](NameMap& map, const std::string& s) -> int
    {
      auto [it, found] = map.insert({ s, static_cast<int>(std::ssize(map)) + 1 });
      return it->second;
    };

  int line{ -1 };
  while (++line < std::ssize(v))
  {
    if (v[line] == "") break;

    Workflow w;
    char name[bufferLength]{};
    char list[bufferLength]{};
    int z = sscanf_s(v[line].c_str(), "%[^{]{%[^}]}", name, bufferLength, list, bufferLength);
    assert(z == 2);

    int p{ 0 };
    char var[bufferLength]{};
    char oper{};
    Number limit{};
    char target[bufferLength]{};
    int n{ 0 };
    while (sscanf_s(list + p, "%[^><]%c%lld:%[^,]%n", var, bufferLength, &oper, 1, &limit, target, bufferLength, &n) == 4)
    {
      p += n + 1;
      assert(p < bufferLength);

      Condition c{ GetNameIndex(vName,var), oper, limit, GetNameIndex(wName,target) };
      w.cond.push_back(c);
    }
    w.target = GetNameIndex(wName,var);
    workflow[GetNameIndex(wName, name)] = w;
  }


  using Part = std::vector<Number>;
  std::vector<Part> part{};

  while (++line < std::ssize(v))
  {
    Part pa;
    pa.resize(vName.size()+1);

    int p{ 1 };
    char var[bufferLength]{};
    Number value{};
    int n{ 0 };
    while (sscanf_s(v[line].c_str() + p, "%[^=]=%lld%n", var, bufferLength, &value, &n) == 2)
    {
      p += n + 1;
      assert(p < bufferLength);

      pa[GetNameIndex(vName,var)] = value;
    }

    part.push_back(pa);
  }

  auto GetNextWf = [&workflow](const Part& p, int current) -> int
    {
      const Workflow& w = workflow[current];
      for (int i = 0; i < std::ssize(w.cond); ++i)
      {
        switch (w.cond[i].oper)
        {
          case '>': if (p[w.cond[i].var] > w.cond[i].limit) return w.cond[i].target; break;
          case '<': if (p[w.cond[i].var] < w.cond[i].limit) return w.cond[i].target; break;
          default: assert(false);
        }
      }
      return w.target;
    };
  const int wfA = GetNameIndex(wName, "A");
  const int wfR = GetNameIndex(wName, "R");
  const int wfin = GetNameIndex(wName, "in");
  Number res{ 0 };
  for (int i = 0; i < std::ssize(part); ++i)
  {
    int current = wfin;

    while (true)
    {
      if (current == wfR) break; // rejected
      if (current == wfA)        // accepted
      {
        for (int j = 1; j < std::ssize(part[i]); ++j)
        {
          res += part[i][j];
        }
        break;
      }

      current = GetNextWf(part[i],current);
    }
  }
  return res;
}

//template<> auto InputData<2023, 19, B>() { return
//"px{a<2006:qkq,m>2090:A,rfg}\n"
//"pv{a>1716:R,A}\n"
//"lnx{m>1548:A,A}\n"
//"rfg{s<537:gd,x>2440:R,A}\n"
//"qs{s>3448:A,lnx}\n"
//"qkq{x<1416:A,crn}\n"
//"crn{x>2662:A,R}\n"
//"in{s<1351:px,qqz}\n"
//"qqz{s>2770:qs,m<1801:hdj,R}\n"
//"gd{a>3333:R,R}\n"
//"hdj{m>838:A,pv}\n"
//"\n"
//"{x=787,m=2655,a=1222,s=2876}\n"
//"{x=1679,m=44,a=2067,s=496}\n"
//"{x=2036,m=264,a=79,s=2244}\n"
//"{x=2461,m=1339,a=466,s=291}\n"
//"{x=2127,m=1623,a=2188,s=1013}\n";}; // Result: 167409079868000
template<> Number AoC<2023, 19, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr unsigned int bufferLength{ 100 };

  class Decision
  {
  public:
    int varIndex{};  // variable to look at (1...4)
    int limit{};     // cutoff point, <= limit or > limit
    int dIndexLE{};  // decision to use for values LE = Lower Equal limit
    int dIndexGT{};  // decision to use for values GT = Greater Than limit
  };
  std::vector<Decision> decisions{};
  decisions.resize(std::ssize(v)*5); // overkill, but to be sure

  using NameMap = std::unordered_map<std::string, int>;
  NameMap dName{};
  NameMap vName{};
  auto GetNameIndex = [](NameMap& map, const std::string& s) -> int
    {
      auto [it, found] = map.insert({ s, static_cast<int>(std::ssize(map))});
      return it->second;
    };

  int line{ -1 };
  int nextDecisionNumber{ 2 * static_cast<int>(std::ssize(v)) };
  while (++line < std::ssize(v))
  {
    if (v[line] == "") break;

    char name[bufferLength]{};
    char list[bufferLength]{};
    int z = sscanf_s(v[line].c_str(), "%[^{]{%[^}]}", name, bufferLength, list, bufferLength);
    assert(z == 2);

    int p{ 0 };
    int currentDecision = GetNameIndex(dName, name);
    while (true)
    {
      char var[bufferLength]{};
      char thisOper{};
      char nextOper{};
      int limit{};
      char thisTarget[bufferLength]{};
      char nextTarget[bufferLength]{};
      int n{ 0 };

      int z = sscanf_s(list + p, "%[^><]%c%d:%[^,]%n,%[^><]%c", var, bufferLength, &thisOper, 1, &limit, thisTarget, bufferLength, &n, nextTarget, bufferLength, &nextOper,1);
      assert(z >= 5);

      p += n + 1;
      assert(p < bufferLength);

      int secondTarget = z == 6 ? ++nextDecisionNumber : GetNameIndex(dName, nextTarget);
      if (thisOper == '>')
      {
        Decision d(GetNameIndex(vName, var), limit, secondTarget, GetNameIndex(dName, thisTarget));
        decisions[currentDecision] = d;
        currentDecision = nextDecisionNumber;
      }
      else {
        Decision d(GetNameIndex(vName, var), limit-1, GetNameIndex(dName, thisTarget), secondTarget);
        decisions[currentDecision] = d;
        currentDecision = nextDecisionNumber;
      }

      if (z < 6) break;
    }
  }

  constexpr int Dims{ 4 };
  class Interval
  {
  public:
    int fr{1};
    int to{4000};
    Number GetSize() const noexcept { return to - fr + 1; }
  };
  class Range
  {
  public:
    int current{}; // current workflow
    Interval interval[Dims]{};
    Number GetVol() const noexcept
    {
      Number res{ 1LL };
      for (int i = 0; i < Dims; ++i)
        res *= interval[i].GetSize();
      return res;
    }
  };

  const int dA = GetNameIndex(dName, "A");
  const int dR = GetNameIndex(dName, "R");

  Number total{ 0 };
  auto Decide = [&decisions,&total,dA,dR](int decisionIndex, const Range& r, auto& Decide) -> void
    {
      if (decisionIndex == dR) return;                            // rejected
      if (decisionIndex == dA) { total += r.GetVol(); return; }   // approved

      const Decision& d{ decisions[decisionIndex] };                                                     // limit:       ]
      if      (r.interval[d.varIndex].to <= d.limit) Decide(d.dIndexLE, r, Decide);                      // case 1: [....]
      else if (r.interval[d.varIndex].fr >  d.limit) Decide(d.dIndexGT, r, Decide);                      // case 3:       [....]
      else                                                                                               // case 2:   [..][..]
      {
        Range rLeft{ r };
        rLeft.interval[d.varIndex].to = d.limit;
        Decide(d.dIndexLE, rLeft, Decide);
        Range rRight{ r };
        rRight.interval[d.varIndex].fr = d.limit + 1;
        Decide(d.dIndexGT, rRight, Decide);
      }
    };

  Range r{};
  assert(r.GetVol() == 4000LL * 4000LL * 4000LL * 4000LL);
  const int dIn = GetNameIndex(dName, "in");
  Decide(dIn, r, Decide);

  return total;
}
