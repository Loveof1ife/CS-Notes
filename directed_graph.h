//const at end of the declaretion
// a constant member function. It means that within this function, 
//you cannot modify any member variables of the object (except those explicitly marked as mutable).
#include "graph_node.h"
#include "directed_graph_iterator.h"

namespace Graph
{
       template <typename T>
       class directed_graph : public std::enable_shared_from_this<directed_graph<T>> {
           public:
           using value_type = T;
           using reference = value_type&;

           using const_reference = const value_type&;//In C++, const value_type& means a constant reference to a value_type. This makes the variable it refers to immutable, not the reference itself.
           using size_type = size_t;
           using difference_type = ptrdiff_t;

           using iterator = const_directed_graph_iterator<directed_graph>;
           using const_iterator = const_directed_graph_iterator<directed_graph>;


           std::pair<iterator, bool> insert(const T& node_value);
           std::pair<iterator, bool> insert(T&& node_value);
           iterator insert(const_iterator hint, const T& node_value);
           iterator insert(const_iterator hint, T&& node_value);

           template<typename Iter>
           void insert(Iter first, Iter last);



           bool erase(const T& node_value);
           iterator erase(const_iterator pos);
           iterator erase(const_iterator first, const_iterator last);

           bool insert_edge(const T& from_node_value, const T& to_node_value);
           bool erase_edge(const T& from_node_value, const T& to_node_value);
           void clear() noexcept;

           T& operator[](size_type  index);
           const T& operator[](size_type  index) const;

           reference at(size_type index);
           const_reference at(size_type index) const;

           bool operator==(const directed_graph& rhs) const;
           bool operator!=(const directed_graph& rhs) const;

           void swap(directed_graph& other_graph) noexcept;

           [[nodiscard]] size_type size() const noexcept;
           [[nodiscard]] size_type max_size() const noexcept;
           [[nodiscard]] bool empty() const noexcept;


           [[nodiscard]] std::set<T> get_adjacent_nodes_values(const typename details::graph_node<T>::adjacency_list_type& indices) const;
           [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;

           //Iterator method;
           iterator begin() noexcept;
           iterator end() noexcept;
           const_iterator begin() const noexcept; //this method marked as const， it promises not to modify the state of the object. Therefore, it can be called on const instances of directed_graph.
           const_iterator end() const noexcept;

           [[maybe_unused]] const_iterator cbegin() const noexcept;

           [[maybe_unused]] const_iterator cend() const noexcept;

       private:
           //xx_xx_iterator 使用了私有node_contain_type的类型别名
           //When class A defines class B as a friend, class B gains access to all of class A's members, including its private and protected members.
           // This means that any instance of class B can access the private and protected data members and member functions of any instance of class A.
           friend class directed_graph_iterator<directed_graph>;
           friend class const_directed_graph_iterator<directed_graph>;

           using nodes_container_type = std::vector<details::graph_node<T> >;
           nodes_container_type m_nodes;

           typename directed_graph<T>::nodes_container_type::iterator findNode(const T& node_value);
           typename directed_graph<T>::nodes_container_type::const_iterator findNode(const T& node_value) const;

           void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

           [[nodiscard]]size_t get_index_of_node(const typename directed_graph<T>::nodes_container_type::const_iterator& iter) const noexcept;
       };



    template<typename T>
    void swap(directed_graph<T>& first_graph, directed_graph<T>& second_graph) noexcept
    {
          first_graph.swap(second_graph);
    }
}
