// .cppm files are primarily used to define module interface units
// A module interface unit declares the public-facing parts of a module that can be imported by other translation units.
// export module declarations, export statements for functions, classes, and other entities that are intended to be accessible outside the module.
#include<graph_node.h>

namespace Graph
{
template<typename T> class directed_graph;

namespace details
{
       template<typename T>
       graph_node<T>::graph_node(std::shared_ptr<directed_graph<T> > graph, const T& t)
       : m_graph(std::move(graph)), m_data(t){}

       template<typename T> 
       graph_node<T>::graph_node(std::shared_ptr<directed_graph<T> > graph, T&& t)
       : m_graph(std::move(graph)), m_data(std::move(t)){}

       template<typename T> 
       T& graph_node<T>::value() noexcept {return m_data;}
        
       template<typename T>
       const T& graph_node<T>::value() const noexcept {return m_data;}

       template<typename T>
       typename graph_node<T>::adjacency_list_type& 
              graph_node<T>::get_adjacent_nodes_indices()
              {
                     return m_adjacencyNodeIndices;
              }

       template<typename T>
       const typename graph_node<T>::adjacency_list_type& 
              graph_node<T>::get_adjacent_nodes_indices() const
              {
                     return m_adjacencyNodeIndices;
              }
}
}

// Usage of [[nodiscard]]:

// When you mark a function with [[nodiscard]],
//  the compiler will issue a warning if the function’s return value is ignored. This is particularly useful for functions where the return value is critical, such as error codes, resource handles, or important computation results
