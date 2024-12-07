#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "string"

namespace draft {

    class Constraint {

      public:

        enum ConstraintType {
            LENGTH, // of a Line
            RADIUS,
            ANGLE,
            
        };

      protected:

        ConstraintType _type;

        std::string _target; // could be a vertex or a connector
        std::string _reference; // could be a vertex or a connector

        float _value;

      public:

        Constraint() = default;
        Constraint(ConstraintType type, const std::string& target, const std::string& reference, float value);

        void setType(ConstraintType type);
        void setTarget(const std::string& target);
        void setReference(const std::string& reference);
        void setValue(float value);

        ConstraintType getType() const;
        const std::string& getTarget() const;
        const std::string& getReference() const;
        float getValue() const;

    };

} // draft

#endif // CONSTRAINTS_H