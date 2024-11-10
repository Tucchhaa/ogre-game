#pragma once

#include <OgreTrays.h>

namespace core {

class UIListener : public OgreBites::TrayListener {
public:
    virtual std::string getName() = 0;

    virtual void show() = 0;

    virtual void hide() = 0;
};

class UIManager {
public:
    void addListener(const std::shared_ptr<UIListener>& listener);

    void showOnly(const std::string& name);

private:
    std::map<std::string, std::shared_ptr<UIListener>> m_listeners;
};

} // end namespace core
