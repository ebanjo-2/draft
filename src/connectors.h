#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "string"

namespace draft {

    class Connector {

      public:

        enum ConnectorType {
            LINE,
            CIRCLE_ARC,
        };

      protected:

        std::string _vertex0;
        std::string _vertex1;

        ConnectorType _type;

      public:

        Connector() = default;
        Connector(const std::string& vertex0, const std::string& vertex1, ConnectorType type);

        void setVertex0(const std::string& vertex0);
        void setVertex1(const std::string& vertex1);
        void setConnectorType(ConnectorType type);

        const std::string& getVertex0() const;
        const std::string& getVertex1() const;
        ConnectorType getConnectorType() const;

    };

} // draft

#endif // CONNECTORS_H