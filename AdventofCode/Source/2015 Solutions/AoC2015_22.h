//template<> auto InputData<2015, 22, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 22, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  class Creature
  {
  public:
    int hp{ 0 };
    int damage{ 0 };
    int armor{ 0 };
    int mana{ 0 };
  };

  Creature boss{};
  // Hit Points: 71
  // Damage: 10
  assert(v.size() == 2);
  int n1 = sscanf_s(v[0].c_str(), "Hit Points: %d", &boss.hp);
  assert(n1 == 1);
  int n2 = sscanf_s(v[1].c_str(), "Damage: %d", &boss.damage);
  assert(n2 == 1);

  Creature me{50,0,0,500};



  // Magic Missile costs 53 mana. It instantly does 4 damage.
  // Drain costs 73 mana. It instantly does 2 damage and heals you for 2 hit points.
  // Shield costs 113 mana. It starts an effect that lasts for 6 turns. While it is active, your armor is increased by 7.
  // Poison costs 173 mana. It starts an effect that lasts for 6 turns. At the start of each turn while it is active, it deals the boss 3 damage.
  // Recharge costs 229 mana. It starts an effect that lasts for 5 turns. At the start of each turn while it is active, it gives you 101 new mana.

  class Action
  {
  public:
    const std::string name;
    const int mana;
    const int damage;
    const int hp;
    const int duration;
    const int armor;
    const int newmana;
  };

  using Actions = std::vector<Action>;
  const Actions action
  {
    { "Shield",        113,  0,  0,  6,  7,   0 },
    { "Recharge",      229,  0,  0,  5,  0, 101 },
    { "Poison",        173,  3,  0,  6,  0,   0 },
    { "Drain",          73,  2,  2,  0,  0,   0 },
    { "Magic Missile",  53,  4,  0,  0,  0,   0 },
//    { "Nothing",         0,  0,  0,  0,  0,   0 },
  };

  using Ongoing = std::vector<int>;

  int mintotalmana{ std::numeric_limits<int>::max() };
  auto BossDead = [&mintotalmana](const Creature& boss, int totalmana, [[maybe_unused]] const std::string& s) -> bool
    {
      if (boss.hp > 0) return false;
      if (totalmana < mintotalmana)
      { 
        //std::cout << totalmana << ' ' << s << std::endl;
        mintotalmana = totalmana;
      }
      return true;
    };

  auto ApplyOngoing = [&action](Creature& b, Creature& m, Ongoing& o) -> void
    {
      m.armor = 0;
      for (int i = 0; i < action.size(); ++i)
      {
        if (o[i] > 0)
        {
          --o[i];
          m.armor += action[i].armor;
          b.hp    -= action[i].damage;
          m.mana  += action[i].newmana;
        }
      }
    };

  auto TryAction = [&action, &BossDead, &ApplyOngoing, &mintotalmana](const Creature& b, const Creature& m, const Ongoing& o, const int t, const std::string& s, auto& TryAction) -> void
    {
      // abort if too much mana already used
      if (t >= mintotalmana) return;

      // my turn:
      for (int i = 0; i < action.size(); ++i)
      {
        if (o[i] > 1) continue; // can't cast that yet, try something else
        if (m.mana < action[i].mana) continue; // can't cast that, not enough mana, try something else

        Creature boss{ b };
        Creature me{ m };
        Ongoing ongoing{ o };
        int totalmana{ t };
        std::string sequence{ s };
        sequence += action[i].name;
        sequence += ", ";

        // handle lingering effects
        ApplyOngoing(boss, me, ongoing);
        if (BossDead(boss, totalmana, sequence)) continue; // this branch ends, try something else

        me.mana -= action[i].mana;
        totalmana += action[i].mana;
        if (action[i].duration == 0)
        {
          boss.hp -= action[i].damage;
          me.hp += action[i].hp;
        }
        ongoing[i] = action[i].duration;
        if (BossDead(boss, totalmana, sequence)) continue; // this branch ends, try something else

        // Boss' turn:
        // handle lingering effects
        ApplyOngoing(boss, me, ongoing);
        if (BossDead(boss, totalmana, sequence)) continue; // this branch ends, try something else

        int damage = boss.damage - me.armor;
        me.hp -= damage < 1 ? 1 : damage;
        if (me.hp <= 0)
        {
//          std::cout << boss.hp << ' ' << sequence << std::endl;
          continue; // I died, try something else
        }

        TryAction(boss, me, ongoing, totalmana, sequence, TryAction);
      }
    };

  Ongoing ongoing{};
  ongoing.resize(action.size());
  TryAction(boss, me, ongoing, 0, "", TryAction);

  return mintotalmana;
}

