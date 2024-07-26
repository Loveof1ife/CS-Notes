#include <cstddef>
#include "memory"

namespace Graph
{
    template<typename T>
    class directed_graph;

    template<typename DirectedGraph>
    class const_directed_graph_iterator{
    public:
        using value_type = typename DirectedGraph::value_type;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;

        const_directed_graph_iterator() = default;
        const_directed_graph_iterator(iterator_type it, std::shared_ptr<const DirectedGraph> graph);

        reference operator*() const;
        //In C++, the operator-> is used to access members of the object pointed to by an iterator.
        // (iterator.operator->())->member.So the return type of operator-> must be a pointer to allow the compiler to apply the -> operator to the result

        pointer operator->() const;

        const_directed_graph_iterator& operator++();
        const_directed_graph_iterator operator++(int);
        const_directed_graph_iterator& operator--();
        const_directed_graph_iterator operator--(int);
        // C++20 defaulted operator==.
        bool operator==(const const_directed_graph_iterator&) const = default;

    protected:
        friend  class directed_graph<value_type >;

        iterator_type m_nodeIterator;
        std::shared_ptr<const DirectedGraph> m_graph;
        // Helper methods for operator++ and operator--
        void increment();
        void decrement();
    };

    template<typename DirectedGraph>
    class directed_graph_iterator : public const_directed_graph_iterator<DirectedGraph> {
    public:
        using value_type = typename DirectedGraph::value_type;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer =  value_type*;
        using reference =  value_type&;
        using iterator_type = typename DirectedGraph::nodes_container_type::iterator;

        directed_graph_iterator() = default;
        directed_graph_iterator(iterator_type iter, std::shared_ptr<const DirectedGraph>  graph);

        reference operator*();
        pointer operator->();

        directed_graph_iterator& operator++();
        directed_graph_iterator operator++(int);


        directed_graph_iterator& operator--();
        directed_graph_iterator operator--(int);

    };


}