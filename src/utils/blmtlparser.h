#ifndef BLMTLPARSER_H
#define BLMTLPARSER_H

#include <src/core/blmaterial.h>

#include <string>
#include <fstream>
#include <map>

namespace black {

/**
 * @brief The MtlParser class
 * Parses a .mtl files. File can contain one or more
 * materials.
 *
 * @version 1.0 23.03.2017
 * Working version. Can parse all materials in .mtl file.
 *
 * @author george popoff <popoff96@live.com>
 */
class MtlParser
{
public:
    MtlParser();

    void parse(std::string file);


    std::map<std::string, Material> getMaterials() const;
    const Material& getMaterial(std::string name) const { return m_materials.at(name); }

    QVector3D getAmbient() const;
    QVector3D getDiffuse() const;
    QVector3D getSpectacular() const;
    float getShineFactor() const;

private:
    QVector3D getVector();

private:

    std::ifstream m_file;
    std::map<std::string, Material> m_materials;
};

} // end of black namespace
#endif // BLMTLPARSER_H
