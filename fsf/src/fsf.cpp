/**
 * @file fsf.cpp
 * @brief Save file system implementation
 * @author Leandro Bombino Bravo (ImJustFish)
 * @version 0.5.0
 */

#include "fsf.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <cctype>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251 4275 4018 4244 4267)
#endif

namespace fsf {

    namespace {
        char decode_char(char x, short seed) {
            int result = static_cast<int>(x) - 33;
            if(result - seed < 0){
                result = result + (126 + (result - seed));
            }else {
                result = result - seed;
            }
            result += 33;
            return (char)(result);
        }

        char encode_char(char x, short seed) {
            int result = (static_cast<int>(x) + seed)%127;
            if(result < 33)result += 33;
            return (char)(result);
        }

        bool is_valid_path(const std::string& path) {
            if (path.empty()) return false;

            #ifdef _WIN32
            if (path.find_first_of("<>:\"|?*") != std::string::npos) return false;
            #else
            if (path.find_first_of("\0") != std::string::npos) return false;
            #endif

            return true;
        }
    }

    // ==================== Data Implementation ====================

    Data::Data() = default;

    /**
     * @brief Makes a new integer
     * @param index integer's index
     * @param val integer's value
     */
    void Data::put_int(const std::string &index, long long val) {
        if (_exist.find(index) != _exist.end() && _exist[index] != 0) {
            std::cerr << "FSF::ERROR::Object already exists: " << index << std::endl;
            return;
        }
        _exist[index] = 1;
        _lMap[index] = val;
    }

    /**
     * @brief Makes a new float
     * @param index float's index
     * @param val float's value
     */
    void Data::put_float(const std::string &index, float val) {
        if (_exist.find(index) != _exist.end() && _exist[index] != 0) {
            std::cerr << "FSF::ERROR::Object already exists: " << index << std::endl;
            return;
        }
        _exist[index] = 2;
        _fMap[index] = val;
    }

    /**
     * @brief Makes a new string
     * @param index string's index
     * @param val string's value
     */
    void Data::put_str(const std::string &index, const std::string &val) {
        if (_exist.find(index) != _exist.end() && _exist[index] != 0) {
            std::cerr << "FSF::ERROR::Object already exists: " << index << std::endl;
            return;
        }
        _exist[index] = 3;
        _sMap[index] = val;
    }

    /**
     * @brief Makes a new vector of integers
     * @param index vector's index
     * @param val vector's value
     */
    void Data::put_vint(const std::string &index, const std::vector<long long> &val) {
        if (_exist.find(index) != _exist.end() && _exist[index] != 0) {
            std::cerr << "FSF::ERROR::Object already exists: " << index << std::endl;
            return;
        }
        _exist[index] = 4;
        _viMap[index] = val;
    }

    /**
     * @brief Makes a new vector of floats
     * @param index vector's index
     * @param val vector's value
     */
    void Data::put_vfloat(const std::string &index, const std::vector<float> &val) {
        if (_exist.find(index) != _exist.end() && _exist[index] != 0) {
            std::cerr << "FSF::ERROR::Object already exists: " << index << std::endl;
            return;
        }
        _exist[index] = 5;
        _vfMap[index] = val;
    }

    /**
     * @brief Makes a new vector of strings
     * @param index vector's index
     * @param val vector's value
     */
    void Data::put_vstr(const std::string &index, const std::vector<std::string> &val) {
        if (_exist.find(index) != _exist.end() && _exist[index] != 0) {
            std::cerr << "FSF::ERROR::Object already exists: " << index << std::endl;
            return;
        }
        _exist[index] = 6;
        _vsMap[index] = val;
    }

    /**
     * @brief shows the type of a value
     * @param index value's index
     */
    std::string Data::kindof(const std::string &index) const {
        auto it = _exist.find(index);
        if (it == _exist.end() || it->second == 0) {
            return "none";
        }

        switch (it->second) {
            case 1: return "int";
            case 2: return "float";
            case 3: return "string";
            case 4: return "vector int";
            case 5: return "vector float";
            case 6: return "vector string";
            default: return "unknown";
        }
    }

    // ==================== Fsf Implementation ====================

    /**
     * @brief Fsf class builder
     * @param path folder's path
     * @param name object's name
     */
    Fsf::Fsf(const std::string &path, const std::string &name)
    : _path(path), _name(name), _seed(-1) {

        if (!is_valid_path(path)) {
            std::cerr << "FSF::ERROR::Invalid path: " << path << std::endl;
            return;
        }

        // Si ambos parámetros están vacíos, no hacer nada (objeto vacío)
        if (path.empty() && name.empty()) {
            return;
        }

        std::string filename ="../" + _path + _name + ".fsf", code;
        std::ifstream file(filename, std::ios::binary);

        if (file.is_open() && file.good()) {
            char seed_char;
            if (1) {
                getline(file,code);
                _seed = 0;
                for(char c : code){
                    _seed = _seed * 10 + (c - 48);
                }
            }
            file.close();
        }

        _build();
    }

    bool Fsf::build() {
        return _build();
    }

