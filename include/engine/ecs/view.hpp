#pragma once

#include "component_pool.hpp"
#include <tuple>
#include <algorithm>

template <typename... Components>
class ComponentView
{
public:
    ComponentView(ComponentPool<Components> *...pools)
        : t_pools_(pools...)
    {
        b_isEmpty_ = ((pools == nullptr) || ...);

        if (!b_isEmpty_)
        {
            const IPool *base_pools[] = {static_cast<const IPool *>(pools)...};

            const IPool *min_pool = *std::min_element(std::begin(base_pools), std::end(base_pools),
                                                      [](const IPool *a, const IPool *b)
                                                      {
                                                          return a->size() < b->size();
                                                      });

            p_target_pool_ = min_pool;
        }
    }

    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = uint16_t;
        using difference_type = std::ptrdiff_t;
        using pointer = uint16_t *;
        using reference = uint16_t &;

        Iterator(const ComponentView *view, uint16_t index)
            : p_view_(view), i_index_(index)
        {
            if (i_index_ < GetTargetSize() && !IsValid())
            {
                ++(*this);
            }
        }

        Iterator &operator++()
        {
            do
            {
                ++i_index_;
            } while (i_index_ < GetTargetSize() && !IsValid());

            return *this;
        }

        // postfix increment is a little slower than prefix so we are just avoiding it here

        // Iterator operator++(int)
        // {
        //     Iterator tmp = *this;
        //     do
        //     {
        //         ++i_index_;
        //     } while (i_index_ < GetTargetSize() && !IsValid());

        //     return tmp;
        // }

        value_type operator*() const
        {
            return p_view_->p_target_pool_->GetEntityList()[i_index_];
        }

        friend bool operator==(const Iterator &a, const Iterator &b)
        {
            return (a.i_index_ == b.i_index_) && (a.p_view_ == b.p_view_);
        }

        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return (a.i_index_ != b.i_index_) || (a.p_view_ != b.p_view_);
        }

    private:
        size_t GetTargetSize() const
        {
            return p_view_->p_target_pool_->size();
        }

        bool IsValid() const
        {
            entity ent = p_view_->p_target_pool_->GetEntityList()[i_index_];
            return p_view_->HasAllComponents(ent);
        }

        size_t i_index_;
        const ComponentView *p_view_;
    };

    Iterator begin() const
    {
        if (b_isEmpty_ || p_target_pool_->size() == 0)
        {
            return end();
        }
        return Iterator(this, 0);
    }

    Iterator end() const
    {
        return Iterator(this, p_target_pool_ ? p_target_pool_->size() : 0);
    }

private:
    bool HasAllComponents(entity ent) const
    {
        return std::apply([ent](ComponentPool<Components> *...pools)
                          { return (pools->Has(ent) && ...); }, t_pools_);
    }

    std::tuple<ComponentPool<Components> *...> t_pools_;
    const IPool *p_target_pool_ = nullptr;
    bool b_isEmpty_;
};