#pragma once

#include <OgreTrays.h>

namespace core {

class UserInterface : public OgreBites::TrayListener {
public:
    virtual std::string getName() = 0;

    virtual void show() = 0;

    virtual void hide();
};

class UIManager {
public:
    void addListener(const std::shared_ptr<UserInterface>& listener);

    void showOnly(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<UserInterface>> m_interfaces;
};

} // end namespace core
