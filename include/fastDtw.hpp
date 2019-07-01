#pragma once
#include "common_include.h"
#define MAX_INF 1e+9
#include <unordered_set>
using namespace std;
class fastDtw
{

public:
    fastDtw();
    ~fastDtw();
/*******************************************************************
    '''
    return the approximate distance between 2 time series with O(N)
        time and memory complexity

        Parameters
        ----------
        x : array_like
            input array 1
        y : array_like
            input array 2
        radius : int
            size of neighborhood when expanding the path. A higher value will
            increase the accuracy of the calculation but also increase time
            and memory consumption. A radius equal to the size of x and y will
            yield an exact dynamic time warping calculation.
        dist : function or int
            The method for calculating the distance between x[i] and y[j]. If
            dist is an int of value p > 0, then the p-norm will be used. If
            dist is a function then dist(x[i], y[j]) will be used. If dist is
            None then abs(x[i] - y[j]) will be used.

        Returns
        -------
        distance : float
            the approximate distance between the 2 time series
        path : list
            list of indexes for the inputs x and y

        Examples
        --------
        >>> import numpy as np
        >>> import fastdtw
        >>> x = np.array([1, 2, 3, 4, 5], dtype='float')
        >>> y = np.array([2, 3, 4], dtype='float')
        >>> fastdtw.fastdtw(x, y)
        (2.0, [(0, 0), (1, 0), (2, 1), (3, 2), (4, 2)])
    '''
************************************************************/
    void static fastdtw(vector<float> x, vector<float> y,float *distance,vector<pair_2> &path, FunctionName dist = nullptr, int radius = 1);
    void static s__fastDtw(vector<float> x, vector<float> y,float *distance,vector<pair_2> &path, FunctionName dist = nullptr, int radius = 1);
    float static  s__difference(float a,float b);
    void static reduce_by_half(vector<float> x,vector<float> &x_result);
    void static expand_windows(vector<pair_2> &path,int len_x,int len_y,int radius);
    // void static __difference()

/*    ''' return the distance between 2 time series without approximation

        Parameters
        ----------
        x : array_like
            input array 1
        y : array_like
            input array 2
        dist : function or int
            The method for calculating the distance between x[i] and y[j]. If
            dist is an int of value p > 0, then the p-norm will be used. If
            dist is a function then dist(x[i], y[j]) will be used. If dist is
            None then abs(x[i] - y[j]) will be used.

        Returns
        -------
        distance : float
            the approximate distance between the 2 time series
        path : list
            list of indexes for the inputs x and y

        Examples
        --------
        >>> import numpy as np
        >>> import fastdtw
        >>> x = np.array([1, 2, 3, 4, 5], dtype='float')
        >>> y = np.array([2, 3, 4], dtype='float')
        >>> fastdtw.dtw(x, y)
        (2.0, [(0, 0), (1, 0), (2, 1), (3, 2), (4, 2)])
    '''*/
    void static dtw(vector<float> x, vector<float> y,float *distance,vector<pair_2> &path,FunctionName dist = nullptr);
    void static s__dtw(vector<float> x, vector<float> y,vector<pair_2> &windows,float *distance,vector<pair_2> &path,FunctionName dist =nullptr);
    void static s__prep_input(vector<float> x, vector<float> y, FunctionName dist=nullptr);
private:
};
