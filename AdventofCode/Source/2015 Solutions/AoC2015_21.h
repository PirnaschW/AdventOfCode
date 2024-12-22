//template<> auto InputData<2015, 21, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 21, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // Weapons:    Cost  Damage  Armor
  // Dagger        8     4       0
  // Shortsword   10     5       0
  // Warhammer    25     6       0
  // Longsword    40     7       0
  // Greataxe     74     8       0
  // 
  // Armor:      Cost  Damage  Armor
  // Leather      13     0       1
  // Chainmail    31     0       2
  // Splintmail   53     0       3
  // Bandedmail   75     0       4
  // Platemail   102     0       5
  // 
  // Rings:      Cost  Damage  Armor
  // Damage +1    25     1       0
  // Damage +2    50     2       0
  // Damage +3   100     3       0
  // Defense +1   20     0       1
  // Defense +2   40     0       2
  // Defense +3   80     0       3

  class Object
  {
  public:
    Object() = delete;
    Object(int cost, int damage, int armor) noexcept : cost_(cost), damage_(damage), armor_(armor) {}
    int GetCost() const noexcept { return cost_; }
    int GetDamage() const noexcept { return damage_; }
    int GetArmor() const noexcept { return armor_; }
  private:
    const int cost_;
    const int damage_;
    const int armor_;
  };

  using Objects = std::vector<Object>;

  Objects weapon
  {
    {  8,  4,  0 },
    { 10,  5,  0 },
    { 25,  6,  0 },
    { 40,  7,  0 },
    { 74,  8,  0 },
  };
  Objects armor
  {
    {  13,  0,  1 },
    {  31,  0,  2 },
    {  53,  0,  3 },
    {  75,  0,  4 },
    { 102,  0,  5 },
    {   0,  0,  0 },
  };
  Objects ring
  {
    {  25,  1,  0 },
    {  25,  1,  0 },
    {  50,  2,  0 },
    { 100,  3,  0 },
    {  20,  0,  1 },
    {  40,  0,  2 },
    {  80,  0,  3 },
    {   0,  0,  0 },
    {   0,  0,  0 },
  };

  class Creature
  {
  public:
    int hp;
    int damage;
    int armor;
  };

  Creature boss{};
  // Hit Points: 103
  // Damage: 9
  // Armor: 2
  assert(v.size() == 3);
  int n1 = sscanf_s(v[0].c_str(), "Hit Points: %d", &boss.hp);
  assert(n1 == 1);
  int n2 = sscanf_s(v[1].c_str(), "Damage: %d", &boss.damage);
  assert(n2 == 1);
  int n3 = sscanf_s(v[2].c_str(), "Armor: %d", &boss.armor);
  assert(n3 == 1);

  int mincost{ std::numeric_limits<int>::max() };
  auto Fight = [&mincost,&boss](int cost, int damage, int armor) -> void
    {
      if (cost >= mincost) return;
  
      Creature b = boss;
      Creature m{ 100,damage,armor };
      while (m.hp > 0)
      {
        b.hp -= std::max(m.damage - b.armor,1);
        if (b.hp < 1)
        {
          mincost = cost;
          return;
        }
        m.hp -= std::max(b.damage - m.armor,1);
      }
    };

  for (int w = 0; w < weapon.size(); ++w)
  {
    for (int a = 0; a < armor.size(); ++a)
    {
      for (int r1 = 0; r1 < ring.size(); ++r1)
      {
        for (int r2 = 0; r2 < ring.size(); ++r2)
        {
          if (r1 == r2) continue;
          Fight(weapon[w].GetCost() + armor[a].GetCost() + ring[r1].GetCost() + ring[r2].GetCost(), weapon[w].GetDamage() + armor[a].GetDamage() + ring[r1].GetDamage() + ring[r2].GetDamage(), weapon[w].GetArmor() + armor[a].GetArmor() + ring[r1].GetArmor() + ring[r2].GetArmor());
        }
      }
    }
  }

  return mincost;
}

