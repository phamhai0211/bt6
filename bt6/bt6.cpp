// bt6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>
class Model
{
public:
    int id;
    std::string name;
    int reference_price;
    enum ProductType{CHAIR, TABLE, CABINET} product_type;

    Model(int id, std::string name, int reference_price, ProductType product_type)
        : id(id), name(name),reference_price(reference_price),product_type(product_type){}

    static std::vector<Model*> models;

    static void addModel(Model* model) 
    {
        models.push_back(model);
    }

    static void printModel() 
    {
        for (Model* model : models) 
        {
            std::cout << "ID" << model->id << std::endl;
            std::cout << "Name" << model->name << std::endl;
            std::cout << "Prize" << model->reference_price << std::endl;
            std::cout << "Product type: " << model->product_type << std::endl;
        }
    }
};

class Product 
{
public:
    int id;
    std::string name;
    int price;
    virtual std::string getSpecificInfo() = 0;
};

class Chair : public Product {
public:
    std::string material;
    std::string color;
    Chair(int id, std::string name, int price, std::string material, std::string color)
        :material(material), color(color) 
    {
        this->id = id;
        this->name = name;
        this->price = price;
    }
    std::string getSpecificInfo() override 
    {
        return "Chair specific info";
    }
};

class Table : public Product
{
public:
    std::string material;
    std::string shape;
    Table(int id, std::string name, int price, std::string material, std::string shape)
        :material(material), shape(shape)
    {
        this->id = id;
        this->name = name;
        this->price = price;
    }
    std::string getSpecificInfo() override 
    {
        return "Table specific info";
    }
};
class Cabinet : public Product 
{
public:
    std::string material;
    int num_drawers;
    Cabinet(int id, std::string name, int price, std::string material, int num_drawers)
        :material(material), num_drawers(num_drawers)
    {
        this->id = id;
        this->name = name;
        this->price = price;
    };
    std::string getSpecificInfo() override 
    {
        return "Cabinet specific info";
    }
};

class Store {
private:
    std::vector<Product*> products;
    static Store* instance;
    Store(){}
public:
    static Store* getInstance() {
        if (instance == nullptr) {
            instance = new Store();
        }
        return instance;
    }
    void addProduct(Product* product) {
        products.push_back(product);
    }

    void printProductList() {
        for (Product* product : products) {
            std::cout << "ID" << product->id << std::endl;
            std::cout << "Name" << product->name << std::endl;
            std::cout << "Price" << product->price << std::endl;
            std::cout << "Specific info" << product->getSpecificInfo() << std::endl;
        }
    }
};
Store* Store::instance = nullptr;
std::vector<Model*> Model::models;
int main()
{
    Model* model1 = new Model(1, "chair a", 100, Model::CHAIR);

    Model::addModel(model1);
    Model::printModel();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
