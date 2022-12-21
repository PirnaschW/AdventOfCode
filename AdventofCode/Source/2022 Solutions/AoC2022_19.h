
//template<> auto InputData<2022, 19, A>() { return "Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.\nBlueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian."; };

template<> Number AoC<2022, 19, A>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  struct Robot
  {
    int oe{ 0 };
    int cl{ 0 };
    int ob{ 0 };
    int ge{ 0 };
  };
  struct Blueprint
  {
    int id;
    Robot oe;
    Robot cl;
    Robot ob;
    Robot ge;
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  std::vector<Blueprint> blue{};
  for (const auto& line : v)
  {
    Blueprint b;

    int n = sscanf_s(line.c_str(),"Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", &b.id, &b.oe.oe, &b.cl.oe, &b.ob.oe, &b.ob.cl, &b.ge.oe, &b.ge.ob);
    assert(n == 7);

    blue.push_back(b);
  }

  struct Option
  {
    int oe{ 0 };
    int cl{ 0 };
    int ob{ 0 };
    int ge{ 0 };
    int rooe{ 1 };
    int rocl{ 0 };
    int roob{ 0 };
    int roge{ 0 };
  };
  
  struct OHash
  {
    size_t operator() (const Option& o) const noexcept
    {
      return std::hash<int>()(
          (o.oe << 0   ) +
          (o.cl << 4   ) +
          (o.ob << 8   ) +
          (o.ge << 12  ) +
          (o.rooe << 16) +
          (o.rocl << 19) +
          (o.roob << 22) +
          (o.roge << 25));
    }
  };
  struct OEqual
  {
    bool operator() (const Option& o1, const Option& o2) const noexcept
    {
      return
        o1.oe == o2.oe &&
        o1.cl == o2.cl &&
        o1.ob == o2.ob &&
        o1.ge == o2.ge &&
        o1.rooe == o2.rooe &&
        o1.rocl == o2.rocl &&
        o1.roob == o2.roob &&
        o1.roge == o2.roge;
    }
  };

  
  Option start{};
  Number z{ 0 };

  for (const auto& b : blue)
  {
    std::unordered_set<Option,OHash,OEqual> options{};
    options.insert(start);
    for (int i = 0; i < 24; ++i)
    {
      int cutoff{ 0 };
      for (const auto& o : options)
      {
        if (o.ge + (24 - i) * o.roge > cutoff) cutoff = o.ge + (24 - i) * o.roge;
      }

      std::unordered_set<Option, OHash, OEqual> newoptions{};
      for (const auto& o : options)
      {

       // try to build 0 to n geode robots:
        int nge = (o.oe >= b.ge.oe && o.cl >= b.ge.cl && o.ob >= b.ge.ob && o.ge >= b.ge.ge) ? 1 : 0;
        Option oge = o;

        // build:
        oge.oe -= b.ge.oe * nge;
        oge.cl -= b.ge.cl * nge;
        oge.ob -= b.ge.ob * nge;
        oge.ge -= b.ge.ge * nge;
        oge.roge += nge;


          // try to build 0 to n obsidian robots:
        int nroob = 1;
        if (b.ob.oe > 0 && nroob > oge.oe / b.ob.oe) nroob = oge.oe / b.ob.oe;
        if (b.ob.cl > 0 && nroob > oge.cl / b.ob.cl) nroob = oge.cl / b.ob.cl;
        if (b.ob.ob > 0 && nroob > oge.ob / b.ob.ob) nroob = oge.ob / b.ob.ob;
        if (b.ob.ge > 0 && nroob > oge.ge / b.ob.ge) nroob = oge.ge / b.ob.ge;
        //if (i > 21) nroob = 0;
        if (nge >= 1) nroob = 0;

        for (int nob = 0; nob <= nroob; ++nob)
        {
          Option oob = oge;

          // build:
          oob.oe -= b.ob.oe * nob;
          oob.cl -= b.ob.cl * nob;
          oob.ob -= b.ob.ob * nob;
          oob.ge -= b.ob.ge * nob;
          oob.roob += nob;


          // try to build 0 to n clay robots:
          int nrocl = 1;
          if (b.cl.oe > 0 && nrocl > oob.oe / b.cl.oe) nrocl = oob.oe / b.cl.oe;
          if (b.cl.cl > 0 && nrocl > oob.cl / b.cl.cl) nrocl = oob.cl / b.cl.cl;
          if (b.cl.ob > 0 && nrocl > oob.ob / b.cl.ob) nrocl = oob.ob / b.cl.ob;
          if (b.cl.ge > 0 && nrocl > oob.ge / b.cl.ge) nrocl = oob.ge / b.cl.ge;
          if (nge + nob >= 1) nrocl = 0;

          for (int ncl = 0; ncl <= nrocl; ++ncl)
          {
            Option ocl = oob;

            // build:
            ocl.oe -= b.cl.oe * ncl;
            ocl.cl -= b.cl.cl * ncl;
            ocl.ob -= b.cl.ob * ncl;
            ocl.ge -= b.cl.ge * ncl;
            ocl.rocl += ncl;


           // try to build 0 to n ore robots:
            int nrooe = 1;
            if (b.oe.oe > 0 && nrooe > ocl.oe / b.oe.oe) nrooe = ocl.oe / b.oe.oe;
            if (b.oe.cl > 0 && nrooe > ocl.cl / b.oe.cl) nrooe = ocl.cl / b.oe.cl;
            if (b.oe.ob > 0 && nrooe > ocl.ob / b.oe.ob) nrooe = ocl.ob / b.oe.ob;
            if (b.oe.ge > 0 && nrooe > ocl.ge / b.oe.ge) nrooe = ocl.ge / b.oe.ge;
            if (nge + nob + ncl >= 1) nrooe = 0;

            for (int noe = 0; noe <= nrooe; ++noe)
            {
              Option ooe = ocl;

              // build:
              ooe.oe -= b.oe.oe * noe;
              ooe.cl -= b.oe.cl * noe;
              ooe.ob -= b.oe.ob * noe;
              ooe.ge -= b.oe.ge * noe;
              ooe.rooe += noe;

              ooe.oe += o.rooe;
              ooe.cl += o.rocl;
              ooe.ob += o.roob;
              ooe.ge += o.roge;


              if (!newoptions.contains(ooe))
              {
                if (ooe.ge + (24 - i) * ooe.roge * 2 >= cutoff)
                  newoptions.insert(ooe);
              }
            }
          }
        }
      }

      std::cout << i << ':' << newoptions.size() << std::endl;


      //std::vector<Option> ooo{};
      //ooo.reserve(newoptions.size());
      //for (const auto& o : newoptions)
      //{
      //  ooo.push_back(o);
      //}

      //struct
      //{
      //  bool operator()(const Option& o1, const Option& o2) const
      //  {
      //    if (o1.ge > o2.ge && o1.roge >= o2.roge) return true;
      //    if (o1.ge == o2.ge && o1.ob >= o2.ob) return true;

      //    return false;
      //  }
      //   
      //} Sorter;
      //std::sort(ooo.begin(), ooo.end(), Sorter);

      //options.clear();
      //for (int n=0; n<5000 && n<ooo.size(); ++n)
      //{
      //  options.insert(ooo[n]);
      //}

      std::swap(newoptions, options);
    }

    int maxge{ 0 };
    for (const auto& o : options)
    {
      if (o.ge > maxge) maxge = o.ge;
    }

    z += maxge* b.id;
  }



  return z;
}


