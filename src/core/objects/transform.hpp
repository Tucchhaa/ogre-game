#pragma once

#include "base_movable_object.hpp"
#include "state/transform_state.hpp"

namespace core {

const Ogre::String TRANSFORM_TYPE = "Transform";

/**
 * This object must is used to synchronize Node's transform
 * and collider transform.
 *
 * This object should be created before any other objects.
 */
class Transform : public BaseMovableObject {
public:
    Transform() = default;
    explicit Transform(const std::string& name): BaseMovableObject(name) { }

    const std::string& getMovableType() const override { return TRANSFORM_TYPE; }

    std::shared_ptr<State> state() override { return m_state; }

    std::shared_ptr<TransformState> transformState() { return m_state; }

    /**
     * Sets transform state's values to the Node's transform values
     * Call this function after any scene node transform changing functions: setPosition, translate, etc...
     * But it's not necessary to call it in Scene::init(), because it's called in Transform::sceneInited()
     */
    void resetState() const;

    /**
     * Updates scene node's transform from current transform state
     */
    void updateNodeTransform() const;

private:
    std::shared_ptr<TransformState> m_state = std::make_shared<TransformState>();


    void sceneInited() override;
};

class TransformFactory : public Ogre::MovableObjectFactory {
    Ogre::MovableObject* createInstanceImpl(const std::string& name, const Ogre::NameValuePairList* params) override {
        return new Transform(name);
    }

public:
    const std::string& getType() const override { return TRANSFORM_TYPE; };
};

} // end namespace core

