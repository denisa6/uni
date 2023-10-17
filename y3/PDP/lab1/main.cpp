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
    std::vector<std::string> productNames;
    std::vector<int> quantities;
    int totalPrice;
};

std::vector<Product> supermarketProducts;
std::vector<Bill> sales;
int aquiredMoney = 0;

std::mutex* productsMutexes;
std::mutex aquiredMoneyMutex;
std::mutex billsMutex;
std::mutex salesMutex;

int generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void checkInventory() {
    aquiredMoneyMutex.lock();
    billsMutex.lock();
    
    int calculatedAmount = 0;
    for (const auto& bill : sales) {
        calculatedAmount += bill.totalPrice;
    }
    if (aquiredMoney == calculatedAmount) {
        std::cout << "check passed :)\n";
    }
    else {
        std::cout << "check failed :(\n";
    }
    std::cout << "calculated amount from bills:  " << calculatedAmount << ", actual amount in the bank: " << aquiredMoney <<"\n";

    aquiredMoneyMutex.unlock();
    billsMutex.unlock();
}

void populateSupermarket() {
    std::vector<std::string> productNames = { "apples","bananas","chocolate","eggs","flour","milk","cheese","tomatoes","lettuce","pumpkin" };
    for (int i = 0; i < productNames.size(); i++) {
        int quantity = generateRandomNumber(1, 100);
        int price = generateRandomNumber(1, 25);
        Product product;
        product.name = productNames[i];
        product.quantity = quantity;
        product.unitPrice = price;
        supermarketProducts.push_back(product);
    }
    std::cout << "the supermarket was populated\n";
};

bool sellProduct(std::vector<int> productIds, std::vector<int> quantities) {
    int totalPrice = 0;
    std::vector<std::string> soldItems;
    std::vector<int> soldQuantities;
    
    for (int i = 0; i < productIds.size(); i++) {
        productsMutexes[productIds[i]].lock();
        
        if (productIds[i] < 0 || productIds[i] > supermarketProducts.size() - 1) {
            productsMutexes[productIds[i]].unlock();
            return false;
        }
        else if (supermarketProducts[productIds[i]].quantity < quantities[i]) {
            productsMutexes[productIds[i]].unlock();
        }
        else {
            totalPrice += supermarketProducts[productIds[i]].unitPrice * quantities[i];
            supermarketProducts[productIds[i]].quantity = supermarketProducts[productIds[i]].quantity - quantities[i];
            soldItems.push_back(supermarketProducts[productIds[i]].name);
            soldQuantities.push_back(quantities[i]);
            productsMutexes[productIds[i]].unlock();
        }
    }
    aquiredMoneyMutex.lock();
    aquiredMoney += totalPrice;
    aquiredMoneyMutex.unlock();

    Bill bill;
    bill.productNames = soldItems;
    bill.quantities = quantities;
    bill.totalPrice = totalPrice;

    salesMutex.lock();
    sales.push_back(bill);
    salesMutex.unlock();
    return true;
}

int main() {
    populateSupermarket();
    int numThreads = 25;
    int numSalesPerThread = 10;
    productsMutexes = new std::mutex[supermarketProducts.size()];

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back([&]() {
            for (int j = 0; j < numSalesPerThread; j++) {
                int nbProducts = generateRandomNumber(1, 5);
                std::vector<int> productsToBuy;
                std::vector<int> quantitiesToBuy;
                for (int k = 0; k < nbProducts; k++) {
                    int productId = generateRandomNumber(0, supermarketProducts.size()-1);
                    int quantity = generateRandomNumber(1, 20);
                    productsToBuy.push_back(productId);
                    quantitiesToBuy.push_back(quantity);
                }
                bool trySell = sellProduct(productsToBuy, quantitiesToBuy);
                if (sales.size() % 5 == 0) {
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
