#include "constraints.h"

namespace draft {

    Constraint::Constraint(ConstraintType type, const std::string& target, const std::string& reference, float value) 
        : _type(type), _target(target), _reference(reference), _value(value) {

    }

    void Constraint::setType(ConstraintType type) {

        _type = type;
    }

    void Constraint::setTarget(const std::string& target) {

        _target = target;
    }

    void Constraint::setReference(const std::string& reference) {

        _reference = reference;
    }

    void Constraint::setValue(float value) {

        _value = value;
    }

    Constraint::ConstraintType Constraint::getType() const {

        return _type;
    }

    const std::string& Constraint::getTarget() const {

        return _target;
    }

    const std::string& Constraint::getReference() const {

        return _reference;
    }

    float Constraint::getValue() const {

        return _value;
    }

} // draft