template<> Number AoC<2022, 13, A>(std::istream& input)
{
  struct List;
  struct Node
  {
    bool isnum{ true };
    Number n{};
    List* l;
  };
  struct List
  {
    List* parent{ nullptr };
    std::vector<Node> nodes{};

    static int Compare(const List& l, const List& r)
    {
      for (size_t z = 0; z < l.nodes.size(); ++z)
      {
        if (z >= r.nodes.size()) return 1;

        if (l.nodes[z].isnum && r.nodes[z].isnum)
        {
          if (l.nodes[z].n < r.nodes[z].n) return -1;
          if (l.nodes[z].n > r.nodes[z].n) return 1;
          continue;
        }

        if (!l.nodes[z].isnum && !r.nodes[z].isnum)
        {
          int res = Compare(*l.nodes[z].l, *r.nodes[z].l);
          if (res != 0) return res;
          continue;
        }

        if (l.nodes[z].isnum)
        {
          List ll;
          ll.nodes.push_back(l.nodes[z]);
          int res = Compare(ll, *r.nodes[z].l);
          if (res != 0) return res;
          continue;
        }
        if (r.nodes[z].isnum)
        {
          List rr;
          rr.nodes.push_back(r.nodes[z]);
          int res = Compare(*l.nodes[z].l, rr);
          if (res != 0) return res;
          continue;
        }
      }

      if (l.nodes.size() < r.nodes.size()) return -1;
      return 0;
    }
    bool operator< (const List& r) { return Compare(*this, r) == -1; }
  };

  struct H
  {
    static List ReadList(const std::string& s)
    {
      List l;
      l.parent = nullptr;

      size_t z = 1;
      assert(s[0] == '[');
      List* current = &l;

      while (z < s.size())
      {
        switch (s[z])
        {
          case '[':
          {
            List* ll = new List;
            ll->parent = current;
            current = ll;
          }
            ++z;
            break;
          case ']':
            if (current->parent == nullptr) return l;
            current->parent->nodes.push_back(Node{ false,0,current });
            current = current->parent;
            ++z;
            break;
          case ',':
            ++z;
            break;
          default: // number!
          {
            Number n=0;
            while (isdigit(s[z]))
            {
              n *= 10;
              n += s[z] - '0';
              ++z;
            }
            current->nodes.push_back(Node{ true,n,nullptr});
          }
        }
      }
      return l;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  Number z = 0;
  for (int i = 0; i < v.size(); i += 3)
  {
    List left = H::ReadList(v[i]);
    List right = H::ReadList(v[i+1]);

    if (List::Compare(left, right) == -1)
    {
//      std::cout << i / 3 + 1 << ',';
      z += i / 3 + 1;
    }
  }

  return z;
}

template<> Number AoC<2022, 13, B>(std::istream& input)
{
  struct List;
  struct Node
  {
    bool isnum{ true };
    Number n{};
    List* l;
  };
  struct List
  {
    List* parent{ nullptr };
    std::vector<Node> nodes{};
    bool flag{ false };

    static int Compare(const List& l, const List& r)
    {
      for (size_t z = 0; z < l.nodes.size(); ++z)
      {
        if (z >= r.nodes.size()) return 1;

        if (l.nodes[z].isnum && r.nodes[z].isnum)
        {
          if (l.nodes[z].n < r.nodes[z].n) return -1;
          if (l.nodes[z].n > r.nodes[z].n) return 1;
          continue;
        }

        if (!l.nodes[z].isnum && !r.nodes[z].isnum)
        {
          int res = Compare(*l.nodes[z].l, *r.nodes[z].l);
          if (res != 0) return res;
          continue;
        }

        if (l.nodes[z].isnum)
        {
          List ll;
          ll.nodes.push_back(l.nodes[z]);
          int res = Compare(ll, *r.nodes[z].l);
          if (res != 0) return res;
          continue;
        }
        if (r.nodes[z].isnum)
        {
          List rr;
          rr.nodes.push_back(r.nodes[z]);
          int res = Compare(*l.nodes[z].l, rr);
          if (res != 0) return res;
          continue;
        }
      }

      if (l.nodes.size() < r.nodes.size()) return -1;
      return 0;
    }
    bool operator< (const List& r) const { return Compare(*this, r) == -1; }
  };

  struct H
  {
    static List ReadList(const std::string& s, bool flag = false)
    {
      List l;
      l.parent = nullptr;
      l.flag = flag;

      size_t z = 1;
      assert(s[0] == '[');
      List* current = &l;

      while (z < s.size())
      {
        switch (s[z])
        {
          case '[':
          {
            List* ll = new List;
            ll->parent = current;
            current = ll;
          }
          ++z;
          break;
          case ']':
            if (current->parent == nullptr) return l;
            current->parent->nodes.push_back(Node{ false,0,current });
            current = current->parent;
            ++z;
            break;
          case ',':
            ++z;
            break;
          default: // number!
          {
            Number n = 0;
            while (isdigit(s[z]))
            {
              n *= 10;
              n += s[z] - '0';
              ++z;
            }
            current->nodes.push_back(Node{ true,n,nullptr });
          }
        }
      }
      return l;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<List> l{};
  for (int i = 0; i < v.size(); ++i)
  {
    if (v[i].size() == 0) continue;
    l.push_back(H::ReadList(v[i]));
  }

  l.push_back(H::ReadList("[[2]]", true));
  l.push_back(H::ReadList("[[6]]", true));

  struct {
    bool operator() (const List& l, const List& r) const
    {
      return l < r;
    }
  } sorter;

  std::sort(l.begin(), l.end(), sorter);

  Number z = 1;
  for (int i = 0; i < l.size(); ++i)
  {
    if (l[i].flag)
      z *= i + 1;
  }

  return z;
}

