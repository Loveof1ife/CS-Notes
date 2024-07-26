#include "directed_graph_iterator.h"
namespace Graph
{

    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator(
            iterator_type iter, std::shared_ptr<const DirectedGraph> graph)
            : m_nodeIterator{iter}, m_graph{graph}
    {
    }
    template<typename DirectedGraph>
    typename const_directed_graph_iterator<DirectedGraph>::pointer
        const_directed_graph_iterator<DirectedGraph>::operator->() const
    {
        return &(m_nodeIterator->value() );
    }

    template<typename DirectedGraph>
    typename const_directed_graph_iterator<DirectedGraph>::reference
        const_directed_graph_iterator<DirectedGraph>::operator*() const
    {
        return m_nodeIterator->value();
    }
    // Defer the details to the increment() helper.
    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph> &const_directed_graph_iterator<DirectedGraph>::operator++()
    {
        increment();
        return *this;
    }
    // Defer the details to the increment() helper.
    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph> const_directed_graph_iterator<DirectedGraph>::operator++(int)
    {
        auto oldIter{ *this };
        increment();
        return oldIter;
    }

    // Defer the details to the decrement() helper.
    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>&
        const_directed_graph_iterator<DirectedGraph>::operator--()
    {
        decrement();
        return *this;
    }

    // Defer the details to the decrement() helper.
    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>
        const_directed_graph_iterator<DirectedGraph>::operator--(int)
    {
        auto oldIter{ *this };
        decrement();
        return oldIter;
    }

    template<typename DirectedGraph>
    void const_directed_graph_iterator<DirectedGraph>::increment()
    {
        ++m_nodeIterator;
    }
    // undefined if m_nodeIterator already refers to the first
    template<typename DirectedGraph>
    void const_directed_graph_iterator<DirectedGraph>::decrement()
    {
        --m_nodeIterator;
    }
//    template<typename DirectedGraph>
//    bool const_directed_graph_iterator<DirectedGraph>::operator==(
//            const const_directed_graph_iterator<DirectedGraph> &rhs) const
//    {
//        return (rhs.m_nodeIterator == m_nodeIterator) && (rhs.m_graph == m_graph);
//
//    }
    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>::directed_graph_iterator(
            iterator_type iter, std::shared_ptr<const DirectedGraph> graph)
            :const_directed_graph_iterator<DirectedGraph>{iter, graph}
    {
    }

    template<typename DirectedGraph>
    typename directed_graph_iterator<DirectedGraph>::reference
        directed_graph_iterator<DirectedGraph>::operator*()
    {
        return const_cast<reference>(this->m_nodeIterator->value() );
    }

    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>::pointer
        directed_graph_iterator<DirectedGraph>::operator->()
    {
        return const_cast<pointer>(&(this->m_nodeIterator->value() ) );
    }

    // Defer the details to the increment() helper in the base class.
    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>&
    directed_graph_iterator<DirectedGraph>::operator++()
    {
        this->increment();
        return *this;
    }

    // Defer the details to the increment() helper in the base class.
    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>
    directed_graph_iterator<DirectedGraph>::operator++(int)
    {
        auto oldIt{ *this };
        this->increment();
        return oldIt;
    }

    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>&
        directed_graph_iterator<DirectedGraph>::operator--()
    {
        this->decrement();
        return *this;
    }
    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>
        directed_graph_iterator<DirectedGraph>::operator--(int)
    {
        auto oldIter{*this};
        this->decrement();
        return  oldIter;
    }


}