
#ifndef BOOST_QUERY_RESULT_H
#define BOOST_QUERY_RESULT_H

#include <list>
#include <tuple>
#include <sstream>

namespace waqqas{
namespace asio{
    template <typename... T>
class query_result
{
public:
  using query_data_type      = std::list<std::tuple<T...>>;
  using result_data_type = typename query_data_type::value_type;

  template <std::size_t N>
  using element_type = typename std::tuple_element<N, result_data_type>::type;

  template <std::size_t N>
  static element_type<N> get_data(char** data){
    std::stringstream st(data[N]);
    element_type<N> value;
    st >> value;

    return value;
  }

  // std::list<std::string> column_names;
  query_data_type            data;
};
}}
#endif