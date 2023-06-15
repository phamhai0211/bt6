#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

enum class ProductType {
    CHAIR,
    TABLE,
    CABINET
};

class Model {
public:
    Model(int id, const std::string& name, int referencePrice, ProductType type)
        : _m_id(id)
        , _m_name(name)
        , _m_referencePrice(referencePrice)
        , _m_type(type)
    {
    }
    ~Model() {}
    int getId() const {
        return _m_id;
    }

    const std::string& getName() const {
        return _m_name;
    }

    int getReferencePrice() const {
        return _m_referencePrice;
    }

    ProductType getType() const {
        return _m_type;
    }

private:
    int _m_id;
    std::string _m_name;
    int _m_referencePrice;
    ProductType _m_type;
};

class Product {
public:
    Product(int id, const std::string& name, int price)
        : _m_id(id)
        , _m_name(name)
        , _m_price(price)
    {
    }
    ~Product(){}
    int getId() const {
        return _m_id;
    }

    const std::string& getName() const {
        return _m_name;
    }

    int getPrice() const {
        return _m_price;
    }

    
    virtual std::string getSpecificInfo() const = 0;

private:
    int _m_id;
    std::string _m_name;
    int _m_price;
};

class Chair : public Product {
public:
    Chair(int id, const std::string& name, int price)
        : Product(id, name, price)
    {
    }
    ~Chair(){}
    std::string getSpecificInfo() const override {
        return "Chair specific info";
    }
};

class Table : public Product {
public:
    Table(int id, const std::string& name, int price)
        : Product(id, name, price)
    {
    }
    ~Table(){}
    std::string getSpecificInfo() const override {
        return "Table specific info";
    }
};


class Cabinet : public Product {
public:
    Cabinet(int id, const std::string& name, int price)
        : Product(id, name, price)
    {
    }

    std::string getSpecificInfo() const override {
        return "Cabinet specific info";
    }
};


class ModelList {
public:
    
    void addModel(const Model& model) {
        m_models.push_back(model);
    }

   
    void printList() const {
        for (const auto& model : m_models) {
            std::cout << "Model ID: " << model.getId() << ", Name: " << model.getName()
                << ", Reference Price: " << model.getReferencePrice() << std::endl;
        }
    }

private:
    std::vector<Model> m_models;
};

class Store {
public:
    void addProduct(const std::shared_ptr<Product>& product) {
        m_products.push_back(product);
    }

    void printList() const {
        for (const auto& product : m_products) {
            std::cout << "Product ID: " << product->getId() << ", Name: " << product->getName()
                << ", Price: " << product->getPrice() << ", Specific Info: "
                << product->getSpecificInfo() << std::endl;
        }
    }

    static Store& getInstance() {
        static Store instance;
        return instance;
    }

private:
    Store() {}
    ~Store(){}
    std::vector<std::shared_ptr<Product>> m_products;
};

class Factory {
public:
 
        static std::shared_ptr<Product> createProductByName(const std::string & modelName) {
        const auto& models = ModelList::getInstance().getModels();
        for (const auto& model : models) {
            if (model.getName() == modelName) {
                return createProductByType(model.getType(), model.getName(), model.getReferencePrice());
            }
        }
        return nullptr;
    }

    static std::shared_ptr<Product> createProductById(int modelId) {
        const auto& models = ModelList::getInstance().getModels();
        for (const auto& model : models) {
            if (model.getId() == modelId) {
                return createProductByType(model.getType(), model.getName(), model.getReferencePrice());
            }
        }
        return nullptr;
    }

private:
    
    static std::shared_ptr<Product> createProductByType(ProductType type, const std::string& name, int referencePrice) {
        switch (type) {
        case ProductType::CHAIR:
            return std::make_shared<Chair>(0, name, referencePrice);
        case ProductType::TABLE:
            return std::make_shared<Table>(0, name, referencePrice);
        case ProductType::CABINET:
            return std::make_shared<Cabinet>(0, name, referencePrice);
        default:
            return nullptr;
        }
    }
};

class ModelList {
public:
    
    void addModel(const Model& model) {
        _m_models.push_back(model);
    }

   
    void printList() const {
        for (const auto& model : _m_models) {
            std::cout << "Model ID: " << model.getId() << ", Name: " << model.getName()
                << ", Reference Price: " << model.getReferencePrice() << std::endl;
        }
    }

   
    const std::vector<Model>& getModels() const {
        return _m_models;
    }

    static ModelList& getInstance() {
        static ModelList instance;
        return instance;
    }

private:
    ModelList() {}
    std::vector<Model> _m_models;
};

int main() {
    
    ModelList::getInstance().addModel(Model(1, "Chair Model 1", 100, ProductType::CHAIR));
    ModelList::getInstance().addModel(Model(2, "Table Model 1", 200, ProductType::TABLE));
    ModelList::getInstance().addModel(Model(3, "Cabinet Model 1", 300, ProductType::CABINET));

    
    std::cout << "Model List:" << std::endl;
    ModelList::getInstance().printList();

  
    auto product1 = Factory::createProductById(1);
    auto product2 = Factory::createProductByName("Table Model 1");
    auto product3 = Factory::createProductById(3);

    
    Store::getInstance().addProduct(product1);
    Store::getInstance().addProduct(product2);
    Store::getInstance().addProduct(product3);

    
    std::cout << "Product List:" << std::endl;
    Store::getInstance().printList();

    return 0;
}