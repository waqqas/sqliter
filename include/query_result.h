
#ifndef BOOST_QUERY_RESULT_H
#define BOOST_QUERY_RESULT_H

#include <list>
#include <tuple>

namespace waqqas{
namespace asio{
    template <typename... T>
class query_result
{
public:
  using data_type_t      = std::list<std::tuple<T...>>;
  using result_data_type = typename data_type_t::value_type;

  template <std::size_t N>
  using element_type = typename std::tuple_element<N, result_data_type>::type;

  std::list<std::string> column_names;
  data_type_t            data;
};
}}
#endif