//template<> auto InputData<2022, 19, B>() { return "Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.\nBlueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian."; };

template<> Number AoC<2022, 19, B>(std::istream& input)
{
  struct H
  {
    static int f(void)
    {
    }
  };

  struct Robot
  {
    int oe{ 0 };
    int cl{ 0 };
    int ob{ 0 };
    int ge{ 0 };
  };
  struct Blueprint
  {
    int id;
    Robot oe;
    Robot cl;
    Robot ob;
    Robot ge;
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
  std::vector<Blueprint> blue{};
  for (int i=0; i<3; ++i) // limit to three
  {
    Blueprint b;

    int n = sscanf_s(v[i].c_str(), "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", &b.id, &b.oe.oe, &b.cl.oe, &b.ob.oe, &b.ob.cl, &b.ge.oe, &b.ge.ob);
    assert(n == 7);

    blue.push_back(b);
  }

  struct Option
  {
    unsigned char oe{ 0 };
    unsigned char cl{ 0 };
    unsigned char ob{ 0 };
    unsigned char ge{ 0 };
    unsigned char rooe{ 1 };
    unsigned char rocl{ 0 };
    unsigned char roob{ 0 };
    unsigned char roge{ 0 };
  };

  struct OHash
  {
    size_t operator() (const Option& o) const noexcept
    {
      return std::hash<long long>()(
          ((long long)(o.oe) << 0) +
          ((long long)(o.cl) << 8) +
          ((long long)(o.ob) << 16) +
          ((long long)(o.ge) << 24) +
          ((long long)(o.rooe) << 32) +
          ((long long)(o.rocl) << 40) +
          ((long long)(o.roob) << 48) +
          ((long long)(o.roge) << 56));
    }
  };
  struct OEqual
  {
    bool operator() (const Option& o1, const Option& o2) const noexcept
    {
      return
        o1.oe == o2.oe &&
        o1.cl == o2.cl &&
        o1.ob == o2.ob &&
        o1.ge == o2.ge &&
        o1.rooe == o2.rooe &&
        o1.rocl == o2.rocl &&
        o1.roob == o2.roob &&
        o1.roge == o2.roge;
    }
  };


  Option start{};
  Number z{ 1 };
  int maxoe   {0};
  int maxcl   {0};
  int maxob   {0};
  int maxge   {0};
  int maxrooe {0};
  int maxrocl {0};
  int maxroob {0};
  int maxroge {0};

  for (const auto& b : blue)
  {
    std::unordered_set<Option, OHash, OEqual> options{};
    options.insert(start);
    for (int i = 0; i < 32; ++i)
    {
      int cutoff{ 0 };
      for (const auto& o : options)
      {
        if (o.oe > maxoe) maxoe = o.oe;
        if (o.cl > maxcl) maxcl = o.cl;
        if (o.ob > maxob) maxob = o.ob;
        if (o.ge > maxge) maxge = o.ge;
        if (o.rooe > maxrooe) maxrooe = o.rooe;
        if (o.rocl > maxrocl) maxrocl = o.rocl;
        if (o.roob > maxroob) maxroob = o.roob;
        if (o.roge > maxroge) maxroge = o.roge;
        if (o.ge + (32 - i) * o.roge + (32 - i) * o.roob > cutoff) cutoff = o.ge + (32 - i) * o.roge + (32 - i) * o.roob;
      }

      std::unordered_set<Option, OHash, OEqual> newoptions{};
      for (const auto& o : options)
      {

       // try to build 0 to n geode robots:
        int nge = (o.oe >= b.ge.oe && o.cl >= b.ge.cl && o.ob >= b.ge.ob && o.ge >= b.ge.ge) ? 1 : 0;
        Option oge = o;

        // build:
        oge.oe -= b.ge.oe * nge;
        oge.cl -= b.ge.cl * nge;
        oge.ob -= b.ge.ob * nge;
        oge.ge -= b.ge.ge * nge;
        oge.roge += nge;


          // try to build 0 to n obsidian robots:
        int nroob = 1;
        if (b.ob.oe > 0 && nroob > oge.oe / b.ob.oe) nroob = oge.oe / b.ob.oe;
        if (b.ob.cl > 0 && nroob > oge.cl / b.ob.cl) nroob = oge.cl / b.ob.cl;
        if (b.ob.ob > 0 && nroob > oge.ob / b.ob.ob) nroob = oge.ob / b.ob.ob;
        if (b.ob.ge > 0 && nroob > oge.ge / b.ob.ge) nroob = oge.ge / b.ob.ge;
        //if (i > 21) nroob = 0;
        if (nge >= 1) nroob = 0;

        for (int nob = 0; nob <= nroob; ++nob)
        {
          Option oob = oge;

          // build:
          oob.oe -= b.ob.oe * nob;
          oob.cl -= b.ob.cl * nob;
          oob.ob -= b.ob.ob * nob;
          oob.ge -= b.ob.ge * nob;
          oob.roob += nob;


          // try to build 0 to n clay robots:
          int nrocl = 1;
          if (b.cl.oe > 0 && nrocl > oob.oe / b.cl.oe) nrocl = oob.oe / b.cl.oe;
          if (b.cl.cl > 0 && nrocl > oob.cl / b.cl.cl) nrocl = oob.cl / b.cl.cl;
          if (b.cl.ob > 0 && nrocl > oob.ob / b.cl.ob) nrocl = oob.ob / b.cl.ob;
          if (b.cl.ge > 0 && nrocl > oob.ge / b.cl.ge) nrocl = oob.ge / b.cl.ge;
          if (nge + nob >= 1) nrocl = 0;

          for (int ncl = 0; ncl <= nrocl; ++ncl)
          {
            Option ocl = oob;

            // build:
            ocl.oe -= b.cl.oe * ncl;
            ocl.cl -= b.cl.cl * ncl;
            ocl.ob -= b.cl.ob * ncl;
            ocl.ge -= b.cl.ge * ncl;
            ocl.rocl += ncl;


           // try to build 0 to n ore robots:
            int nrooe = 1;
            if (b.oe.oe > 0 && nrooe > ocl.oe / b.oe.oe) nrooe = ocl.oe / b.oe.oe;
            if (b.oe.cl > 0 && nrooe > ocl.cl / b.oe.cl) nrooe = ocl.cl / b.oe.cl;
            if (b.oe.ob > 0 && nrooe > ocl.ob / b.oe.ob) nrooe = ocl.ob / b.oe.ob;
            if (b.oe.ge > 0 && nrooe > ocl.ge / b.oe.ge) nrooe = ocl.ge / b.oe.ge;
            if (nge + nob + ncl >= 1) nrooe = 0;

            for (int noe = 0; noe <= nrooe; ++noe)
            {
              Option ooe = ocl;

              // build:
              ooe.oe -= b.oe.oe * noe;
              ooe.cl -= b.oe.cl * noe;
              ooe.ob -= b.oe.ob * noe;
              ooe.ge -= b.oe.ge * noe;
              ooe.rooe += noe;

              ooe.oe += o.rooe;
              ooe.cl += o.rocl;
              ooe.ob += o.roob;
              ooe.ge += o.roge;


              if (!newoptions.contains(ooe))
              {
                if (i < 24 || ooe.ge + (32 - i) * ooe.roge * 3 + (32 - i) * ooe.roob >= cutoff)
                  newoptions.insert(ooe);
              }
            }
          }
        }
      }

      std::cout << i << ':' << newoptions.size() << std::endl;

      //std::cout << maxoe    << std::endl;
      //std::cout << maxcl    << std::endl;
      //std::cout << maxob    << std::endl;
      //std::cout << maxge    << std::endl;
      //std::cout << maxrooe  << std::endl;
      //std::cout << maxrocl  << std::endl;
      //std::cout << maxroob  << std::endl;
      //std::cout << maxroge  << std::endl;


      //std::vector<Option> ooo{};
      //ooo.reserve(newoptions.size());
      //for (const auto& o : newoptions)
      //{
      //  ooo.push_back(o);
      //}

      //struct
      //{
      //  bool operator()(const Option& o1, const Option& o2) const
      //  {
      //    if (o1.ge > o2.ge && o1.roge >= o2.roge) return true;
      //    if (o1.ge == o2.ge && o1.ob >= o2.ob) return true;

      //    return false;
      //  }
      //   
      //} Sorter;
      //std::sort(ooo.begin(), ooo.end(), Sorter);

      //options.clear();
      //for (int n=0; n<5000 && n<ooo.size(); ++n)
      //{
      //  options.insert(ooo[n]);
      //}

      std::swap(newoptions, options);
    }

    int maxge{ 0 };
    for (const auto& o : options)
    {
      if (o.ge > maxge) maxge = o.ge;
    }

    z *= maxge;
  }



  return z;
}
