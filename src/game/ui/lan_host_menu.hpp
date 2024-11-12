#pragma once

#include "../../core/ui_manager.hpp"

namespace game {

class LANHostMenu : public core::UserInterface {
public:
    std::string getName() override { return "LAN_HOST_MENU"; }

    void show() override;

    void buttonHit(OgreBites::Button* button) override;

private:
    OgreBites::TextBox* m_countBox = nullptr;
    unsigned int m_callbackId = -1;

    void updateCountBox() const;

    std::string getCountBoxText() const;
};

} // end namespace game
