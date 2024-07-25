#include<directed_graph.h>

namespace Graph
{      
       //当使用依赖模板参数的类型时，必须使用typename关键字，
       // nodes_container_type::iterator::  vector<details:graph_nodeM<T> >::iterator which rely on template type parameter T
	template<typename T>
	typename directed_graph<T>::nodes_container_type::iterator
		directed_graph<T>::findNode(const T& node_value)
	{
              return std::find_if(std::begin(m_nodes), std::end(m_nodes),
                                   [&node_value](const auto& node){ return node.value == node_value; } );
	}
	template<typename T>
	typename directed_graph<T>::nodes_container_type::const_iterator
		directed_graph<T>::findNode(const T& node_value) const
	{
              return const_cast<directed_graph<T>* >(this)->findNode(node_value);
        //const_cast to remove the const qualifier from this pointer. 
        //This allows the const member function to call a non-const version of findNode.
        //In a const member function, this is a pointer to a const object of the class type. That means inside a const member function, you cannot call any non-const member functions or modify any member variables (except those marked as mutable).                      

	}
    template<typename T>
    bool directed_graph<T>::insert(T&& node_value)
    {
          auto iter( findNode(node_value));
          if(iter != std::end(m_nodes))
                 return false;

          m_nodes.emplace(this, std::move(node_value));
          return true;
    }
    template<typename T>
    bool directed_graph<T>::insert(const T& node_value)
    {
          T copy{node_value};
          return insert(std::move(copy));
    }
    template<typename T>
    bool directed_graph<T>::insert_edge(const T& from_node_value, const T& to_node_value)
    {
          const auto from{ findNode(from_node_value) };
          const auto to{ findNode(to_node_value) };
          if(from == std::end(m_nodes) || to== std::end(m_nodes) )
                 return false;

          const size_t to_index { get_index_of_node(to) };
          return from->get_adjacent_nodes_indices().insert(to_index).second;
    }

    template<typename T>
    size_t directed_graph<T>::get_index_of_node(
          const typename directed_graph<T>::nodes_container_type::const_iterator& iter) const noexcept
    {
          const auto index{std::distance(std::cbegin(m_nodes), iter) };
          return static_cast<size_t>(index);
    }
    template<typename T>
    bool directed_graph<T>::erase(const T &node_value)
    {
        auto iter {findNode(node_value) };
        if(iter == std::end(m_nodes) ) return false;

        remove_all_links_to(iter);
        m_nodes.erase(iter);
        return true;
    }
    template<typename T>
    void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node_iter) {
        const size_t node_index = get_index_of_node(node_iter);

        for (auto&& node: m_nodes) {
            auto& adjacencyIndices {node.get_adjacent_nodes_indices() };
            adjacencyIndices.erase(node_index);

            std::vector<size_t> indices(std::begin(adjacencyIndices), std::begin(adjacencyIndices));

            std::for_each(std::begin(indices), std::end(indices),
                          [node_index](size_t& index){if(index > node_index) index--; } );
            adjacencyIndices.clear();
            adjacencyIndices.insert(std::begin(indices), std::end(indices) );
        }
    }
    template<typename T>
    bool directed_graph<T>::erase_edge(const T& from_node_value, const T& to_node_value)
    {
          const auto from{ findNode(from_node_value) };
          const auto to{ findNode(to_node_value) };
          if(from == std::end(m_nodes) || to== std::end(m_nodes) )
                 return false;

          const size_t to_index { get_index_of_node(to) };
          from->get_adjacent_nodes_indices().erase(to_index);
          return true;
    }

    template<typename T>
    void directed_graph<T>::clear() noexcept
    {
        //转发到vector.clear()
        m_nodes.clear();
    }
    template<typename T>
    void directed_graph<T>::swap(directed_graph& other_graph) noexcept
    {
        m_nodes.swap(other_graph.m_nodes);
    }

    template<typename T>
    T&  directed_graph<T>::operator[](size_t index)
    {
          return m_nodes[index].value();
    }

    template<typename T>
    const T&  directed_graph<T>::operator[](size_t index) const
    {
        return m_nodes[index].value();
    }

    template<typename T>
    bool directed_graph<T>::operator==(const directed_graph& rhs) const
    {
        //1.check size of directed_graph
        if(m_nodes.size() != rhs.m_nodes.size()) return false;
        //2.check each node
        for(auto&& node : m_nodes){
            const auto rhsNodeIter {rhs.findNode(node) };
            if(rhsNodeIter == std::end(rhs.m_nodes) ) return false;

            const auto adjacent_values_lhs {get_adjacent_nodes_values(node.get_adjacent_nodes_indices() ) };
            const auto adjacent_values_rhs {rhs.get_adjacent_nodes_values(rhsNodeIter->get_adjacent_nodes_indices() ) };
            if(adjacent_values_lhs != adjacent_values_rhs) return false;
        }
        return true;
    }

    template<typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(
            const typename details::graph_node<T>::adjacency_list_type& indices) const
    {
        std::set<T> values;
        //'auto&&' universal references, it can bind to both lvalues and rvalues.
        for(auto&& index : indices) values.insert(index);

        return values;
    }

    template<typename T>
    std::set<T> directed_graph<T>::get_adjacent_nodes_values(const T& node_value) const
    {
        auto iter{findNode(node_value) };
        if (iter == std::end(m_nodes) ) return std::set<T>{};
        //转发到 indices版本
        return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices() );
    }
    template<typename T>
    bool directed_graph<T>::operator!=(const directed_graph& rhs) const
    {
        return !(*this == rhs);
    }

    template<typename T>
    size_t directed_graph<T>::size() const noexcept
    {
        return m_nodes.size();
    }
}