#include "../include/boost/monad.hpp"
#include <iostream>

using namespace BOOST_OUTCOME_V1_NAMESPACE;

//! [monad_bind_example]
template<class T> outcome<T> do_test(outcome<T> m)
{
  std::cout << "The value of my input monad is ";
  if(m)
    std::cout << m.get() << std::endl;
  else
    std::cout << (m.has_error() ? "errored" : m.has_exception() ? "excepted" : "empty") << std::endl;
  
  std::cout << "  or via bind(), my value is ";
  auto o(m >> [](T v) { std::cout << v; return v; }
           >> [](std::error_code e) { std::cout << "errored"; return e; }
           >> [](std::exception_ptr e) { std::cout << "excepted"; return e; }
           >> [](typename decltype(m)::empty_type) { std::cout << "empty"; });
  std::cout << std::endl;
  return o;
}
//! [monad_bind_example]

int main(void)
{
  do_test(make_outcome(5));
  do_test(make_outcome<std::string>());
  do_test(make_outcome<int>(std::error_code(5, std::generic_category())));
  do_test(make_outcome<double>(std::make_exception_ptr(std::logic_error("bad dog"))));
  return 0;
}
