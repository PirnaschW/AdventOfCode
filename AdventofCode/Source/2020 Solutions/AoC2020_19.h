void AoC2020_19A(std::istream& input)
{
  enum Types
  {
    Simple,
    Sequence,
    Choice,
    Undefined,
  };
  using RuleID = size_t;
  constexpr RuleID Invalid{ 99999 };

  struct Rule
  {
    Rule() {}
    Types t{ Undefined };
    RuleID r11{ Invalid };
    RuleID r12{ Invalid };
    RuleID r13{ Invalid };
    RuleID r21{ Invalid };
    RuleID r22{ Invalid };
    std::string text{};
  };


  using Container = std::unordered_set<std::string>;
  using Regulations = std::map<RuleID, Rule>;
  Regulations rules{};

  struct H
  {
    static Container CollectRuleStrings(Regulations& rules, RuleID id)
    {
      Container patterns{};
      if (id == Invalid)
      {
        patterns.insert("");
        return patterns;
      }
      switch (rules[id].t)
      {
        case Types::Simple:
          patterns.insert(rules[id].text);
          break;
        case Types::Sequence:
          {
            auto patterns11 = CollectRuleStrings(rules, rules[id].r11);
            auto patterns12 = CollectRuleStrings(rules, rules[id].r12);
            auto patterns13 = CollectRuleStrings(rules, rules[id].r13);
            for (const auto& p11 : patterns11)
              for (const auto& p12 : patterns12)
                for (const auto& p13 : patterns13)
                  patterns.insert(p11 + p12 + p13);
          }
          break;
        case Types::Choice:
          {
            auto patterns11 = CollectRuleStrings(rules, rules[id].r11);
            auto patterns12 = CollectRuleStrings(rules, rules[id].r12);
            auto patterns13 = CollectRuleStrings(rules, rules[id].r13);
            for (const auto& p11 : patterns11)
              for (const auto& p12 : patterns12)
                for (const auto& p13 : patterns13)
                  patterns.insert(p11 + p12 + p13);
          }
          {
            auto patterns21 = CollectRuleStrings(rules, rules[id].r21);
            auto patterns22 = CollectRuleStrings(rules, rules[id].r22);
            for (const auto& p21 : patterns21)
              for (const auto& p22 : patterns22)
                patterns.insert(p21 + p22);
          }
          break;
        case Types::Undefined:
        default:
          assert(false);
          break;
      }
      return patterns;
    }

  };

  std::string line{};
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    RuleID id{ Invalid };
    Rule r{};
    constexpr unsigned int BUFLEN{ 128 };
    char buffer[BUFLEN];
    char pastend{ 0 };
    if (sscanf_s(line.c_str(), "%zu: %zu %zu %zu | %zu %zu %c", &id, &r.r11, &r.r12, &r.r13, &r.r21, &r.r22, &pastend, 1) == 6)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu | %zu %zu %c", &id, &r.r11, &r.r12, &r.r21, &r.r22, &pastend, 1) == 5)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu | %zu %c", &id, &r.r11, &r.r12, &r.r21, &pastend, 1) == 4)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu | %zu %zu %c", &id, &r.r11, &r.r21, &r.r22, &pastend, 1) == 4)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu | %zu %c", &id, &r.r11, &r.r21, &pastend, 1) == 3)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu %zu %c", &id, &r.r11, &r.r12, &r.r13, &pastend, 1) == 4)
    {
      r.t = Types::Sequence;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu %c", &id, &r.r11, &r.r12, &pastend, 1) == 3)
    {
      r.t = Types::Sequence;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %c", &id, &r.r11, &pastend, 1) == 2)
    {
      r.t = Types::Sequence;
    }
    else if (sscanf_s(line.c_str(), "%zu: \"%[^\"]\" %c", &id, buffer, BUFLEN - 1, &pastend, 1) == 2)
    {
      r.t = Types::Simple;
      r.text = buffer;
    }
    else assert(false);
    rules.insert({ id,r });
  }

  Container patterns{};
  patterns = H::CollectRuleStrings(rules, 0);


  int z{ 0 };
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    if (patterns.contains(line)) ++z;
  }

  std::cout << z << std::endl;
}

