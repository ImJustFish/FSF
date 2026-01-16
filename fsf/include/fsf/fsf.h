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

#ifdef _WIN32
    #ifdef FSF_BUILD_DLL
        #define FSF_API __declspec(dllexport)
    #else
        #define FSF_API __declspec(dllimport)
    #endif
#else
    #ifdef FSF_BUILD_DLL
        #define FSF_API __attribute__((visibility("default")))
    #else
        #define FSF_API
    #endif
#endif

namespace fsf {

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
        std::string _path;//File's Path
        short _seed;//Seed
        std::fstream _file;//File
        Data _data;//Data storage

        bool _build();//Builds the file
        void _save_to_file();//Saves the file

    public:
        
        explicit Fsf(const std::string &path = "");
        ~Fsf();

        Fsf(const Fsf&) = delete;
        Fsf& operator=(const Fsf&) = delete;

        Fsf(Fsf&&) = default;
        Fsf& operator=(Fsf&&) = default;

        bool set(const std::string &path);//Sets path
        bool set_seed(short seed);//Sets seed
        bool build();//Builds the file

        void put_int(const std::string &index, long long val);//Makes an integer
        void put_float(const std::string &index, float val);//Makes a float
        void put_str(const std::string &index, const std::string &val);//Makes a string

        long long& get_int(const std::string &index);//Gets an integer
        std::string& get_str(const std::string &index);//Gets a string
        float& get_float(const std::string &index);//Gets a float

        bool contains(const std::string &index) const;//Sees if a variable exists
        std::string get_type(const std::string &index) const;//Gets the type of a variable
        void clear();//Clears the file
    };

} 

#endif 
