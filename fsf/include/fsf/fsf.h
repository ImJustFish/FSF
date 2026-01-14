/**
 * @file fsf.h
 * @brief Save file system library for "Fidel"
 * @author Leandro Bombino Bravo (ImJustFish)
 * @version 0.5.0
 * @license MIT
 */

#pragma once
#ifndef FSF_H
#define FSF_H

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>

namespace fsf {

    #if defined(_WIN32)
    #ifdef FSF_EXPORTS
    #define FSF_API __declspec(dllexport)
    #else
    #define FSF_API __declspec(dllimport)
    #endif
    #else
    #define FSF_API __attribute__((visibility("default")))
    #endif

    struct FSF_API Data {
        std::map<std::string, long long> _lMap;
        std::map<std::string, std::string> _sMap;
        std::map<std::string, float> _fMap;
        std::map<std::string, short> _exist;
        std::map<std::string, std::vector<long long>> _viMap;
        std::map<std::string, std::vector<std::string>> _vsMap;
        std::map<std::string, std::vector<float>> _vfMap;

        Data();

        void put_int(const std::string &index, long long val);
        void put_float(const std::string &index, float val);
        void put_str(const std::string &index, const std::string &val);
        void put_vint(const std::string &index, const std::vector<long long> &val);
        void put_vfloat(const std::string &index, const std::vector<float> &val);
        void put_vstr(const std::string &index, const std::vector<std::string> &val);

        std::string kindof(const std::string &index) const;  // Añadido const
    };

    class FSF_API Fsf {
    private:
        std::string _path, _name;
        short _seed;
        std::fstream _file;
        Data _data;

        bool _build();
        void _save_to_file();

    public:
        // Solo un constructor con parámetros por defecto
        explicit Fsf(const std::string &path = "", const std::string &name = "");
        ~Fsf();

        Fsf(const Fsf&) = delete;
        Fsf& operator=(const Fsf&) = delete;

        Fsf(Fsf&&) = default;
        Fsf& operator=(Fsf&&) = default;

        bool set(const std::string &path, const std::string &name);
        bool set_seed(short seed);
        bool build();

        void put_int(const std::string &index, long long val);
        void put_float(const std::string &index, float val);
        void put_str(const std::string &index, const std::string &val);

        long long& get_int(const std::string &index);
        std::string& get_str(const std::string &index);
        float& get_float(const std::string &index);

        bool contains(const std::string &index) const;
        std::string get_type(const std::string &index) const;
        void clear();
    };

} // namespace fsf

#endif // FSF_H
