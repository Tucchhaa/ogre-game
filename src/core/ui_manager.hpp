#pragma once

#include <OgreTrays.h>

namespace core {

class NetworkManager;
class UIManager;

class UserInterface : public OgreBites::TrayListener {
public:
    UserInterface();

    virtual std::string getName() = 0;

    virtual void show() = 0;

    virtual void hide();

    virtual void update();

protected:
    OgreBites::TrayManager* m_tray;

    std::shared_ptr<UIManager> m_ui;
    std::shared_ptr<NetworkManager> m_network;
};

class UIManager {
public:
    void addListener(const std::shared_ptr<UserInterface>& listener);

    void showOnly(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<UserInterface>> m_interfaces;
};

} // end namespace core
