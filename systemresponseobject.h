#ifndef SYSTEMRESPONSEOBJECT_H
#define SYSTEMRESPONSEOBJECT_H

#include <vector>
#include <cinttypes>
#include <iostream>

class SystemResponseObject
{
public:
    SystemResponseObject();
    SystemResponseObject(const std::vector<double> & a, const std::vector<double> & b);
    bool setCoeffs(const std::vector<double> & a, const std::vector<double> & b);

    double response(const double & );

    void pushInput(const double & in);
    void shiftInputs();
    void shiftOutputs();

private:
    std::vector<double> m_a;
    std::vector<double> m_b;
    std::vector<double> m_input_memory;
    std::vector<double> m_output_memory;
};

#endif // SYSTEMRESPONSEOBJECT_H
