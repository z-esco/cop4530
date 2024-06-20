

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
HashTable<K, V>::HashTable(int vSize){
  vect.resize(prime_below(vSize));
}

template <typename K, typename V>
HashTable<K, V>::~HashTable(){
  makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K& k) const{
  auto& l = vect[myhash(k)];
  return find(begin(l), end(l), k) != end(l);
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K,V> &kv) const{
  if(!contains(kv.get(0)))
    return false;

  return &myhash(kv.get(0)) == kv.get(1);
}

template <typename K, typename V>
int HashTable<K, V>::myhash(const K& k) const{
  static HashTable<K, V> ht;
  return ht(k) % vect.size();
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k){
  auto & l = vect[myhash(k)];
  auto itr = find(begin(vect), end(vect), k);

  if(itr == end(vect))
    return false;

  l.erase(itr);
  --vSize;
  return true;

}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K,V> &kv){
  auto & l = vect[myhash(kv.get(0))];
  if(find(begin(l), end(l), kv.get(0)) != end(l))
    return false;

  vect.push_back(kv);

  if(++vSize > vect.size())
    rehash();

  return true;
}

template <typename K, typename V>
bool HashTable<K ,V>::insert(std::pair<K,V> &&kv){
  auto & l = vect[myhash(kv.get(0))];
  if(find(begin(l), end(l), kv.get(0)) != end(l))
    return false;

  vect.push_back(kv);

  if(++vSize > vect.size())
    rehash();

  return true;
}

template <typename K, typename V>
void HashTable<K, V>::rehash(){
  vect.resize(prime_below(vSize*2));

  for(auto & l:vect){
    auto itr = begin(l);
    while(itr != end(l))
      myhash(&itr);
  }
}

template <typename K, typename V>
void HashTable<K, V>::clear(){
  makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename){
  std::ifstream input;
  input.open(filename);
  K k1;
  V v1;

  if(!input.good()){
    input.close();
    return false;
  }  
  else{
    while(!input.eof()){
      input >> k1;
      input >> v1;
      insert(std::pair(k1,v1));
    }
    input.close();
    return true;
  }
}

template <typename K, typename V> 
bool HashTable<K, V>::write_to_file(const char* filename){
  std::ofstream output;
  int count = 0;
  output.open(filename);

  if(!output.good()){
    output.close();
    return false;
  }
  else{
    if(vect.empty())
      return false;
    while(count < vect.size()){
      auto l = vect[count];
      auto itr = l.begin();
      while(itr != l.end()){
        output << &itr.get(0) << ' ' << &itr.get(1) << std::endl;
        itr++;
      }
      count ++;
    }
    output.close();
    return true;
  }

}

template <typename K, typename V> 
void HashTable<K, V>::dump() const{
  int count;
  while(count < vect.size()){
      auto l = vect[count];
      auto itr = l.begin();

      std::cout << "v[" << count << "]: ";
      if(itr != l.end()){
        std::cout << &itr.get(0) << ' ' << &itr.get(1);
        itr++;
      }
      while(itr != l.end()){
        std::cout << ':'<< &itr.get(0) << ' ' << &itr.get(1);
      }
      std::cout << '\n';
      count ++;
    }
}

template <typename K, typename V> 
int HashTable<K, V>::size() const{
  return vSize;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty(){
  vect.clear();
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0; 
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

