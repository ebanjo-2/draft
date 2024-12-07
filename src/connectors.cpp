#include "connectors.h"

namespace draft {

    Connector::Connector(const std::string& vertex0, const std::string& vertex1, ConnectorType type)
        : _vertex0(vertex0), _vertex1(vertex1), _type(type) {

    }

    void Connector::setVertex0(const std::string& vertex0) {

        _vertex0 = vertex0;
    }

    void Connector::setVertex1(const std::string& vertex1) {

        _vertex1 = vertex1;
    }

    void Connector::setConnectorType(ConnectorType type) {

        _type = type;
    }

    const std::string& Connector::getVertex0() const {

        return _vertex0;
    }

    const std::string& Connector::getVertex1() const {

        return _vertex1;
    }

    Connector::ConnectorType Connector::getConnectorType() const {

        return _type;
    }

} // draft