//template<> auto InputData<2015, 22, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 22, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  class Creature
  {
  public:
    int hp{ 0 };
    int damage{ 0 };
    int armor{ 0 };
    int mana{ 0 };
  };

  Creature boss{};
  // Hit Points: 71
  // Damage: 10
  assert(v.size() == 2);
  int n1 = sscanf_s(v[0].c_str(), "Hit Points: %d", &boss.hp);
  assert(n1 == 1);
  int n2 = sscanf_s(v[1].c_str(), "Damage: %d", &boss.damage);
  assert(n2 == 1);

  Creature me{50,0,0,500};



  // Magic Missile costs 53 mana. It instantly does 4 damage.
  // Drain costs 73 mana. It instantly does 2 damage and heals you for 2 hit points.
  // Shield costs 113 mana. It starts an effect that lasts for 6 turns. While it is active, your armor is increased by 7.
  // Poison costs 173 mana. It starts an effect that lasts for 6 turns. At the start of each turn while it is active, it deals the boss 3 damage.
  // Recharge costs 229 mana. It starts an effect that lasts for 5 turns. At the start of each turn while it is active, it gives you 101 new mana.

  class Action
  {
  public:
    const std::string name;
    const int mana;
    const int damage;
    const int hp;
    const int duration;
    const int armor;
    const int newmana;
  };

  using Actions = std::vector<Action>;
  const Actions action
  {
    { "Shield",        113,  0,  0,  6,  7,   0 },
    { "Recharge",      229,  0,  0,  5,  0, 101 },
    { "Poison",        173,  3,  0,  6,  0,   0 },
    { "Drain",          73,  2,  2,  0,  0,   0 },
    { "Magic Missile",  53,  4,  0,  0,  0,   0 },
    //    { "Nothing",         0,  0,  0,  0,  0,   0 },
  };

  using Ongoing = std::vector<int>;

  int mintotalmana{ std::numeric_limits<int>::max() };
  auto BossDead = [&mintotalmana](const Creature& boss, int totalmana, [[maybe_unused]] const std::string& s) -> bool
    {
      if (boss.hp > 0) return false;
      if (totalmana < mintotalmana)
      { 
        //std::cout << totalmana << ' ' << s << std::endl;
        mintotalmana = totalmana;
      }
      return true;
    };

  auto MeDead = [](Creature& me, int damage) -> bool
    {
      return (me.hp -= damage) <= 0;
    };

  auto ApplyOngoing = [&action](Creature& b, Creature& m, Ongoing& o) -> void
    {
      m.armor = 0;
      for (int i = 0; i < action.size(); ++i)
      {
        if (o[i] > 0)
        {
          --o[i];
          m.armor += action[i].armor;
          b.hp    -= action[i].damage;
          m.mana  += action[i].newmana;
        }
      }
    };

  auto TryAction = [&action, &BossDead, &MeDead, &ApplyOngoing, &mintotalmana](const Creature& b, const Creature& m, const Ongoing& o, const int t, const std::string& s, auto& TryAction) -> void
    {
      // abort if too much mana already used
      if (t >= mintotalmana) return;

      // my turn:
      for (int i = 0; i < action.size(); ++i)
      {
        if (o[i] > 1) continue; // can't cast that yet, try something else
        if (m.mana < action[i].mana) continue; // can't cast that, not enough mana, try something else

        Creature boss{ b };
        Creature me{ m };
        Ongoing ongoing{ o };
        int totalmana{ t };
        std::string sequence{ s };
        sequence += action[i].name;
        sequence += ", ";

        // handle lingering effects
        if (MeDead(me,1)) continue;
        ApplyOngoing(boss, me, ongoing);
        if (BossDead(boss, totalmana, sequence)) continue; // this branch ends, try something else

        me.mana -= action[i].mana;
        totalmana += action[i].mana;
        if (action[i].duration == 0)
        {
          boss.hp -= action[i].damage;
          me.hp += action[i].hp;
        }
        ongoing[i] = action[i].duration;
        if (BossDead(boss, totalmana, sequence)) continue; // this branch ends, try something else

        // Boss' turn:
        // handle lingering effects
        ApplyOngoing(boss, me, ongoing);
        if (BossDead(boss, totalmana, sequence)) continue; // this branch ends, try something else

        int damage = boss.damage - me.armor;
        if (MeDead(me,damage < 1 ? 1 : damage)) continue;

        TryAction(boss, me, ongoing, totalmana, sequence, TryAction);
      }
    };

  Ongoing ongoing{};
  ongoing.resize(action.size());
  TryAction(boss, me, ongoing, 0, "", TryAction);

  return mintotalmana;
}
