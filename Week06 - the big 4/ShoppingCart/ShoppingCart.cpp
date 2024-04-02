#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable : 4996)

const int MAX_QUANTITY = 100;
const int BUFF_SIZE = 1024;

class Product {
private:
    char* name;
    double price;
    int quantity;

    void copyFrom(const Product& other);
    void free();

public:
    Product(const char* name, double price, int quantity);

    Product() : name(nullptr), price(0.00), quantity(0) {}

    Product(const Product& other);

    Product& operator=(const Product& other);

    ~Product();

    char* getName() const;
    
    double getPrice() const;

    int getQuantity() const;

    void setName(const char* name);

    void setPrice(double price);

    void setQuantity(int quantity);
};

void Product::copyFrom(const Product& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    price = other.price;
    quantity = other.quantity;
}

void Product::free() {
    delete[] name;
    name = nullptr;

    price = 0.00;
    quantity = 0;
}

Product::Product(const char* name, double price, int quantity) {
    setName(name);
    setPrice(price);
    setQuantity(quantity);
}

Product::Product(const Product& other) {
    copyFrom(other);
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Product::~Product() {
    free();
}

char* Product::getName() const {
    return this->name;
}

double Product::getPrice() const {
    return this->price;
}

int Product::getQuantity() const {
    return this->quantity;
}

void Product::setName(const char* name) {
    if (!name || this->name == name) {
        return;
    }
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Product::setPrice(double price) {
    if (price >= 0) {
        this->price = price;
    }
}

void Product::setQuantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
    }
}


class ShoppingCart {
private:
    Product* product;
    int maxQuantity;

    void copyFrom(const ShoppingCart& other);
    void free();

public:
    ShoppingCart(const Product* product, int max_quantity);

    ShoppingCart() : product(nullptr), maxQuantity(MAX_QUANTITY) {}

    ShoppingCart(const ShoppingCart& other);

    ShoppingCart& operator=(const ShoppingCart& other);

    ~ShoppingCart();

    Product* getProduct() const;

    int getMaxQuantity() const;

    void setProduct(const Product* product);

    void setMaxQuantity(int maxQuantity);

    void addProductToTheCart(const Product& product, int quantity);

    void removeProduct(const char* productName);

    bool isEmpty() const;

    double totalPrice();

    void sortByPrices();

    void sortByQuantity();

    void sortByName();

    void saveToFile(const ShoppingCart& cart, std::ofstream& file);
};

void ShoppingCart::copyFrom(const ShoppingCart& other) {
    this->maxQuantity = other.maxQuantity;
    this->product = new Product[this->maxQuantity];
    for (int i = 0; i < this->maxQuantity; ++i) {
        this->product[i] = other.product[i];
    }
}

void ShoppingCart::free() {
    delete[] product;

    product = nullptr;
    maxQuantity = 0;
}

ShoppingCart::ShoppingCart(const Product* product, int max_quantity) {
    setProduct(product);
    setMaxQuantity(max_quantity);
}

ShoppingCart::ShoppingCart(const ShoppingCart& other) {
    copyFrom(other);
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

ShoppingCart::~ShoppingCart() {
    free();
}

Product* ShoppingCart::getProduct() const {
    return this->product;
}

int ShoppingCart::getMaxQuantity() const {
    return this->maxQuantity;;
}

void ShoppingCart::setProduct(const Product* product) {
    /*if (!product || product == this->product) {
        return;
    }
    delete[] this->product;*/
    this->product = new Product[this->maxQuantity];
    for (int i = 0; i < this->maxQuantity; ++i) {
        this->product[i] = product[i];
    }
}

void ShoppingCart::setMaxQuantity(int maxQuantity) {
    if (maxQuantity >= 0) {
        this->maxQuantity = maxQuantity;
    }
}

void ShoppingCart::addProductToTheCart(const Product& product, int quantity) {
    if (quantity >= this->maxQuantity) {
        return;
    }

    for (int i = 0; i < this->maxQuantity; i++) {
        if (strcmp(product.getName(), this->product[i].getName()) == 0) {
            return;
        }
    }

    this->product[this->maxQuantity] = product;
    this->maxQuantity++;
}

void ShoppingCart::removeProduct(const char* productName) {
    for (int i = 0; i < this->maxQuantity; ++i) {
        if (strcmp(this->product[i].getName(), productName) == 0) {
            Product temp{};
            temp = this->product[i];
            this->product[i] = this->product[i + 1];
            this->product[i + 1] = temp;
            this->maxQuantity--;
            break;
        }
    }
}

bool ShoppingCart::isEmpty() const{
    if (maxQuantity == 0) {
        return true;
    }
    else return false;
}

double ShoppingCart::totalPrice() {
    double total = 0.00;
    for (int i = 0; i < this->maxQuantity; ++i) {
        total += product[i].getPrice();
    }
    return total;
}

void ShoppingCart::sortByName() {
    for (int i = 0; i < this->maxQuantity - 1; ++i) {
        for (int j = i; j < this->maxQuantity - i - 1; ++j) {
            if (strcmp(this->product[j].getName(), this->product[j + 1].getName()) > 0) {
                Product temp{};
                temp = this->product[j + 1];
                this->product[j + 1] = this->product[j];
                product[j] = temp;
            }
        }
    }
}

void ShoppingCart::sortByPrices() {
    for (int i = 0; i < maxQuantity - 1; ++i) {
        for (int j = i; j < this->maxQuantity - i - 1; ++j) {
            if (strcmp(this->product[j].getName(), this->product[j + 1].getName()) > 0) {
                Product temp{};
                temp = this->product[j + 1];
                this->product[j + 1] = this->product[j];
                product[j] = temp;
            }
        }
    }
}

void ShoppingCart::sortByQuantity() {
    for (int i = 0; i < maxQuantity - 1; ++i) {
        for (int j = i; j < this->maxQuantity - i - 1; ++j) {
            if (strcmp(this->product[j].getName(), this->product[j + 1].getName()) > 0) {
                Product temp{};
                temp = this->product[j + 1];
                this->product[j + 1] = this->product[j];
                product[j] = temp;
            }
        }
    }
}

void ShoppingCart::saveToFile(const ShoppingCart& cart, std::ofstream& file) {
    if (cart.isEmpty()) {
        std::cout << "Shopping cart has no products in it!\n";
        return;
    }

    if (!file.is_open()) {
        std::cout << "Error!\n";
        return;
    }

    while (!file.eof()) {
        char buff[BUFF_SIZE];
        for (int i = 0; i < maxQuantity; i++) {
            file << "name: " << product[i].getName() << ", price: " << product[i].getPrice() << ", quantity: " << product[i].getQuantity() << std::endl;
        }
    }

    if (file.eof()) {
        std::cout << "Products from the shopping cart has been added to a '.txt' file!\n";
    }
}


int main() {
    ShoppingCart cart;

    Product p1("Yogurt", 1.60, 3);
    Product p2("Eggs", 0.50, 6);

    cart.addProductToTheCart(p1, 1);
    cart.addProductToTheCart(p2, 1);

    std::cout << "Total price of cart: " << cart.totalPrice() << std::endl;

    cart.sortByPrices();

    std::ofstream file("products.txt");
    cart.saveToFile(cart, file);

    return 0;
}