#include <iostream>
#include <string>
using namespace std;

const int MAX = 50;

// ---------------- PRODUCT STRUCTURE ----------------
struct Product {
    int id;
    string name;
    float price;
    int stock;
};

// ---------------- DEFAULT PRODUCTS ----------------
Product products[MAX] = {
    {101, "Laptop\t",   120000, 10},
    {102, "Mouse\t",     1500, 50},
    {103, "Keyboard",3500,30},
    {104, "Printer\t",  45000, 5},
    {105, "Monitor\t",  38000, 12}
};

int productCount = 5;

// ---------------- FUNCTION DECLARATIONS ----------------
void login();
void adminMenu();
void userMenu();
void viewProducts();
void addProduct();
void searchProduct();
void updateStock();
void inventorySummary();
void multiProductBilling();

// ---------------- MAIN ----------------
int main() {
    login();
    return 0;
}

// ---------------- LOGIN ----------------
void login() {
    string username, password;

    cout << "\n\t\t=============================================\n";
    cout << "\t\t\t INVENTORY MANAGEMENT SYSTEM\n";
    cout << "\t\t=============================================\n";

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "ihtisham" && password == "222")
        adminMenu();
    else if (password == "000")
        userMenu();
    else
        cout << "\nInvalid Login!\n";
}

// ---------------- ADMIN MENU ----------------
void adminMenu() {
    int choice;
    do {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. View Products\n";
        cout << "2. Add Product\n";
        cout << "3. Search Product\n";
        cout << "4. Update Stock\n";
        cout << "5. Sell Products\n";
        cout << "6. Inventory Summary\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: addProduct(); break;
            case 3: searchProduct(); break;
            case 4: updateStock(); break;
            case 5: multiProductBilling(); break;
            case 6: inventorySummary(); break;
        }
    } while (choice != 0);
}

// ---------------- USER MENU ----------------
void userMenu() {
    int choice;
    do {
        cout << "\n========== USER MENU ==========\n";
        cout << "1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Buy Products\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: searchProduct(); break;
            case 3: multiProductBilling(); break;
        }
    } while (choice != 0);
}

// ---------------- VIEW PRODUCTS (LOW STOCK ALERT) ----------------
void viewProducts() {
    cout << "\nID\tName\t\tPrice\tStock\tStatus\n";
    cout << "-------------------------------------------------\n";

    for (int i = 0; i < productCount; i++) {
        cout << products[i].id << "\t"
             << products[i].name << "\t"
             << products[i].price << "\t"
             << products[i].stock << "\t";

        if (products[i].stock <= 5)
            cout << "LOW STOCK!";
        else
            cout << "Available";

        cout << endl;
    }
}

// ---------------- ADD PRODUCT ----------------
void addProduct() {
    if (productCount >= MAX) {
        cout << "Product limit reached!\n";
        return;
    }

    cout << "Enter Product ID: ";
    cin >> products[productCount].id;
    cout << "Enter Product Name: ";
    cin >> products[productCount].name;
    cout << "Enter Price: ";
    cin >> products[productCount].price;
    cout << "Enter Stock: ";
    cin >> products[productCount].stock;

    productCount++;
    cout << "Product added successfully!\n";
}

// ---------------- SEARCH PRODUCT ----------------
void searchProduct() {
    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "\nName: " << products[i].name
                 << "\nPrice: " << products[i].price
                 << "\nStock: " << products[i].stock << endl;
            return;
        }
    }
    cout << "Product not found!\n";
}

// ---------------- UPDATE STOCK ----------------
void updateStock() {
    int id, choice, qty;
    cout << "Enter Product ID: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            cout << "Current Stock: " << products[i].stock << endl;
            cout << "1. Add Stock\n2. Remove Stock\nChoose: ";
            cin >> choice;

            cout << "Enter Quantity: ";
            cin >> qty;

            if (choice == 1)
                products[i].stock += qty;
            else if (choice == 2 && qty <= products[i].stock)
                products[i].stock -= qty;
            else {
                cout << "Invalid operation!\n";
                return;
            }

            cout << "Updated Stock: " << products[i].stock << endl;
            return;
        }
    }
    cout << "Product not found!\n";
}

// ---------------- INVENTORY SUMMARY ----------------
void inventorySummary() {
    int totalStock = 0;
    float totalValue = 0;

    for (int i = 0; i < productCount; i++) {
        totalStock += products[i].stock;
        totalValue += products[i].stock * products[i].price;
    }

    cout << "\n========== INVENTORY SUMMARY ==========\n";
    cout << "Total Products: " << productCount << endl;
    cout << "Total Stock Items: " << totalStock << endl;
    cout << "Total Inventory Value: Rs. " << totalValue << endl;
}

// ---------------- DETAILED BILLING ----------------
void multiProductBilling() {
    int id, qty;
    char more;
    float grandTotal = 0;

    cout << "\n=========== DETAILED BILL ===========\n";
    cout << "Product\t\tQty\tPrice\tTotal\n";
    cout << "------------------------------------\n";

    do {
        cout << "Enter Product ID: ";
        cin >> id;

        bool found = false;

        for (int i = 0; i < productCount; i++) {
            if (products[i].id == id) {
                found = true;

                cout << "Enter Quantity: ";
                cin >> qty;

                if (qty <= 0 || qty > products[i].stock) {
                    cout << "Invalid quantity!\n";
                    return;
                }

                float total = qty * products[i].price;
                grandTotal += total;
                products[i].stock -= qty;

                cout << products[i].name << "\t\t"
                     << qty << "\t"
                     << products[i].price << "\t"
                     << total << endl;
                break;
            }
        }

        if (!found) {
            cout << "Product not found!\n";
            return;
        }

        cout << "Add more products? (y/n): ";
        cin >> more;

    } while (more == 'y' || more == 'Y');

    cout << "------------------------------------\n";
    cout << "GRAND TOTAL: Rs. " << grandTotal << endl;
    cout << "Thank you for shopping!\n";
}

