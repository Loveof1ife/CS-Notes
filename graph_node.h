// .cppm files are primarily used to define module interface units
// A module interface unit declares the public-facing parts of a module that can be imported by other translation units.
// export module declarations, export statements for functions, classes, and other entities that are intended to be accessible outside the module.

#include <cstddef>
#include <memory>
#include <set>
#include <vector>

namespace Graph
{
template<typename T> class directed_graph;

namespace details
{
       template<typename T> class graph_node{
       public:
              graph_node(std::shared_ptr<directed_graph<T> > graph, const T& t);
              graph_node(std::shared_ptr<directed_graph<T> > graph, T&& t);

              [[nodiscard]] T& value() noexcept;
              [[nodiscard]] const T& value() const noexcept;

              bool operator==(const graph_node&) const = default;

       private:
              friend class directed_graph<T>;

              std::shared_ptr<directed_graph<T> > m_graph;
              T m_data;

              using adjacency_list_type = std::set<size_t>;
              adjacency_list_type m_adjacencyNodeIndices;

              [[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices();
              [[nodiscard]] const adjacency_list_type& get_adjacent_nodes_indices() const;
       };


}
}

// Usage of [[nodiscard]]:

// When you mark a function with [[nodiscard]],
//  the compiler will issue a warning if the function’s return value is ignored. This is particularly useful for functions where the return value is critical, such as error codes, resource handles, or important computation results
