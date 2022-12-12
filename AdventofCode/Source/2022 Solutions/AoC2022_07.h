template<> Number AoC<2022, 7, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct dir
  {
    std::string name{};
    dir* parent{};
    bool total{false};
    Number size{};
    std::map<std::string,dir*> subdirs{};
  };

  struct H
  {
    static Number TotalOf(dir* d)
    {
      if (! d->total)
      {
        for (const auto& [name,sub] : d->subdirs)
        {
          d->size += TotalOf(sub);
        }
        d->total = true;
      }
      return d->size;
    }

    static Number TotalSizeIf(dir* d,Number mx)
    {
      Number total = 0;
      if (d->size <= mx) total += d->size;

      for (const auto& [name, sub] : d->subdirs)
      {
        total += TotalSizeIf(sub, mx);
      }
      return total;
    }
  };


  dir root{"/"};
  dir* current{&root};

  int lineno = -1;
  while (++lineno < v.size())
  {
    const std::string& line = v[lineno];
    
    switch (line[0])
    {
      case '$':
        if (line == "$ cd ..")
        {
          current = current->parent;
        }
        else if (line == "$ ls")
        {

        }
        else  // must be cd subdir
        {
          if (line == "$ cd /")
          {
            current = &root;
          }
          else
          {
            current = current->subdirs[line.c_str() + 5];
          }
        }
        break;
      default:
        if (line.substr(0, 4) == "dir ")
        {
          std::string name = line.substr(4);
          dir* d = new dir{ name,current };
          current->subdirs.insert({ name,d });
        }
        else
        {
          std::istringstream str(line);
          Number size{};
          str >> size;
          current->size += size;
        }
        break;
    }
  }

  H::TotalOf(&root);

  Number z = H::TotalSizeIf(&root,100000);


  return z;
}

template<> Number AoC<2022, 7, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  struct dir
  {
    std::string name{};
    dir* parent{};
    bool total{ false };
    Number size{};
    std::map<std::string, dir*> subdirs{};
  };

  struct H
  {
    static Number TotalOf(dir* d)
    {
      if (!d->total)
      {
        for (const auto& [name, sub] : d->subdirs)
        {
          d->size += TotalOf(sub);
        }
        d->total = true;
      }
      return d->size;
    }

    static Number TotalSizeIf(dir* d, Number mx)
    {
      Number total = 0;
      if (d->size <= mx) total += d->size;

      for (const auto& [name, sub] : d->subdirs)
      {
        total += TotalSizeIf(sub, mx);
      }
      return total;
    }

    static void Best(dir* d, dir*& best, Number above)
    {
      if (d->size >= above && d->size < best->size)
      {
        best = d;
      }
      for (const auto& [name, sub] : d->subdirs)
      {
        Best(sub, best, above);
      }
    }
  };


  dir root{ "/" };
  dir* current{ &root };

  int lineno = -1;
  while (++lineno < v.size())
  {
    const std::string& line = v[lineno];

    switch (line[0])
    {
      case '$':
        if (line == "$ cd ..")
        {
          current = current->parent;
        }
        else if (line == "$ ls")
        {

        }
        else  // must be cd subdir
        {
          if (line == "$ cd /")
          {
            current = &root;
          }
          else
          {
            current = current->subdirs[line.c_str() + 5];
          }
        }
        break;
      default:
        if (line.substr(0, 4) == "dir ")
        {
          std::string name = line.substr(4);
          dir* d = new dir{ name,current };
          current->subdirs.insert({ name,d });
        }
        else
        {
          std::istringstream str(line);
          Number size{};
          str >> size;
          current->size += size;
        }
        break;
    }
  }

  H::TotalOf(&root);

  dir* best = &root;
  
  Number above = root.size - 40'000'000;
  H::Best(&root, best, above);


  return best->size;

}