    bool Fsf::_build() {
        if (_path.empty()) {
            std::cerr << "FSF::ERROR::No path specified\n";
            return false;
        }

        if (_name.empty()) {
            std::cerr << "FSF::ERROR::No name specified\n";
            return false;
        }

        if (_seed == -1) {
            std::cerr << "FSF::WARNING::No seed specified - using default seed 0\n";
            _seed = 0;
        }

        std::string filename ="../" + _path + _name + ".fsf";
        std::string cosa;

        std::ifstream test_file(filename);
        if (test_file.good()) {
            _file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
            if (!_file.is_open()) {
                std::cerr << "FSF::ERROR::Cannot open file: " << filename << std::endl;
                return false;
            }

            getline(_file,cosa);

            std::string line;
            std::string index;
            bool end,fp;
            std::string type;
            long long ia,fn;
            float fa;
            std::string sa;
            std::vector<long long> via;
            std::vector<float> fia;
            std::vector<std::string> sia;
            while (std::getline(_file, line)) {
                std::string decoded_line;
                for (char c : line) {
                    decoded_line += decode_char(c, _seed);
                }
                index = "";
                end = 0;
                ia = 0;
                fa = 0;
                sa = "";
                fp = 0;
                fn = 1;
                for(char i:decoded_line){
                    if(!end){
                        if(i=='!'||i=='$'||i=='%'||i=='['){
                            end = 1;
                            type = i;
                            if(type == "["){
                                i++;
                                type += i;
                            }
                        }else{
                            index += i;
                        }
                    }else {
                        if(type[0] == '!'){
                            ia = ia * 10 + (i - 48);
                        }else if(type[0] == '%'){
                            if(!fp){
                                if(i == '.'){
                                    fp = 1;
                                }else{
                                    fa = fa * 10 + (i - 48);
                                }
                            }else {
                                fa += (i - 48) / (10 * fn);
                                fn++;
                            }
                        }else if(type[0] == '$'){
                            sa += i;
                        }else {
                            if(i == '{'){
                                continue;
                            }
                            if(i == ',' || i == '}'){
                                if(type[1]=='!'){
                                    via.push_back(ia);
                                    ia = 0;
                                }else if(type[1]=='%'){
                                    fia.push_back(fa);
                                    fa = 0.0;
                                    fp = 0;
                                    fn = 0;
                                }else if(type[1]=='$'){
                                    sia.push_back(sa);
                                    sa = "";
                                }
                            }if(type[1] == '!'){
                                ia = ia * 10 + (i - 48);
                            }else if(type[1] == '%'){
                                if(!fp){
                                    if(i == '.'){
                                        fp = 1;
                                    }else{
                                        fa = fa * 10 + (i - 48);
                                    }
                                }else {
                                    fa += (i - 48) / (10 * fn);
                                    fn++;
                                }
                            }else if(type[1] == '$'){
                                sa += i;
                            }
                        }
                    }

                }
                if(type[0]=='!'){
                    _data.put_int(index,ia);
                }else if(type[0]=='%'){
                    _data.put_float(index,fa);
                }else if(type[0]=='$'){
                    _data.put_str(index,sa);
                }else{
                    if(type[1]=='!'){
                        _data.put_vint(index,via);
                    }else if(type[1]=='%'){
                        _data.put_vfloat(index,fia);
                    }else if(type[1]=='$'){
                        _data.put_vstr(index,sia);
                    }
                }
            }

            test_file.close();
        } else {
            std::ofstream pfile(filename);
            pfile.close();
            _file.open(filename, std::ios::out | std::ios::binary);
            if (!_file.is_open()) {
                std::cerr << "FSF::ERROR::Cannot create file: " << filename << std::endl;
                return false;
            }

            _file<<std::to_string(_seed);
            _file.close();

            _file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        }

        return true;
    }

    /**
     * @brief sets new values
     * @param path folder's path
     * @param name object's name
     */
    bool Fsf::set(const std::string &path, const std::string &name) {
        if (!is_valid_path(path)) {
            std::cerr << "FSF::ERROR::Invalid path: " << path << std::endl;
            return false;
        }

        if (_file.is_open()) {
            _file.close();
        }

        _path = path;
        _name = name;

        return _build();
    }

    /**
     * @brief sets a seed
     * @param seed seed value
     */
    bool Fsf::set_seed(short seed) {
        if (seed < 0) {
            std::cerr << "FSF::ERROR::Invalid seed (must be >= 0)\n";
            return false;
        }

        if (seed > 126) {
            seed = seed % 127;
            std::cerr << "FSF::WARNING::Seed truncated to: " << seed << std::endl;
        }

        _seed = seed;

        if (_file.is_open()) {
            _file.close();
        }

        _save_to_file();

        return _build();
    }

    /**
     * @brief gets an integer from data
     * @param index integer's index
     */
    long long& Fsf::get_int(const std::string &index) {
        if (_data._exist.find(index) == _data._exist.end() || _data._exist[index] != 1) {
            throw std::runtime_error("FSF::ERROR::Integer not found or wrong type: " + index);
        }
        return _data._lMap[index];
    }

