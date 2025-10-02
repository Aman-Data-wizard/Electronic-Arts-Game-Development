#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <limits>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(
            std::string name,
            int quantity,
            float price
    ) :
            name{std::move(name)},
            quantity{quantity},
            price{price} {

    }

    std::string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const std::string &other) {
        return name == other;
    }
};


class Inventory {
private:
    std::vector<std::unique_ptr<Item>> m_items;
    float m_total_money;

    static void display_data(const std::unique_ptr<Item>& item) {
        std::cout << "\nItem name: " << item->get_name();
        std::cout << "\nQuantity: " << item->get_quantity();
        std::cout << "\nPrice: " << item->get_price();
    }

public:
    Inventory() : m_total_money{0} {
    }
    
    ~Inventory() = default;

    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cout << "\nEnter item name: ";
        std::cin >> std::ws;
        std::getline(std::cin, name);

        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        m_items.push_back(std::make_unique<Item>(name, quantity, price));
        std::cout << "\nItem '" << name << "' added to inventory.";
    }

    void sell_item() {
        std::string item_to_check;
        std::cout << "\nEnter item name: ";
        std::cin >> std::ws;
        std::getline(std::cin, item_to_check);

        for (auto it = m_items.begin(); it != m_items.end(); ++it) {
            if ((*it)->is_match(item_to_check)) {
                remove_item(it);
                return;
            }
        }
        std::cout << "\nThis item is not in your Inventory";
    }

    void remove_item(std::vector<std::unique_ptr<Item>>::iterator it) {
        int input_quantity;
        Item* item = it->get();

        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int current_quantity = item->get_quantity();
        if (input_quantity < current_quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            item->set_quantity(current_quantity - input_quantity);
            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;
            m_total_money += money_earned;
        } else if (input_quantity == current_quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            std::cout << "\nFinal items sold.";
            std::cout << "\nMoney received: " << money_earned;
            m_total_money += money_earned;
            
            m_items.erase(it);
            std::cout << "\nThe item has been completely removed from inventory.";
        } else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() {
        if (m_items.empty()) {
            std::cout << "\nInventory empty.";
            return;
        }
        
        for (const auto& item : m_items) {
            display_data(item);
            std::cout << "\n";
        }
    }
};

int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (true) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;
        
        if(std::cin.fail()) {
            std::cout << "\nInvalid choice entered. Please enter a number.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                return 0;

            default:
                std::cout << "\nInvalid choice entered. Please choose from the menu.";
                break;
        }
    }
}

