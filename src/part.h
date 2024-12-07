#ifndef PART_H
#define PART_H

#include "glm/glm.hpp"
#include "string"
#include "vector"
#include "map"

#include "connectors.h"
#include "constraints.h"

namespace draft {

    class Part {

      protected:

        // vertices are addressed by a unique string
        std::map<std::string, glm::vec3> _vertices;

        // connecting two vertices
        std::map<std::string, Connector> _connectors;

        // constraining degrees of freedom of vertices and connectors
        std::vector<Constraint> _constraints;
        
      public:

        std::string addVertex(const glm::vec3& vertex); // @return the unique identifier for the vertex
        std::string addConnector(const Connector& connector);  // @return the unique identifier for the connector

        bool moveVertex(const std::string& identifier, const glm::vec3& vertex);

        bool getVertex(const std::string& identifier, glm::vec3& vertex) const;
        std::string getVertex(const glm::vec3& position, float radius) const; // will return "" if no vertex was found there

        bool eraseVertex(const std::string& identifier);

        std::string getConnector(const glm::vec3& position, float radius) const;
        bool eraseConnector(const std::string& identifier);

        const std::map<std::string, glm::vec3>& getVertices() const;
        const std::map<std::string, Connector>& getConnectors() const;

      protected:

        bool isUniqueIdentifier(const std::string& identifier) const;
        std::string makeUniqueIdentifier(std::string identifier_base, uint32_t start_num = 0) const;

    };

} // draft

#endif // PART_H