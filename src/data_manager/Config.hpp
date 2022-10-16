#pragma once

#include <string>

namespace irt
{
    class Config
    {
    public:
        // SETTER
        void set_input_file_path(const std::string& input_file_path) { _input_file_path = input_file_path; }
        void set_output_file_path(const std::string& output_file_path) { _output_file_path = output_file_path; }
        // GETTER
        std::string get_input_file_path() const { return _input_file_path; }
        std::string get_output_file_path() const { return _output_file_path; }
        // function

    private:
        std::string _input_file_path;
        std::string _output_file_path;
    };
}
