/*** 
 * @Date: 2025-04-01 14:30:27
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-04-01 15:17:40
 * @FilePath: \qt_custom_widget\include\basemodule\templates.h
 */
#pragma once
#include <QString>

// Forward declarations
class AbstractTemplate;
class MachineTemplate;
class AbstractMachine;
class Machine;
class AbstractMeasureLocation;
class MeasureLocation;

class AbstractTemplate
{
    AbstractTemplate() = default;
    virtual ~AbstractTemplate() = default;
};


class AbstractMachine
{
public:
    AbstractMachine() = default;
    virtual ~AbstractMachine() = default;

protected:
    void loadJsonParams(const QString &jsonFilePath);
};


class MachineTemplate
{
public:
    MachineTemplate() = default;
    virtual ~MachineTemplate() = default;
};


class AbstractMeasureLocation
{
public:
    AbstractMeasureLocation() = default;
    virtual ~AbstractMeasureLocation() = default;
};


class MeasureLocation
{
public:
    MeasureLocation() = default;
    virtual ~MeasureLocation() = default;
};





