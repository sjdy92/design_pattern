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

// 윈도우용 버튼 클래스
class WindowsButton : public Button {
public:
    virtual ~WindowsButton() {}
    virtual void render() override {
        std::cout << "Rendering a Windows button." << std::endl;
    }
};

// 윈도우용 체크박스 클래스
class WindowsCheckbox : public Checkbox {
public:
    virtual ~WindowsCheckbox() {}
    virtual void render() override {
        std::cout << "Rendering a Windows checkbox." << std::endl;
    }
};

// 맥용 버튼 클래스
class MacButton : public Button {
public:
    virtual ~MacButton() {}
    virtual void render() override {
        std::cout << "Rendering a Mac button." << std::endl;
    }
};

// 맥용 체크박스 클래스
class MacCheckbox : public Checkbox {
public:
    virtual ~MacCheckbox() {}
    virtual void render() override {
        std::cout << "Rendering a Mac checkbox." << std::endl;
    }
};


// 추상 팩토리 인터페이스
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;

    static GUIFactory& getInstance();
};

// 윈도우용 팩토리 클래스
class WindowsFactory : public GUIFactory {
public:
    virtual Button* createButton() override {
        return new WindowsButton();
    }

    virtual Checkbox* createCheckbox() override {
        return new WindowsCheckbox();
    }
};

// 맥용 팩토리 클래스
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