void AoC2020_19B(std::istream& input)
{
  enum Types
  {
    Simple,
    Sequence,
    Choice,
    Undefined,
  };
  using RuleID = size_t;
  constexpr RuleID Invalid{ 99999 };

  using Container = std::unordered_set<std::string>;
  struct Rule
  {
    Rule() {}
    Types t{ Undefined };
    RuleID r11{ Invalid };
    RuleID r12{ Invalid };
    RuleID r13{ Invalid };
    RuleID r21{ Invalid };
    RuleID r22{ Invalid };
    std::string text{};
    Container results{};
  };

  using Regulations = std::map<RuleID, Rule>;
  Regulations rules{};

  struct H
  {
    static Container CollectRuleStrings(Regulations& rules, RuleID id, int depth)
    {
      Container patterns{};
      if (id == Invalid || depth > 100)
      {
        patterns.insert("");
        return patterns;
      }

      if (rules[id].results.size() > 0) return rules[id].results;

      switch (rules[id].t)
      {
        case Types::Simple:
          patterns.insert(rules[id].text);
          break;
        case Types::Sequence:
          {
            auto patterns11 = CollectRuleStrings(rules, rules[id].r11, depth + 1);
            auto patterns12 = CollectRuleStrings(rules, rules[id].r12, depth + 1);
            auto patterns13 = CollectRuleStrings(rules, rules[id].r13, depth + 1);
            for (const auto& p11 : patterns11)
              for (const auto& p12 : patterns12)
                for (const auto& p13 : patterns13)
                  patterns.insert(p11 + p12 + p13);
          }
          break;
        case Types::Choice:
          {
            auto patterns11 = CollectRuleStrings(rules, rules[id].r11, depth + 1);
            auto patterns12 = CollectRuleStrings(rules, rules[id].r12, depth + 1);
            auto patterns13 = CollectRuleStrings(rules, rules[id].r13, depth + 1);
            for (const auto& p11 : patterns11)
              for (const auto& p12 : patterns12)
                for (const auto& p13 : patterns13)
                  patterns.insert(p11 + p12 + p13);
          }
          {
            auto patterns21 = CollectRuleStrings(rules, rules[id].r21, depth + 1);
            auto patterns22 = CollectRuleStrings(rules, rules[id].r22, depth + 1);
            for (const auto& p21 : patterns21)
              for (const auto& p22 : patterns22)
                patterns.insert(p21 + p22);
          }
          break;
        case Types::Undefined:
        default:
          assert(false);
          break;
      }
      rules[id].results = patterns;
      return patterns;
    }

  };

  std::string line{};
  while (getline(input, line))
  {
    if (line.size() == 0) break;

    RuleID id{ Invalid };
    Rule r{};
    constexpr unsigned int BUFLEN{ 128 };
    char buffer[BUFLEN];
    char pastend{ 0 };
    if (sscanf_s(line.c_str(), "%zu: %zu %zu %zu | %zu %zu %c", &id, &r.r11, &r.r12, &r.r13, &r.r21, &r.r22, &pastend, 1) == 6)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu | %zu %zu %c", &id, &r.r11, &r.r12, &r.r21, &r.r22, &pastend, 1) == 5)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu | %zu %c", &id, &r.r11, &r.r12, &r.r21, &pastend, 1) == 4)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu | %zu %zu %c", &id, &r.r11, &r.r21, &r.r22, &pastend, 1) == 4)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu | %zu %c", &id, &r.r11, &r.r21, &pastend, 1) == 3)
    {
      r.t = Types::Choice;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu %zu %c", &id, &r.r11, &r.r12, &r.r13, &pastend, 1) == 4)
    {
      r.t = Types::Sequence;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %zu %c", &id, &r.r11, &r.r12, &pastend, 1) == 3)
    {
      r.t = Types::Sequence;
    }
    else if (sscanf_s(line.c_str(), "%zu: %zu %c", &id, &r.r11, &pastend, 1) == 2)
    {
      r.t = Types::Sequence;
    }
    else if (sscanf_s(line.c_str(), "%zu: \"%[^\"]\" %c", &id, buffer, BUFLEN - 1, &pastend, 1) == 2)
    {
      r.t = Types::Simple;
      r.text = buffer;
    }
    else assert(false);
    rules.insert({ id,r });
  }


// rule change for B
  rules[8].t = Types::Choice;
  rules[8].r21 = 42;
  rules[8].r22 = 8;
  rules[11].t = Types::Choice;
  rules[11].r12 = 11;
  rules[11].r13 = 31;
  rules[11].r21 = 42;
  rules[11].r22 = 31;

  Container patterns{};
//  patterns = H::CollectRuleStrings(rules, 0, 0);
  auto patterns42 = H::CollectRuleStrings(rules, 42, 0);
  auto patterns31 = H::CollectRuleStrings(rules, 31, 0);

  constexpr int LEN{ 8 };
  for (const auto& p : patterns42) assert(p.size() == LEN);
  for (const auto& p : patterns31) assert(p.size() == LEN);

  int z{ 0 };
  size_t smax{ 0 };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  for (const auto& line : v)
  {
    if (line.size() == 0) break;
    if (line.size() > smax) smax = line.size();
    if (line.size() % LEN) continue;

    int offset{ 0 };
    int pre{ 0 };
    int post{ 0 };
    bool done = false;
    while (patterns42.contains(line.substr(offset, LEN)))
    {
      if (patterns31.contains(line.substr(offset, LEN)))
      {
        int offset2 = offset;
        while (patterns31.contains(line.substr(offset2, LEN)))
        {
          offset2 += LEN;
          ++post;
        }
        if (pre > post && post > 0)
        {
          ++z;
          std::cout << line << std::endl;
          done = true;
          break;
        }
      }
      offset += LEN;
      ++pre;
    }
    if (done) continue;
    if (pre < 1) continue;
    while (patterns31.contains(line.substr(offset, LEN)))
    {
      offset += LEN;
      ++post;
    }
    if (pre <= post || post == 0) continue;
    if (line.size() == offset && pre > post && post > 0)
    {
      ++z;
//      std::cout << line << std::endl;
    }
  }

  std::cout << z << std::endl;
}
