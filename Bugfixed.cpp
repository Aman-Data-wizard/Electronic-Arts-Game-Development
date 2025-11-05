#include <string>
#include <iostream>
#include <utility>
#include <vector> // We'll add this for the optimal solution later.

class Item {
// ... (Item class remains the same) ...
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
    Item *items[20];
    float total_money;
    int item_count;

    static void display_data(Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

    // --- NEW HELPER FUNCTION ---
    // This private method handles the actual removal and shifting.
    void completely_remove_item_at_index(int index) {
        // Step 1: Free the memory to prevent a leak.
        delete items[index];

        // Step 2: Shift all subsequent elements one position to the left.
        for (int i = index; i < item_count - 1; ++i) {
            items[i] = items[i + 1];
        }

        // Step 3: Decrement the total item count.
        item_count--;
        std::cout << "\nThe item has been completely removed from inventory.";
    }


public:
    Inventory() :
            items{},
            total_money{0},
            item_count{0} {

    }
    
    // Destructor to prevent memory leaks when the program closes.
    ~Inventory() {
        for(int i = 0; i < item_count; ++i) {
            delete items[i];
        }
    }

    void add_item() {
        // This check prevents the buffer overflow crash.
        if (item_count >= 20) {
            std::cout << "\nInventory is full. Cannot add more items.";
            return;
        }
        
        std::string name;
        int quantity;
        float price;

        // Using std::ws to consume any leftover whitespace from previous inputs.
        std::cout << "\nEnter item name: ";
        std::cin >> std::ws;
        std::getline(std::cin, name);

        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        items[item_count] = new Item(name, quantity, price);
        item_count++;
    }

    void sell_item() {
        std::string item_to_check;
        std::cout << "\nEnter item name: ";
        std::cin >> std::ws;
        std::getline(std::cin, item_to_check);


        for (int i = 0; i < item_count; i++) {
            if (items[i]->is_match(item_to_check)) {
                // Pass the index 'i' to the remove_item function
                remove_item(i);
                return;
            }
        }
        std::cout << "\nThis item is not in your Inventory";
    }

    // --- MODIFIED FUNCTION ---
    void remove_item(int item_index) {
        int input_quantity;
        Item *item = items[item_index];
        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int current_quantity = item->get_quantity();
        if (input_quantity < current_quantity) {
            // If we are not selling all of them, just update the quantity.
            float price = item->get_price();
            float money_earned = price * input_quantity;
            item->set_quantity(current_quantity - input_quantity);
            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;
            total_money += money_earned;
        } else if (input_quantity == current_quantity) {
            // If the quantity will become zero, remove the item completely.
            float price = item->get_price();
            float money_earned = price * input_quantity;
            std::cout << "\nFinal items sold.";
            std::cout << "\nMoney received: " << money_earned;
            total_money += money_earned;
            completely_remove_item_at_index(item_index);
        }
        else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() {
        if (item_count == 0) {
            std::cout << "\nInventory empty.";
            return;
        }

        for (int i = 0; i < item_count; i++) {
            display_data(*items[i]);
            std::cout << "\n";
        }
    }
};

// --- Main function remains the same ---
int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (1) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

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
                return 0; // Use return 0 for a clean exit.

            default:
                std::cout << "\nInvalid choice entered";
                // Clear error flags and ignore the rest of the line.
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                break;
        }
    }
}
