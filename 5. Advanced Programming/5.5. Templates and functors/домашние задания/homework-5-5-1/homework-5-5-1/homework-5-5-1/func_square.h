#pragma once
#include <vector>

template <class T>
T func_square(const T &val)
{
    return val * val;
}

template <class T>
std::vector<T> func_square(const std::vector<T> &val)
{
    int sz = val.size();
    std::vector<T> new_vec(sz);
    
    new_vec.assign(val.begin(), val.end());

    for (auto &elem : new_vec)
    {
        elem *= elem;       
    }     
    return new_vec; 
}





