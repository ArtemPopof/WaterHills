#include "blmtlparser.h"

#include <src/utils/bllogger.h>
#include <map>

namespace black {

MtlParser::MtlParser()
    : m_file(), m_materials()
{

}

void MtlParser::parse(std::string file)
{
    if ( m_file.is_open() ) {
        m_file.close();
    }

    m_file.open(file);

    if ( !m_file.is_open() ) {
        // TODO: Exceptions
        Logger::getInstance() << "Can't open the file " << file << "!" << std::endl;

        throw "Cannot open the file!";
    }

    std::string line;

    // First file header
    getline(m_file, line);

    if ( line.find("MTL") == std::string::npos ) {
        // TODO: Exceptions
        Logger::getInstance() << "Bad file format " << file << "!" << std::endl;

        throw "Bad file format";
    }

    // Second header. Contains materials count
    m_file >> line; // #
    m_file >> line; // Material
    m_file >> line; // Count:

    int count = 0;
    m_file >> count;

    if ( count == 0 ) {
        // TODO: Exceptions
        Logger::getInstance() << "No materials found in file " << file << "!" << std::endl;

        throw "Empty material file";
    }

    QVector3D ambient;
    QVector3D diffuse;
    QVector3D spectacular;
    float shineFactor;

    std::string matName;
    std::string type;
    float value;
    while ( m_file >> line ) {
        while ( line != "newmtl" ) { }

        // Defaults
        ambient = { 0, 0, 0 };
        diffuse = { 0, 0, 0 };
        spectacular = { 0, 0, 0 };
        shineFactor = 0.5f;

        // Material name
        m_file >> matName;

        while ( m_file >> type ) {
            if ( type == "newmtl" ) { // Continue with next material
                m_file.unget();
                break;
            }

            if ( type == "Ns" ) {
                m_file >> value;

                shineFactor = value / 1000.0f;
            } else if ( type == "Ka" ) {
                ambient = getVector();
            } else if ( type == "Kd" ) {
                diffuse = getVector();
            } else if ( type == "Ks" ) {
                spectacular = getVector();
            }
        }

        m_materials[matName] = Material(ambient, diffuse, spectacular, shineFactor);
    }
}

QVector3D MtlParser::getVector()
{
    float x, y, z;

    m_file >> x;
    m_file >> y;
    m_file >> z;

    return { x, y, z };
}

std::map<std::string, Material> MtlParser::getMaterials() const
{
    return m_materials;
}

QVector3D MtlParser::getAmbient() const
{
    return m_materials.begin()->second.ambient();
}

QVector3D MtlParser::getDiffuse() const
{
    return m_materials.begin()->second.diffuse();
}

QVector3D MtlParser::getSpectacular() const
{
    return m_materials.begin()->second.spectacular();
}

float MtlParser::getShineFactor() const
{
    return m_materials.begin()->second.shineFactor();
}

} // end of black namespace
