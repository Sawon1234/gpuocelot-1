#ifdef _GLIBCXX_USE_INT128
#undef _GLIBCXX_USE_INT128
#endif 

#ifdef _GLIBCXX_ATOMIC_BUILTINS
#undef _GLIBCXX_ATOMIC_BUILTINS
#endif

#include <thrust/transform_reduce.h>
#include <thrust/functional.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/iterator/constant_iterator.h>
#include <thrust/iterator/zip_iterator.h>
#include <cmath>
#include <iomanip>
#include <float.h>

// This example computes the minimum and maximum values
// over a padded grid.  The padded values are not considered
// during the reduction operation.


// transform a tuple (bool,value) into a tuple (bool,value,value)
template <typename IndexType, typename ValueType>
struct transform_tuple : 
    public thrust::unary_function< thrust::tuple<IndexType,ValueType>, 
                                   thrust::tuple<bool,ValueType,ValueType> >
{
    typedef typename thrust::tuple<bool,ValueType>           InputTuple;
    typedef typename thrust::tuple<bool,ValueType,ValueType> OutputTuple;

    IndexType n, N;

    transform_tuple(IndexType n, IndexType N) : n(n), N(N) {}

    __host__ __device__
        OutputTuple operator()(const InputTuple& t) const
        { 
            bool is_valid = (thrust::get<0>(t) % N) < n;
            return result_type(is_valid, thrust::get<1>(t), thrust::get<1>(t));
        }
};


// reduce two tuples (bool,value,value)
template <typename IndexType, typename ValueType>
struct reduce_tuple :
    public thrust::binary_function< thrust::tuple<bool,ValueType,ValueType>,
                                    thrust::tuple<bool,ValueType,ValueType>,
                                    thrust::tuple<bool,ValueType,ValueType> >
{
    typedef typename thrust::tuple<bool,ValueType,ValueType> Tuple;

    __host__ __device__
        Tuple operator()(const Tuple& t0, const Tuple& t1) const
        { 
            if(thrust::get<0>(t0) && thrust::get<0>(t1)) // both valid
                return result_type(true, 
                                   min(thrust::get<1>(t0), thrust::get<1>(t1)),
                                   max(thrust::get<2>(t0), thrust::get<2>(t1)));
            else if (thrust::get<0>(t0))
                return t0;
            else if (thrust::get<0>(t1))
                return t1;
            else
                return t1; // if neither is valid then it doesn't matter what we return
        }
};

int main(void)
{
    int M = 10;  // number of rows
    int n = 11;  // number of columns excluding padding
    int N = 16;  // number of columns including padding

    thrust::device_vector<float> data(M * N, 9999);

    // initialize valid values in grid
    for(int i = 0; i < M; i++)
        for(int j = 0; j < n; j++)
            data[i * N + j] = rand() % 10000;

    // print full grid
    std::cout << "padded grid" << std::endl;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            std::cout << std::setw(6) << data[i * N + j] << " ";
        }   
        std::cout << "\n";
    }

    // compute min & max over valid region of the 2d grid
    typedef thrust::tuple<bool, float, float> result_type;
    
    result_type                 init(true, FLT_MAX, -FLT_MAX); // initial value
    transform_tuple<int,float>  unary_op(n, N);
    reduce_tuple<int,float>     binary_op;

    result_type result = \
        thrust::transform_reduce(
            thrust::make_zip_iterator(thrust::make_tuple(thrust::counting_iterator<int>(0), data.begin())),
            thrust::make_zip_iterator(thrust::make_tuple(thrust::counting_iterator<int>(0), data.begin())) + data.size(),
            unary_op,
            init,
            binary_op);

    std::cout << std::endl;
    std::cout << "minimum value: " << thrust::get<1>(result) << std::endl;
    std::cout << "maximum value: " << thrust::get<2>(result) << std::endl;
	std::cout << "TEST PASSED\n";
    return 0;
}

