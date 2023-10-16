#include <mutex>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <ctime>
#include <atomic>
#include <windows.h>

struct Product {
    std::string name;
    int quantity;
    int unitPrice;
};

struct Bill {
    std::vector<std::string> productsName;
    std::vector<int> quantities;
    int totalPrice;
};

std::vector<Product> supermarket;
std::vector<Bill> sales;
int totalMoney = 0;

std::mutex* productMutaxes;
std::mutex totalMoneyMutex;
std::mutex billsMutex;
std::mutex salesMutex;

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void checkInventory() {
    totalMoneyMutex.lock();
    billsMutex.lock();
    
    int calculatedAmount = 0;
    for (const auto& bill : sales) {
        calculatedAmount += bill.totalPrice;
    }
    if (totalMoney == calculatedAmount) {
        std::cout << "Inventory check passed.\n";
    }
    else {
        std::cout << "Inventory check failed!\n";
    }
    std::cout << "calculated amount from bills:  " << calculatedAmount << ", actual amount in the bank: " << totalMoney <<"\n";

    billsMutex.unlock();
    totalMoneyMutex.unlock();
}

void populateSupermarket() {
    std::vector<std::string> products = { "apples","bananas","chocolate","eggs","flour","milk","cheese","tomatoes","lettuce","pumpkin" };
    for (int i = 0; i < products.size(); i++) {
        int quantity = generateRandomNumber(1, 100);
        int price = generateRandomNumber(1, 25);
        Product product;
        product.name = products[i];
        product.quantity = quantity;
        product.unitPrice = price;
        supermarket.push_back(product);
    }
    std::cout << "the supermarket was populated\n";
};

bool sellProduct(std::vector<int> productIds, std::vector<int> quantities) {
    int totalPrice = 0;
    std::vector<std::string> soldItems;
    std::vector<int> soldQuantities;
    
    for (int i = 0; i < productIds.size(); i++) {
        productMutaxes[productIds[i]].lock();
        
        if (productIds[i] < 0 || productIds[i] > supermarket.size() - 1) {
            productMutaxes[productIds[i]].unlock();
            return false;
        }
        else if (supermarket[productIds[i]].quantity < quantities[i]) {
            productMutaxes[productIds[i]].unlock();
        }
        else {
            totalPrice += supermarket[productIds[i]].unitPrice * quantities[i];
            supermarket[productIds[i]].quantity = supermarket[productIds[i]].quantity - quantities[i];
            soldItems.push_back(supermarket[productIds[i]].name);
            soldQuantities.push_back(quantities[i]);
            productMutaxes[productIds[i]].unlock();
        }
    }
    totalMoneyMutex.lock();
    totalMoney += totalPrice;
    totalMoneyMutex.unlock();

    Bill bill;
    bill.productsName = soldItems;
    bill.quantities = quantities;
    bill.totalPrice = totalPrice;

    salesMutex.lock();
    sales.push_back(bill);
    salesMutex.unlock();
    return true;
}

int main() {
    populateSupermarket();
    int numThreads = 15;
    int numSalesPerThread = 10;
    productMutaxes = new std::mutex[supermarket.size()];

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back([&]() {
            for (int j = 0; j < numSalesPerThread; j++) {
                int nbProducts = generateRandomNumber(1, 5);
                std::vector<int> productsToBuy;
                std::vector<int> quantitiesToBuy;
                for (int k = 0; k < nbProducts; k++) {
                    int productId = generateRandomNumber(0, supermarket.size()-1);
                    int quantity = generateRandomNumber(1, 20);
                    productsToBuy.push_back(productId);
                    quantitiesToBuy.push_back(quantity);
                }
                bool trySell = sellProduct(productsToBuy, quantitiesToBuy);
                if (sales.size() % 3 == 0) {
                    Sleep(1);
                    checkInventory();
                }
            }
        }
        );
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    std::cout << "\nfinal check\n";
    checkInventory();
    return 0;
}