//template<> auto InputData<2015, 21, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 21, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // Weapons:    Cost  Damage  Armor
  // Dagger        8     4       0
  // Shortsword   10     5       0
  // Warhammer    25     6       0
  // Longsword    40     7       0
  // Greataxe     74     8       0
  // 
  // Armor:      Cost  Damage  Armor
  // Leather      13     0       1
  // Chainmail    31     0       2
  // Splintmail   53     0       3
  // Bandedmail   75     0       4
  // Platemail   102     0       5
  // 
  // Rings:      Cost  Damage  Armor
  // Damage +1    25     1       0
  // Damage +2    50     2       0
  // Damage +3   100     3       0
  // Defense +1   20     0       1
  // Defense +2   40     0       2
  // Defense +3   80     0       3

  class Object
  {
  public:
    Object() = delete;
    Object(int cost, int damage, int armor) noexcept : cost_(cost), damage_(damage), armor_(armor) {}
    int GetCost() const noexcept { return cost_; }
    int GetDamage() const noexcept { return damage_; }
    int GetArmor() const noexcept { return armor_; }
  private:
    const int cost_;
    const int damage_;
    const int armor_;
  };

  using Objects = std::vector<Object>;

  Objects weapon
  {
    {  8,  4,  0 },
    { 10,  5,  0 },
    { 25,  6,  0 },
    { 40,  7,  0 },
    { 74,  8,  0 },
  };
  Objects armor
  {
    {  13,  0,  1 },
    {  31,  0,  2 },
    {  53,  0,  3 },
    {  75,  0,  4 },
    { 102,  0,  5 },
    {   0,  0,  0 },
  };
  Objects ring
  {
    {  25,  1,  0 },
    {  25,  1,  0 },
    {  50,  2,  0 },
    { 100,  3,  0 },
    {  20,  0,  1 },
    {  40,  0,  2 },
    {  80,  0,  3 },
    {   0,  0,  0 },
    {   0,  0,  0 },
  };

  class Creature
  {
  public:
    int hp;
    int damage;
    int armor;
  };

  Creature boss{};
  // Hit Points: 103
  // Damage: 9
  // Armor: 2
  assert(v.size() == 3);
  int n1 = sscanf_s(v[0].c_str(), "Hit Points: %d", &boss.hp);
  assert(n1 == 1);
  int n2 = sscanf_s(v[1].c_str(), "Damage: %d", &boss.damage);
  assert(n2 == 1);
  int n3 = sscanf_s(v[2].c_str(), "Armor: %d", &boss.armor);
  assert(n3 == 1);

  int maxcost{ std::numeric_limits<int>::min() };
  auto Fight = [&maxcost,&boss](int cost, int damage, int armor) -> void
    {
      if (cost <= maxcost) return;

      Creature b = boss;
      Creature m{ 100,damage,armor };
      while (m.hp > 0)
      {
        b.hp -= std::max(m.damage - b.armor,1);
        if (b.hp < 1)
        {
          return;
        }
        m.hp -= std::max(b.damage - m.armor,1);
      }
      maxcost = cost;
    };

  for (int w = 0; w < weapon.size(); ++w)
  {
    for (int a = 0; a < armor.size(); ++a)
    {
      for (int r1 = 0; r1 < ring.size(); ++r1)
      {
        for (int r2 = 0; r2 < ring.size(); ++r2)
        {
          if (r1 == r2) continue;
          Fight(weapon[w].GetCost() + armor[a].GetCost() + ring[r1].GetCost() + ring[r2].GetCost(), weapon[w].GetDamage() + armor[a].GetDamage() + ring[r1].GetDamage() + ring[r2].GetDamage(), weapon[w].GetArmor() + armor[a].GetArmor() + ring[r1].GetArmor() + ring[r2].GetArmor());
        }
      }
    }
  }

  return maxcost;
}
