//const at end of the declaretion
// a constant member function. It means that within this function, 
//you cannot modify any member variables of the object (except those explicitly marked as mutable).
#include <cstddef>
#include <graph_node.h>
#include <vector>

namespace Graph
{
       template <typename T>
       class directed_graph { 
       using nodes_container_type = std::vector<details::graph_node<T> >;

       public:
       bool insert(const T& node_value);
       bool insert(T&& node_value);

       bool erase(const T& node_value);
       bool insert_edge(const T& from_node_value, const T& to_node_value);
       bool erase_edge(const T& from_node_value, const T& to_node_value);
       void clear() noexcept;
       
       T& operator[](size_t index);
       const T& operator[](size_t index) const;

       bool operator==(const directed_graph& rhs) const;
       bool operator!=(const directed_graph& rhs) const;

       void swap(directed_graph& other_graph) noexcept;

       [[nodiscard]] size_t size() const noexcept;
//

       typename directed_graph<T>::nodes_container_type::iterator findNode(const T& node_value);
       typename directed_graph<T>::nodes_container_type::const_iterator findNode(const T& node_value) const;
       void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);
       size_t get_index_of_node(const typename directed_graph<T>::nodes_container_type::const_iterator& iter) const noexcept;
       [[nodiscard]] std::set<T> get_adjacent_nodes_values(const typename details::graph_node<T>::adjacency_list_type& indices) const;
       [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;
       private:
       nodes_container_type m_nodes;
       };

    template<typename T>
       void swap(directed_graph<T>& first_graph, directed_graph<T>& second_graph) noexcept
       {
              first_graph.swap(second_graph);
       }
}
