//template<> auto InputData<2023, 20, A>() { return "broadcaster -> a, b, c\n%a -> b\n%b -> c\n%c -> inv\n&inv -> a\n";}; // Result: 32000000
//template<> auto InputData<2023, 20, A>() { return "broadcaster -> a\n%a -> inv, con\n&inv -> b\n%b -> con\n&con -> output\n"; }; // Result: 11687500
template<> Number AoC<2023, 20, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr unsigned int bufferLength{ 32 };

  using NameMap = std::unordered_map<std::string, int>;
  NameMap mName{};
  auto GetNameIndex = [&mName](const std::string& s) -> int
    {
      auto [it, found] = mName.insert({ s, static_cast<int>(std::ssize(mName)) });
      return it->second;
    };
  const int broadcaster = GetNameIndex("broadcaster");

  constexpr int maxDest{ 7 };
  constexpr int maxInp{ 10 };
  class Module
  {
  public:
    char type{};
    bool on{};
    std::array<int, maxDest> dest{};
    std::array<int, maxInp> inp{};
    std::array<bool, maxInp> mem{};
  };
  std::vector<Module> module{ v.size() + 1 }; // one extr for test 'output'
  constexpr int None{ -2 };
  for (int m = 0; m < std::ssize(module); ++m)
  {
    for (int i = 0; i < maxDest; ++i) module[m].dest[i] = None;
    for (int i = 0; i < maxInp; ++i) module[m].inp[i] = None;
  }

  int nFlip{ 0 };
  int nConj{ 0 };
  for (const auto& line : v)
  {
    char mod[bufferLength]{};
    char rec[bufferLength]{};
    int z = sscanf_s(line.c_str(), "%s -> %[^@]", mod, bufferLength, rec, bufferLength);
    assert(z == 2);

    int index{ -1 };
    switch (mod[0])
    {
      case '%': index = GetNameIndex(mod + 1); module[index].type = '%'; ++nFlip; break;
      case '&': index = GetNameIndex(mod + 1); module[index].type = '&'; ++nConj; break;
      default:  index = GetNameIndex(mod);     module[index].type = ' ';          break;
    }

    auto SetDest = [&module](int m, int d) -> void
      {
        bool successd{ false };
        for (int i = 0; i < maxDest; ++i)
        {
          if (module[m].dest[i] == None)
          {
            module[m].dest[i] = d;
            successd = true;
            break;
          }
        }
        assert(successd);
        bool successi{ false };
        for (int i = 0; i < maxInp; ++i)
        {
          if (module[d].inp[i] == None)
          {
            module[d].inp[i] = m;
            successi = true;
            break;
          }
        }
        assert(successi);
      };

    char comma{};
    int p{ 0 };
    int n{ 0 };
    while (sscanf_s(rec + p, " %[^,]%n%c", mod, bufferLength, &n, &comma, 1) == 2)
    {
      p += n + 1;
      SetDest(index, GetNameIndex(mod));
    }
    SetDest(index, GetNameIndex(mod));
  }

  auto GetStateAsString = [&nFlip, &nConj, &module]() -> std::string
    {
      std::string s;
      s.reserve(nFlip + nConj * maxInp);
      for (int m = 0; m < std::ssize(module); ++m)
      {
        switch (module[m].type)
        {
          case '%': s.push_back(module[m].on ? '1' : '0');  break;
          case '&': for (int i = 0; i < maxInp; ++i) s.push_back(module[m].mem[i] ? 'H' : 'L'); break;
          default: break;
        }
      }
      return s;
    };
  std::vector<std::string> sHistory{};
  std::vector<Number> lHistory{};
  std::vector<Number> hHistory{};

  constexpr bool Low = false; // for readability of rules
  constexpr bool High = true;

  class Signal
  {
  public:
    int sender;
    int receiver;
    bool signal;
  };

  Number lCount{ 0 };
  Number hCount{ 0 };
  std::queue<Signal> q{};
  auto SendSignal = [&q, &lCount, &hCount](int sender, int receiver, bool signal) -> void
    {
      if (receiver == None) return;
      ++(signal == High ? hCount : lCount);
      q.push({ sender, receiver, signal });
    };

  auto ProcessQueue = [&q, &module, &SendSignal]() -> void
    {
      while (q.size() > 0)
      {
        const Signal& s = q.front();
        Module& m = module[s.receiver];
        switch (m.type)
        {
          case '%':
            if (s.signal == Low)  // ignore High
            {
              m.on = !m.on; // toggle on/off
              for (int i = 0; i < maxDest; ++i)
              {
                SendSignal(s.receiver, m.dest[i], m.on);  // send on = High or off = Low
              }
            }
            break;
          case '&':
            {
              bool allHigh{ true };
              for (int i = 0; i < maxInp; ++i)
              {
                if (m.inp[i] == None) break;
                if (m.inp[i] == s.sender)
                {
                  m.mem[i] = s.signal;
                }
                if (m.mem[i] == Low) allHigh = false;
              }
              for (int i = 0; i < maxDest; ++i)
              {
                SendSignal(s.receiver, m.dest[i], allHigh ? Low : High);  // send allHigh = Low or !allHigh = High
              }
            }
            break;
          default:
            for (int i = 0; i < maxDest; ++i)
            {
              SendSignal(s.receiver, m.dest[i], s.signal);  // simply forward to all
            }
            break;
        }
        q.pop(); // remove the first entry, it has been processed
      }
    };

  Number Count{ 1'000 };
  //Number Count{ 50 };
  for (Number z = 0; z < Count; ++z)
  {
    SendSignal(None, broadcaster, Low);
    ProcessQueue();

    //std::string s = GetStateAsString();
    //for (int i = 0; i < std::ssize(sHistory); ++i)
    //{
    //  if (s == sHistory[i]) // found period!
    //  {
    //    Number cycle = (z - i);
    //    Number cycles = (Count - i - 1) / cycle;
    //    int extras = static_cast<int>(Count - cycles * cycle - i - 1);
    //    Number lTotal = cycles * (lCount - lHistory[i]) + lHistory[i+extras];
    //    Number hTotal = cycles * (hCount - hHistory[i]) + hHistory[i+extras];
    //    Number res = lTotal * hTotal;
    //    return res;
    //  }
    //}
    //sHistory.push_back(s);
    //lHistory.push_back(lCount);
    //hHistory.push_back(hCount);
  }

  //std::sort(sHistory.begin(), sHistory.end());
  return lCount * hCount;
}

