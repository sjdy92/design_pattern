#include <iostream>
#include <vector>
#include <string>

class Component {
public:
    Component(std::string&& name)
        : _name(name) {}

    virtual std::string extension() = 0;

    virtual void print(int depth) {
        for (int index = 0; index < depth; ++index) {
            std::cout << "  ";
        }
        std::cout << _name << "." << extension() << std::endl;
    }

private:
    std::string _name;
};

class Folder : public Component {
public:
    Folder(std::string&& name)
        : Component(std::move(name)) {}

    virtual std::string extension() { return ""; }

    virtual void print(int depth) override {
        Component::print(depth);
        ++depth;

        // iterator
        for (auto it = components.begin(); it != components.end(); ++it) {
            (*it)->print(depth);
        }
    }

    void addComponent(Component* component) {
        components.push_back(component);
    }

    std::vector<Component*> components;
};

class ExeFile : public Component {
public:
    ExeFile(std::string&& name)
        : Component(std::move(name)) {}
    virtual std::string extension() { return "exe"; }
};

class TextFile : public Component {
public:
    TextFile(std::string&& name)
        : Component(std::move(name)) {}
    virtual std::string extension() { return "txt"; }
};

class ImageFile : public Component {
public:
    ImageFile(std::string&& name)
        : Component(std::move(name)) {}
    virtual std::string extension() { return "png"; }
};

//int main() {
//    Folder* folder1 = new Folder("sub-dir");
//    Folder* folder2 = new Folder("root");
//    ExeFile* exe = new ExeFile("hello");
//    TextFile* txt = new TextFile("composite");
//    ImageFile* img = new ImageFile("pattern");
//
//    folder1->addComponent(exe);
//    folder1->addComponent(txt);
//    folder2->addComponent(folder1);
//    folder2->addComponent(img);
//    folder2->print(0);
//
//    return 0;
//}
