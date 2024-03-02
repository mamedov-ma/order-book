#pragma once

#include <map>
#include <cstdint>
#include <iostream>
#include <concepts>
#include <stdexcept>

namespace stock
{

using amount_t = std::size_t; // arbitrary chosen type
using price_t = double; // arbitrary chosen type

struct order
{
    order(price_t rprice, amount_t ramnount) noexcept { set(rprice, ramnount); }
    void set(price_t, amount_t) noexcept;

    price_t price{};
    amount_t amount{};
};

struct sale: public order
{
    using order::order;
};

struct purchase: public order
{
    using order::order;
};

template <class T>
concept AnOrder = std::is_base_of_v<order, T> && std::copyable<T> && std::movable<T>;

class OrderBook
{
public:
    using orders_t = std::map<price_t, amount_t>;

    orders_t const& crefSales() const noexcept { return m_sales; }
    orders_t const& crefPurchases() const noexcept { return m_purchases; }

    template <AnOrder ORDER>
    void addOrder(ORDER const& order)
    {
        if constexpr (std::is_same_v<ORDER, sale>)
        {
            if (auto const& [_, emplaced] = m_sales.try_emplace(order.price, order.amount); !emplaced) { m_sales[order.price] += order.amount; }
        }
        else
        {
            if (auto const& [_, emplaced] = m_purchases.try_emplace(order.price, order.amount); !emplaced) { m_purchases[order.price] += order.amount; }
        }
    }

    template <AnOrder ORDER>
    void modifyOrder(ORDER const& newOrder) // maybe look for std::expected, if exceptions aren't suitable
    {
        // TODO: get rid of copypaste, perhapse introduce lambda or smth
        if constexpr (std::is_same_v<ORDER, sale>)
        {
            if (auto it = m_sales.find(newOrder.price); it != m_sales.end())
            {
                it->second = newOrder.amount;
            }
            else
            {
                throw std::runtime_error("no order to modify");
            }
        }
        else
        {
            if (auto it = m_purchases.find(newOrder.price); it != m_purchases.end())
            {
                it->second = newOrder.amount;
            }
            else
            {
                throw std::runtime_error("no order to modify");
            }
        }
    }

    template <AnOrder ORDER>
    void deleteOrder(ORDER const& order)
    {
        if constexpr (std::is_same_v<ORDER, sale>) { m_sales.erase(order.price); }
        else { m_purchases.erase(order.price); }
    }

    void displayTopOrders(std::ostream& = std::cout) noexcept;

private:
    orders_t m_sales;
    orders_t m_purchases;
    static constexpr std::size_t WINDOW_SIZE{5};
};

} // namespace stock

