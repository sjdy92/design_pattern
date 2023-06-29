#include <iostream>

enum Platform {
    Windows,
    Mac
};

Platform gPlatform = Windows;

bool isPlatformWindows() {
    return gPlatform == Windows;
}

bool isPlatformMac() {
    return gPlatform == Mac;
}

class UIObject {
public:
    virtual ~UIObject() {}
    virtual void render() = 0;
};

class Button : public UIObject {
public:
    virtual ~Button() {}
    virtual void render() = 0;
};

class Checkbox : public UIObject {
public:
    virtual ~Checkbox() {}
    virtual void render() = 0;
};

// ������� ��ư Ŭ����
class WindowsButton : public Button {
public:
    virtual ~WindowsButton() {}
    virtual void render() override {
        std::cout << "Rendering a Windows button." << std::endl;
    }
};

// ������� üũ�ڽ� Ŭ����
class WindowsCheckbox : public Checkbox {
public:
    virtual ~WindowsCheckbox() {}
    virtual void render() override {
        std::cout << "Rendering a Windows checkbox." << std::endl;
    }
};

// �ƿ� ��ư Ŭ����
class MacButton : public Button {
public:
    virtual ~MacButton() {}
    virtual void render() override {
        std::cout << "Rendering a Mac button." << std::endl;
    }
};

// �ƿ� üũ�ڽ� Ŭ����
class MacCheckbox : public Checkbox {
public:
    virtual ~MacCheckbox() {}
    virtual void render() override {
        std::cout << "Rendering a Mac checkbox." << std::endl;
    }
};


// �߻� ���丮 �������̽�
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;

    static GUIFactory& getInstance();
};

// ������� ���丮 Ŭ����
class WindowsFactory : public GUIFactory {
public:
    virtual Button* createButton() override {
        return new WindowsButton();
    }

    virtual Checkbox* createCheckbox() override {
        return new WindowsCheckbox();
    }
};

// �ƿ� ���丮 Ŭ����
class MacFactory : public GUIFactory {
public:
    virtual Button* createButton() override {
        return new MacButton();
    }

    virtual Checkbox* createCheckbox() override {
        return new MacCheckbox();
    }
};

GUIFactory& GUIFactory::getInstance() {
    if (isPlatformWindows()) {
        static WindowsFactory f;
        return f;
    }
    else if (isPlatformMac()) {
        static MacFactory f;
        return f;
    }
    else {
        //throw 
    }
}


int main() {
    Button* button = GUIFactory::getInstance().createButton();
    Checkbox* checkBox = GUIFactory::getInstance().createCheckbox();
    button->render();
    checkBox->render();
}