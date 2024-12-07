#include "part.h"
#include "sstream"
#include "iostream"

namespace draft {


    std::string Part::addVertex(const glm::vec3& vertex) {
        // @return false, if another vertex uses the same identifier string, in which case the vertex will not be added

        std::string identifier = makeUniqueIdentifier("v_");

        _vertices[identifier] = vertex;

        return identifier;
    }

    std::string Part::addConnector(const Connector& connector) {

        if(connector.getVertex0() == connector.getVertex1())
            return "";
        
        std::string identifier = makeUniqueIdentifier("c_");

        _connectors[identifier] = connector;

        return identifier;
    }

    bool Part::moveVertex(const std::string& identifier, const glm::vec3& vertex) {

        if(_vertices.find(identifier) == _vertices.end())
            return false;

        _vertices.at(identifier) = vertex;

        return true;
    }

    bool Part::getVertex(const std::string& identifier, glm::vec3& vertex) const {

        if(_vertices.find(identifier) == _vertices.end())
            return false;

        vertex = _vertices.at(identifier);

        return true;
    }

    std::string Part::getVertex(const glm::vec3& position, float radius) const {
        // will return "" if no vertex was found there

        for(auto const& p : _vertices) {

            if(glm::length(position - p.second) < radius)
                return p.first;

        }
        
        return "";
    } 
    
    bool Part::eraseVertex(const std::string& identifier) {

        if(_vertices.find(identifier) == _vertices.end())
            return false;

        _vertices.erase(identifier);

        std::vector<std::string> unused_connectors;
        for(auto& c : _connectors) {

            if(c.second.getVertex0() == identifier || c.second.getVertex1() == identifier) {
                
                unused_connectors.push_back(c.first);
            }

        }

        for(const std::string& s : unused_connectors)
            _connectors.erase(s);

        return true;
    }

    std::string Part::getConnector(const glm::vec3& position, float radius) const {

        for(auto& c : _connectors) {

            if(c.second.getConnectorType() == Connector::ConnectorType::LINE) {

                glm::vec3 v0, v1;
                if(getVertex(c.second.getVertex0(), v0) && getVertex(c.second.getVertex1(), v1)) {

                    glm::vec3 dir = glm::normalize(v1 - v0);
                    float f = glm::dot(dir, position - v0);

                    if(f < 0.0f || f > glm::length(v1 - v0))
                        continue;

                    if(glm::length(v0 + dir * f - position) < radius)
                        return c.first;

                }

            }

        }

        return "";
    }

    bool Part::eraseConnector(const std::string& identifier) {

        if(_connectors.find(identifier) == _connectors.end())
            return false;

        _connectors.erase(identifier);

        return true;
    }

    const std::map<std::string, glm::vec3>& Part::getVertices() const {
        
        return _vertices;
    }

    const std::map<std::string, Connector>& Part::getConnectors() const {

        return _connectors;
    }

    bool Part::isUniqueIdentifier(const std::string& identifier) const {

        if(_vertices.find(identifier) != _vertices.end() || _connectors.find(identifier) != _connectors.end()) {
            // identifier is not unique
            return false;
        }

        return true;
    }

    std::string Part::makeUniqueIdentifier(std::string identifier_base, uint32_t start_num) const {

        if(identifier_base == "")
            identifier_base = "_";

        if(isUniqueIdentifier(identifier_base))
            return identifier_base;

        std::string identifier = identifier_base + std::to_string(start_num);

        if(isUniqueIdentifier(identifier))
            return identifier;

        // recursivly call makeUniqueIdentifier
        return makeUniqueIdentifier(identifier_base, start_num + 1);
    }

} // draft