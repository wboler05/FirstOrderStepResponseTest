#include "systemresponseobject.h"

SystemResponseObject::SystemResponseObject()
{

}

SystemResponseObject::SystemResponseObject(const std::vector<double> & a, const std::vector<double> & b) {

    if (!setCoeffs(a, b)) {
        std::cout << "Failed to set coefficients." << std::endl;
    }

}

double SystemResponseObject::response(const double & in) {

    if (in != 0.0) {
        std::cout << "Test time!" << std::endl;
    }
    pushInput(in);
    shiftOutputs();

    // Handle Response
    double l_inputs = 0, l_outputs = 0;
    for (size_t i = 0; i < m_b.size(); i++){
        l_inputs += m_b[i]*m_input_memory[i];
    }

    for (size_t i = 1; i < m_a.size(); i++) {
        l_outputs += m_a[i]*m_output_memory[i];
    }

    m_output_memory[0] = l_inputs - l_outputs / m_a[0];
    return m_output_memory[0];
}

void SystemResponseObject::pushInput(const double & in) {
    // Handle Input
    if (m_input_memory.size() != 0) {
        shiftInputs();
        m_input_memory[0] = in;
    }
}

void SystemResponseObject::shiftInputs() {
    for (size_t i = 0; i < m_input_memory.size()-1; i++) {
        size_t it = m_input_memory.size() - 1 - i;
        m_input_memory[it] = m_input_memory[it-1];
    }
}

void SystemResponseObject::shiftOutputs() {
    for (size_t i = 0; i < m_output_memory.size() -1; i++) {
        size_t it = m_output_memory.size() - 1 - i;
        m_output_memory[it] = m_output_memory[it-1];
    }
}

bool SystemResponseObject::setCoeffs(const std::vector<double> & a, const std::vector<double> & b) {
    if (a.size() < 1) {
        return false;
    }

    m_a.resize(a.size());
    for (size_t i = 0; i < a.size(); i++) {
        m_a[i] = a[i];
    }

    m_b.resize(b.size());
    for (size_t i = 0; i < b.size(); i++) {
        m_b[i] = b[i];
    }

    m_output_memory.resize(a.size());
    m_input_memory.resize(b.size());

    return true;
}
