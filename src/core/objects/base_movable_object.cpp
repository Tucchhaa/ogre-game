#include "base_movable_object.hpp"

#include "../game.hpp"
#include "../network_layer/network_layer_manager.hpp"
#include "../network_layer/server.hpp"

namespace core {

std::map<int, BaseMovableObject*> BaseMovableObject::m_instances;

} // end namespace core