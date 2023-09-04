
std::vector<std::vector<std::string>> ReadGroups(std::istream& input); // read all lines, grouping multiple lines separated by blank lines into sub-vector 
std::vector<std::string> ReadLines(std::istream& input); // read all lines into vector 
std::vector<Number> ReadNumbers(std::istream& input, char separator = '\n'); // read all input as Numbers into vector
std::vector<std::string> ReadWords(std::istream& input, char separator); // read input as words (with provided separator) into vector
std::vector<std::string> ReadWords(std::istream& input); // read all words (separated by whitespace) into vector

template <class T>
void ShowBucketHistogram(const T& cont)
{
  std::map<int, int> histogram;
  for (size_t i = 0; i < cont.bucket_count(); ++i)
    ++histogram[static_cast<int>(cont.bucket_size(static_cast<int>(i)))];
  for (auto& kv : histogram)
    std::cout << ".bucket_size() " << kv.first << " seen " << kv.second << " times\n";
  std::cout << std::endl;
}

template <typename T>
constexpr T gcd(T a, T b) requires std::integral<T>
{
  if (a == b) return a;
  if (a == 0) return b;
  if (b == 0) return a;
  return a > b ? gcd(a % b, b) : gcd(b % a, a);
}

template <typename T>  // don't call this directly
constexpr T ModuloPower_(T base, T exponent, T modulus)
{
  if (modulus == 1) return 0;
  assert(std::numeric_limits<T>::max() / modulus > modulus);
  T result{ 1 };
  base %= modulus;
  while (exponent > 0)
  {
    if (exponent % 2)
    {
      result *= base;
      result %= modulus;
    }
    exponent >>= 1;
    assert(std::numeric_limits<T>::max() / base > base);
    base *= base;
    base %= modulus;
  }
  return result;
}
template <typename T>
constexpr T ModuloPower(T base, T exponent, T modulus) requires std::integral<T>
{ // automatically uses 128 bits when needed
  return (std::numeric_limits<T>::max() / modulus > modulus) ? ModuloPower_(base, exponent, modulus) : static_cast<T>(ModuloPower_(static_cast<std::_Signed128>(base), static_cast<std::_Signed128>(exponent), static_cast<std::_Signed128>(modulus)));
}


template <typename T>  // don't call this directly
constexpr T ModuloMultiply_(T factor1, T factor2, T modulus) { return factor1 * factor2 % modulus; }
template <typename T>
constexpr T ModuloMultiply(T factor1, T factor2, T modulus) requires std::integral<T>
{ // automatically uses 128 bits when needed
  return (std::numeric_limits<T>::max() / factor1 > factor2) ? ModuloMultiply_(factor1, factor2, modulus) : static_cast<T>(ModuloMultiply_(static_cast<std::_Signed128>(factor1), static_cast<std::_Signed128>(factor2), static_cast<std::_Signed128>(modulus)));
}


template <typename T>
constexpr T ModularInverse(T value, T modulus) requires std::integral<T>
{
  // modulus MUST be a prime for this to work; using "Fermat's little theorem": a^prime = a % prime
  return ModuloPower(value, modulus - 2, modulus);
}
