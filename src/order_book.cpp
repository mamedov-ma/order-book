#include "order_book.hpp"

namespace stock
{

void order::set(price_t rprice, amount_t ramnount) noexcept
{
    price = rprice;
    amount = ramnount;
}

void OrderBook::displayTopOrders(std::ostream& ostream) const noexcept
{
    std::size_t count = WINDOW_SIZE > m_sales.size() ? m_sales.size() : WINDOW_SIZE;
    ostream << "\nTop sale orders:";
    for(auto it = m_sales.begin(); count != 0; --count)
    {
        ostream << " [price: " << it->first << ", amount: " << it->second << "]";
        ++it;
    }

    count = WINDOW_SIZE > m_purchases.size() ? m_purchases.size() : WINDOW_SIZE;
    ostream << "\nTop purchase orders:";
    for(auto it = m_purchases.rbegin(); count != 0; --count)
    {
        ostream << " [price: " << it->first << ", amount: " << it->second << "]";
        ++it;
    }
    ostream << "\n";
}

} // namespace stock