    /**
     * @brief gets a string from data
     * @param index string's index
     */
    std::string& Fsf::get_str(const std::string &index) {
        if (_data._exist.find(index) == _data._exist.end() || _data._exist[index] != 3) {
            throw std::runtime_error("FSF::ERROR::String not found or wrong type: " + index);
        }
        return _data._sMap[index];
    }

    /**
     * @brief gets a float from data
     * @param index float's index
     */
    float& Fsf::get_float(const std::string &index) {
        if (_data._exist.find(index) == _data._exist.end() || _data._exist[index] != 2) {
            throw std::runtime_error("FSF::ERROR::Float not found or wrong type: " + index);
        }
        return _data._fMap[index];
    }

    /**
     * @brief makes a new integer
     * @param index integer's index
     * @param val integer's value
     */
    void Fsf::put_int(const std::string &index, long long val) {
        _data.put_int(index, val);
        _save_to_file();
    }

    /**
     * @brief makes a new string
     * @param index string's index
     * @param val string's value
     */
    void Fsf::put_str(const std::string &index, const std::string &val) {
        _data.put_str(index, val);
        _save_to_file();
    }

    /**
     * @brief makes a new float
     * @param index float's index
     * @param val float's value
     */
    void Fsf::put_float(const std::string &index, float val) {
        _data.put_float(index, val);
        _save_to_file();
    }

    /**
     * @brief saves the file
     */
    void Fsf::_save_to_file() {
        if (!_file.is_open()) {
            std::cerr << "FSF::ERROR::File not open for writing\n";
            return;
        }

        _file.close();
        std::ofstream clear_file("../" + _path + _name + ".fsf", std::ios::binary | std::ios::trunc);
        std::string sseed = std::to_string(_seed);
        clear_file<<sseed<<"\n";
        clear_file.close();

        _file.open("../" + _path + _name + ".fsf", std::ios::out | std::ios::binary | std::ios::app);

        for (const auto& pair : _data._exist) {
            const std::string& index = pair.first;
            short type = pair.second;

            std::string encoded_line;

            for (char c : index) {
                encoded_line += encode_char(c, _seed);
            }

            switch (type) {
                case 1:
                    encoded_line += encode_char('!', _seed);
                    {
                        long long val = _data._lMap.at(index);
                        std::string val_str = std::to_string(val);
                        for (char c : val_str) {
                            encoded_line += encode_char(c, _seed);
                        }
                    }
                    break;

                case 2:
                    encoded_line += encode_char('%', _seed);
                    {
                        float val = _data._fMap.at(index);
                        std::string val_str = std::to_string(val);
                        for (char c : val_str) {
                            encoded_line += encode_char(c, _seed);
                        }
                    }
                    break;

                case 3:
                    encoded_line += encode_char('$', _seed);
                    {
                        std::string val = _data._sMap.at(index);
                        for (char c : val) {
                            encoded_line += encode_char(c, _seed);
                        }
                    }
                    break;
                default:
                    encoded_line += encode_char('!', _seed);
                    switch(type-3){
                        case 1:
                            encoded_line += encode_char('!', _seed);
                            {
                                long long val = _data._lMap.at(index);
                                std::string val_str = std::to_string(val);
                                for (char c : val_str) {
                                    encoded_line += encode_char(c, _seed);
                                }
                            }
                            break;

                        case 2:
                            encoded_line += encode_char('%', _seed);
                            {
                                float val = _data._fMap.at(index);
                                std::string val_str = std::to_string(val);
                                for (char c : val_str) {
                                    encoded_line += encode_char(c, _seed);
                                }
                            }
                            break;

                        case 3:
                            encoded_line += encode_char('$', _seed);
                            {
                                std::string val = _data._sMap.at(index);
                                for (char c : val) {
                                    encoded_line += encode_char(c, _seed);
                                }
                            }
                            break;
                    }
                    break;
            }

            _file << encoded_line << '\n';
        }

        _file.flush();
    }

    /**
     * @brief sees if a value exists
     * @param index value's index
     */
    bool Fsf::contains(const std::string &index) const {
        auto it = _data._exist.find(index);
        return it != _data._exist.end() && it->second != 0;
    }

    /**
     * @brief gets the type of a value
     * @param index value's index
     */
    std::string Fsf::get_type(const std::string &index) const {
        return _data.kindof(index);
    }

    /**
     * @brief erases all in the file
     */
    void Fsf::clear() {
        _data._lMap.clear();
        _data._fMap.clear();
        _data._sMap.clear();
        _data._viMap.clear();
        _data._vfMap.clear();
        _data._vsMap.clear();
        _data._exist.clear();

        if (_file.is_open()) {
            _file.close();
        }

        std::ofstream clear_file("../" + _path + _name + ".fsf", std::ios::binary | std::ios::trunc);
        if (clear_file.is_open()) {
            clear_file<<std::to_string(_seed);
            clear_file.close();
        }

        _file.open("../" + _path + _name + ".fsf", std::ios::in | std::ios::out | std::ios::binary);
    }

    Fsf::~Fsf() {
        if (_file.is_open()) {
            _file.close();
        }
    }

} // namespace fsf

#ifdef _MSC_VER
#pragma warning(pop)
#endif
