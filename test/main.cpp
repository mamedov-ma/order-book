#include "order_book.hpp"

#include <chrono>
#include <string>
#include <cassert>
#include <sstream>
#include <iostream>
#include <string_view>

using namespace std::string_literals;
using namespace std::string_view_literals;

inline constexpr std::size_t MAX_REPS = 100'000'000;

class Validator
{
public:
    void validate()
    {
        checkAdd();
        checkModify();
        checkDelete();
        checkPrint();
        benchmark();
    }

private:
    void checkAdd()
    {
        stock::sale s{13.5, 70};
        m_book.addOrder(s);
        assert(m_book.crefSales().at(s.price) == s.amount);
        m_book.addOrder(s);
        assert(m_book.crefSales().at(s.price) == s.amount * 2);

        stock::purchase p{13.5, 70};
        m_book.addOrder(p);
        assert(m_book.crefPurchases().at(p.price) == p.amount);
        m_book.addOrder(p);
        assert(m_book.crefPurchases().at(p.price) == p.amount * 2);
    }

    void checkModify()
    {
        stock::sale s{13.5, 70};
        m_book.modifyOrder(s);
        assert(m_book.crefSales().at(s.price) == s.amount);
        s.set(15.5, 100);
        try
        {
            m_book.modifyOrder(s);
        }
        catch (std::exception const& exc)
        {
            assert(exc.what() == "no order to modify"sv);
        }

        stock::purchase p{13.5, 70};
        m_book.modifyOrder(p);
        assert(m_book.crefPurchases().at(p.price) == p.amount);
        p.set(15.5, 100);
        try
        {
            m_book.modifyOrder(p);
        }
        catch (std::exception const& exc)
        {
            assert(exc.what() == "no order to modify"sv);
        }
    }

    void checkDelete()
    {
        stock::sale s{13.5, 70};
        m_book.deleteOrder(s);
        assert(m_book.crefSales().empty());

        stock::purchase p{13.5, 70};
        m_book.deleteOrder(p);
        assert(m_book.crefPurchases().empty());
    }

    void checkPrint()
    {
        for (std::size_t i = 0; i < 10; ++i)
        {
            m_book.addOrder(stock::sale{1.0 + i, 100});
            m_book.addOrder(stock::purchase{1.0 + i, 100});
        }

        std::stringbuf buf;
        std::ostream ostream{&buf};

        m_book.displayTopOrders(ostream);
        assert(buf.str().find("Top sale orders: [price: 1, amount: 100] [price: 2, amount: 100] [price: 3, amount: 100] [price: 4, amount: 100] [price: 5, amount: 100]"s +
            "\nTop purchase orders: [price: 10, amount: 100] [price: 9, amount: 100] [price: 8, amount: 100] [price: 7, amount: 100] [price: 6, amount: 100]"s +
            "\n"s) != std::string::npos);

        for (std::size_t i = 0; i < 10; ++i)
        {
            m_book.deleteOrder(stock::sale{1.0 + i, 100});
            m_book.deleteOrder(stock::purchase{1.0 + i, 100});
        }
    }

    void benchmark() // TODO: use GBench or Catch2
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (std::size_t i = 0; i < MAX_REPS; ++i)
        {
            m_book.addOrder(stock::sale{1.0 + i, 100});
            m_book.addOrder(stock::purchase{1.0 + i, 100});
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << "Average time taken for adding orders: " << duration.count() / MAX_REPS << " nanoseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (std::size_t i = 0; i < MAX_REPS; ++i)
        {
            m_book.modifyOrder(stock::sale{1.0 + i, 200});
            m_book.modifyOrder(stock::purchase{1.0 + i, 200});
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << "Average time taken for modifying orders: " << duration.count() / MAX_REPS << " nanoseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (std::size_t i = 0; i < MAX_REPS; ++i)
        {
            m_book.deleteOrder(stock::sale{1.0 + i, 200});
            m_book.addOrder(stock::purchase{1.0 + i, 100});
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << "Average time taken for deleting orders: " << duration.count() / MAX_REPS << " nanoseconds" << std::endl;
    }

    stock::OrderBook m_book;
};

int main()
{
    Validator val;
    val.validate();

    return 0;
}