//template<> auto InputData<2023, 20, B>() { return "broadcaster -> a, b, c\n%a -> b\n%b -> c\n%c -> inv\n&inv -> a\n";}; // Result: 32000000
//template<> auto InputData<2023, 20, B>() { return "broadcaster -> a\n%a -> inv, con\n&inv -> b\n%b -> con\n&con -> output\n"; }; // Result: 11687500
template<> Number AoC<2023, 20, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr unsigned int bufferLength{ 32 };

  using NameMap = std::unordered_map<std::string, int>;
  NameMap mName{};
  auto GetNameIndex = [&mName](const std::string& s) -> int
    {
      auto [it, found] = mName.insert({ s, static_cast<int>(std::ssize(mName)) });
      return it->second;
    };
  const int broadcaster = GetNameIndex("broadcaster");

  constexpr int maxDest{ 7 };
  constexpr int maxInp{ 10 };
  class Module
  {
  public:
    char type{};
    bool on{};
    std::array<int, maxDest> dest{};
    std::array<int, maxInp> inp{};
    std::array<bool, maxInp> mem{};
    std::array<bool, maxInp> hi{};
  };
  std::vector<Module> module{ v.size() + 1 }; // one extr for test 'output'
  constexpr int None{ -2 };
  for (int m = 0; m < std::ssize(module); ++m)
  {
    for (int i = 0; i < maxDest; ++i) module[m].dest[i] = None;
    for (int i = 0; i < maxInp; ++i) module[m].inp[i] = None;
  }

  int nFlip{ 0 };
  int nConj{ 0 };
  for (const auto& line : v)
  {
    char mod[bufferLength]{};
    char rec[bufferLength]{};
    int z = sscanf_s(line.c_str(), "%s -> %[^@]", mod, bufferLength, rec, bufferLength);
    assert(z == 2);

    int index{ -1 };
    switch (mod[0])
    {
      case '%': index = GetNameIndex(mod + 1); module[index].type = '%'; ++nFlip; break;
      case '&': index = GetNameIndex(mod + 1); module[index].type = '&'; ++nConj; break;
      default:  index = GetNameIndex(mod);     module[index].type = ' ';          break;
    }

    auto SetDest = [&module](int m, int d) -> void
      {
        bool successd{ false };
        for (int i = 0; i < maxDest; ++i)
        {
          if (module[m].dest[i] == None)
          {
            module[m].dest[i] = d;
            successd = true;
            break;
          }
        }
        assert(successd);
        bool successi{ false };
        for (int i = 0; i < maxInp; ++i)
        {
          if (module[d].inp[i] == None)
          {
            module[d].inp[i] = m;
            successi = true;
            break;
          }
        }
        assert(successi);
      };

    char comma{};
    int p{ 0 };
    int n{ 0 };
    while (sscanf_s(rec + p, " %[^,]%n%c", mod, bufferLength, &n, &comma, 1) == 2)
    {
      p += n + 1;
      SetDest(index, GetNameIndex(mod));
    }
    SetDest(index, GetNameIndex(mod));
  }

  auto GetStateAsString = [&nFlip, &nConj, &module]() -> std::string
    {
      std::string s;
      s.reserve(nFlip + nConj * maxInp);
      for (int m = 0; m < std::ssize(module); ++m)
      {
        switch (module[m].type)
        {
          case '%': s.push_back(module[m].on ? '1' : '0');  break;
          case '&': for (int i = 0; i < maxInp; ++i) s.push_back(module[m].mem[i] ? 'H' : 'L'); break;
          default: break;
        }
      }
      return s;
    };
  std::vector<std::string> sHistory{};
  std::vector<Number> lHistory{};
  std::vector<Number> hHistory{};

  constexpr bool Low = false; // for readability of rules
  constexpr bool High = true;

  class Signal
  {
  public:
    int sender;
    int receiver;
    bool signal;
  };

  Number lCount{ 0 };
  Number hCount{ 0 };
  std::queue<Signal> q{};
  auto SendSignal = [&q, &lCount, &hCount](int sender, int receiver, bool signal) -> void
    {
      if (receiver == None) return;
      ++(signal == High ? hCount : lCount);
      q.push({ sender, receiver, signal });
    };

  auto ProcessQueue = [&q, &module, &SendSignal]() -> void
    {
      while (q.size() > 0)
      {
        const Signal& s = q.front();
        Module& m = module[s.receiver];
        switch (m.type)
        {
          case '%':
            if (s.signal == Low)  // ignore High
            {
              m.on = !m.on; // toggle on/off
              for (int i = 0; i < maxDest; ++i)
              {
                SendSignal(s.receiver, m.dest[i], m.on);  // send on = High or off = Low
              }
            }
            break;
          case '&':
            {
              bool allHigh{ true };
              for (int i = 0; i < maxInp; ++i)
              {
                if (m.inp[i] == None) break;
                if (m.inp[i] == s.sender)
                {
                  m.mem[i] = s.signal;
                  if (s.signal == High)
                    m.hi[i] = true;
                }
                if (m.mem[i] == Low) allHigh = false;
              }
              for (int i = 0; i < maxDest; ++i)
              {
                SendSignal(s.receiver, m.dest[i], allHigh ? Low : High);  // send allHigh = Low or !allHigh = High
              }
            }
            break;
          default:
            for (int i = 0; i < maxDest; ++i)
            {
              SendSignal(s.receiver, m.dest[i], s.signal);  // simply forward to all
            }
            break;
        }
        q.pop(); // remove the first entry, it has been processed
      }
    };

  const int rx = GetNameIndex("rx");
  assert(module[rx].type == 0);
  assert(module[rx].inp[0] != None);
  assert(module[rx].inp[1] == None);
  const int gateIndex = module[rx].inp[0];
  std::array<std::vector<Number>, maxInp> cycle{};

  Number Count{ 1'000'000'000 };
  for (Number z = 0; z < Count; ++z)
  {
    SendSignal(None, broadcaster, Low);
    ProcessQueue();

    for (int i = 0; i < maxInp; ++i)
    {
      if (module[gateIndex].inp[i] == None) break;
      if (module[gateIndex].hi[i] == true)
      {
        cycle[i].push_back(z+1);
        module[gateIndex].hi[i] = false;
      }
    }
    bool moreNeeded{ false };
    for (int i = 0; i < maxInp; ++i)
    {
      if (module[gateIndex].inp[i] == None) break;
      if (cycle[i].size() < 2) moreNeeded = true;
    }
    if (!moreNeeded)
    {
      Number res{ 1 };
      for (int i = 0; i < maxInp; ++i)
      {
        if (module[gateIndex].inp[i] == None) break;
        res *= cycle[i][1] - cycle[i][0];
      }
      return res;
    }
  }

  assert(false);
  return 0;
}
